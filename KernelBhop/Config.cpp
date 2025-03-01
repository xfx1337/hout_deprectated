#include "Config.h"

bool Config::espEnable = true;
bool Config::espBox = true;
bool Config::espName = true;
bool Config::espArmor = false;
bool Config::espHealth = true;
bool Config::espUnderLine = false;
bool Config::espWeapon = false;
bool Config::espSnap = false;
bool Config::espGlow = false;
int Config::espThickness = 5;
int Config::espHealthSide = 2;
int Config::espArmorSide = 2;
COLORREF Config::espBoxColor = RGB(0, 0, 255);
COLORREF Config::espNameColor = RGB(255, 0, 0);
COLORREF Config::espNameBackgroundColor = RGB(255, 255, 255);
COLORREF Config::espArmorColor = RGB(255, 255, 255);
COLORREF Config::espHealthColor = RGB(0, 255, 0);
COLORREF Config::espUnderLineColor = RGB(255, 255, 255);
COLORREF Config::espWeaponColor = RGB(255, 255, 255);
COLORREF Config::espSnapColor = RGB(255, 255, 255);
COLORREF Config::espGlowColor = RGB(255, 255, 255);
HFONT Config::espNameFont = CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, "SYSTEM_FIXED_FONT");

bool Config::bhopEnable = false;
bool Config::bhopMode = false; // mode like 0 - read only, 1 - with write func
bool Config::bhoprealistic = false; // enable realistic bhop
int Config::bhopCoef = 0; // auto bhop realistic coeficent

bool Config::antiFlash = false;

int Config::width = 1920;
int Config::height = 1080;

HFONT Config::defFont = CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, "SYSTEM_FIXED_FONT");
HBRUSH Config::defBrush = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH Config::blackBrush = CreateSolidBrush(RGB(0, 0, 0));


void Config::ExportConfig(std::string path) {

}

void Config::ImportConfig(std::string path) {

}