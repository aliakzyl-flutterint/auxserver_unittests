#include "AtfUtility.h"
#include "AtfPropertyPublisher.h"
#include "auxservercommon/StatusCheckServer.h"
#include "auxdbm/AuxDbmServerObject.h"

const char* Atf::AtfUtil::getClientIP(const CommServerConnection* conn, PString& ipAddrBuff)
{
	return "";
}
UINT32 Atf::AtfUtil::getAndSkipReqId(const CommMsgBody& body)
{
	return 0;
}

Atf::AtfPropertyPublisher::AtfPropertyPublisher()
{
}

// destructor
Atf::AtfPropertyPublisher::~AtfPropertyPublisher()
{
}

void Atf::AtfPropertyPublisher::setProperty(const char* propName, const Variant& propValue)
{ }

StatusServerPerformanceCounter::StatusServerPerformanceCounter()
	:statusServer(nullptr)
{
}

StatusServer& StatusServer::addCriticalComponent(CriticalPtr critical)
{
	return *this;
}

StatusServer& StatusServer::addCriticalComponent(const char* name)
{
	return *this;
}

StatusServer& StatusServer::setCriticalComponentStatus(const char* name, const char* status)
{
	return *this;
}

void Atf::AtfCommServerPublisher::publish(CommServerPublisherPool& pool, const char* name, bool autoFlushUpdate, bool supportCIPWA, Atf::AtfCommObjectImpl* obj)
{
}

void Atf::AtfCommServerPublisher::unpublish()
{
}

void Atf::AtfCommServerPublisher::postUpdate()
{
}

Atf::AtfCommServerPublisher::AtfCommServerPublisher(size_t jsonStringCompressThreshold_)
	: jsonStringCompressThreshold(jsonStringCompressThreshold_)
{
}

Atf::AtfCommServerPublisher::~AtfCommServerPublisher()
{
}

void AuxDbmPerformanceCounter::reset()
{ }

void AuxDbmPerformanceCounter::getPerformanceData(std::vector<PNameValue>& data)
{
}

void StatusServerPerformanceCounter::reset()
{
}

void StatusServerPerformanceCounter::getPerformanceData(std::vector<PNameValue>& data)
{
}

static CommServerNullGuardFactory nullGuardFactoryS;
StatusServer::StatusServer() :
	statusCheckConnFactory(nullGuardFactoryS)
{
}

void StatusServer::StatusCheckServerConnection::connected()
{
}

void StatusServer::StatusCheckServerConnection::closedOrDisconnected(int errCode, const char* errMsg)
{
}

void StatusServer::StatusCheckServerConnection::processMessage(UINT32 msgId, const CommMsgBody& body) //override
{
}

CommClientNullGuardFactory AuxTableAlertReporter::guard;
AuxTableAlertReporter::AuxTableAlertReporter(Atf::AtfCommObjectImpl* impl) :
	monitorConn(impl, guard),
	sendAlertServiceRunning(false),
	urgentEnabled(false)
{
}
AuxTableAlertReporter::MonitorGConnection::MonitorGConnection(
	Atf::AtfCommObjectImpl* impl, CommClientNullGuardFactory& guardFactory) : 
	Atf::AtfCommClientGConnection(impl, guardFactory, "Alter")
{ }

AuxTableAlertReporter::~AuxTableAlertReporter()
{
}

aux::GamingSiteGroup getSiteGroup(UINT32 hosts, UINT64 sites)
{
	return aux::GAMING_SITE_GROUP_UNDEFINED;
}

PString getAuxUserId(UINT16 hostId, UINT32 userIntId)
{
	return PString();
}

bool isInteger(const char* string)
{
	return false;
}

bool needToCheckGeoStatusForGamingSite(UINT32 siteId)
{
	return false;
}

UINT32 convertAuxHostIdToPokerStarsBrandId(UINT32 hostId)
{
	return 0;
}

UINT16 getBoId(UINT16 hostId)
{
	return hostId;
}

UINT16 getBoOfHosts(UINT32 hosts)
{
	return 0;
}

void getHostIdsOfBoId(UINT16 boId, vector<UINT16>& hostIds)
{
}

PString getClientPlatformDesc(UINT32 clientPlatfromId)
{
	return PString();
}

PString getVendorDesc(UINT32 vendorId)
{
	return PString();
}

bool isRemoteGameVendor(UINT32 vendorId)
{
	return false;
}

bool vendorNeedUserSuffixIfStuckSessionExist(UINT32 vendorId)
{
	return false;
}
const char* getSiteDesc(UINT32 siteId)
{
	return "";
}
const char* getHostDesc(UINT16 hostId)
{
	return "";
}
bool isPokerStarsBrand(int hostId)
{
	return false;
}
bool isForPokerStarsBrands(UINT32 hosts)
{
	return false;
}
bool isForGgn(UINT32 hosts)
{
	return false;
}
bool isValidAuxHost(int hostId)
{
	return false;
}
bool isValidAuxSite(UINT32 siteId)
{
	return false;
}
bool isValidAuxClientPlatform(UINT32 clientPlatformId)
{
	return false;
}

bool isSbgHost(UINT16 hostId)
{
	return false;
}

bool isPpbHost(UINT16 hostId)
{
	return false;
}

bool isFdHost(UINT16 hostId)
{
	return false;
}


bool parseSimpleGameManagementString(const PString& scopeString, set<UINT32>& values, PString& error)
{
	return false;
}

const char* generateSHA256Hash(const PString& token, PString& hashStr)
{
	return "";
}

DailyLocalScheduleTimeRanges::DailyLocalScheduleTimeRanges(const char* strLocalTimeRange_, const eTimeZone& localServerTimezone_)
{
}

bool DailyLocalScheduleTimeRanges::isValid()
{
	return false;
}

bool DailyLocalScheduleTimeRanges::isCurrentTimeInRange()
{
	return false;
}

bool isGermanyTable(UINT32 hosts, UINT64 sites)
{
	return false;
}

bool auxnoti::isRaceNotifyCategory(UINT16 type)
{
	return false;
}

bool isESLimitsControlBitSet(UINT32 boUserControlBits)
{
	return false;
}