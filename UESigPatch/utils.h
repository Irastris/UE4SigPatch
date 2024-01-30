#pragma once
#include <chrono>
#include <map>
#include <string>
#include "pch.h"
#include "memorymgr.h"
#include "patterns.h"

#define			RVAtoLP( base, offset )		((PBYTE)base + offset)
#define			FuncMap						std::map<std::string, ULONGLONG>
#define			LibMap						std::map<std::string, FuncMap>
typedef			__int64						int64;

int64			GetGameEntryPoint();
int64			GetGameAddr(__int64 addr);
std::string		GetProcessName();
std::string		GetFileName(std::string filename);
uint64_t*		FindPattern(void* handle, std::string_view bytes);
uint64_t		HookPattern(std::string Pattern, const char* PatternName, void* HookProc, int64_t PatternOffset = 0, PatchTypeEnum PatchType = PatchTypeEnum::PATCH_CALL, uint64_t PrePat = NULL, uint64_t* Entry = nullptr);
uint64_t		GetDestinationFromOpCode(uint64_t Caller, uint64_t Offset = 1, uint64_t FuncLen = 5, uint16_t size = 4);
int32_t			GetOffsetFromOpCode(uint64_t Caller, uint64_t Offset, uint16_t size);
void			ConditionalJumpToJump(uint64_t HookAddress, uint32_t Offset);
void			ConditionalJumpToJump(uint64_t HookAddress);