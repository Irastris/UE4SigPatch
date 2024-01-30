#include "pch.h"
#include "patches.h"
#include <string>

using namespace Patches;

enum eSupportedGames {
	eGameBramble,
	eGameMK12,
	eGameSifu,
	eUnsupportedGame
};

eSupportedGames GetEnumeratorFromProcessName(std::string const& sProcessName) {
	if (sProcessName == "Bramble_TMK-Win64-Shipping.exe") return eGameBramble;
	if (sProcessName == "MK12.exe") return eGameMK12;
	if (sProcessName == "Sifu-Win64-Shipping.exe") return eGameSifu;
	return eUnsupportedGame;
}

bool Initialize()
{
	const char* pSigCheck;
	const char* pSigWarn;
	const char* pChunkSigCheck;
	const char* pChunkSigCheckFunc;
	const char* pTOCCheck;

	switch (GetEnumeratorFromProcessName(GetProcessName())) {
		case eGameBramble:
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";
			pTOCCheck = "4D 8B CE 45 33 C0 E8 ? ? ? ? 44 39 AD ? ? ? ? 0F 84";

			DisableSignatureCheck(pSigCheck);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);
			DisableTOCSigCheck(pTOCCheck);

			break;

		case eGameMK12:
			// Patterns for Mortal Kombat 1 researched and contributed by @thethiny -- https://github.com/thethiny
			// Patterns may be reused for additional game support when applicable
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pSigWarn = "4C 03 F1 80 3D ? ? ? ? 03 0F 82";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";
			pTOCCheck = "4D 8B CE 45 33 C0 E8 ? ? ? ? 44 39 BD ? ? ? ? 0F 84";

			DisableSignatureCheck(pSigCheck);
			DisableSignatureWarn(pSigWarn);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);
			DisableTOCSigCheck(pTOCCheck);

			break;

		case eGameSifu:
			pSigCheck = "80 B9 ? ? ? ? 00 49 8B F0 48 8B FA 48 8B D9 75";
			pChunkSigCheck = "0F B6 51 ? 48 8B F1 48 8B 0D ? ? ? ? E8 ? ? ? ? C6 46 ? ? 0F AE F8";
			pChunkSigCheckFunc = "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 48 8D 59 08 49 63 F9 48 8B F1 49 8B E8 48 8B CB 44 0F B6 F2";

			DisableSignatureCheck(pSigCheck);
			DisableChunkSigCheck(pChunkSigCheck, pChunkSigCheckFunc);

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