#include "Config.h"

using namespace nlohmann;

bool Config::espEnable = true;
bool Config::espEnableDRAW = true;
bool Config::espBox = true;
bool Config::espWeapon = true;
bool Config::espArmor = true;
bool Config::espHealth = true;
bool Config::espDefuse = true;
int Config::espThickness = 3;
int Config::espHealthSide = 2;
int Config::espArmorSide = 2;
D3DCOLOR Config::espBoxColor = D3DCOLOR_ARGB(255, 255, 0, 0);
D3DCOLOR Config::espWeaponColor = D3DCOLOR_ARGB(255, 255, 0, 0);
D3DCOLOR Config::espArmorColor = D3DCOLOR_ARGB(255, 0, 0, 255);
D3DCOLOR Config::espHealthColor = D3DCOLOR_ARGB(255, 0, 255, 0);
D3DCOLOR Config::espDefuseColor = D3DCOLOR_ARGB(255, 255, 0, 0);

bool Config::bombEnable = true;
int Config::bombX = 1850;
int Config::bombY = 1000;

bool Config::bhopEnable = true;
bool Config::bhopMode = false; // mode like 0 - read only, 1 - with write func

bool Config::antiFlash = true;

bool Config::TriggerBotEnabled = true;
bool Config::TriggerBotMode = 0;
int Config::TriggerLatency = 0;
int Config::TriggerButton = VK_XBUTTON2;

bool Config::RCSEnabled = true;
bool Config::RCSMode = true;
int Config::RCSDelay = 0;
float Config::RCSSmooth = 0.1;

bool Config::specListEnable = true;
int Config::specListX = 1560;
int Config::specListY = 60;
D3DCOLOR Config::specListColor = D3DCOLOR_ARGB(255, 255, 0, 0);
D3DCOLOR Config::specListFrameColor = D3DCOLOR_ARGB(255, 0, 0, 255);

bool Config::rankRevealer = true;

bool Config::localPlayerThread = true;

int Config::width = 1920;
int Config::height = 1080;
float Config::winsens = 1;
float Config::gamesens = 4.8;

// shit
std::vector<std::string> SplitWithCharacters(const std::string& str, int splitLength) {
	int NumSubstrings = str.length() / splitLength;
	std::vector<std::string> ret;

	for (int i = 0; i < NumSubstrings; i++) {
		ret.push_back(str.substr(i * splitLength, splitLength));
	}

	// If there are leftover characters, create a shorter item at the end.
	if (str.length() % splitLength != 0) {
		ret.push_back(str.substr(splitLength * NumSubstrings));
	}


	return ret;
}

ARGB hex2rgb(std::string hex) {
	ARGB color;
	if (hex.at(0) == '#') {
		hex.erase(0, 1);
	}

	while (hex.length() != 6) {
		hex += "0";
	}

	std::vector<std::string> colori = SplitWithCharacters(hex, 2);
	color.a = 255;
	color.r = stoi(colori[0], nullptr, 16);
	color.g = stoi(colori[1], nullptr, 16);
	color.b = stoi(colori[2], nullptr, 16);

	return color;
}

D3DCOLOR rgb2d3d(ARGB color) {
	return D3DCOLOR_ARGB(color.a, color.r, color.g, color.b);
}

void Config::ExportConfig(std::string path) {

}

void Config::ImportConfig(std::string path) {
	std::ifstream file(path);
	json j;
	file >> j;

	Config::espEnableDRAW = j["espEnableDRAW"];
	Config::espBox = j["espBox"];
	Config::espWeapon = j["espWeapon"];
	Config::espArmor = j["espArmor"];
	Config::espHealth = j["espHealth"];
	Config::espDefuse = j["espDefuse"];
	Config::espThickness = j["espThickness"];
	Config::espHealthSide = j["espHealthSide"];
	Config::espArmorSide = j["espArmorSide"];
	Config::espBoxColor = rgb2d3d(hex2rgb(j["espBoxColor"]));
	Config::espWeaponColor = rgb2d3d(hex2rgb(j["espWeaponColor"]));
	Config::espArmorColor = rgb2d3d(hex2rgb(j["espArmorColor"]));
	Config::espHealthColor = rgb2d3d(hex2rgb(j["espHealthColor"]));
	Config::espDefuseColor = rgb2d3d(hex2rgb(j["espDefuseColor"]));
	Config::bhopEnable = j["bhopEnable"];
	Config::bhopMode = j["bhopMode"];
	Config::antiFlash = j["antiFlash"];
	Config::TriggerBotEnabled = j["TriggerBotEnabled"];
	Config::TriggerBotMode = j["TriggerBotMode"];
	Config::TriggerLatency = j["TriggerLatency"];
	Config::TriggerButton = j["TriggerButton"];
	Config::RCSEnabled = j["RCSEnabled"];
	Config::RCSMode = j["RCSMode"];
	Config::RCSDelay = j["RCSDelay"];
	Config::specListEnable = j["specListEnable"];
	Config::specListX = j["specListX"];
	Config::specListY = j["specListY"];
	Config::specListColor = rgb2d3d(hex2rgb(j["specListColor"]));
	Config::specListFrameColor = rgb2d3d(hex2rgb(j["specListFrameColor"]));
	Config::width = j["width"];
	Config::height = j["height"];
	Config::winsens = j["winsens"];
	Config::gamesens = j["gamesens"];
}