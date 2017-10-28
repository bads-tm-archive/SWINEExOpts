// S.W.I.N.E. ExOptions indev2 (or easy and light ExOptions base for anyone to use)
// Coding: bads.tm, steakhal
// Injector: thelink2012,
// IniReader: ThirteenAG,
// Progress: --Get it compillable--. compillable new version.. Then make sure it works in game. Then finish it!
// Testing: bads.tm (in linux, console Thing does not work in wine)
// If you're contributor or outsourced programmer, credit yourself here is recommended!
// Remove this line and few ones bellow when it's quite well finished (maybe)
// Stuff to do:
// Camera Max Zoom In/Out = done | Camera Rotation and angle up-down = yes! | Cam Map out of bound limit = yes! | Selectable Thing = yes!
// Unitslots and Upgrade Slot = NO! | Mod Loader = NO! | Add Money current+1000,000 = NO!
// Non CE : Takeover++ , Try finding out debug developer mode, Try adding new menu button (not replacing existing ones)
// Need to do: Clean up maybe, have a working INI reader.... Mod loader - If there is 1 in config file, it will load mod(s) from mod/*.ini and maybe Change
// way like when game wants to load units/....*.4d it will load instead from mod/units/.....*.4d this also could work with music swap....
// Not sure if it's possible, but replacing-breaking gamespy stuff to some new one would be cool, or simply chaning network/internet/multiplayer things....

#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"

#include <iostream>  // only for debugging - part by steakhal

DWORD WINAPI Thing(LPVOID); // nlgzrgn's usual thing

//this part is by steakhal
using namespace injector;

template <std::size_t Level>
static DWORD FindDynAddr(DWORD baseAddr, const DWORD (&offsets)[Level]) {
	for (int i = 0; i < Level; ++i)
		baseAddr = ReadMemory<DWORD>(baseAddr, false) + offsets[i];
	return baseAddr;
}

/* main codebase */
//this part is by steakhal, with GetAsyncKeyState by bads
if (GetAsyncKeyState(49) & 1) {

static void setMaxZoomIn() {
	const DWORD base  = 0x0057B270;
	const DWORD off[] = { 0x88, 0x404, 0x3c, 0x0, 0x1c };

	const DWORD dyn = FindDynAddr(base, off);
	const float value = ReadMemory<float>(dyn, false);

	std::cout << std::hex << dyn << " :: max zoom in old: "
		<< std::dec << value << std::flush;

	WriteMemory<float>(dyn, 1.0, true /*unpotect*/);
	std::cout << ", new value: " << 1 << std::endl;
}}
static void readMoney() {
	const DWORD moneyBaseAddr = 0x0057B270;
	const DWORD moneyOffsets[] = { 0x24 };

	const DWORD dynMoneyAddr = FindDynAddr(moneyBaseAddr, moneyOffsets);
	const int value = ReadMemory<int>(dynMoneyAddr, false);

	std::cout << std::hex << dynMoneyAddr  << " :: money: "
		<< std::dec << value << std::endl;
}
//this part is by bads.tm

static void setMaxZoomOut() {
	const DWORD camZoomOutBaseAddr  = 0x0057B270;
	const DWORD camZoomOutOffsets[] = { 0x20, 0x88 };

	const DWORD dynZoomOutCombo = FindDynAddr(camZoomOutBaseAddr, camZoomOutOffsets);

	WriteMemory<float>(dynZoomOutCombo, 1.0, true /*unpotect*/);
}
static void setMaxAnglUp() {
	const DWORD camAnglUpBaseAddr  = 0x0057B270;
	const DWORD camAnglUpOffsets[] = { 0x14, 0x0, 0x44, 0x404, 0x88 };

	const DWORD dynAnglUpCombo = FindDynAddr(camAnglUpBaseAddr, camAnglUpOffsets);

	WriteMemory<float>(dynAnglUpCombo, 1.0, true /*unpotect*/);
}
static void setMaxAnglDown() {
	const DWORD camAnglDownBaseAddr  = 0x0057B270;
	const DWORD camAnglDownOffsets[] = { 0x18, 0x0, 0x3C, 0x404, 0x88 };

	const DWORD dynAnglDownCombo = FindDynAddr(camAnglDownBaseAddr, camAnglDownOffsets);

	WriteMemory<float>(dynAnglDownCombo, 1.0, true /*unpotect*/);
}
static void setMaxLimit() {
	const DWORD camMaxLimitBaseAddr  = 0x0057B270;
	const DWORD camMaxLimitOffsets[] = { 0x18, 0x0, 0x3C, 0x404, 0x88 };

	const DWORD dynMaxLimitCombo = FindDynAddr(camMaxLimitBaseAddr, camMaxLimitOffsets);

	WriteMemory<float>(dynMaxLimitCombo, 1.0, true /*unpotect*/);
}
static void setSelectable() {
	WriteMemory<string>(0x00542A9C, 11, true /*unpotect*/);
}
/* TAKEOVER!! */
DWORD StringReplacementCodeCaveExit = 0x15dfff; // Bless hex editor (https://cdn.discordapp.com/attachments/291939894652043274/373737654073950210/unknown.png)
char* StringBuffer1 = "S.W.I.N.E. %s v%d.%d-%d ^With Extra Options - © 2018 Extra Options Team. ^No rights reserved.";
DWORD _A7EBC389_New = (DWORD)StringBuffer1; //00535FEC?
void __declspec(naked) StringReplacementCodeCave()
{
	_asm
	{
			mov ecx, dword ptr ds : [ebx + eax * 0x08]

			cmp nlgzrgnTakeOver, 0x00
			je continuee
			cmp ecx, 0xA7EBC389
			je ReplaceCopyrightString
			// cmp ecx, AnotherStringHashHere
			// je ReplaceAnotherString
			jmp continuee

		ReplaceCopyrightString :
			cmp once1, 0x01
			je continuee

			mov ecx, _A7EBC389_New
			mov dword ptr[ebx + eax * 0x08 + 0x04], ecx

			mov once1, 0x01
			mov ecx, 0xA7EBC389

		continuee :
			cmp ecx, edx
			jmp StringReplacementCodeCaveExit

	}
}
// String Replacement
injector::MakeJMP(0x57861A, StringReplacementCodeCave, true);

/* INI File reader*/

void Init()
{
	CIniReader iniReader("SWINEExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyToggleForceHeat = iniReader.ReadInteger("Hotkeys", "HeatLevelHack", 118); //F7
	hotkeyForceHeatLevel = iniReader.ReadInteger("Hotkeys", "ChangeHeatLevel", 33); //PageUp
	hotkeyToggleCopLights = iniReader.ReadInteger("Hotkeys", "CopLights", 79); // O
	hotkeyToggleHeadLights = iniReader.ReadInteger("Hotkeys", "HeadLights", 72); // H
	hotkeyUnlockSeriesCarsAndUpgrades = iniReader.ReadInteger("Hotkeys", "UnlockSeriesCarsAndUpgrades", 119); // F8
	hotkeyAutoDrive = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); // F6


	// LapControllers
	minLaps = iniReader.ReadInteger("LapControllers", "Minimum", 0);
	maxLaps = iniReader.ReadInteger("LapControllers", "Maximum", 127);
	minTime = iniReader.ReadInteger("LapControllers", "MinTimePursuitTag", 0);
	maxTime = iniReader.ReadInteger("LapControllers", "MaxTimePursuitTag", 127);

	// OpponentControllers
	minOpponents = iniReader.ReadInteger("OpponentControllers", "Minimum", 0);
	maxOpponents = iniReader.ReadInteger("OpponentControllers", "Maximum", 19);
	UnfreezeRaceWarsCircuits = iniReader.ReadInteger("OpponentControllers", "UnfreezeRaceWarsCircuits", 1) == 1;

	// TrafficControllers
	TrafficLow = iniReader.ReadInteger("TrafficControllers", "Low", 3);
	TrafficMed = iniReader.ReadInteger("TrafficControllers", "Medium", 10);
	TrafficHigh = iniReader.ReadInteger("TrafficControllers", "High", 50);

	// Menu
	ShowMoreRaceOptions = iniReader.ReadInteger("Menu", "ShowMoreRaceOptions", 0);
	ShowSubs = iniReader.ReadInteger("Menu", "ShowSubs", 0) == 1;
	EnableMoreCarCategories = iniReader.ReadInteger("Menu", "ShowMoreCarCategories", 0) == 1;
	ShowLanguageSelectScreen = iniReader.ReadInteger("Menu", "ShowLanguageSelectScreen", 0) == 1;
	ShowSpecialVinyls = iniReader.ReadInteger("Menu", "ShowSpecialVinyls", 0);
	ShowDebugCarCustomize = iniReader.ReadInteger("Menu", "ShowDebugCarCustomize", 0) == 1;
	InfiniteAutosculptSliders = iniReader.ReadInteger("Menu", "InfiniteAutosculptSliders", 0) == 1;
	csBlacklist = iniReader.ReadInteger("Menu", "ChallengeSeriesBlacklist", 19);
	SplashScreenTimeLimit = iniReader.ReadFloat("Menu", "SplashScreenTimeLimit", 30.0f);
	GarageZoom = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteZoom", 0) == 1;
	GarageRotate = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteRotation", 0) == 1;
	GarageShowcase = iniReader.ReadInteger("Menu", "ShowcaseCamAlwaysEnable", 0) == 1;
	nlgzrgnTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableCameras = iniReader.ReadInteger("Gameplay", "EnableHiddenCameraModes", 0) == 1;
	CameraDriftMoveMode = iniReader.ReadInteger("Gameplay", "SmartLookaheadCameraMode", 0);
	GameSpeed = iniReader.ReadFloat("Gameplay", "GameSpeed", 1.0f);
	WorldAnimationSpeed = iniReader.ReadFloat("Gameplay", "WorldAnimationSpeed", 45.0f);
	CarScale = iniReader.ReadFloat("Gameplay", "CarScale", 1.0f);
	copLightsEnabled = iniReader.ReadInteger("Gameplay", "CopLightsMode", 0) == 1;
	copLightsAmount = iniReader.ReadFloat("Gameplay", "CopLightsBrightness", 1.00f);
	headLightsMode = iniReader.ReadInteger("Gameplay", "HeadLightsMode", 2);
	LowBeamAmount = iniReader.ReadFloat("Gameplay", "LowBeamBrightness", 0.75f);
	HighBeamAmount = iniReader.ReadFloat("Gameplay", "HighBeamBrightness", 1.00f);
	RemoveNeonBarriers = iniReader.ReadInteger("Gameplay", "RemoveNeonBarriers", 0) == 1;
	UnlockStrangeRace = iniReader.ReadInteger("Gameplay", "UnlockStrangeRace", 0) == 1;
	UnlockSeriesCarsAndUpgrades = iniReader.ReadInteger("Gameplay", "UnlockSeriesCarsAndUpgrades", 0) == 1;
	UnlockAllThings = iniReader.ReadInteger("Gameplay", "UnlockAllThings", 0) == 1;

	// Drift
	MaximumMultiplierTrack = iniReader.ReadInteger("Drift", "MaximumMultiplierTrack", 10);
	MaximumMultiplierCanyon = iniReader.ReadInteger("Drift", "MaximumMultiplierCanyon", 20);
	AugmentedDriftWithEBrake = iniReader.ReadInteger("Drift", "AugmentedDriftWithEBrake", 0) == 1;

	// Pursuit
	EnableHeatLevelOverride = iniReader.ReadInteger("Pursuit", "HeatLevelOverride", 0) == 1;
	MinHeatLevel = iniReader.ReadFloat("Pursuit", "MinimumHeatLevel", 1.00f);
	MaxHeatLevel = iniReader.ReadFloat("Pursuit", "MaximumHeatLevel", 10.00f);

	// Weather
	AlwaysRain = iniReader.ReadInteger("Weather", "AlwaysRain", 0) == 1;
	RainAmount = iniReader.ReadFloat("Weather", "GeneralRainAmount", 1.0f);
	RoadReflection = iniReader.ReadFloat("Weather", "RoadReflectionAmount", 1.0f);
	FallingRainSize = iniReader.ReadFloat("Weather", "RainSize", 0.01f);
	RainIntensity = iniReader.ReadFloat("Weather", "RainIntensity", 0.45f);
	RainXing = iniReader.ReadFloat("Weather", "RainCrossing", 0.02f);
	RainFallSpeed = iniReader.ReadFloat("Weather", "RainSpeed", 0.03f);
	RainGravity = iniReader.ReadFloat("Weather", "RainGravity", 0.35f);

	// Misc
	WindowedMode = iniReader.ReadInteger("Misc", "WindowedMode", 0) == 1;
	Win10Fix = iniReader.ReadInteger("Misc", "Win10Fix", 1) == 1;
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) == 1;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) == 1;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) == 1;
	EnableVoice = iniReader.ReadInteger("Misc", "EnableVoice", 1) == 1;

/* SAMPLE-FY*/
if ((GetAsyncKeyState(VK_LSHIFT) & 1)) // Save
{
	while ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) > 0)
	{
		Sleep(0);
		if (GetAsyncKeyState(49) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x01, true); while ((GetAsyncKeyState(49) & 0x8000) > 0) Sleep(0); }
		if (GetAsyncKeyState(50) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x02, true); while ((GetAsyncKeyState(50) & 0x8000) > 0) Sleep(0); }
		if (GetAsyncKeyState(51) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x03, true); while ((GetAsyncKeyState(51) & 0x8000) > 0) Sleep(0); }
		if (GetAsyncKeyState(52) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x04, true); while ((GetAsyncKeyState(52) & 0x8000) > 0) Sleep(0); }
		if (GetAsyncKeyState(53) & 1) { injector::WriteMemory<unsigned char>(0xb74bf8, 0x05, true); while ((GetAsyncKeyState(53) & 0x8000) > 0) Sleep(0); }
	}
}


if (GetAsyncKeyState(49) & 1) {
	 // CODE
}


/* old code */

	// Restrictions
	if (minLaps < 0 || minLaps > 127) minLaps = 1;
	if (maxLaps < 0 || maxLaps > 127) maxLaps = 8;
	if (minTime < 0 || minTime > 127) minTime = 3;
	if (maxTime < 0 || maxTime > 127) maxTime = 7;

	if (minOpponents < 0 || minOpponents > 29) minOpponents = 0;
	if (maxOpponents < 0 || maxOpponents > 29) maxOpponents = 7;

	if (MaximumMultiplierTrack < 1 || MaximumMultiplierTrack > 127) MaximumMultiplierTrack = 10;
	if (MaximumMultiplierCanyon < 1 || MaximumMultiplierCanyon > 127) MaximumMultiplierCanyon = 20;

	if (MaxHeatLevel < 1 || MaxHeatLevel < MinHeatLevel || MaxHeatLevel > 10) MaxHeatLevel = 5;
	if (MinHeatLevel < 1 || MaxHeatLevel < MinHeatLevel || MinHeatLevel > 10) MinHeatLevel = 1;
	if (headLightsMode > 2) headLightsMode = 2;

	if (TrafficLow < 0 || TrafficLow > 100) TrafficLow = 3;
	if (TrafficMed < 0 || TrafficMed > 100) TrafficMed = 10;
	if (TrafficHigh < 0 || TrafficHigh > 100) TrafficHigh = 50;

	if (ShowSpecialVinyls > 2) ShowSpecialVinyls = 2;

	// Lap Controllers
	injector::WriteMemory<unsigned char>(0x4ac7fd, maxLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac811, maxLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac803, minLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac80b, minLaps, true);
	injector::WriteMemory<unsigned char>(0x4ac819, maxTime, true); // P Tag Max Time
	injector::WriteMemory<unsigned char>(0x4ac82d, maxTime, true); // P Tag Max Time
	injector::WriteMemory<unsigned char>(0x4ac827, minTime, true); // P Tag Min Time
	injector::WriteMemory<unsigned char>(0x4ac81f, minTime, true); // P Tag Min Time

	// Opponent Controllers
	injector::MakeNOP(0x4a5bb8, 7, true); // Enable crew on controllers
	injector::WriteMemory<unsigned char>(0x4ac884, minOpponents, true); // Min - Crew Off
	injector::WriteMemory<unsigned char>(0x4ac897, minOpponents, true); // Min - Crew On
	injector::WriteMemory<unsigned char>(0x4ac890, maxOpponents, true); // Max - Crew Off
	injector::WriteMemory<unsigned char>(0x4ac87d, maxOpponents, true); // Max - Crew On
	injector::WriteMemory<unsigned char>(0x4ac8df, maxOpponents, true); // Max - P Tag
	injector::WriteMemory<unsigned char>(0x4ac8e9, maxOpponents, true); // Max - P Tag
	injector::WriteMemory<unsigned char>(0x4ac8c5, maxOpponents, true); // Max - Canyon S
	injector::WriteMemory<unsigned char>(0x4ac8d7, maxOpponents, true); // Max - Canyon S
	//injector::WriteMemory<unsigned char>(0x668ae7, maxOpponents, true); // Fix Crew Member option until 10 opponents?? (Cancelled, limits everything with 10)

	// Unfreeze Opponent Count for Race Wars Circuit Events
	if (UnfreezeRaceWarsCircuits)
	{
		injector::WriteMemory<unsigned char>(0x84b9a4, 0xEB, true);
	}

	// Traffic Density Controllers (0-100)
	injector::WriteMemory<unsigned char>(0x7A9E40, TrafficLow, true); // Low (3)
	injector::WriteMemory<unsigned char>(0x7A9E44, TrafficMed, true); // Medium (10)
	injector::WriteMemory<unsigned char>(0x7A9E48, TrafficHigh, true); // High (50)


	// Tweaked Race Options Menus
	if (ShowMoreRaceOptions)
	{
		// Add 10th option to Quick Race Settings
		injector::WriteMemory<unsigned char>(0x84bdee, 0x0A, true);
		injector::WriteMemory<DWORD>(0x84c458, 0x84c1dc, true);

		// Reuse NOS Option to put things together
		injector::MakeJMP(0x84c1dc, CopsOptionCodeCave, true);
		injector::MakeJMP(0x84c205, CopsOptionCodeCave2, true);
		injector::MakeNOP(0x84c211, CopsOptionCodeCave3Exit - 0x84c211, true);
		injector::MakeJMP(0x84c211, CopsOptionCodeCave3, true);

		// Use a Reworked Circuit Menu for All
		injector::MakeRangedNOP(0x85E62D, 0x85E639, true);
		injector::MakeJMP(0x85E62D, LearnRaceModeCodeCave, true);
		injector::MakeCALL(0x85E63B, NewRaceMenuCodeCave, true);

		// Force-Enable Game Mode Selection??
		if (ShowMoreRaceOptions==2) injector::MakeRangedNOP(0x84b771, 0x84b799, true);

	}

	// Show Subtitles
	if (ShowSubs)
	{
		injector::MakeNOP(0x5b687a, 2, true);
		injector::MakeNOP(0x5bb8f0, 2, true);
		injector::MakeNOP(0x5bbafb, 2, true);
	}

	// More Car Categories
	if (EnableMoreCarCategories)
	{
		injector::WriteMemory<unsigned char>(0x844A53, 0x80, true);
		injector::WriteMemory<unsigned char>(0x844A54, 0xFC, true);
		injector::WriteMemory<unsigned char>(0x844A55, 0x01, true);
		injector::WriteMemory<int>(0x844A20, 256, true);
		injector::WriteMemory<int>(0x86205A, 256, true);
	}

	// Language Select Screen
	if (ShowLanguageSelectScreen)
	{
		injector::WriteMemory<DWORD>(0x5BD584, 0x5BD4D0, true);
		injector::WriteMemory<DWORD>(0x5BD59C, 0x5BD424, true);

		// Show all languages
		injector::MakeNOP(0x85E14B, 2, true);
		injector::WriteMemory<unsigned char>(0x85E1CF, 0x0B, true);
	}

	// Infinite Autosculpt
	if (InfiniteAutosculptSliders)
	{
		injector::MakeNOP(0x57331E, 5, true);
	}

	// Challenge Series Bin
	injector::WriteMemory<unsigned char>(0x4a9f3c, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4aa009, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4aa08a, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4aa73b, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4b9c58, csBlacklist, true);
	injector::WriteMemory<unsigned char>(0x4cb833, csBlacklist, true);

	// Splash Screen Time Limit
	injector::WriteMemory<float>(0x9C79A4 ,SplashScreenTimeLimit, true);

	// Enable Drift Camera View Everywhere
	if (EnableCameras)
	{
		injector::MakeNOP(0x4C4EE3, 2, true);
		injector::MakeNOP(0x4C4F3F, 2, true);
	}

	// Load headlights preferences
	switch (headLightsMode)
	{
		case 0:
			injector::WriteMemory<float>(0x7cbf96, 0, true); // Left HeadLight
			injector::WriteMemory<float>(0x7cbf77, 0, true); // Right HeadLight
			break;
		case 1:
			injector::WriteMemory<float>(0x7cbf96, LowBeamAmount, true); // Left HeadLight
			injector::WriteMemory<float>(0x7cbf77, LowBeamAmount, true); // Right HeadLight
			break;
		case 2: default:
			injector::WriteMemory<float>(0x7cbf96, HighBeamAmount, true); // Left HeadLight
			injector::WriteMemory<float>(0x7cbf77, HighBeamAmount, true); // Right HeadLight
			break;
	}

	// Load cop lights preferences
	if (copLightsEnabled)
	{
		injector::WriteMemory<float>(0x7cbed9, copLightsAmount, true); // Red Flashing Lights
		injector::WriteMemory<float>(0x7cbee1, copLightsAmount, true); // Blue Flashing Lights
		injector::WriteMemory<float>(0x7cbee9, copLightsAmount, true); // White Flashing Lights
	}

	// Remove Barriers
	if (RemoveNeonBarriers)
	{
		injector::WriteMemory<unsigned char>(0x9d85c8, 0x59, true); // BARRIER_SPLINE_4501
		injector::WriteMemory<unsigned char>(0x9d85dc, 0x59, true); // BARRIER_SPLINE_4500
		injector::WriteMemory<unsigned char>(0x9d85f0, 0x59, true); // BARRIER_SPLINE_4091
		injector::WriteMemory<unsigned char>(0x9d8604, 0x59, true); // BARRIER_SPLINE_4090
		injector::WriteMemory<unsigned char>(0x9d8618, 0x59, true); // BARRIER_SPLINE_306
		injector::WriteMemory<unsigned char>(0x9d862c, 0x59, true); // BARRIER_SPLINE_305
		injector::WriteMemory<unsigned char>(0x9d8b34, 0x59, true); // BARRIER_SPLINE_%d
	}

	// Unlock a strange Canyon Race
	if (UnlockStrangeRace)
	{
		injector::MakeNOP(0x61C237, 6, true);
	}

	// Unlock Series Cars & Upgrades Option From NFSC Unlocker
	if (UnlockSeriesCarsAndUpgrades)
	{
		injector::WriteMemory<unsigned char>(0x49ECD2, 0xB0, true);
		injector::WriteMemory<unsigned char>(0x49ECD3, 0x01, true);
	}

	// Load Any Save Game
	injector::WriteMemory<unsigned char>(0x89584b, 0xEB, true);

	// Drift Multipliers
	injector::WriteMemory<unsigned char>(0x6be947, MaximumMultiplierTrack, true);
	injector::WriteMemory<unsigned char>(0x6ab943, MaximumMultiplierCanyon, true);
	injector::WriteMemory<unsigned char>(0x6ab945, MaximumMultiplierCanyon, true);

	// Heat Level Overrides EnableHeatLevelOverride
	injector::MakeNOP(0x449a7c, HeatLevelsCodeCaveExit - 0x449a7c, true); // Clean the unused code
	injector::MakeJMP(0x449a7c, HeatLevelsCodeCave, true); // Prepare the game for advanced force heat level hack

	// Rain Options
	if (AlwaysRain)
	{
		injector::WriteMemory<unsigned char>(0xB74D20, 0x01, true);
		injector::WriteMemory<unsigned char>(0x7D83C9, 0xEB, true); // Road Reflection Fix?? 7d8403??
	}
	injector::WriteMemory<float>(0xA798D4, RoadReflection, true);
	injector::WriteMemory<float>(0xA7984C, FallingRainSize, true);
	injector::WriteMemory<float>(0xA797D0, RainAmount, true);
	injector::WriteMemory<float>(0xA79850, RainIntensity, true);
	injector::WriteMemory<float>(0xA797E0, RainXing, true);
	injector::WriteMemory<float>(0xA797E4, RainFallSpeed, true);
	injector::WriteMemory<float>(0xA797E8, RainGravity, true);

	// Misc Options (Like MW Mod Loader)
	if (WindowedMode)
	{
		injector::WriteMemory<unsigned char>(0xAB0AD4, WindowedMode, true);
	}

	if (SkipMovies)
	{
		injector::WriteMemory<unsigned char>(0xA9E6D8, SkipMovies, true);
	}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x87E926) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.4 English nfsc.exe (6,88 MB (7.217.152 bytes)).", "NFSC Extra Options", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;

}
