#include "pch.h"

#include "patches.h"
#include "utils.h"

using namespace Memory::VP;

bool DisableSignatureCheck(const char* pSigCheck, uint32_t subtract_offset)
{
	uint64_t* lpSigCheckPattern = FindPattern(GetModuleHandleA(NULL), pSigCheck);
	std::cout << "lpSigCheckPattern " << (lpSigCheckPattern ? "FOUND" : "NOT FOUND") << "\n";
	if (!lpSigCheckPattern) return false;
	uint64_t hook_address = (uint64_t)lpSigCheckPattern;
	Patch<uint8_t>(GetGameAddr(hook_address) - subtract_offset, 0xC3);
	Patch<uint32_t>(GetGameAddr(hook_address) - subtract_offset + 1, 0x90909090);
	return true;
}

bool DisableSignatureWarn(const char* pSigWarn)
{
	uint64_t* lpSigWarnPattern = FindPattern(GetModuleHandleA(NULL), pSigWarn);
	std::cout << "lpSigWarnPattern " << (lpSigWarnPattern ? "FOUND" : "NOT FOUND") << "\n";
	if (!lpSigWarnPattern) return false;
	ConditionalJumpToJump((uint64_t)lpSigWarnPattern, 0xA);
	return true;
}

bool DisableChunkSigCheck(const char* pChunkSigCheck, const char* pChunkSigCheckFunc)
{
	uint64_t* lpChunkSigCheckPattern = FindPattern(GetModuleHandleA(NULL), pChunkSigCheck);
	uint64_t* lpChunkSigCheckFuncPattern = FindPattern(GetModuleHandleA(NULL), pChunkSigCheckFunc);
	std::cout << "lpChunkSigCheckPattern " << (lpChunkSigCheckPattern ? "FOUND" : "NOT FOUND") << "\n";
	std::cout << "lpChunkSigCheckFuncPattern " << (lpChunkSigCheckFuncPattern ? "FOUND" : "NOT FOUND") << "\n";
	if (!lpChunkSigCheckPattern || !lpChunkSigCheckFuncPattern) return false;
	Patch<uint32_t>(((uint64_t)lpChunkSigCheckPattern) + 0xF, ((uint64_t)lpChunkSigCheckFuncPattern) - (((uint64_t)lpChunkSigCheckPattern) + 0xE + 5));
	return true;
}

bool DisableTOCSigCheck(const char* pTOCCheck, uint32_t offset)
{
	uint64_t* lpTocSigCheckPattern = FindPattern(GetModuleHandleA(NULL), pTOCCheck);
	std::cout << "lpTocSigCheckPattern " << (lpTocSigCheckPattern ? "FOUND" : "NOT FOUND") << "\n";
	if (!lpTocSigCheckPattern) return false;
	ConditionalJumpToJump((uint64_t)lpTocSigCheckPattern, offset);
	return true;
}

bool DisableTOCCompare(const char* pTOCCompare)
{
	uint64_t* lpTOCCompare = FindPattern(GetModuleHandleA(NULL), pTOCCompare);
	std::cout << "lpTOCCompare " << (lpTOCCompare ? "FOUND" : "NOT FOUND") << "\n";
	if (!lpTOCCompare) return false;
	Patch<uint16_t>((uint64_t)lpTOCCompare, 0x3B45);
	Patch<uint8_t>((uint64_t)lpTOCCompare + 0x2, 0xE4);
	Patch<uint32_t>((uint64_t)lpTOCCompare + 0x3, 0x90909090);
	return true;
}

bool DisablePakTOCCheck(const char* pPakTOCCheck)
{
	uint64_t* lpPakTocCheckPattern = FindPattern(GetModuleHandleA(NULL), pPakTOCCheck);
	std::cout << "lpPakTocCheckPattern " << (lpPakTocCheckPattern ? "FOUND" : "NOT FOUND") << "\n";
	if (!lpPakTocCheckPattern) return false;
	uint64_t hook_address = (uint64_t)lpPakTocCheckPattern;
	Patch<uint8_t>(hook_address + 0x12, 0xEB); // je to short jump
	return true;
}

bool DisablePakTOCCheckAlt(const char* pPakTOCCheck)
{
	uint64_t* lpPakTocCheckPattern = FindPattern(GetModuleHandleA(NULL), pPakTOCCheck);
	std::cout << "lpPakTocCheckPattern " << (lpPakTocCheckPattern ? "FOUND" : "NOT FOUND") << "\n";
	if (!lpPakTocCheckPattern) return false;
	uint64_t hook_address = (uint64_t)lpPakTocCheckPattern;
	Patch<uint8_t>(hook_address + 0x22, 0x38); // test to cmp
	return true;
}