// S.W.I.N.E. ExOpts ALPHA (or easy and light ExOptions base for anyone to use)
// Coding: bads.tm, steakhal
// Injector: thelink2012,
// IniReader: ThirteenAG,
// Testing: bads.tm (in linux, console Thing does not work in wine), nlgzrgn (in Windows)
// If you're contributor or outsourced programmer, credit yourself here is recommended!
// Remove this line and few ones bellow when it's quite well finished (maybe)
// Stuff to do:
// Camera Max Zoom In/Out = done | Camera Rotation and angle up-down = yes! | Cam Map out of bound limit = yes! | Selectable Thing = NO!
// Unitslots and Upgrade Slot = NO! | Mod Loader = NO! | Add Money current+1000,000 = YES!
// Non CE : Takeover++ , Try finding out debug developer mode, Try adding new menu button (not replacing existing ones)
// Need to do: Clean up maybe, have a working INI reader.... Mod loader - If there is 1 in config file, it will load mod(s) from mod/*.ini and maybe Change
// way like when game wants to load units/....*.4d it will load instead from mod/units/.....*.4d this also could work with music swap....
// Not sure if it's possible, but replacing-breaking gamespy stuff to some new one would be cool, or simply chaning network/internet/multiplayer things....

#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"

using namespace injector;
char* Takeover = "S.W.I.N.E. %s v%d.%d with Extra Options - © 2017 ExOpts Team. No rights reserved.";

DWORD WINAPI Thing(LPVOID); // nlgzrgn's usual thing
DWORD SPPointer;
int SPAmount;
float CamMaxZoomIn, CamMaxZoomOut, CamMaxAngleUp, CamMaxAngleDown, CamMapLimit;
int HotAddSP, HotDecSP, HotAddDecSPAmount;
bool ExOptsTeamTakeover;

/*this part is by steakhal


template <std::size_t Level>
static DWORD FindDynAddr(DWORD baseAddr, const DWORD(&offsets)[Level]) {
	for (int i = 0; i < Level; ++i)
		baseAddr = ReadMemory<DWORD>(baseAddr, false) + offsets[i];
	return baseAddr;
}

// main codebase
//this part is by steakhal, with GetAsyncKeyState by bads

static void readMoney() {
	const DWORD moneyBaseAddr = 0x0057B270;
	const DWORD moneyOffsets[] = { 0x24 };

	const DWORD dynMoneyAddr = FindDynAddr(moneyBaseAddr, moneyOffsets);
	const int value = ReadMemory<int>(dynMoneyAddr, false);

	std::cout << std::hex << dynMoneyAddr << " :: money: "
		<< std::dec << value << std::endl;
}
*/

void Init()
{
	CIniReader iniReader("SWINEExtraOptionsSettings.ini");

	// Hotkeys
	HotAddSP = iniReader.ReadInteger("Hotkeys", "AddSP", 104); // Num8
	HotDecSP = iniReader.ReadInteger("Hotkeys", "DecSP", 98); // Num2
	HotAddDecSPAmount = iniReader.ReadInteger("Hotkeys", "AddOrDecSPAmount", 100);

	// Camera
	CamMaxZoomIn = iniReader.ReadFloat("Camera", "MaxZoomIn", 10.0f);
	CamMaxZoomOut = iniReader.ReadFloat("Camera", "MaxZoomOut", 20.0f);
	CamMaxAngleUp = iniReader.ReadFloat("Camera", "MaxAngleUp", -1.13f);
	CamMaxAngleDown = iniReader.ReadFloat("Camera", "MaxAngleDown", -0.7f);
	CamMapLimit = iniReader.ReadFloat("Camera", "MapCameraLimit", 48.0f);

	// Menu
	ExOptsTeamTakeover = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Camera Controllers
	WriteMemory<float>(0x4CB3A9, CamMaxZoomIn, true); // Max zoom in
	WriteMemory<float>(0x4CB3B3, CamMaxZoomOut, true); // Max zoom out
	WriteMemory<float>(0x4CB395, CamMaxAngleUp, true); // Max angle up
	WriteMemory<float>(0x4CB39F, CamMaxAngleDown, true); // Max angle down
	WriteMemory<float>(0x4CB3D5, CamMapLimit, true); // Map Cameralimit

	// Takeover
	if (ExOptsTeamTakeover)
	{
		injector::WriteMemory<DWORD>(0x43A85E, (DWORD)Takeover, true);
	}
	

	// Other Things
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Thing, NULL, 0, NULL);
}

DWORD WINAPI Thing(LPVOID)
{
	while (true)
	{
		SPPointer = *(DWORD*)0x57B270;

		if ((GetAsyncKeyState(HotAddSP) & 1)) // Add SP
		{
			*(int*)(SPPointer + 0x24) = *(int*)(SPPointer + 0x24) + HotAddDecSPAmount;

			while ((GetAsyncKeyState(HotAddSP) & 0x8000) > 0) { Sleep(0); }
		}

		if ((GetAsyncKeyState(HotDecSP) & 1)) // Decrease SP
		{
			*(int*)(SPPointer + 0x24) = *(int*)(SPPointer + 0x24) - HotAddDecSPAmount;

			while ((GetAsyncKeyState(HotDecSP) & 0x8000) > 0) { Sleep(0); }
		}
	}
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x5186A7) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.9 English swine.exe (1,36 MB (1.433.600 bytes)).", "S.W.I.N.E. Extra Options", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;

}
