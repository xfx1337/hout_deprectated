#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <future>
#include <math.h>
//web server menu

// self made
#include "httpreq.h"
#include "KeInterface.h"
#include "Config.h"


using std::cerr;

// driver init
KeInterface Driver("\\\\.\\kernelhout");

DWORD ProcessId;
DWORD ClientAddress;

HWND hWnd;
HDC hdcScreen;


void DrawMyText(float x, float y, char* buffer, HFONT font, COLORREF color)
{
	SelectObject(hdcScreen, font);
	SetTextColor(hdcScreen, color);
	TextOut(hdcScreen, x, y, buffer, strlen(buffer));
	UpdateWindow(hWnd);
}

struct Vector3 {
	float x, y, z;
};

struct view_matrix_t {
	float matrix[16];
};

void DrawFilledRect(int x, int y, int w, int h, HBRUSH brush)
{
	RECT rect = { x, y, x + w, y + h };
	FillRect(hdcScreen, &rect, brush);
}


void DrawBorderBox(int x, int y, int w, int h, int thickness, HBRUSH brush)
{

	DrawFilledRect(x, y, w, thickness, brush);

	DrawFilledRect(x, y, thickness, h, brush);

	DrawFilledRect((x + w), y, thickness, h, brush);

	DrawFilledRect(x, y + h, w + thickness, thickness, brush);
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



void Bhop(std::future<void> futureObj) {
	DWORD dwLocalPlayer = Driver.GetOffset("dwLocalPlayer");
	DWORD LocalPlayer;
	Driver.ReadVirtualMemory(ProcessId, ClientAddress + dwLocalPlayer, sizeof(ULONG), &LocalPlayer);
	DWORD Flags = Driver.GetOffset("m_fFlags");
	DWORD dwForceJump = Driver.GetOffset("dwForceJump");
	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) {
		while (Config::bhopEnable == true) {
			DWORD InGround;
			Driver.ReadVirtualMemory(ProcessId, LocalPlayer + Flags, sizeof(ULONG), &InGround);
			if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && (InGround & 1 == 1))
			{
				Driver.WriteVirtualMemory(ProcessId, ClientAddress + dwForceJump, 0x5, 8);
				Sleep(1);
				Driver.WriteVirtualMemory(ProcessId, ClientAddress + dwForceJump, 0x4, 8);
			}
		}
	}
}

void Esp(std::future<void> futureObj) {
	DWORD dwEntityList = Driver.GetOffset("dwEntityList");
	DWORD dwViewMatrix = Driver.GetOffset("dwViewMatrix");
	DWORD m_vecOrigin = Driver.GetOffset("m_vecOrigin");
	DWORD m_iHealth = Driver.GetOffset("m_iHealth");
	view_matrix_t vm;
	DWORD pEnt;
	Vector3 pos;
	Vector3 head;
	Vector3 screenpos;
	Vector3 screenhead;
	float height;
	float width;
	DWORD health;
	int healthBar;
	int armorbar;
	RECT healthBarPos;
	RECT armorBarPos;
	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) {
		HBRUSH healthbrush = CreateSolidBrush(Config::espHealthColor);
		HBRUSH boxbrush = CreateSolidBrush(Config::espBoxColor);
		while (Config::espEnable == true) {
			Driver.ReadVirtualMemory(ProcessId, ClientAddress + dwViewMatrix, sizeof(view_matrix_t), &vm);
			for (int i = 1; i < 64; i++) {
				Driver.ReadVirtualMemory(ProcessId, ClientAddress + dwEntityList + (i * 0x10), sizeof(DWORD), &pEnt);
				if (pEnt == 0) {
					break;
				}

				Driver.ReadVirtualMemory(ProcessId, pEnt + m_vecOrigin, sizeof(Vector3), &pos);
				Driver.ReadVirtualMemory(ProcessId, pEnt + m_iHealth, sizeof(DWORD), &health);
				//printf("%i\n", (int)health);
				if ((int)health == 0) {
					continue;
				}
				head.x = pos.x; head.y = pos.y; head.z = pos.z + 72.f;
				screenpos = WorldToScreen(pos, vm);
				screenhead = WorldToScreen(head, vm);
				height = screenhead.y - screenpos.y;
				width = height / 2.4f;

				if (screenpos.z >= 0.01f && screenpos.x > 0 && screenpos.y > 0) {
					//std::cout << screenhead.x << " " << screenhead.y << " " << ((screenhead.y - screenpos.y) / 2.4f) << " " << (screenhead.y - screenpos.y) << std::endl;
					//DrawBorderBox(screenpos.x-(width/2), screenpos.y, width, height, 5);
					//DrawString(screenpos.x, screenpos.y, TextCOLOR, "Player");
					//DrawFilledRect(screenpos.x - (width / 2), screenpos.y, width, 5);
					if (Config::espName) {
						DrawMyText(screenpos.x + (width / 2), screenpos.y, "[Test]", Config::espNameFont, Config::espNameColor);
					}
					if (Config::espBox) {
						DrawBorderBox(screenpos.x - width / 2, screenpos.y, width, height, Config::espThickness, boxbrush);
					}

					if (Config::espHealth) {

						if (Config::espHealthSide == 0) {
							healthBar = height * ((int)health * 0.01f);
							healthBarPos = { (long)(screenpos.x + width / 2 - 6), (long)(screenhead.y - ((screenhead.y - screenpos.y) - healthBar)), (long)(screenpos.x + width / 2 - 11), (long)screenpos.y };
						}
						else if (Config::espHealthSide == 1) {
							healthBar = width * ((int)health * 0.01f);
							healthBarPos = { (long)(screenpos.x - width / 2), (long)(screenhead.y - 5), (long)(screenhead.x - width / 2 + healthBar), (long)(screenhead.y - 10) };
						}
						else if (Config::espHealthSide == 2) {
							healthBar = height * ((int)health * 0.01f);
							healthBarPos = { (long)(screenpos.x - width / 2 + 6), (long)(screenhead.y - ((screenhead.y - screenpos.y) - healthBar)), (long)(screenpos.x - width / 2 + 11), (long)screenpos.y };
						}
						else {
							healthBar = width * ((int)health * 0.01f);
							healthBarPos = { (long)screenpos.x, (long)screenhead.y - 5, (long)screenhead.x + healthBar, (long)screenhead.y - 10 };
						}
						FillRect(hdcScreen, &healthBarPos, healthbrush);
						//healthBarPos.top += 5;
						//FillRect(hdcScreen, &healthBarPos, Config::blackBrush);
					}
				}
			}
			UpdateWindow(hWnd);
			//ReleaseDC(hWnd, hdcScreen);
			//DeleteObject(hdcScreen);
		}
	}
}


int main()
{
	hWnd = CreateWindowEx(0,
		"WindowClass",
		"overlay",
		WS_EX_TOPMOST | WS_POPUP,
		0, 0,
		Config::width, Config::height,
		NULL,
		NULL,
		0,
		NULL);
	hdcScreen = GetDC(hWnd);
	std::cout << "[hout] Initalizing Driver" << std::endl;
	ProcessId = Driver.GetTargetPid();
	ClientAddress = Driver.GetClientModule();
	std::cout << "[hout] Loading Offsets" << std::endl;

	http::Request request{ "http://houtlogs.herokuapp.com/HoutStarted" };
	request.send("GET");

	Driver.ParseOffsets();

	std::cout << "[hout] Found csgo Process Id: " << ProcessId << std::endl;
	std::cout << "[hout] Found client.dll ClientBase: 0x" << std::uppercase
		<< std::hex << ClientAddress << std::endl;

	//bhop
	std::promise<void> bhopExit;
	std::future<void> BhopObj = bhopExit.get_future();
	std::thread bhop(&Bhop, std::move(BhopObj));
	// Esp
	std::promise<void> EspExit;
	std::future<void> EspObj = EspExit.get_future();
	std::thread wh(&Esp, std::move(EspObj));




	return 0;
}

