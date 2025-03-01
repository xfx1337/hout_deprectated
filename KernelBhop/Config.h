#pragma once

#include <string>
#include <Windows.h>


class Config
{
public:
	static bool espEnable;
	static bool espBox;
	static bool espName;
	static bool espArmor;
	static bool espHealth;
	static bool espUnderLine;
	static bool espWeapon;
	static bool espSnap;
	static bool espGlow;
	static int espThickness;
	static int espHealthSide;
	static int espArmorSide;
	static COLORREF espBoxColor;
	static COLORREF espNameColor;
	static COLORREF espNameBackgroundColor;
	static COLORREF espArmorColor;
	static COLORREF espHealthColor;
	static COLORREF espUnderLineColor;
	static COLORREF espWeaponColor;
	static COLORREF espSnapColor;
	static COLORREF espGlowColor;
	static HFONT espNameFont;

	static bool bhopEnable;
	static bool bhopMode; // mode like 0 - read only, 1 - with write func
	static bool bhoprealistic; // enable realistic bhop
	static int bhopCoef; // auto bhop realistic coeficent

	static bool antiFlash;

	static int width; // game res
	static int height; // game res
	static HFONT defFont;
	static HBRUSH defBrush;
	static HBRUSH blackBrush;

	static void ExportConfig(std::string path);
	static void ImportConfig(std::string path);
private:
	Config() {}
};

