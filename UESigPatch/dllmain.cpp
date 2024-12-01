#include <iostream>
#include "gamesupport.h"
#include "patternscan.h"

// MinHook dependencies
#include <MinHook.h>
#pragma comment(lib, "libMinHook.x64.lib")

// Dumper-7 SDK -- may be needed for solving type 2, excluded for now
// #include "UnrealContainers.hpp"
// #include "SDK/Basic.hpp"
// using namespace SDK;

constexpr const char* ASI_VERSION = "2.0.0";

bool bPauseOnStart = false;
bool bShowConsole = false;

void CreateConsole()
{
	FreeConsole();
	AllocConsole();

	FILE* fNull;
	freopen_s(&fNull, "CONOUT$", "w", stdout);
	freopen_s(&fNull, "CONOUT$", "w", stderr);

	std::string consoleName = "UESigPatch Console";
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	SetConsoleTitleA(consoleName.c_str());
	GetConsoleMode(Console, &dwMode);
	SetConsoleMode(Console, dwMode);

	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(coutbuf);
}

void (*OGetPakSigningKeysDelegate)() = nullptr; // TDelegate<void(TArray<uint8>&, TArray<uint8>&)>&
void GetPakSigningKeysDelegate()
{
	// OGetPakSigningKeysDelegate();

	std::cout << "Hello from MinHook'd function" << std::endl;

	// Type 1 function return -- needs Dumper-7 SDK, disabled for now
	// static TDelegate<void(TArray<uint8>&, TArray<uint8>&)> PakSigningKeysDelegate;
	// return PakSigningKeysDelegate;

	// Type 2 function return -- currently does not bypass signing
	// TDelegate<void(TArray<uint8>&, TArray<uint8>&)> PakSigningKeysDelegate = OGetPakSigningKeysDelegate();
	// std::cout << "PakSigningKeysDelegate address: 0x" << &PakSigningKeysDelegate << std::endl;
	// return PakSigningKeysDelegate;
}

bool Initialize()
{
	if (bPauseOnStart) MessageBoxA(0, "Pausing execution, attach your debugger now.", "UESigPatch", MB_ICONINFORMATION);
	if (bShowConsole) CreateConsole();

	const char* pattern = GetPatternFromExecutableName();
	if (!pattern)
	{
		MessageBoxA(NULL, "This version of UESigPatch is not marked as compatible with the currently loading game. UESigPatch will not be active.", "UESigPatch", MB_ICONEXCLAMATION);
		return false;
	}

	uintptr_t GetPakSigningKeysAddr = PatternScan(pattern);
	if (!GetPakSigningKeysAddr)
	{
		MessageBoxA(NULL, "Failed to find the necessary function to patch, it's possible a game update has broken UESigPatch's support. UESigPatch will not be active.", "UESigPatch", MB_ICONEXCLAMATION);
		return false;
	}

	std::cout << "GetPakSigningKeysAddr was found at 0x" << std::hex << (uintptr_t)GetPakSigningKeysAddr << std::endl;

	if (MH_Initialize() != MH_STATUS::MH_OK)
	{
		MessageBoxA(NULL, "MinHook failed to initialize. UESigPatch will not be active.", "UESigPatch", MB_ICONEXCLAMATION);
		return false;
	}

	if (MH_CreateHook(reinterpret_cast<LPVOID>(GetPakSigningKeysAddr), GetPakSigningKeysDelegate, reinterpret_cast<LPVOID*>(&OGetPakSigningKeysDelegate)) != MH_STATUS::MH_OK)
	{
		MessageBoxA(NULL, "MinHook failed to create the hook. UESigPatch will not be active.", "UESigPatch", MB_ICONEXCLAMATION);
		return false;
	}

	if (MH_EnableHook(reinterpret_cast<LPVOID>(GetPakSigningKeysAddr)) != MH_STATUS::MH_OK)
	{
		MessageBoxA(NULL, "MinHook failed to enable the hook. UESigPatch will not be active.", "UESigPatch", MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
		case DLL_PROCESS_ATTACH:
			if (!Initialize()) return false;
    }
    return true;
}