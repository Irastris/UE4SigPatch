#include <map>
#include "pch.h"
#include "utils.h"

using namespace Memory::VP;
using namespace hook;

int64 GetGameEntryPoint()
{
	static __int64 addr = reinterpret_cast<__int64>(GetModuleHandle(nullptr));
	return addr;
}

int64 GetGameAddr(__int64 addr)
{
	int64 Entry = GetGameEntryPoint();
	return addr > Entry - 40000000 ? addr : Entry + addr;
	if (addr > Entry)
		return addr;
	if (addr > Entry - 40000000)
		return addr;
	return Entry + addr;
}

// Functional Utilities

std::string GetFileName(std::string filename)
{
	std::string basename;
	size_t pos = filename.find_last_of("/\\"); // Or
	if (pos != -1)
	{
		basename = filename.substr(pos + 1);
		return basename;
	}
	return filename;
}

std::string GetProcessName()
{
	CHAR fileName[MAX_PATH + 1];
	DWORD chars = GetModuleFileNameA(NULL, fileName, MAX_PATH + 1);
	if (chars)
	{
		return GetFileName(std::string(fileName));
	}
	return "";
}


uint64_t* FindPattern(void* handle, std::string_view bytes)
{
	hook::pattern pCamPattern = hook::make_module_pattern(handle, bytes); // Make pattern external
	if (!pCamPattern.count_hint(1).empty())
	{
		return pCamPattern.get(0).get<uint64_t>(0);
	}
	return nullptr;
}

uint64_t HookPattern(std::string Pattern, const char* PatternName, void* HookProc, int64_t PatternOffset, PatchTypeEnum PatchType, uint64_t PrePat, uint64_t* Entry)
{
	uint64_t lpPattern;
	if (PrePat)
	{
		lpPattern = PrePat;
	}
	else
	{
		lpPattern = (uint64_t)FindPattern(GetModuleHandleA(NULL), Pattern);
		if (lpPattern == NULL) return lpPattern;
	}

	if (Entry != NULL)
	{
		uint64_t FuncEntry = GetDestinationFromOpCode(lpPattern + PatternOffset); // Already relative to game address so GetGameAddr is unnecessary
		*Entry = FuncEntry;
	}

	uint64_t hook_address = lpPattern + PatternOffset;
	InjectHook(hook_address, HookProc, PatchType);

	return lpPattern;
}

void ConditionalJumpToJump(uint64_t HookAddress)
{
	uint64_t GameAddr = GetGameAddr(HookAddress);
	uint32_t JumpAddress = GetOffsetFromOpCode(GameAddr, 2, 4);
	Patch(GameAddr, (uint8_t)0xE9); // jmp
	Patch(GameAddr + 1, JumpAddress + 1); // jmp address+1 cuz we reduced function size by 1
	Patch(GameAddr + 5, (uint8_t)0x90); // nop
}

void ConditionalJumpToJump(uint64_t HookAddress, uint32_t Offset)
{
	HookAddress += Offset;
	uint64_t GameAddr = GetGameAddr(HookAddress);
	uint32_t JumpAddress = GetOffsetFromOpCode(GameAddr, 2, 4);
	Patch<uint8_t>(GameAddr, 0xE9); // jmp
	Patch<uint32_t>(GameAddr + 1, JumpAddress + 1); // jmp address+1 cuz we reduced function size by 1
	Patch<uint8_t>(GameAddr + 5, 0x90); // nop
}

/**
	Get Relative Offset From OpCode. Caller is the address to call / jmp / jne ...etc, Offset is the size of the opcode to the address, size is the size of the address.
	Example, call MK12.exe+21CDA30 from MK12.exe+3855356 becomes Function(143855356, 1, 4) since Call is E8 * * * * where * are the relative jump address.

	 * Get the relative offset from an opcode.
	 *
	 * @param Caller The address of the jump / call.
	 * @param Offset The offset to add to the caller to reach the address. It is 1 for jmp / call, 2 for je, jne, jg... etc since jmp is E9 Address.
	 * @param Size The size of the address, usually 4 for near jumps, 8 for long jumps.
	 * @return The calculated offset.
*/
int32_t GetOffsetFromOpCode(uint64_t Caller, uint64_t Offset, uint16_t Size)
{
	int32_t offset = 0;
	memcpy(&offset, (uint64_t*)(Caller + Offset), Size);
	return offset;
}


/**
 * Calculate the destination address from an opcode call.
 * Get relative offset and then adds it to address to get the entry of the called function, or destination jump address.
 *
 * @param Caller The address of the opcode call.
 * @param Offset The offset to add to the caller to reach the address in the opcode. Example, 1 for jmp, 2 for je.
 * @param FuncLen The length of the function to be added to the RIP register.
 * @param Size The size of the address.
 * @return The calculated destination address.
 *
 * @todo offset should allow int64_t in cases where Size is > 4 so negatives are handled correctly.
 */
uint64_t GetDestinationFromOpCode(uint64_t Caller, uint64_t Offset, uint64_t FuncLen, uint16_t Size)
{
	int32_t offset = GetOffsetFromOpCode(Caller, Offset, Size);
	return uint64_t(Caller + offset) + FuncLen;
}