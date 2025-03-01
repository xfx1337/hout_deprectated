#include "ids.h"

const char* weaponStr[56] = {
	"deagle",
	"duals",
	"fiveseven",
	"glock",
	"ak47",
	"aug",
	"awp",
	"famas",
	"g3sg1",
	"galil-ar",
	"m249",
	"m4a4",
	"mac10",
	"p90",
	"ump45",
	"xm1014",
	"bizon",
	"mag7",
	"negev",
	"sawedoff",
	"tec9",
	"taser",
	"p2000",
	"mp7",
	"mp9",
	"nova",
	"p250",
	"scar20",
	"sg553",
	"ssg08",
	"knife",
	"flashbang",
	"hegrenade",
	"smokegrenade",
	"molotov",
	"decoy",
	"incgrenade",
	"c4",
	"m4a1-s",
	"usp-s",
	"cz75",
	"revolver"
};

std::string weaponToStr(short int wpn) {
	switch (wpn) {
	case WEAPON_DEAGLE:
		return weaponStr[0];
	case WEAPON_ELITE:
		return weaponStr[1];
	case WEAPON_FIVESEVEN:
		return weaponStr[2];
	case WEAPON_GLOCK:
		return weaponStr[3];
	case WEAPON_AK47:
		return weaponStr[4];
	case WEAPON_AUG:
		return weaponStr[5];
	case WEAPON_AWP:
		return weaponStr[6];
	case WEAPON_FAMAS:
		return weaponStr[7];
	case WEAPON_G3SG1:
		return weaponStr[8];
	case WEAPON_GALILAR:
		return weaponStr[9];
	case WEAPON_M249:
		return weaponStr[10];
	case WEAPON_M4A1:
		return weaponStr[11];
	case WEAPON_MAC10:
		return weaponStr[12];
	case WEAPON_P90:
		return weaponStr[13];
	case WEAPON_UMP45:
		return weaponStr[14];
	case WEAPON_XM1014:
		return weaponStr[15];
	case WEAPON_BIZON:
		return weaponStr[16];
	case WEAPON_MAG7:
		return weaponStr[17];
	case WEAPON_NEGEV:
		return weaponStr[18];
	case WEAPON_SAWEDOFF:
		return weaponStr[19];
	case WEAPON_TEC9:
		return weaponStr[20];
	case WEAPON_TASER:
		return weaponStr[21];
	case WEAPON_HKP2000:
		return weaponStr[22];
	case WEAPON_MP7:
		return weaponStr[23];
	case WEAPON_MP9:
		return weaponStr[24];
	case WEAPON_NOVA:
		return weaponStr[25];
	case WEAPON_P250:
		return weaponStr[26];
	case WEAPON_SCAR20:
		return weaponStr[27];
	case WEAPON_SG553:
		return weaponStr[28];
	case WEAPON_SSG08:
		return weaponStr[29];
	case WEAPON_KNIFE: case WEAPON_KNIFE_T: case WEAPON_KNIFE_BAYONET: case WEAPON_KNIFE_FLIP: case WEAPON_KNIFE_GUT: case WEAPON_KNIFE_KARAMBIT: case WEAPON_KNIFE_M9_BAYONET: case WEAPON_KNIFE_TACTICAL: case WEAPON_KNIFE_FALCHION: case WEAPON_KNIFE_SURVIVAL_BOWIE: case WEAPON_KNIFE_BUTTERFLY: case WEAPON_KNIFE_PUSH:
		return weaponStr[30];
	case WEAPON_FLASHBANG:
		return weaponStr[31];
	case WEAPON_HEGRENADE:
		return weaponStr[32];
	case WEAPON_SMOKEGRENADE:
		return weaponStr[33];
	case WEAPON_MOLOTOV:
		return weaponStr[34];
	case WEAPON_DECOY:
		return weaponStr[35];
	case WEAPON_INCGRENADE:
		return weaponStr[36];
	case WEAPON_C4:
		return weaponStr[37];
	case WEAPON_M4A1_SILENCER:
		return weaponStr[38];
	case WEAPON_USP_SILENCER:
		return weaponStr[39];
	case WEAPON_CZ75A:
		return weaponStr[40];
	case WEAPON_REVOLVER:
		return weaponStr[41];
	default:
		return std::to_string(wpn);
	}
}

const char* Ranks[] =
{
		"Unranked",

		"Silver I",
		"Silver II",
		"Silver III",
		"Silver IV",
		"Silver Elite",
		"Silver Elite Master",

		"Gold Nova I",
		"Gold Nova II",
		"Gold Nova III",
		"Gold Nova Master",
		"Master Guardian I",
		"Master Guardian II",

		"Master Guardian Elite",
		"Distinguished Master Guardian",
		"Legendary Eagle",
		"Legendary Eagle Master",
		"Supreme Master First Class",
		"The Global Elite"
};