// S.W.I.N.E. ExOptions (or easy and light ExOptions base for anyone to use)
// Coding: bads.tm
// Injector:
// IniReader:
// Progress: Get it compillable. Then make sure it works in game. Then finish it!
#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"

DWORD WINAPI Thing(LPVOID);

// Once I get it working, I can use this code in future as a base / finish this project.
// Easy changing here #Setup #Set

//-------SELECTABLE VARS--------
// TYPE "STRING" ADDRESS 00541FDC NO POINTERS [STATIC]
//number we are going to overwrite the current ammo with in bytes
STRING SelectableValue[] = "BD"; // Any modifications to address will make all things selectable
STRING SelectableBaseAddress = 00541FDC; 

//-------CAMERA MAX IN VARS-------- NOT STATIC ALL CAMERA, MUST HAVE LOOP OR PRESS KEY TO START INJECT
// TYPE "FLOAT" ADDRESS "swine 1.9 en.exe"+0017B270 
// POINTERS FROM CHEAT ENGINE (TOP TO BOTTOM): 1C ; 0 ; 3C ; 404
//number we are going to overwrite the current ammo with in bytes
BYTE CamMaxInValue[] = 1; //SHOULD READ FROM INI, NOW HARDCODED FOR TESTING
DWORD CamMaxInBaseAddress = 0017B270; 
DWORD CamMaxInOffsets[] = 1C, 0 , 3C , 404; //4 LEVEL pointer

//-------CAMERA MAX OUT VARS--------
// TYPE "FLOAT" ADDRESS "swine 1.9 en.exe"+0017B270
// POINTERS FROM CHEAT ENGINE (TOP TO BOTTOM): 20 ; 88
//number we are going to overwrite the current ammo with in bytes
BYTE CamMaxOutValue[] = 100; //SHOULD READ FROM INI, NOW HARDCODED FOR TESTING
DWORD CamMaxOutBaseAddress = 0017B270; 
DWORD CamMaxOutOffsets[] = 20, 88; //2 LEVEL pointer

//-------CAMERA ROTATION UP VARS--------
// TYPE "FLOAT" ADDRESS "swine 1.9 en.exe"+0017B270
// POINTERS FROM CHEAT ENGINE (TOP TO BOTTOM): 14 ; 0 ; ; 44 ; 404 ; 88
//number we are going to overwrite the current ammo with in bytes
BYTE CamRotUpValue[] = -1.960000038; //SHOULD READ FROM INI, NOW HARDCODED FOR TESTING
DWORD CamRotUpBaseAddress = 0017B270; 
DWORD CamRotUpOffsets[] = 14, 0, 44, 404, 88; //5 LEVEL pointer

//-------CAMERA ROTATION Down VARS-------- -999
// TYPE "FLOAT" ADDRESS "swine 1.9 en.exe"+0017B270
// POINTERS FROM CHEAT ENGINE (TOP TO BOTTOM): 18 ; 0 ; 3C ; 404 ; 88
//number we are going to overwrite the current ammo with in bytes
BYTE CamRotDownValue[] = 0.05000000075; //SHOULD READ FROM INI, NOW HARDCODED FOR TESTING
DWORD CamRotDownBaseAddress = 0017B270; 
DWORD CamRotDownOffsets[] = 18, 0, 3C, 404, 88; //5 LEVEL pointer

//-------CAMERA Boundry Limit VARS-------- -999
// TYPE "FLOAT" ADDRESS "swine 1.9 en.exe"+0017B270
// POINTERS FROM CHEAT ENGINE (TOP TO BOTTOM): 10 ; 0 ; 3C ; 404 ; 88
//number we are going to overwrite the current ammo with in bytes
BYTE CamOutsideValue[] = -999; //SHOULD READ FROM INI, NOW HARDCODED FOR TESTING
DWORD CamOutsideBaseAddress = 0017B270; 
DWORD CamOutsideDownOffsets[] = 10, 0, 3C, 404, 88; //5 LEVEL pointer

// #empty 



// just keep that empty
// Look at http://cherrytree.at/misc/vk.htm for key values (decimal)
// #Write #Memory #WM
{
	if ((GetAsyncKeyState(VK_PRIOR) & 1)) //When pressed "Everything is selectable" [Key is PAGE UP]
	{
	injector::WriteMemory<unsigned char>(SelectableBaseAddress, SelectableValue, true);
	}
}