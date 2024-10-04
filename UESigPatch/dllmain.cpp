#include "pch.h"

#include "patches.h"
#include "utils.h"
#include <string>

constexpr const char* ASI_VERSION = "1.5.3";

bool bPauseOnStart = false;
bool bShowConsole = false;

enum eSupportedGames {
	eGameAsterigos,
	eGameBramble,
	eGameKKFOS,
	eGameMK12,
	eGameFirstDescendant,
	eGameSifu,
	eGameSouthPark,
	eGameSuicideSquad,
	eGameQuidditch,
	eUnsupportedGame
};

eSupportedGames GetEnumeratorFromProcessName(std::string const& sProcessName) {
	if (sProcessName == "Genesis-Win64-Shipping.exe") return eGameAsterigos;
	if (sProcessName == "Bramble_TMK-Win64-Shipping.exe") return eGameBramble;
	if (sProcessName == "Diony.exe") return eGameKKFOS;
	if (sProcessName == "MK12.exe") return eGameMK12;
	if (sProcessName == "M1-Win64-Shipping.exe") return eGameFirstDescendant;
	if (sProcessName == "Sifu-Win64-Shipping.exe") return eGameSifu;
	if (sProcessName == "SnowDay-Win64-Shipping.exe") return eGameSouthPark;
	if (sProcessName == "SuicideSquad_KTJL.exe") return eGameSuicideSquad;
	if (sProcessName == "QuidditchChampions-Win64-Shipping.exe") return eGameQuidditch;
	return eUnsupportedGame;
}

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

bool Initialize()
{
	const char* pSigCheck;
	const char* pChunkSigCheck;
	const char* pChunkSigCheckFunc;
	const char* pTOCCheck;
	const char* pTOCCompare;
	const char* pPakTOCCheck;

	if (bPauseOnStart) MessageBoxA(0, "Pausing execution, attach your debugger now.", "UESigPatch", MB_ICONINFORMATION);
	if (bShowConsole) CreateConsole();

	switch (GetEnumeratorFromProcessName(GetProcessName())) {
		case eGameAsterigos:
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";
			pTOCCheck = "4D 8B CE 45 33 C0 E8 ? ? ? ? 44 39 AD ? ? ? ? 0F 84";

			DisableSignatureCheck(pSigCheck, 0x14);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);
			DisableTOCSigCheck(pTOCCheck, 0x12);

			break;

		case eGameBramble:
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";
			pTOCCheck = "4D 8B CE 45 33 C0 E8 ? ? ? ? 44 39 AD ? ? ? ? 0F 84";

			DisableSignatureCheck(pSigCheck, 0x14);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);
			DisableTOCSigCheck(pTOCCheck, 0x12);

			break;

		case eGameKKFOS:
			pSigCheck = "EC 20 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75 51";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 FA";
			pTOCCheck = "4D 8B CE 45 33 C0 E8 ? ? ? ? 39 B5 ? ? ? ? 0F 84";

			DisableSignatureCheck(pSigCheck, 0x14);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);
			DisableTOCSigCheck(pTOCCheck, 0x11);

			break;

		case eGameMK12:
			// Patterns for Mortal Kombat 1 researched and contributed by @thethiny -- https://github.com/thethiny
			// Patterns may be reused for additional game support when applicable
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";
			pTOCCheck = "4D 8B CE 45 33 C0 E8 ? ? ? ? 44 39 BD ? ? ? ? 0F 84";

			DisableSignatureCheck(pSigCheck, 0x14);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);
			DisableTOCSigCheck(pTOCCheck, 0x12);

			break;

		case eGameFirstDescendant:
			pTOCCheck = "49 ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 44 39 AD ? ? ? ? 0F 84";
			pPakTOCCheck = "49 ? ? ? E8 ? ? ? ? E8 ? ? ? ? 83 78 ? 00 74 16";

			DisableTOCSigCheck(pTOCCheck, 0x16);
			DisablePakTOCCheck(pPakTOCCheck);

			break;

		case eGameSifu:
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";

			DisableSignatureCheck(pSigCheck, 0x14);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);

			break;

		case eGameSouthPark:
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";

			DisableSignatureCheck(pSigCheck, 0x14);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);

			break;

		case eGameSuicideSquad:
			// Necessary patch explained by @thethiny
			pTOCCompare = "44 39 BD ? ? 00 00 0F 85 ? ? ? ? 44 39 7B 1C";

			DisableTOCCompare(pTOCCompare);
			
			break;

		case eGameQuidditch:
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";
			pTOCCheck = "4D 8B CE 45 33 C0 E8 ? ? ? ? 44 39 AD ? ? ? ? 0F 84";

			DisableSignatureCheck(pSigCheck, 0x14);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);
			DisableTOCSigCheck(pTOCCheck, 0x12);

			break;

		case eUnsupportedGame:
		default:
			MessageBoxA(NULL, "This version of UESigPatch is not compatible with the currently loading game, all patches have been skipped.", "UESigPatch", MB_ICONEXCLAMATION);
			return false;
	}

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason)
    {
		case DLL_PROCESS_ATTACH:
			if (!Initialize())
				return false;
    }
    return true;
}
