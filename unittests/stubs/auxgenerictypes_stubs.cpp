#include "auxcommon/auxgenerictypes.h"
bool getHostIdAndUserIntIdFromAuxUserIdRg(const char* auxUserId, BYTE& hostId, UINT32& userIntId)
{
    return false;
}

UINT32 getUserIntIdFromAuxUserId(const char* auxUserId)
{
    return 0;
}

UINT32 convertAuxSiteMaskToPokerStarsLicenseMask(UINT64 auxSiteIds) {
    return 0;
}

PBitmask convertAuxSitesToPokerStarsLicenseBitMask(UINT64 auxSiteIds)
{
    return PBitmask::zero;
}

PString getMaskedUserName(const PString& userName)
{
    PString ret;
    return ret;
}

const char* generateRandomToken(PString& randomToken)
{
    return "";
}