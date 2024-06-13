#include "pch.h"

#include "memorymgr.h"
#include "patterns.h"

bool DisableSignatureCheck(const char* pSigCheck);
bool DisableSignatureWarn(const char* pSigWarn);
bool DisableChunkSigCheck(const char* pChunkSigCheck, const char* pChunkSigCheckFunc);
bool DisableTOCSigCheck(const char* pTOCCheck, uint32_t offset);
bool DisableTOCCompare(const char* pTOCCompare);
