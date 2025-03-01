#include "Utils.h"

KeInterface Driver("\\\\.\\kernelhout");
LPDIRECT3DDEVICE9 D3D9_DEVICE;
DWORD ProcessId = 0;
DWORD ClientAddress = 0;
DWORD EngineAddress = 0;

HWND overlay;

const MARGINS margin = { 0, 0, Config::width, Config::height };
LPD3DXFONT TEXT_FONT;

INT Fps = 0;
FLOAT LastTickCount = 0.0f;
FLOAT CurrentTickCount;
CHAR FrameRate[50] = "";

struct Player {
	DWORD pEnt;
	Vector3 pos;
	Vector3 head;
	DWORD health;
	DWORD armor;
	DWORD team;
	bool dormant;

	DWORD getWeapEnt;
	DWORD getWeapHandle;
	DWORD getCurrentWeapon;
	short int weapon;

	int defusing;
	DWORD spec;

	int wins;
	int rank;
	player_info_s pInfo;
};

struct Storage {
	view_matrix_t vm;
	Player entities[64];
	DWORD ClientState;
	float height;
	float width;
	Vector3 screenpos;
	Vector3 screenhead;
	int healthBar;
	int armorBar;
	RECT healthBarPos;
	RECT armorBarPos;

	DWORD playerInfo;
	DWORD playerRes;
	DWORD playerResource;
	int speclistNum;
} storage;

struct localPlayer {
	DWORD old_pEnt;
	DWORD pEnt;
	DWORD team;
	DWORD health;
	DWORD armor;
	int weapon;
	DWORD getWeapEnt;
	DWORD tmp;
	int index;
} LocalPlayer;

void init3D(HWND hwnd) {
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = Config::width;
	d3dpp.BackBufferHeight = Config::height;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3D9_DEVICE);
	D3DXCreateFont(D3D9_DEVICE, 16, 0, FW_NORMAL, 1, 0, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Unicode MS", &TEXT_FONT);
}



struct Vector3 WorldToScreen(const struct Vector3 pos, struct view_matrix_t matrix) {
	struct Vector3 out;
	float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
	float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
	out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];

	_x *= 1.f / out.z;
	_y *= 1.f / out.z;

	out.x = Config::width * 0.5f;
	out.y = Config::height * 0.5f;

	out.x += 0.5f * _x * Config::width + 0.5f;
	out.y -= 0.5f * _y * Config::height + 0.5f;

	return out;
}


void DrawFilledRect(LONG x, LONG y, LONG h, LONG w, DWORD color) {
	D3DRECT rect = { x, y, w, h };
	D3D9_DEVICE->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawString(int x, int y, DWORD color, LPD3DXFONT Font, string str) {
	RECT fontPos = { x, y, x + 120, y + 16 };
	std::wstring widestr = string2wstring(str);
	Font->DrawTextW(nullptr, widestr.c_str(), -1, &fontPos, DT_NOCLIP, color);
}

void Line(float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color) {
	ID3DXLine* line;
	D3DXCreateLine(D3D9_DEVICE, &line);

	D3DXVECTOR2 linePos[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
	line->SetWidth(width);
	if (antialias)
		line->SetAntialias(antialias);
	line->Begin();
	line->Draw(linePos, 2, color);
	line->End();
	line->Release();
}

void DrawBorderBox(int x, int y, int w, int h, int thickness, DWORD color) {
	Line(x, y, x + w, y, thickness, false, color);
	Line(x, y + h, x + w, y + h, thickness, false, color);
	Line(x, y, x, y + h, thickness, false, color);
	Line(x + w, y, x + w, y + h, thickness, false, color);
}

void render() {
	D3D9_DEVICE->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1, 0);
	D3D9_DEVICE->BeginScene();
	DrawString(0, 50, D3DCOLOR_ARGB(255, 255, 0, 0), TEXT_FONT, FrameRate);
	DrawString(0, 0, D3DCOLOR_ARGB(255, 255, 0, 0), TEXT_FONT, "[hout beta]");

	if (Config::espEnable) {
		Driver.ReadVirtualMemory(ProcessId, ClientAddress + Offsets::dwViewMatrix, sizeof(view_matrix_t), &storage.vm);
		for (int i = 0; i < 64; i++) {
			Driver.ReadVirtualMemory(ProcessId, ClientAddress + Offsets::dwEntityList + (i * 0x10), sizeof(DWORD), &storage.entities[i].pEnt);
			if (storage.entities[i].pEnt == 0) {
				continue;
			}

			Driver.ReadVirtualMemory(ProcessId, storage.entities[i].pEnt + Offsets::m_vecOrigin, sizeof(Vector3), &storage.entities[i].pos);
			Driver.ReadVirtualMemory(ProcessId, storage.entities[i].pEnt + Offsets::m_iHealth, sizeof(DWORD), &storage.entities[i].health);
			Driver.ReadVirtualMemory(ProcessId, storage.entities[i].pEnt + Offsets::m_iTeamNum, sizeof(DWORD), &storage.entities[i].team);
			Driver.ReadVirtualMemory(ProcessId, storage.entities[i].dormant + Offsets::m_bDormant, sizeof(bool), &storage.entities[i].dormant);
			if (storage.entities[i].dormant == 1) {
				continue;
			}

			if (Config::espDefuse) {
				Driver.ReadVirtualMemory(ProcessId, storage.entities[i].pEnt + Offsets::m_bIsDefusing, sizeof(int), &storage.entities[i].defusing);
			}

			if (Config::espWeapon) {
				Driver.ReadVirtualMemory(ProcessId, storage.entities[i].pEnt + Offsets::m_hActiveWeapon, sizeof(DWORD), &storage.entities[i].getWeapHandle);
				storage.entities[i].getWeapEnt = storage.entities[i].getWeapHandle & 0xFFF;
				Driver.ReadVirtualMemory(ProcessId, ClientAddress + Offsets::dwEntityList + (storage.entities[i].getWeapEnt - 1) * 0x10, sizeof(DWORD), &storage.entities[i].getCurrentWeapon);
				Driver.ReadVirtualMemory(ProcessId, storage.entities[i].getCurrentWeapon + Offsets::m_iItemDefinitionIndex, sizeof(short int), &storage.entities[i].weapon);
			}
			if ((int)storage.entities[i].health == 0) {
				continue;
			}
			if ((int)LocalPlayer.team == (int)storage.entities[i].team) {
				continue;
			}
			if (Config::espEnableDRAW) {
				storage.entities[i].head.x = storage.entities[i].pos.x; storage.entities[i].head.y = storage.entities[i].pos.y; storage.entities[i].head.z = storage.entities[i].pos.z + 72.f;
				storage.screenpos = WorldToScreen(storage.entities[i].pos, storage.vm);
				storage.screenhead = WorldToScreen(storage.entities[i].head, storage.vm);
				storage.height = storage.screenhead.y - storage.screenpos.y;
				storage.width = storage.height / 2.4f;

				if (storage.screenpos.z >= 0.01f && storage.screenpos.x > 0 && storage.screenpos.y > 0) {
					if (Config::espBox) {
						DrawBorderBox(storage.screenpos.x - storage.width / 2, storage.screenpos.y, storage.width, storage.height, Config::espThickness, Config::espBoxColor);
					}

					if (Config::espHealth) {
						if (Config::espHealthSide == 0) {
							storage.healthBar = storage.height * ((int)storage.entities[i].health * 0.01f);
							storage.healthBarPos = { (long)(storage.screenpos.x + storage.width / 2 - 6), (long)(storage.screenhead.y - ((storage.screenhead.y - storage.screenpos.y) - storage.healthBar)), (long)(storage.screenpos.x + storage.width / 2 - 6), (long)storage.screenpos.y };
						}
						else if (Config::espHealthSide == 1) {
							storage.healthBar = storage.width * ((int)storage.entities[i].health * 0.01f);
							storage.healthBarPos = { (long)(storage.screenhead.x + storage.width / 2), (long)storage.screenhead.y - 5, (long)(storage.screenhead.x + storage.width / 2 - storage.healthBar), (long)storage.screenhead.y - 5 };
						}
						else if (Config::espHealthSide == 2) {
							storage.healthBar = storage.height * ((int)storage.entities[i].health * 0.01f);
							storage.healthBarPos = { (long)(storage.screenpos.x - storage.width / 2 + 6), (long)(storage.screenhead.y - ((storage.screenhead.y - storage.screenpos.y) - storage.healthBar)), (long)(storage.screenpos.x - storage.width / 2 + 6), (long)storage.screenpos.y };
						}
						else {
							storage.healthBar = storage.width * ((int)storage.entities[i].health * 0.01f);
							storage.healthBarPos = { (long)(storage.screenhead.x + storage.width / 2), (long)storage.screenpos.y + 5, (long)(storage.screenhead.x + storage.width / 2 - storage.healthBar), (long)storage.screenpos.y + 5 };
						}
						Line(storage.healthBarPos.left, storage.healthBarPos.bottom, storage.healthBarPos.right, storage.healthBarPos.top, Config::espThickness, false, Config::espHealthColor);
					}
					if (Config::espArmor) {
						Driver.ReadVirtualMemory(ProcessId, storage.entities[i].pEnt + Offsets::m_ArmorValue, sizeof(DWORD), &storage.entities[i].armor);
						if (Config::espArmorSide == 0) {
							storage.armorBar = storage.height * ((int)storage.entities[i].armor * 0.01f);
							storage.armorBarPos = { (long)(storage.screenpos.x + storage.width / 2 - 11), (long)(storage.screenhead.y - ((storage.screenhead.y - storage.screenpos.y) - storage.armorBar)), (long)(storage.screenpos.x + storage.width / 2 - 11), (long)storage.screenpos.y };
						}
						else if (Config::espArmorSide == 1) {
							storage.armorBar = storage.width * ((int)storage.entities[i].armor * 0.01f);
							storage.armorBarPos = { (long)(storage.screenhead.x + storage.width / 2), (long)storage.screenhead.y - 11, (long)(storage.screenhead.x + storage.width / 2 - storage.armorBar), (long)storage.screenhead.y - 11 };
						}
						else if (Config::espArmorSide == 2) {
							storage.armorBar = storage.height * ((int)storage.entities[i].armor * 0.01f);
							storage.armorBarPos = { (long)(storage.screenpos.x - storage.width / 2 + 11), (long)(storage.screenhead.y - ((storage.screenhead.y - storage.screenpos.y) - storage.armorBar)), (long)(storage.screenpos.x - storage.width / 2 + 11), (long)storage.screenpos.y };
						}
						else {
							storage.armorBar = storage.width * ((int)storage.entities[i].armor * 0.01f);
							storage.armorBarPos = { (long)(storage.screenhead.x + storage.width / 2), (long)storage.screenpos.y + 11, (long)(storage.screenhead.x + storage.width / 2 - storage.armorBar), (long)storage.screenpos.y + 11 };
						}
						Line(storage.armorBarPos.left, storage.armorBarPos.bottom, storage.armorBarPos.right, storage.armorBarPos.top, Config::espThickness, false, Config::espArmorColor);
					}
					if (Config::espWeapon) {
						DrawString(storage.screenpos.x - GetTextWidth((weaponToStr(storage.entities[i].weapon)).c_str(), TEXT_FONT) / 2, storage.screenpos.y, Config::espWeaponColor, TEXT_FONT, weaponToStr(storage.entities[i].weapon));
					}
					if (Config::espDefuse) {
						if (storage.entities[i].defusing != 0) {
							DrawString(storage.screenpos.x - GetTextWidth("Defusing", TEXT_FONT) / 2, storage.screenhead.y - 16, Config::espDefuseColor, TEXT_FONT, "Defusing");
						}
					}
				}
			}
		}
	}

	if (Config::specListEnable) {
		storage.speclistNum = 0;

		Driver.ReadVirtualMemory(ProcessId, storage.ClientState + Offsets::dwClientState_PlayerInfo, sizeof(DWORD), &storage.playerInfo); // IDK how it all work
		Driver.ReadVirtualMemory(ProcessId, storage.playerInfo + 0x40, sizeof(DWORD), &storage.playerInfo);
		Driver.ReadVirtualMemory(ProcessId, storage.playerInfo + 0x0C, sizeof(DWORD), &storage.playerInfo);
		for (int i = 0; i < 64; i++) {
			if (storage.entities[i].pEnt == 0) {
				continue;
			}
			if (storage.entities[i].pEnt == LocalPlayer.pEnt) {
				continue;
			}
			Driver.ReadVirtualMemory(ProcessId, storage.entities[i].pEnt + Offsets::m_hObserverTarget, sizeof(int), &storage.entities[i].spec);
			storage.entities[i].spec = storage.entities[i].spec & 0xFFF;
			if ((int)storage.entities[i].spec == (LocalPlayer.index + 1)) {
				storage.speclistNum += 1;
				Driver.ReadVirtualMemory(ProcessId, storage.playerInfo + 0x28 + i * 0x34, sizeof(DWORD), &storage.playerRes);
				Driver.ReadVirtualMemory(ProcessId, storage.playerRes, sizeof(player_info_s), &storage.entities[i].pInfo);
				DrawString(Config::specListX + 20, Config::specListY + storage.speclistNum * 20 + 10, Config::specListColor, TEXT_FONT, storage.entities[i].pInfo.name);
			}
		}
		DrawString(Config::specListX + 150 - GetTextWidth("Spectator List", TEXT_FONT) / 2, Config::specListY + 5, Config::specListColor, TEXT_FONT, "Spectator List");
		if (storage.speclistNum == 0) {
			DrawBorderBox(Config::specListX, Config::specListY, 300, 50, 2, Config::specListFrameColor);
		}
		else {
			DrawBorderBox(Config::specListX, Config::specListY, 300, storage.speclistNum * 20 + 35, 2, Config::specListFrameColor);
		}
	}

	CurrentTickCount = clock() * 0.001f;
	Fps++;

	if ((CurrentTickCount - LastTickCount) > 1.0f)
	{
		LastTickCount = CurrentTickCount;
		sprintf(FrameRate, "[ FPS: %d ]", Fps);
		Fps = 0;
	}
	Sleep(1);

	D3D9_DEVICE->EndScene();
	D3D9_DEVICE->Present(nullptr, nullptr, nullptr, nullptr);
}

int GetTextWidth(const char* szText, LPD3DXFONT pFont) {
	RECT rcRect = { 0,0,0,0 };
	if (pFont)
	{
		// calculate required rect
		pFont->DrawText(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT,
			D3DCOLOR_XRGB(0, 0, 0));
	}

	// return width
	return rcRect.right - rcRect.left;
}

wstring string2wstring(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

void GetLocalPlayerThread() {
	DWORD getWeapHandle;
	DWORD getCurrentWeapon;
	Driver.ReadVirtualMemory(ProcessId, EngineAddress + Offsets::dwClientState, sizeof(DWORD), &storage.ClientState);
	while (true) {
		if (Config::localPlayerThread) {
			Driver.ReadVirtualMemory(ProcessId, ClientAddress + Offsets::dwLocalPlayer, sizeof(DWORD), &LocalPlayer.pEnt);
			if (LocalPlayer.pEnt != LocalPlayer.old_pEnt) {
				Driver.ReadVirtualMemory(ProcessId, storage.ClientState + Offsets::dwClientState_GetLocalPlayer, sizeof(int), &LocalPlayer.index);
				LocalPlayer.old_pEnt = LocalPlayer.pEnt;
			}
			Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_iTeamNum, sizeof(DWORD), &LocalPlayer.team);
			Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_hActiveWeapon, sizeof(DWORD), &getWeapHandle);
			LocalPlayer.getWeapEnt = getWeapHandle & 0xFFF;
			Driver.ReadVirtualMemory(ProcessId, ClientAddress + Offsets::dwEntityList + (LocalPlayer.getWeapEnt - 1) * 0x10, sizeof(DWORD), &getCurrentWeapon);
			Driver.ReadVirtualMemory(ProcessId, getCurrentWeapon + Offsets::m_iItemDefinitionIndex, sizeof(int), &LocalPlayer.weapon);
			Sleep(1);
		}
	}
}

void BhopThread() {
	while (true) {
		if (Config::bhopEnable) {
			if (Config::bhopMode == 1) {
				DWORD InGround;
				Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_fFlags, sizeof(ULONG), &InGround);
				if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && (InGround & 1 == 1))
				{
					Driver.WriteVirtualMemory(ProcessId, ClientAddress + Offsets::dwForceJump, 0x5, 8);
					Sleep(1);
					Driver.WriteVirtualMemory(ProcessId, ClientAddress + Offsets::dwForceJump, 0x4, 8);
				}
			}
			else {
				DWORD InGround;
				Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_fFlags, sizeof(ULONG), &InGround);
				if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && (InGround & 1 == 1))
				{
					keybd_event(MapVirtualKey(0x20, 0), 0x39, 1, 0);
					keybd_event(MapVirtualKey(0x20, 0), 0x39, 2, 0);
					Sleep(1);
				}
			}
		}
	}
}

void AntiFlashThread() {
	float flash;
	while (true) {
		if (Config::antiFlash) {
			Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_flFlashMaxAlpha, sizeof(float), &flash);
			if (flash > 0.0f) {
				Driver.WriteVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_flFlashMaxAlpha, 0, sizeof(flash));
			}
		}
	}
}

int weaponAuto(DWORD id) {
	int idx = (int)id;
	if (idx == 1 || idx == 3 || idx == 4 || idx == 9 || idx == 11 || idx == 25 || idx == 27 || idx == 29 || idx == 30 || idx == 31 || idx == 32 || idx == 35 || idx == 36 || idx == 38 || idx == 40 || idx == 61 || idx == 64) {
		return 0; // non auto guns
	}
	if ((idx > 41 && idx < 60) || (idx > 500 && idx < 520)) {
		return -1; // someting like knifes
	}
	else {
		return 1; // auto
	}
}

void TriggerBotThread() {
	int crosshairId;
	int hold = -1;
	bool detected = 0;
	while (true) {
		if (Config::TriggerBotEnabled) {
			if (GetAsyncKeyState(Config::TriggerButton)) {
				Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_iCrosshairId, sizeof(int), &crosshairId);
				if (crosshairId != 0 && crosshairId < 64) {
					if (storage.entities[crosshairId - 1].team != LocalPlayer.team && (int)storage.entities[crosshairId - 1].health > 0) {
						if (detected == 0) {
							detected = 1;
						}
						if (weaponAuto(LocalPlayer.weapon) == -1) {
							hold = -1;
							continue;
						}
						else if (weaponAuto(LocalPlayer.weapon) == 0) {
							hold = -1;
							if (detected == 0) {
								Sleep(Config::TriggerLatency);
								detected = 1;
							}
							if (Config::TriggerBotMode == 1) {
								Driver.WriteVirtualMemory(ProcessId, ClientAddress + Offsets::dwForceAttack, 5, sizeof(int));
								Sleep(1);
								Driver.WriteVirtualMemory(ProcessId, ClientAddress + Offsets::dwForceAttack, 4, sizeof(int));
							}
							else {
								mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								Sleep(100);
								mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
						}
						else {
							if (hold == 0 || hold == -1) {
								hold = 1;
								Sleep(Config::TriggerLatency);
								if (Config::TriggerBotMode == 1) {
									Driver.WriteVirtualMemory(ProcessId, ClientAddress + Offsets::dwForceAttack, 5, sizeof(int));
								}
								else {
									mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								}
							}
						}
					}
					else {
						if (hold == 1 && storage.entities[crosshairId - 1].team == LocalPlayer.team) {
							detected = 0;
							hold = -1;
							if (Config::TriggerBotMode == 1) {
								Driver.WriteVirtualMemory(ProcessId, ClientAddress + Offsets::dwForceAttack, 4, sizeof(int));
							}
							else {
								mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
						}
					}
				}
				else {
					if (hold == 1) {
						detected = 0;
						hold = -1;
						if (Config::TriggerBotMode == 1) {
							Driver.WriteVirtualMemory(ProcessId, ClientAddress + Offsets::dwForceAttack, 4, sizeof(int));
						}
						else {
							mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						}
					}
				}
			}
		}
		Sleep(1);
	}
}

void RCSThread() {
	Vector3 viewAngles;
	Vector3 tempAngles;
	Vector3 punchAngle;
	Vector3 oldPunch = {0, 0, 0};
	Vector3 newPunch = { 0, 0, 0 };
	int shotsFired;
	while (true) {
		if (Config::RCSEnabled) {
			Driver.ReadVirtualMemory(ProcessId, storage.ClientState + Offsets::dwClientState_ViewAngles, sizeof(Vector3), &viewAngles);
			Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_iShotsFired, sizeof(int), &shotsFired);
			Driver.ReadVirtualMemory(ProcessId, LocalPlayer.pEnt + Offsets::m_aimPunchAngle, sizeof(Vector3), &punchAngle);
			if (shotsFired > 1 && GetAsyncKeyState(VK_LBUTTON)) {
				if (Config::RCSSmooth != 0) {
					tempAngles.x = (oldPunch.x - (punchAngle.x * 2));
					tempAngles.y = (oldPunch.y - (punchAngle.y * 2));
					tempAngles.x = viewAngles.x + tempAngles.x;
					tempAngles.y = viewAngles.y + tempAngles.y;
				}
				else {
					tempAngles.x = (viewAngles.x + oldPunch.x) - (punchAngle.x * 2);
					tempAngles.y = (viewAngles.y + oldPunch.y) - (punchAngle.y * 2);
				}
				while (tempAngles.y > 180) { tempAngles.y -= 360; }
				while (tempAngles.y < -180) { tempAngles.y += 360; }
				if (tempAngles.x > 89.0f) { tempAngles.x = 89.0f; }
				if (tempAngles.x < -89.0f) { tempAngles.x = -89.0f; }
				//tempAngles.x = tempAngles.x / Config::RCSSmooth;
				//tempAngles.y = tempAngles.y / Config::RCSSmooth;
				if (Config::RCSMode == true) {
					Driver.WriteVirtualMemoryPTR(ProcessId, storage.ClientState + Offsets::dwClientState_ViewAngles, &tempAngles, sizeof(Vector3));
					oldPunch.x = punchAngle.x * 2;
					oldPunch.y = punchAngle.y * 2;
				}
				else {
					if (Config::RCSSmooth == 0) {
						newPunch.x = ((punchAngle.x - oldPunch.x) * 2.0f) / (Config::gamesens * 0.022 * Config::winsens) * (-1);
						newPunch.y = ((punchAngle.y - oldPunch.y) * 2.0f) / (Config::gamesens * 0.022 * Config::winsens);
					}
					else {
						newPunch.x = ((punchAngle.x - oldPunch.x) * 2.0f) / (Config::gamesens * 0.022 * Config::winsens) * (-1);
						newPunch.y = ((punchAngle.y - oldPunch.y) * 2.0f) / (Config::gamesens * 0.022 * Config::winsens);
					}
					mouse_event(MOUSEEVENTF_MOVE, newPunch.y, newPunch.x, 0, 0); // in game x and y are swapped
					oldPunch.x = punchAngle.x;
					oldPunch.y = punchAngle.y;
				}
			}
			else {
				oldPunch.x = 0; // reset old punch
				oldPunch.y = 0;
			}
		}
		Sleep(Config::RCSDelay);
	}
}

void ReadKeysThread() {
	/*while (true) {
		if (GetAsyncKeyState(VK_TAB)) {
			Config::rankRevealer = 1;
		}
		else {
			Config::rankRevealer = 0;
		}
	}*/
}