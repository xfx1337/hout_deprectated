#include "OffsetsStorage.h"

DWORD Offsets::anim_overlays = 0;
DWORD Offsets::clientstate_choked_commands = 0;
DWORD Offsets::clientstate_delta_ticks = 0;
DWORD Offsets::clientstate_last_outgoing_command = 0;
DWORD Offsets::clientstate_net_channel = 0;
DWORD Offsets::convar_name_hash_table = 0;
DWORD Offsets::dwClientState = 0;
DWORD Offsets::dwClientState_GetLocalPlayer = 0;
DWORD Offsets::dwClientState_IsHLTV = 0;
DWORD Offsets::dwClientState_Map = 0;
DWORD Offsets::dwClientState_MapDirectory = 0;
DWORD Offsets::dwClientState_MaxPlayer = 0;
DWORD Offsets::dwClientState_PlayerInfo = 0;
DWORD Offsets::dwClientState_State = 0;
DWORD Offsets::dwClientState_ViewAngles = 0;
DWORD Offsets::dwEntityList = 0;
DWORD Offsets::dwForceAttack = 0;
DWORD Offsets::dwForceAttack2 = 0;
DWORD Offsets::dwForceBackward = 0;
DWORD Offsets::dwForceForward = 0;
DWORD Offsets::dwForceJump = 0;
DWORD Offsets::dwForceLeft = 0;
DWORD Offsets::dwForceRight = 0;
DWORD Offsets::dwGameDir = 0;
DWORD Offsets::dwGameRulesProxy = 0;
DWORD Offsets::dwGetAllClasses = 0;
DWORD Offsets::dwGlobalVars = 0;
DWORD Offsets::dwGlowObjectManager = 0;
DWORD Offsets::dwInput = 0;
DWORD Offsets::dwInterfaceLinkList = 0;
DWORD Offsets::dwLocalPlayer = 0;
DWORD Offsets::dwMouseEnable = 0;
DWORD Offsets::dwMouseEnablePtr = 0;
DWORD Offsets::dwPlayerResource = 0;
DWORD Offsets::dwRadarBase = 0;
DWORD Offsets::dwSensitivity = 0;
DWORD Offsets::dwSensitivityPtr = 0;
DWORD Offsets::dwSetClanTag = 0;
DWORD Offsets::dwViewMatrix = 0;
DWORD Offsets::dwWeaponTable = 0;
DWORD Offsets::dwWeaponTableIndex = 0;
DWORD Offsets::dwYawPtr = 0;
DWORD Offsets::dwZoomSensitivityRatioPtr = 0;
DWORD Offsets::dwbSendPackets = 0;
DWORD Offsets::dwppDirect3DDevice9 = 0;
DWORD Offsets::find_hud_element = 0;
DWORD Offsets::force_update_spectator_glow = 0;
DWORD Offsets::interface_engine_cvar = 0;
DWORD Offsets::is_c4_owner = 0;
DWORD Offsets::m_bDormant = 0;
DWORD Offsets::m_flSpawnTime = 0;
DWORD Offsets::m_pStudioHdr = 0;
DWORD Offsets::m_pitchClassPtr = 0;
DWORD Offsets::m_yawClassPtr = 0;
DWORD Offsets::model_ambient_min = 0;
DWORD Offsets::set_abs_angles = 0;
DWORD Offsets::set_abs_origin = 0;
DWORD Offsets::cs_gamerules_data = 0;
DWORD Offsets::m_ArmorValue = 0;
DWORD Offsets::m_Collision = 0;
DWORD Offsets::m_CollisionGroup = 0;
DWORD Offsets::m_Local = 0;
DWORD Offsets::m_MoveType = 0;
DWORD Offsets::m_OriginalOwnerXuidHigh = 0;
DWORD Offsets::m_OriginalOwnerXuidLow = 0;
DWORD Offsets::m_SurvivalGameRuleDecisionTypes = 0;
DWORD Offsets::m_SurvivalRules = 0;
DWORD Offsets::m_aimPunchAngle = 0;
DWORD Offsets::m_aimPunchAngleVel = 0;
DWORD Offsets::m_angEyeAnglesX = 0;
DWORD Offsets::m_angEyeAnglesY = 0;
DWORD Offsets::m_bBombDefused = 0;
DWORD Offsets::m_bBombPlanted = 0;
DWORD Offsets::m_bBombTicking = 0;
DWORD Offsets::m_bFreezePeriod = 0;
DWORD Offsets::m_bGunGameImmunity = 0;
DWORD Offsets::m_bHasDefuser = 0;
DWORD Offsets::m_bHasHelmet = 0;
DWORD Offsets::m_bInReload = 0;
DWORD Offsets::m_bIsDefusing = 0;
DWORD Offsets::m_bIsQueuedMatchmaking = 0;
DWORD Offsets::m_bIsScoped = 0;
DWORD Offsets::m_bIsValveDS = 0;
DWORD Offsets::m_bSpotted = 0;
DWORD Offsets::m_bSpottedByMask = 0;
DWORD Offsets::m_bStartedArming = 0;
DWORD Offsets::m_bUseCustomAutoExposureMax = 0;
DWORD Offsets::m_bUseCustomAutoExposureMin = 0;
DWORD Offsets::m_bUseCustomBloomScale = 0;
DWORD Offsets::m_clrRender = 0;
DWORD Offsets::m_dwBoneMatrix = 0;
DWORD Offsets::m_fAccuracyPenalty = 0;
DWORD Offsets::m_fFlags = 0;
DWORD Offsets::m_flC4Blow = 0;
DWORD Offsets::m_flCustomAutoExposureMax = 0;
DWORD Offsets::m_flCustomAutoExposureMin = 0;
DWORD Offsets::m_flCustomBloomScale = 0;
DWORD Offsets::m_flDefuseCountDown = 0;
DWORD Offsets::m_flDefuseLength = 0;
DWORD Offsets::m_flFallbackWear = 0;
DWORD Offsets::m_flFlashDuration = 0;
DWORD Offsets::m_flFlashMaxAlpha = 0;
DWORD Offsets::m_flLastBoneSetupTime = 0;
DWORD Offsets::m_flLowerBodyYawTarget = 0;
DWORD Offsets::m_flNextAttack = 0;
DWORD Offsets::m_flNextPrimaryAttack = 0;
DWORD Offsets::m_flSimulationTime = 0;
DWORD Offsets::m_flTimerLength = 0;
DWORD Offsets::m_hActiveWeapon = 0;
DWORD Offsets::m_hBombDefuser = 0;
DWORD Offsets::m_hMyWeapons = 0;
DWORD Offsets::m_hObserverTarget = 0;
DWORD Offsets::m_hOwner = 0;
DWORD Offsets::m_hOwnerEntity = 0;
DWORD Offsets::m_hViewModel = 0;
DWORD Offsets::m_iAccountID = 0;
DWORD Offsets::m_iClip1 = 0;
DWORD Offsets::m_iCompetitiveRanking = 0;
DWORD Offsets::m_iCompetitiveWins = 0;
DWORD Offsets::m_iCrosshairId = 0;
DWORD Offsets::m_iDefaultFOV = 0;
DWORD Offsets::m_iEntityQuality = 0;
DWORD Offsets::m_iFOVStart = 0;
DWORD Offsets::m_iGlowIndex = 0;
DWORD Offsets::m_iHealth = 0;
DWORD Offsets::m_iItemDefinitionIndex = 0;
DWORD Offsets::m_iItemIDHigh = 0;
DWORD Offsets::m_iMostRecentModelBoneCounter = 0;
DWORD Offsets::m_iObserverMode = 0;
DWORD Offsets::m_iShotsFired = 0;
DWORD Offsets::m_iState = 0;
DWORD Offsets::m_iTeamNum = 0;
DWORD Offsets::m_lifeState = 0;
DWORD Offsets::m_nBombSite = 0;
DWORD Offsets::m_nFallbackPaintKit = 0;
DWORD Offsets::m_nFallbackSeed = 0;
DWORD Offsets::m_nFallbackStatTrak = 0;
DWORD Offsets::m_nForceBone = 0;
DWORD Offsets::m_nTickBase = 0;
DWORD Offsets::m_nViewModelIndex = 0;
DWORD Offsets::m_rgflCoordinateFrame = 0;
DWORD Offsets::m_szCustomName = 0;
DWORD Offsets::m_szLastPlaceName = 0;
DWORD Offsets::m_thirdPersonViewAngles = 0;
DWORD Offsets::m_vecOrigin = 0;
DWORD Offsets::m_vecVelocity = 0;
DWORD Offsets::m_vecViewOffset = 0;
DWORD Offsets::m_viewPunchAngle = 0;
DWORD Offsets::m_zoomLevel = 0;

void Offsets::LoadOffsets(KeInterface Driver) {
	anim_overlays = Driver.GetOffset("anim_overlays");
	clientstate_choked_commands = Driver.GetOffset("clientstate_choked_commands");
	clientstate_delta_ticks = Driver.GetOffset("clientstate_delta_ticks");
	clientstate_last_outgoing_command = Driver.GetOffset("clientstate_last_outgoing_command");
	clientstate_net_channel = Driver.GetOffset("clientstate_net_channel");
	convar_name_hash_table = Driver.GetOffset("convar_name_hash_table");
	dwClientState = Driver.GetOffset("dwClientState");
	dwClientState_GetLocalPlayer = Driver.GetOffset("dwClientState_GetLocalPlayer");
	dwClientState_IsHLTV = Driver.GetOffset("dwClientState_IsHLTV");
	dwClientState_Map = Driver.GetOffset("dwClientState_Map");
	dwClientState_MapDirectory = Driver.GetOffset("dwClientState_MapDirectory");
	dwClientState_MaxPlayer = Driver.GetOffset("dwClientState_MaxPlayer");
	dwClientState_PlayerInfo = Driver.GetOffset("dwClientState_PlayerInfo");
	dwClientState_State = Driver.GetOffset("dwClientState_State");
	dwClientState_ViewAngles = Driver.GetOffset("dwClientState_ViewAngles");
	dwEntityList = Driver.GetOffset("dwEntityList");
	dwForceAttack = Driver.GetOffset("dwForceAttack");
	dwForceAttack2 = Driver.GetOffset("dwForceAttack2");
	dwForceBackward = Driver.GetOffset("dwForceBackward");
	dwForceForward = Driver.GetOffset("dwForceForward");
	dwForceJump = Driver.GetOffset("dwForceJump");
	dwForceLeft = Driver.GetOffset("dwForceLeft");
	dwForceRight = Driver.GetOffset("dwForceRight");
	dwGameDir = Driver.GetOffset("dwGameDir");
	dwGameRulesProxy = Driver.GetOffset("dwGameRulesProxy");
	dwGetAllClasses = Driver.GetOffset("dwGetAllClasses");
	dwGlobalVars = Driver.GetOffset("dwGlobalVars");
	dwGlowObjectManager = Driver.GetOffset("dwGlowObjectManager");
	dwInput = Driver.GetOffset("dwInput");
	dwInterfaceLinkList = Driver.GetOffset("dwInterfaceLinkList");
	dwLocalPlayer = Driver.GetOffset("dwLocalPlayer");
	dwMouseEnable = Driver.GetOffset("dwMouseEnable");
	dwMouseEnablePtr = Driver.GetOffset("dwMouseEnablePtr");
	dwPlayerResource = Driver.GetOffset("dwPlayerResource");
	dwRadarBase = Driver.GetOffset("dwRadarBase");
	dwSensitivity = Driver.GetOffset("dwSensitivity");
	dwSensitivityPtr = Driver.GetOffset("dwSensitivityPtr");
	dwSetClanTag = Driver.GetOffset("dwSetClanTag");
	dwViewMatrix = Driver.GetOffset("dwViewMatrix");
	dwWeaponTable = Driver.GetOffset("dwWeaponTable");
	dwWeaponTableIndex = Driver.GetOffset("dwWeaponTableIndex");
	dwYawPtr = Driver.GetOffset("dwYawPtr");
	dwZoomSensitivityRatioPtr = Driver.GetOffset("dwZoomSensitivityRatioPtr");
	dwbSendPackets = Driver.GetOffset("dwbSendPackets");
	dwppDirect3DDevice9 = Driver.GetOffset("dwppDirect3DDevice9");
	find_hud_element = Driver.GetOffset("find_hud_element");
	force_update_spectator_glow = Driver.GetOffset("force_update_spectator_glow");
	interface_engine_cvar = Driver.GetOffset("interface_engine_cvar");
	is_c4_owner = Driver.GetOffset("is_c4_owner");
	m_bDormant = Driver.GetOffset("m_bDormant");
	m_flSpawnTime = Driver.GetOffset("m_flSpawnTime");
	m_pStudioHdr = Driver.GetOffset("m_pStudioHdr");
	m_pitchClassPtr = Driver.GetOffset("m_pitchClassPtr");
	m_yawClassPtr = Driver.GetOffset("m_yawClassPtr");
	model_ambient_min = Driver.GetOffset("model_ambient_min");
	set_abs_angles = Driver.GetOffset("set_abs_angles");
	set_abs_origin = Driver.GetOffset("set_abs_origin");
	cs_gamerules_data = Driver.GetOffset("cs_gamerules_data");
	m_ArmorValue = Driver.GetOffset("m_ArmorValue");
	m_Collision = Driver.GetOffset("m_Collision");
	m_CollisionGroup = Driver.GetOffset("m_CollisionGroup");
	m_Local = Driver.GetOffset("m_Local");
	m_MoveType = Driver.GetOffset("m_MoveType");
	m_OriginalOwnerXuidHigh = Driver.GetOffset("m_OriginalOwnerXuidHigh");
	m_OriginalOwnerXuidLow = Driver.GetOffset("m_OriginalOwnerXuidLow");
	m_SurvivalGameRuleDecisionTypes = Driver.GetOffset("m_SurvivalGameRuleDecisionTypes");
	m_SurvivalRules = Driver.GetOffset("m_SurvivalRules");
	m_aimPunchAngle = Driver.GetOffset("m_aimPunchAngle");
	m_aimPunchAngleVel = Driver.GetOffset("m_aimPunchAngleVel");
	m_angEyeAnglesX = Driver.GetOffset("m_angEyeAnglesX");
	m_angEyeAnglesY = Driver.GetOffset("m_angEyeAnglesY");
	m_bBombDefused = Driver.GetOffset("m_bBombDefused");
	m_bBombPlanted = Driver.GetOffset("m_bBombPlanted");
	m_bBombTicking = Driver.GetOffset("m_bBombTicking");
	m_bFreezePeriod = Driver.GetOffset("m_bFreezePeriod");
	m_bGunGameImmunity = Driver.GetOffset("m_bGunGameImmunity");
	m_bHasDefuser = Driver.GetOffset("m_bHasDefuser");
	m_bHasHelmet = Driver.GetOffset("m_bHasHelmet");
	m_bInReload = Driver.GetOffset("m_bInReload");
	m_bIsDefusing = Driver.GetOffset("m_bIsDefusing");
	m_bIsQueuedMatchmaking = Driver.GetOffset("m_bIsQueuedMatchmaking");
	m_bIsScoped = Driver.GetOffset("m_bIsScoped");
	m_bIsValveDS = Driver.GetOffset("m_bIsValveDS");
	m_bSpotted = Driver.GetOffset("m_bSpotted");
	m_bSpottedByMask = Driver.GetOffset("m_bSpottedByMask");
	m_bStartedArming = Driver.GetOffset("m_bStartedArming");
	m_bUseCustomAutoExposureMax = Driver.GetOffset("m_bUseCustomAutoExposureMax");
	m_bUseCustomAutoExposureMin = Driver.GetOffset("m_bUseCustomAutoExposureMin");
	m_bUseCustomBloomScale = Driver.GetOffset("m_bUseCustomBloomScale");
	m_clrRender = Driver.GetOffset("m_clrRender");
	m_dwBoneMatrix = Driver.GetOffset("m_dwBoneMatrix");
	m_fAccuracyPenalty = Driver.GetOffset("m_fAccuracyPenalty");
	m_fFlags = Driver.GetOffset("m_fFlags");
	m_flC4Blow = Driver.GetOffset("m_flC4Blow");
	m_flCustomAutoExposureMax = Driver.GetOffset("m_flCustomAutoExposureMax");
	m_flCustomAutoExposureMin = Driver.GetOffset("m_flCustomAutoExposureMin");
	m_flCustomBloomScale = Driver.GetOffset("m_flCustomBloomScale");
	m_flDefuseCountDown = Driver.GetOffset("m_flDefuseCountDown");
	m_flDefuseLength = Driver.GetOffset("m_flDefuseLength");
	m_flFallbackWear = Driver.GetOffset("m_flFallbackWear");
	m_flFlashDuration = Driver.GetOffset("m_flFlashDuration");
	m_flFlashMaxAlpha = Driver.GetOffset("m_flFlashMaxAlpha");
	m_flLastBoneSetupTime = Driver.GetOffset("m_flLastBoneSetupTime");
	m_flLowerBodyYawTarget = Driver.GetOffset("m_flLowerBodyYawTarget");
	m_flNextAttack = Driver.GetOffset("m_flNextAttack");
	m_flNextPrimaryAttack = Driver.GetOffset("m_flNextPrimaryAttack");
	m_flSimulationTime = Driver.GetOffset("m_flSimulationTime");
	m_flTimerLength = Driver.GetOffset("m_flTimerLength");
	m_hActiveWeapon = Driver.GetOffset("m_hActiveWeapon");
	m_hBombDefuser = Driver.GetOffset("m_hBombDefuser");
	m_hMyWeapons = Driver.GetOffset("m_hMyWeapons");
	m_hObserverTarget = Driver.GetOffset("m_hObserverTarget");
	m_hOwner = Driver.GetOffset("m_hOwner");
	m_hOwnerEntity = Driver.GetOffset("m_hOwnerEntity");
	m_hViewModel = Driver.GetOffset("m_hViewModel");
	m_iAccountID = Driver.GetOffset("m_iAccountID");
	m_iClip1 = Driver.GetOffset("m_iClip1");
	m_iCompetitiveRanking = Driver.GetOffset("m_iCompetitiveRanking");
	m_iCompetitiveWins = Driver.GetOffset("m_iCompetitiveWins");
	m_iCrosshairId = Driver.GetOffset("m_iCrosshairId");
	m_iDefaultFOV = Driver.GetOffset("m_iDefaultFOV");
	m_iEntityQuality = Driver.GetOffset("m_iEntityQuality");
	m_iFOVStart = Driver.GetOffset("m_iFOVStart");
	m_iGlowIndex = Driver.GetOffset("m_iGlowIndex");
	m_iHealth = Driver.GetOffset("m_iHealth");
	m_iItemDefinitionIndex = Driver.GetOffset("m_iItemDefinitionIndex");
	m_iItemIDHigh = Driver.GetOffset("m_iItemIDHigh");
	m_iMostRecentModelBoneCounter = Driver.GetOffset("m_iMostRecentModelBoneCounter");
	m_iObserverMode = Driver.GetOffset("m_iObserverMode");
	m_iShotsFired = Driver.GetOffset("m_iShotsFired");
	m_iState = Driver.GetOffset("m_iState");
	m_iTeamNum = Driver.GetOffset("m_iTeamNum");
	m_lifeState = Driver.GetOffset("m_lifeState");
	m_nBombSite = Driver.GetOffset("m_nBombSite");
	m_nFallbackPaintKit = Driver.GetOffset("m_nFallbackPaintKit");
	m_nFallbackSeed = Driver.GetOffset("m_nFallbackSeed");
	m_nFallbackStatTrak = Driver.GetOffset("m_nFallbackStatTrak");
	m_nForceBone = Driver.GetOffset("m_nForceBone");
	m_nTickBase = Driver.GetOffset("m_nTickBase");
	m_nViewModelIndex = Driver.GetOffset("m_nViewModelIndex");
	m_rgflCoordinateFrame = Driver.GetOffset("m_rgflCoordinateFrame");
	m_szCustomName = Driver.GetOffset("m_szCustomName");
	m_szLastPlaceName = Driver.GetOffset("m_szLastPlaceName");
	m_thirdPersonViewAngles = Driver.GetOffset("m_thirdPersonViewAngles");
	m_vecOrigin = Driver.GetOffset("m_vecOrigin");
	m_vecVelocity = Driver.GetOffset("m_vecVelocity");
	m_vecViewOffset = Driver.GetOffset("m_vecViewOffset");
	m_viewPunchAngle = Driver.GetOffset("m_viewPunchAngle");
	m_zoomLevel = Driver.GetOffset("m_zoomLevel");
}