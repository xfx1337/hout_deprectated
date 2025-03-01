#ifndef  CONFIG_H
#define CONFIG_H

#pragma once
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "winmm.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <dwmapi.h>
#include <string>

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "json.hpp"

struct ARGB {
	int a, r, g, b;
};
ARGB hex2rgb(std::string hex);
D3DCOLOR rgb2d3d(ARGB color);



class Config
{
public:
	static bool espEnable;
	static bool espEnableDRAW;
	static bool espBox;
	static bool espWeapon;
	static bool espArmor;
	static bool espHealth;
	static bool espDefuse;
	static int espThickness;
	static int espHealthSide;
	static int espArmorSide;
	static D3DCOLOR espBoxColor;
	static D3DCOLOR espWeaponColor;
	static D3DCOLOR espArmorColor;
	static D3DCOLOR espHealthColor;
	static D3DCOLOR espDefuseColor;

	static bool bombEnable;
	static int bombX;
	static int bombY;

	static bool bhopEnable;
	static bool bhopMode; // mode like 0 - read only, 1 - with write func

	static bool antiFlash;

	static bool TriggerBotEnabled;
	static bool TriggerBotMode;
	static int TriggerLatency;
	static int TriggerButton;

	static bool RCSEnabled;
	static bool RCSMode;
	static int RCSDelay;
	static float RCSSmooth;

	static bool specListEnable;
	static int specListX;
	static int specListY;
	static D3DCOLOR specListColor;
	static D3DCOLOR specListFrameColor;

	static bool rankRevealer;

	static int width; // game res
	static int height; // game res
	static float winsens; // windows sensitivity [HKEY_CURRENT_USER\Control Panel\Mouse]
	static float gamesens; // game sensitivity
	static bool localPlayerThread;

	static void ExportConfig(std::string path);
	static void ImportConfig(std::string path);
private:
	Config() {}
};


#endif // ! CONFIG_H