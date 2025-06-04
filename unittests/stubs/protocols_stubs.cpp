#include "msgchecker/MsgChecker.h"
#include "Panoptic/panoptic_atf_thin.h"
#include "Panoptic/PanopticLogger.h"
#include "passwdencrypt.h"


bool MsgChecker::checkLimitRaw(INT64 value, const char* fieldKey, bool fromATF, const char* file, INT32 line) const
{
	return false;
}

bool MsgChecker::isEligible(const char* msgName) const
{
	return false;
}

void MsgChecker::dynamicInit(const char* initialDir, const char* limitsFileName, const PIniFile& iniFile, const char* iniSectionName, bool ignoredIfLimitsFileNotExists)
{
}

void MsgChecker::compose(CommMsgBody& msg) const
{}

PanopticThin::PanopticBridgeServer::Metrics::Metrics()
{}

PanopticThin::PanopticBridgeServer::Events::Events()
{}

bool PanopticLogger::init(CommClientConnectionPool& cliPool, const PIniFile& ini, const bool connSettingsReadFromESL/*=false*/, const ConnectionSettingsManager* connSettMgr/*=nullptr*/)
{
	return false;
}

CommClientNullGuardFactory			PanopticLogger::guardFactoryClient;

void PanopticLogger::addMetric(const PString& measurement, const PStringMap<PString>& tags, time_t ts, const PString& value)
{}

UINT32 PanopticLogger::postMetrics(CommClientGConnection::AsyncCall* call)
{
	return 0;
}

void PanopticLogger::prepareEvent(PanopticThin::PanopticBridgeServer::Event& e, const PString& eventType, const PStringMap<PString>& tags, time_t ts, const PString& value)
{
}

void PanopticLogger::addEvent(const PString& eventType, const PStringMap<PString>& tags, time_t ts, const PString& value)
{
}

UINT32 PanopticLogger::postEvents(CommClientGConnection::AsyncCall* call)
{
	return 0;
}

UINT32 PanopticLogger::postAll(CommClientGConnection::AsyncCall* call)
{
	return 0;
}

bool PasswdEncryptDecrypt::decrypt(const char* encryptedPasswd, PString& clearPasswd)
{
	return false;
}