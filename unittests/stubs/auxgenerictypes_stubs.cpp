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

BYTE getHostIdFromAuxUserId(const char* auxUserId)
{
    return 0;
}

bool isSimulatedHost(UINT16 hostId)
{
    return true;
}

bool isGermany(UINT32 hostId, UINT32 siteId)
{
    return false;
}

PString getBODesc(UINT16 boId)
{
    return "";
}

bool isForPpb(UINT32 hosts)
{
    return false;
}

bool isForFd(UINT32 hosts)
{
    return false;
}

bool isUsSiteMask(UINT64 siteMask)
{
    return false;
}

bool comparePNameValue(const aux::P_PNameValue& p1, const aux::P_PNameValue& p2)
{
    return false;
}

PString critialComponentName(PString prefix, PString instance, PString address, PString type)
{
    return "";
}
