#include "AtfUniSeqId.h"
#include "AtfCommPlayerConns.h"
#include "auxcommon/UniqueSeqId.h"
#include "auxservercommon/TableScriptParser2.h"
#include "auxservercommon/StatusCheckServer.h"
#include "auxservercommon/AuxTableAlertReporter.h"

Atf::AbstractUniqueSequenceNumber::AbstractUniqueSequenceNumber(const char* category)
{ }

Atf::AbstractUniqueSequenceNumber::~AbstractUniqueSequenceNumber()
{
}

UINT64 Atf::AbstractUniqueSequenceNumber::getNextSeqId()
{
	return 0;
}

bool Atf::AbstractUniqueSequenceNumber::hasMoreSeqIds() const
{
	return false;
}

void Atf::AbstractUniqueSequenceNumber::init(AtfCommObjectImpl* obj_, AtfCommClientGConnection* conn_)
{
}

void UniqueSequenceNumber::composeDbmRequestMsg(const char* category, UINT32 reqSize, UINT32& reqMsgIdOut, CommMsgBody& reqBodyOut, UINT32& replyMsgIdOut)
{
}

INT16 UniqueSequenceNumber::parseDbmReplyMsg(UINT32 replyMsgId, const CommMsgBody& body, std::vector< std::pair<UINT64, UINT64> >& chunksOut, PString& errStrOut)
{
	return 0;
}

void UniqueSequenceNumber::init(Atf::AtfCommObjectImpl* obj_, Atf::AtfCommClientGConnection* conn_)
{
}

void UniqueSequenceNumber::init(Atf::AtfCommObjectImpl* obj_, Atf::AtfCommClientGConnection* conn_, UINT32 blockModeThreshold, UINT32 preFetchThreshold, UINT32 fetchSize)
{ }

void TableScriptParser2::getJackpotKeys(const vector< aux::P_PNameValue >& props, vector<UINT32>& jpKeys)
{
}

void TableScriptParser2::loadScript(const PString& script, const PString& targetEnvironment)
{
}

std::vector<aux::P_PNameValue> TableScriptParser2::parseScript(const aux::TableTemplateDef& tableTemplateDef,
	const PIniFile::Section* tableParams, aux::TableTypeDef& tableTypeDO, UINT32 sectionindex)
{
	return std::vector<aux::P_PNameValue>();
}

void TableScriptParser2::parseTemplateScript(const PIniFile::Section& templateSection, aux::TableTemplateDef& templateDO, const std::vector<aux::XclGameVariant>& gameVariants)
{ }

void TableScriptParser2::parseTemplateGlobalScript(PIniFile& scriptFile, std::set<PString, PStringCmp>& gameDevelopers, std::set<PString, PStringCmp>& biGameSegments)
{ }

void TableScriptParser2::parseJackpotScript(const PIniFile::Section& jackpotSection, aux::JpSettings& jpSettingsDO)
{ }

void TableScriptParser2::parseVendorScript(const PIniFile::Section& templateSection, aux::XclVendor& xclVendorDO)
{ }

void TableScriptParser2::parseGameTypeScript(const PIniFile::Section& templateSection, aux::XclGame& xclGameDO)
{ }

void TableScriptParser2::parseGameVariantScript(const PIniFile::Section& templateSection, const std::set<PString, PStringCmp>& gameDevelopers, const std::set<PString, PStringCmp>& biGameSegments, aux::XclGameVariant& xclGameVariantDO)
{ }

std::string TableScriptParser2::getPropertyFromDefaults(const PIniFile::Section* sec, std::string key) const
{
	return "";
}

void TableScriptParser2::validatePPBGameGenericSettings(UINT32 hosts, UINT64 sites, const PString& currency)
{ }

void TableScriptParser2::validateFDGameSettings(const aux::TableTypeDef& tableTypeDO)
{ }

const char* const Atf::AtfCommPlayerOrCipwaConnection::cipwaConnTyeSuffix = "_cipwa";

void myPLogAlways_internal(_In_z_ _Printf_format_string_ const char* format, ...)
{
}

void Atf::AtfCommObjectImpl::_exit()
{
}

UINT32 Atf::AtfCommObjectImpl::getNumberOfRunningServices() const
{
	return 0;
}

UINT32 Atf::AtfCommObjectImpl::getNumberOfRunsTooLongServices() const
{
	return 0;
}

void Atf::AtfCommObjectImpl::reloadHeLoggerSettings()
{
}

void Atf::AtfCommObjectImpl::registerPerformanceCounter(
	const ServerStartParams& params, const PString& iniFileName,
	PerformanceCounter* counter,
	INT32 reportIntervalInSec /*= 0 /* use default report interval */, 
	OlapServerReporter* olapServerReporter /*= nullptr*/, 
	const char* logStationNameFromDispatcher /*= nullptr*/,
	const char* atfMsgTickerMonitoringNamePrefix /*= ""*/)
{ }

void Atf::AtfCommObjectImpl::addMorePerformanceCounter(PerformanceCounter* counter)
{ }

void Atf::AtfCommObjectImpl::setAtfPanopticLogger(IPanopticLogger* panopticLogger, const char* objectTag)
{
}

void StatusServerPerformanceCounter::init(StatusServer* statusServer_)
{
}

StatusServer& StatusServer::init(CommServerConnectionPool& srvpool)
{
	return *this;
}

void AuxTableAlertReporter::init(UINT64 tableId, const PString& address, const PString& instance)
{ }

void AuxTableAlertReporter::sendAlert(const PString& alertType, const PString& data, const PString& details, bool urgent /*= false*/, bool log /*= true*/)
{
}