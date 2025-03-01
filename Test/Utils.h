#ifndef  UTILS_H
#define UTILS_H

#include <iostream>
#include <map>

//#include "WebServer.h"
#include "Config.h"
#include "OffsetsStorage.h"
#include "ids.h"

//driver init
extern KeInterface Driver;

extern HWND overlay;

extern const MARGINS margin;

extern LPDIRECT3DDEVICE9 D3D9_DEVICE;
extern LPD3DXFONT TEXT_FONT;

extern DWORD ProcessId;
extern DWORD ClientAddress, EngineAddress;

extern HWND hWnd;
extern HDC hdcScreen;

using namespace std;
using std::cerr;

void init3D(HWND hwnd);
void DrawFilledRect(LONG x, LONG y, LONG h, LONG w, DWORD color);
void DrawString(int x, int y, DWORD color, LPD3DXFONT Font, string str);
void Line(float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color);
void DrawBorderBox(int x, int y, int w, int h, int thickness, DWORD color);
void render();

int GetTextWidth(const char* szText, LPD3DXFONT pFont);
wstring string2wstring(const std::string& str);


void GetLocalPlayerThread();
void BhopThread();
void AntiFlashThread();
void TriggerBotThread();
void RCSThread();
void ReadKeysThread();

struct Vector3 {
	float x, y, z;
};

struct view_matrix_t {
	float matrix[16];
};

struct Vector3 WorldToScreen(const struct Vector3 pos, struct view_matrix_t matrix);

extern struct Storage;
extern struct Player;
extern struct localPlayer;
typedef struct player_info_s {
	int64_t __pad0;

	union {
		int64_t xuid;

		struct {
			int xuidlow;
			int xuidhigh;
		};
	};

	char name[128];
	int userid;
	char guid[33];
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
};

#endif // ! UTILS_H