// S.W.I.N.E. Extra Options
// Coding: nlgzrgn, bads.tm, steakhal
// Injector: thelink2012,
// IniReader: ThirteenAG,
// Testing: bads.tm, nlgzrgn (in Windows)
// If you're contributor or outsourced programmer, credit yourself here is recommended!

/*
 Remove this line and few ones bellow when it's quite well finished (maybe)
 Done:  Add Money current+1000,000 = YES! | Cam Map out of bound limit = yes! | Camera Max Zoom In/Out = done | Camera Rotation and angle up-down = yes! |
 Stuff to do:
 Selectable Thing = NO!
 Unitslots and Upgrade Slot = NO! | Mod Loader = NO! 

 Good if was added:
 https://gist.github.com/kris7t/2850110 more screen resoliutions... Doing changes in graphics will work, but unmodded original game simply won't display those options
[Advanced graphics options]   - Source: DIGI 2.3 "Patch"
 ; -1 = 640x480, 0 = 800x600, 1 = 1024x768, 2 = 1280x1024, 3 = 1600x1200, 4 = 1280x800, 5 = 1440x900, 6 = 1680x1050, 7 = 1920x1200, 8 = 1024x600, 
 9 = 1280x720, 10 = 1360x768, 11 = 1366x768, 12 = 1600x900, 13 = 1920x1080
 Screen resolution = 11

 Possibles:
 Non CE : Try finding out debug developer mode, Try adding new menu button (not replacing existing ones)

 Need to do: Mod loader - If there is 1 in config file, it will load mod(s) from mod/*.ini and maybe Change
 way like when game wants to load units/....*.4d it will load instead from mod/units/.....*.4d this also could work with music swap....
 Not sure if it's possible, but replacing-breaking gamespy stuff to some new one would be cool, or simply chaning network/internet/multiplayer things....
*/

#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"

#include "..\includes\discord-rpc.h" // Discord RPC
#include <csignal>
#include <iostream>

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

bool quit = false;

	int main(void)
	{
		//quit for stopping the loop
		bool quit = false;

		//Define When to Shutdown
		signal(SIGINT, shutdown_signal);
		signal(SIGTERM, shutdown_signal);
#ifdef SIGBREAK
		signal(SIGBREAK, shutdown_signal);
#endif

		//Start discord-rpc
		void InitDiscord()
		{
			Discord_Initialize("381496838290931713");
		}

		//Loop to thing running also keep this running
		while (!quit)
		{
			void UpdatePresence()
			{
				char buffer[256];
				DiscordRichPresence discordPresence;
				memset(&discordPresence, 0, sizeof(discordPresence));
				discordPresence.details = "Game: S.W.I.N.E.";
				discordPresence.state = "v2 release by bads.tm";
				//sprintf(buffer, "Ranked | Mode: %d", GameEngine.GetMode());
				//discordPresence.details = buffer;
				//discordPresence.endTimestamp = time(0) + 5 * 60;
				discordPresence.largeImageKey = "lrg_game_swine"; //swine
				discordPresence.largeImageText = "S.W.I.N.E."; //when hovered over will show this text
				discordPresence.smallImageKey = "smallimagekey"; //extra options with nfs style
				discordPresence.smallImageText = "Extra Options"; //when hovered over will show this text
				//discordPresence.partyId = GameEngine.GetPartyId();
				//discordPresence.partySize = 1;
				//discordPresence.partyMax = 6;
				//discordPresence.matchSecret = "4b2fdce12f639de8bfa7e3591b71a0d679d7c93f";
				//discordPresence.spectateSecret = "e7eb30d2ee025ed05c71ea495f770b76454ee4e0";
				discordPresence.instance = 1;
				Discord_UpdatePresence(&discordPresence);
			}
			Sleep(10000);
		}
		return 0;
	}


//Break the loop and properly shutdown discord-rpc
void shutdown_signal(int sig)
{
	signal(sig, shutdown_signal);
	Discord_Shutdown();
	exit(1);
	quit = true;
}
