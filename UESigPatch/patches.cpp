#include "pch.h"

#include "patches.h"
#include "utils.h"

using namespace Memory::VP;

bool DisableSignatureCheck(const char* pSigCheck)
{
	uint64_t* lpSigCheckPattern = FindPattern(GetModuleHandleA(NULL), pSigCheck);
	std::cout << "lpSigCheckPattern " << (lpSigCheckPattern ? "Found" : "FAILED") << "\n";
	if (!lpSigCheckPattern) return false;
	uint64_t hook_address = (uint64_t)lpSigCheckPattern;
	Patch(GetGameAddr(hook_address) - 0x14, (uint8_t)0xC3);
	Patch(GetGameAddr(hook_address) - 0x14 + 1, (uint32_t)0x90909090);
	return true;
}

bool DisableSignatureWarn(const char* pSigWarn)
{
	uint64_t* lpSigWarnPattern = FindPattern(GetModuleHandleA(NULL), pSigWarn);
	std::cout << "lpSigWarnPattern " << (lpSigWarnPattern ? "Found" : "FAILED") << "\n";
	if (!lpSigWarnPattern) return false;
	ConditionalJumpToJump((uint64_t)lpSigWarnPattern, 0xA);
	return true;
}

bool DisableChunkSigCheck(const char* pChunkSigCheck, const char* pChunkSigCheckFunc)
{
	uint64_t* lpChunkSigCheckPattern = FindPattern(GetModuleHandleA(NULL), pChunkSigCheck);
	uint64_t* lpChunkSigCheckFuncPattern = FindPattern(GetModuleHandleA(NULL), pChunkSigCheckFunc);
	std::cout << "lpChunkSigCheckPattern " << (lpChunkSigCheckPattern ? "Found" : "FAILED") << "\n";
	std::cout << "lpChunkSigCheckFuncPattern " << (lpChunkSigCheckFuncPattern ? "Found" : "FAILED") << "\n";
	if (!lpChunkSigCheckPattern || !lpChunkSigCheckFuncPattern) return false;
	Patch<uint32_t>(((uint64_t)lpChunkSigCheckPattern) + 0xF, ((uint64_t)lpChunkSigCheckFuncPattern) - (((uint64_t)lpChunkSigCheckPattern) + 0xE + 5));
	return true;
}

bool DisableTOCSigCheck(const char* pTOCCheck)
{
	uint64_t* lpTocSigCheckPattern = FindPattern(GetModuleHandleA(NULL), pTOCCheck);
	std::cout << "lpTocSigCheckPattern Found\n" << (lpTocSigCheckPattern ? "Found" : "FAILED") << "\n";
	if (!lpTocSigCheckPattern) return false;
	ConditionalJumpToJump((uint64_t)lpTocSigCheckPattern, 0x12);
	return true;
}