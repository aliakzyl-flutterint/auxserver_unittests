#include "AuxLobbyServerObject.h"

void AuxFailedSeatConfirmStats::onFailedSeatConfirm(const UINT16 vendorId, const UINT32 clientPlatformId, const UINT16 hostId, const UINT32 siteId)
{
}

LobbyPerformanceCounter::LobbyPerformanceCounter()
{
}

LobbyPerformanceCounter::~LobbyPerformanceCounter()
{
}

void LobbyPerformanceCounter::init(AuxLobbyServerObject* serverObject_)
{
}

void LobbyPerformanceCounter::addLoginMsec(BYTE hostId, UINT32 t)
{
}

void LobbyBlackjack::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}

void LobbyBlackjack::loadSpeedConfigFromIniFile(const PIniFile::Section* section, vector<Atf::MsgBodyWithJSONPtr>& configsOut)
{
}

void LobbyRoulette::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}

void LobbyRoulette::loadSpeedConfigFromIniFile(const PIniFile::Section* section, vector<Atf::MsgBodyWithJSONPtr>& configsOut)
{
}

void LobbyDBRoulette::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}

void LobbyDBRoulette::loadSpeedConfigFromIniFile(const PIniFile::Section* section, vector<Atf::MsgBodyWithJSONPtr>& configsOut)
{
}

void LobbyHUHoldem::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}

void LobbyHUHoldem::loadSpeedConfigFromIniFile(const PIniFile::Section* section, vector<Atf::MsgBodyWithJSONPtr>& configsOut)
{
}

void LobbyCommunityBaccarat::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}

void LobbyCommunityBaccarat::loadSpeedConfigFromIniFile(const PIniFile::Section* section, vector<Atf::MsgBodyWithJSONPtr>& configsOut)
{
}

void LobbyBaccarat::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}
void LobbyBaccarat::loadSpeedConfigFromIniFile(const PIniFile::Section* section, vector<Atf::MsgBodyWithJSONPtr>& configsOut)
{
}

void LobbyThreeCardPoker::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}

void LobbyThreeCardPoker::loadSpeedConfigFromIniFile(const PIniFile::Section* section, vector<Atf::MsgBodyWithJSONPtr>& configsOut)
{
}

void LobbySlots::loadGameConfig(const vector< aux::P_PNameValue >& props)
{
}

bool LobbyICGame::loadGameConfig(const vector< aux::P_PNameValue >& props, const PString& testSetting)
{
	return false;
}

void AuxLobbyStaticConfig::StaticConnect::load(const AuxEslResolver* esl)
{
}

void AuxLobbyStaticConfig::StaticConnect::load(const auxcfg::IniSection& section)
{
}

void AuxLobbyStaticConfig::StaticConnect::log()
{
}

void AuxLobbyDynamicConfig::DynamicConnect::load(const AuxEslResolver* esl)
{
}

void AuxLobbyDynamicConfig::DynamicConnect::load(const auxcfg::IniSection& section)
{
}

void AuxLobbyDynamicConfig::DynamicConnect::log()
{
}

void AuxLobbyDynamicConfig::TableDispathRules::load(const auxcfg::IniSection& section)
{
}

void AuxLobbyDynamicConfig::SpinDelayConfig::load(const auxcfg::IniSection& section)
{
}

const void AuxLobbyDynamicConfig::SpinDelayConfig::getTableSpinDelaySettings(AuxLobbyTableTypePtr tableType, std::vector<aux::SpinDelayTime>& tableSpinDelaySettings)
{
}

void AuxLobbyDynamicConfig::DisabledSpinFeaturesConfig::load(const auxcfg::IniSection& section)
{
}

const void AuxLobbyDynamicConfig::DisabledSpinFeaturesConfig::getTableDisabledSpinFeaturesSettings(
	UINT64 sites, std::vector<aux::DisabledSpinFeatures>& tableDisabledSpinFeaturesSettings)
{
}
void AuxLobbyDynamicConfig::GermanyBreakConfig::load(const auxcfg::IniSection& section)
{
}

void AuxLobbyDynamicConfig::MaxTotalBetPerHandConfig::loadFromIniConfig(const PIniFile::Section* dynamicSection)
{
}

INT32 AuxLobbyDynamicConfig::MaxTotalBetPerHandConfig::getMaxTotalBetPerHand(UINT32 hosts, UINT32 sites, INT32 age, UINT16 gameType) const
{
	return 0;
}

void AuxLobbyDynamicConfig::Prizegame::load(const auxcfg::IniSection& section)
{
}

void HostSystemInfo::convertToReefObject(reef::objs::HostSystemStatus& s)
{
}

void AuxLobbyServerObject::resetHostSystemStatusInReef()
{
}

void AuxLobbyServerObject::updateHostSystemInfoWhenLobbyRecoveryStart()
{
}

void AuxLobbyServerObject::initCriticalComponents()
{
}

void LobbyPerformanceCounter::getPerformanceData(std::vector<PNameValue>& data, std::vector<PerfDataWithTags>& dataWithTags)
{
}

AuxVendorPlayersStats::AuxVendorPlayersStats()
{
}

void LobbyPerformanceCounter::reset()
{
}

LobbyEtc::cli::AuxHandHistoryMetadata::AuxHandHistoryMetadata()
{
}

void LobbyEtc::cli::AuxHandHistoryMetadata::clear()
{
}

bool LobbyEtc::cli::AuxHandHistoryMetadata::equals(const AuxHandHistoryMetadata& _o) const
{
	return false;
}

const char* LobbyEtc::cli::AuxHandHistoryMetadata::toTraceString(PString& _buf) const
{
	return "";
}

const char* LobbyEtc::cli::AuxHandHistoryMetadata::toXmlString(const char* _element, PString& _buf) const
{
	return "";
}

bool LobbyEtc::cli::AuxHandHistoryMetadata::fromXmlString(const PString& _str)
{
	return false;
}

void LobbyEtc::cli::AuxHandHistoryMetadata::composeMsg(CommMsgBody& _msg, bool _ignoreJSON) const
{
}

void LobbyEtc::cli::AuxHandHistoryMetadata::parseMsg(CommMsgParser& _parser)
{
}

const char* LobbyEtc::cli::AuxHandHistoryMetadata::toJSONString(PString& _buf) const
{
	return "";
}

void LobbyEtc::cli::AuxHandHistoryMetadata::fromJSONString(const PString& _jsonString)
{
}

void LobbyEtc::cli::AuxHandHistoryMetadata::validateJSONString(
	const PString& _jsonString, const AtfMsgChecker* _checker, const char* _descr, PString& _fieldsWithUnparsedContent)
{
}

void LobbyEtc::cli::AuxHandHistoryMetadata::validateMsg(
	CommMsgParser& _parser, const AtfMsgChecker* _checker, const char* _descr, PString& _fieldsWithUnparsedContent)
{
}