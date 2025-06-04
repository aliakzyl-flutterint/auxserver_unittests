#include "auxjackpotserver/JackpotServerManager.h"

JackpotServerManager::JackpotServerManager(AuxJackpotServerObject* serverObject) :
	fxRateUpdateCount(0), activeTransSaved(false), serverObject(serverObject), reefLastActiveTransContainer(this)
{
}

JackpotServerManager::~JackpotServerManager()
{
}

void JackpotServerManager::ReefLastActiveTransContainer::getStateUpdateAndClear(std::vector< tuple<UINT64, CommMsgBody, AuxStateAccessor::StateOperation> >& states)
{ }

void JackpotServerManager::ReefLastActiveTransContainer::reconstruct(const std::vector< tuple<UINT64, CommMsgBody> >& states)
{ }

void JackpotServerManager::initJackpotData()
{ }

void JackpotServerManager::resumedInitJackpotData(const CommMsgBody& body)
{ }

UINT64 JackpotServerManager::getXRate(const PString& fromCurrency, const PString& toCurrency) const
{
	return 0;
}

void JackpotServerManager::getBetScale(const JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_GET_BET_SCALE& request, JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_A_GET_BET_SCALE& reply)
{

}

void JackpotServerManager::getSimpleJPSettings(const JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_GET_SIMPLE_JP_SETTINGS& request, JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_A_GET_SIMPLE_JP_SETTINGS& reply)
{
}

void JackpotServerManager::addOrUpdateJackpots(JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_CREATE_JACKPOTS& jackpots, UINT32 sourceConnId, UINT32 sourceReqId, JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_A_CREATE_JACKPOTS& reply)
{
}

void JackpotServerManager::getAllJackpots(std::vector<JackpotServer::Jackpot>& jackpots)
{ }

void JackpotServerManager::disableOrEnable(UINT32 sourceConnId, UINT32 sourceReqId, const JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_DISABLE_OR_ENABLE& request, JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_A_DISABLE_OR_ENABLE& reply)
{ }

void JackpotServerManager::getXrates(vector<aux::CurrencyRate>& rates)
{ }

INT16 JackpotServerManager::deposit(const JackpotServer::JackpotDepositRequest& request, JackpotServer::JackpotDepositResponseArray& response, PString& errStr, bool& isDuplicate)
{
	return 0;
}

INT16 JackpotServerManager::withdraw(const JackpotServer::JackpotWithdrawRequest& request, aux::JackpotWithdrawResponse& response, PString& errStr, bool& isDuplicate)
{
	return 0;
}

INT16 JackpotServerManager::sharedWithdraw(const JackpotServer::JackpotSharedWithdrawRequest& request, JackpotServer::JackpotSharedWithdrawResponse& response, PString& errStr, bool& isDuplicate)
{
	return 0;
}

INT16 JackpotServerManager::publishPendingPayouts(UINT64 transactionId, PString& errStr)
{
	return 0;
}

void JackpotServerManager::publishPendingPayouts(UINT32 timeoutInSec)
{ }

void JackpotServerManager::processHandResult(const JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_HAND_RESULT& request, JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_A_HAND_RESULT& reply)
{ }

void JackpotServerManager::getPoolValue(const JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_GET_POOL_VALUE& request, JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_A_GET_POOL_VALUE& reply)
{ }

INT16 JackpotServerManager::updateFeed(JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_FEED_UPDATE& request, PString& errStr, UINT32& jpKey)
{
	return 0;
}

INT16 JackpotServerManager::deleteExpiredTransactions(const JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_Q_DEL_EXPIRED_TRANSACTION& request, PString& errStr)
{
	return 0;
}

INT16 JackpotServerManager::addOrUpdateFXRates(const IS::JackpotServer::Protocol_AUX_IS_MSG_A_CONVRATES_TO_USD& msg, UINT32 updateId, PString& errStr)
{
	return 0;
}

void JackpotServerManager::setReplenishmentLogStmtParams(JackpotDbm::InsertJPReplenishmentLog& replenishmentLog, UINT32 jpKey, INT64 txId, const SrvTime& replenishTime, INT64 poolValue, INT64 resetPoolValue, INT64 payAmount, INT64 replenishment, INT64 newPoolValue, INT64 newResetPoolValue)
{ }

bool JackpotServerManager::fxRateLoaded() const
{
	return false;
}

void JackpotServerManager::saveActiveTrans()
{ }

void JackpotServerManager::expireActiveTrans(int ttlInSecond)
{ }

void JackpotServerManager::insertJpStatusReports(const CommSrvTime& reportTime, UINT64 sites, JackpotServer::Protocol_AUX_JACKPOT_SERVER_MSG_A_INSERT_JPSTATUS_REPORT& reply)
{ }

void JackpotServerManager::tableClosed(vector<UINT64> tableIds)
{
}

void JackpotServerManager::readIniFileJackpotSettings(PIniFile& iniFile)
{ }

void JackpotServerManager::reefSyncActiveTransactions()
{ }