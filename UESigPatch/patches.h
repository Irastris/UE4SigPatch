#include "pch.h"

#include "memorymgr.h"
#include "patterns.h"

bool DisableSignatureCheck(const char* pSigCheck, uint32_t subtract_offset);
bool DisableSignatureWarn(const char* pSigWarn);
bool DisableChunkSigCheck(const char* pChunkSigCheck, const char* pChunkSigCheckFunc);
bool DisableTOCSigCheck(const char* pTOCCheck, uint32_t offset);
bool DisableTOCCompare(const char* pTOCCompare);
bool DisablePakTOCCheck(const char* pPakTOCCheck);
bool DisablePakTOCCheckAlt(const char* pPakTOCCheck);