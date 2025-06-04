#ifndef MainDbmManager_mock_h__
#define MainDbmManager_mock_h__


#include "commlib.h"
#include "../../protocols/dbcommon_mock.h"
#include "../../auxservercommon/auxdbmcommon_mock.h"
#include "../../auxcommon/auxdbcommon_mock.h"
#include "../../../auxiliary/auxprotocols/MainDbmProtocols.h"
#include "../../BaseCollectionOfInstances.h"
#include <gmock/gmock.h>


typedef std::map<PString, aux::TableTypeDef, PStringCmp> TableTypeDefsMapByRefName;

class AuxDbmServerObject;

struct lessGameStatusChange
{
	bool operator()(const aux::GameStatusChange& bt1, const aux::GameStatusChange& bt2) const
	{
		return std::tie(bt1.gameType, bt1.variantType, bt1.action, bt1.boId, bt1.siteId, bt1.updateTime) <
			std::tie(bt2.gameType, bt2.variantType, bt2.action, bt2.boId, bt2.siteId, bt2.updateTime);
	}
};

class MainDbmManager : public AuxDatabaseManagerCommon, public BaseCollectionOfInstances<MainDbmManager>
{
public:
	MOCK_METHOD(INT16, getTableNames, (std::vector<aux::NamesDef> &names, PString &sqlErr));
	MOCK_METHOD(INT16, getXcTableNames, (std::vector<aux::XcTableNamesDef> &names, PString &sqlErr));
	MOCK_METHOD(INT16, createTableTemplates, (const CommSrvTime &createTime, std::vector<aux::TableTemplateDef>& templates, std::vector<aux::TableTemplateDef>& templatesAdded, std::vector<aux::TableTemplateDef>& templatesObsoleted, std::vector<aux::XclGame> & xclGames,const  std::vector<aux::XclGameVariant> &xclGameVariants, std::vector<aux::XclVendor> &xclVendors, PString& sqlErr));
	MOCK_METHOD(INT16, updateZoneXclData, (const CommSrvTime &createTime, std::vector<aux::XclGame> & xclGames, const  std::vector<aux::XclGameVariant> &xclGameVariants, std::vector<aux::XclVendor> &xclVendors, PString& sqlErr));
	MOCK_METHOD(INT16, getTableTemplates, (std::vector<PString> &templateRefNames, std::vector<aux::TableTemplateDef>& templates, PString& sqlErr));
	MOCK_METHOD(INT16, getTableTemplate, (UINT32 templateId, aux::TableTemplateDef &templateDO, PString& sqlErr));
	MOCK_METHOD(INT16, createTableTypes, (const CommSrvTime &createTime, std::vector<aux::TableTypeDef> &tableTypes, std::vector<aux::TableTypeDef> &tableTypesAdded,  std::vector<aux::TableTypeDef> &tableTypesObsoleted, PString& sqlErr));
	MOCK_METHOD(INT16, getTableType, (UINT32 tableTypeId, aux::TableTypeDef &tableType, PString& sqlErr));
	MOCK_METHOD(INT16, createTables, (std::vector<aux::TableDef> &tables, const CommSrvTime &createTime, PString& sqlErr));
	MOCK_METHOD(INT16, closeTables_impl, (std::vector<UINT64> &tableIds, const CommSrvTime &closeTime, bool& isClosed, PString& sqlErr, bool isCleanup));
	INT16 closeTables(std::vector<UINT64>& tableIds, const CommSrvTime& closeTime, bool& isClosed, PString& sqlErr, bool isCleanup = false)
	{
		return closeTables_impl(tableIds, closeTime, isClosed, sqlErr, isCleanup);
	}
	MOCK_METHOD(INT16, getTables, (std::vector<aux::TableDef> &tables, PString& sqlErr));
	MOCK_METHOD(INT16, getPassivatedTables, (std::vector<aux::TableDef> &tables, PString& sqlErr));
	MOCK_METHOD(INT16, getInUseTableTypes_impl, (std::vector<aux::TableTypeDef>& tableTypes, PString& sqlErr, bool* isLastRecordsPtr, UINT32 beginTableTypeId, UINT32 maxReturnSize));
	INT16 getInUseTableTypes(std::vector<aux::TableTypeDef>& tableTypes, PString& sqlErr, bool* isLastRecordsPtr = nullptr, UINT32 beginTableTypeId = 0, UINT32 maxReturnSize = UINT32_MAX)
	{
		return getInUseTableTypes_impl(tableTypes, sqlErr, isLastRecordsPtr, beginTableTypeId, maxReturnSize);
	}
	INT16 getInUseTableTypes_blablabla(std::vector<aux::TableTypeDef>& tableTypes, PString& sqlErr, bool* isLastRecordsPtr = nullptr, UINT32 beginTableTypeId = 0, UINT32 maxReturnSize = UINT32_MAX)
	{
		return 0;
	}
	MOCK_METHOD(INT16, getInterruptedGameIdByRgToken, (UINT32 userIntId, UINT16 hostId, const PString &rgToken, UINT64 &ufgId, PString &sqlErr ));
	MOCK_METHOD(INT16, saveInterruptedGames, (aux::InterruptedGameDef &interruptedGame, PString &sqlErr));
	MOCK_METHOD(INT16, getInterruptedGames, (UINT32 userIntId, const vector<UINT16>& hostIds, std::vector<aux::InterruptedGameDef> &interruptedGames, PString &sqlErr));
	MOCK_METHOD(INT16, getInterruptedGame, (UINT64 gameSessionId, UINT32 userIntId, UINT16 hostId, aux::InterruptedGameDef &interruptedGame, PString &sqlErr));
	MOCK_METHOD(INT16, retrieveInterruptedGame, (BYTE playForFun, UINT64 gameSessionId, UINT32 userIntId, UINT16 hostId, aux::InterruptedGameDef &interruptedGame, PString &sqlErr));
	MOCK_METHOD(INT16, updateInterruptedGameStatus, (BYTE playForFun, UINT64 gameSessionId, UINT32 userIntId, UINT16 hostId, BYTE status, const PString& actor, PString &sqlErr));
	MOCK_METHOD(INT16, updateInterruptedGameExtraProps, (BYTE playForFun, UINT64 gameSessionId, const PString& propsJSON, PString &sqlErr));
	MOCK_METHOD(INT16, getInRangeInterruptedGamesByHostIdAndSiteId, ( UINT16 hostId, UINT16 siteId, const CommSrvTime& timeThredsholdBegin, const CommSrvTime& timeThredsholdEnd, INT32 queryLimit, bool forNotify, std::vector<aux::InterruptedGameDefEx>& expiredUFGs, PString& errStr ));
	MOCK_METHOD(INT16, getActiveInterruptedGamesCountGroupByHostIdSiteId, (std::vector<Dbm::dbm::HostSiteUfgCount>& counts, PString& errStr));
	MOCK_METHOD(INT16, getAgedInterruptedGamesCountGroupBySiteId, (const CommSrvTime& timeThresholdBegin, std::vector<Dbm::dbm::SiteUfgCount>& counts, PString& errStr));
	MOCK_METHOD(INT16, getExpiredInterruptedGamesCountGroupByHostIdSiteId, (std::vector<Dbm::dbm::HostSiteUfgCount>& counts, PString& errStr));

	MOCK_METHOD(INT16, updateInterruptedGamesStatusToRemoved, (bool gameSessionsExpired, vector<UINT64>& gameSessionIds, const PString& actor, vector<aux::InterruptedGameDef> &deletedGames, PString &sqlErr));
	MOCK_METHOD(INT16, updateInterruptedGamesStatusToPendingRemoval, (vector<UINT64>& gameSessionIds, vector<aux::InterruptedGameDef> &beingDeletedGames, PString &sqlErr ));
	MOCK_METHOD(INT16, updateInterruptedGameStatusToWaitingAdjustment, (UINT64 gameSessionId, aux::InterruptedGameDef &ufg, PString &sqlErr));
	MOCK_METHOD(INT16, updateInterruptedGameStatusToAdjustmentDecided, (UINT64 gameSessionId, INT64 ajustment, bool isRefund, PString &sqlErr));

	MOCK_METHOD(INT16, enableOrDisableTableTypes, (bool disable, vector<UINT32> &tableTypeIds, PString &sqlErr));

	MOCK_METHOD(INT16, insertTableState, (UINT64 tableId, const char* tableState, PString &sqlErr));
	MOCK_METHOD(INT16, updateTableState, (UINT64 tableId, const char *tableState, PString &sqlErr));
	MOCK_METHOD(INT16, updateTable, (UINT64 tableId, BYTE activeStatus, const char* rgToken, PString &sqlErr));

	MOCK_METHOD(void, doMaintenance, (INT32 ttlInSeconds));
	MOCK_METHOD(INT16, getExpiredClosedTables, (const CommSrvTime& expiredTime, std::vector<UINT64>& tables, PString& errStr));
	MOCK_METHOD(INT16, cleanupExpiredClosedTables, (const std::vector<UINT64>& tables, PString& errStr));
	MOCK_METHOD(INT16, getRestoredInterruptedGames, (const CommSrvTime& expiredTime, std::vector<UINT64>& games, PString& errStr));
	MOCK_METHOD(INT16, cleanupRestoredInterruptedGames, (const std::vector<UINT64>& games, PString& errStr));
	MOCK_METHOD(INT16, getExpiredSpainUserLimits, (std::vector<UINT64>& gameSessionIds, PString& errStr));
	MOCK_METHOD(INT16, cleanupExpiredSpainUserLimits, (const std::vector<UINT64>& gameSessionIds, PString& errStr));

	MOCK_METHOD(INT16, getExpiredLastMsgs, (const CommSrvTime& expiredTime, std::vector<UINT64>& hostReqIds, PString& errStr));	//PYR-75016
	MOCK_METHOD(INT16, cleanupExpiredLastMsgs, (const std::vector<UINT64>& hostReqIds, PString& errStr));		//PYR-75016

	MOCK_METHOD(INT16, getLastCropDate, (UINT32 cropType, CommSrvDate& lastCropDate, PString& errStr));
	MOCK_METHOD(INT16, saveLastCropDate, (UINT32 cropType, UINT32 sysId, const CommSrvDate& lastCropDate, const CommSrvTime& finishedTime, PString& errStr));

	MOCK_METHOD(INT16, admAuditLog, (const Dbm::dbm::AdminAuditLogInfo& auditInfo, PString &sqlErr));

	MOCK_METHOD(INT16, updateGameManagementData, (
		const vector<aux::GameManagementRule>& rulesToUpdate, const vector<aux::GameManagementException>& newExceptions, //old logic input
		const vector<aux::GameManagementRule>& rulesToAdd, const vector<UINT32>& rulesToRemove, const vector<aux::GameManagementChangeLog>& changeLogs, UINT64 baseVersion, //new logic input
		vector<aux::GameManagementRule>& updatedRules, vector<aux::GameManagementException>& updatedExceptions, vector<aux::GameManagementRule>& allRules, vector<aux::GameManagementException>& allExceptions, //old logic output
		UINT64& newVersion,
		PString &sqlErr));
	MOCK_METHOD(INT16, getGameManagementData, (bool needActiveDataOnly, vector<aux::GameManagementRule>& rules, vector<aux::GameManagementException>& exceptions, PString &sqlErr));
	MOCK_METHOD(INT16, getXclGameVariants, (std::vector<aux::XclGameVariant> &xclGameVariants, PString &sqlErr));
	MOCK_METHOD(INT16, getXclGames, (std::vector<aux::XclGame> &xclGames, PString &sqlErr), (const));
	MOCK_METHOD(INT16, getGameSessionInfoByGameSessionIds, ( std::vector<UINT64> &gameSessionIds, std::vector<Dbm::dbm::GameSessionTableInfo> &gameSessionInfos, PString &errStr ));
	MOCK_METHOD(INT16, getGameSessionInfoByTableIds, (std::vector<UINT64>& tableIds, std::vector<Dbm::dbm::GameSessionTableInfo>& gameSessionInfos, PString& errStr));
	MOCK_METHOD(void, getGameSessionByTableIdsNoCommit, (std::vector<UINT64>& tableIds, std::vector<Dbm::dbm::GameSessionTableInfo>& gameSessionInfos));
	MOCK_METHOD(INT16, getParentChildGameSessionInfo, (std::vector<UINT64>& tableIds, std::vector<UINT64>& parentTableIds, std::vector<Dbm::dbm::GameSessionTableInfo>& parentChildSessionInfos, PString& errStr));
	MOCK_METHOD(INT16, getUfgInfoByGameSessionIds, ( std::vector<UINT64>& gameSessionIds, std::vector<aux::InterruptedGameDef>& ufgs, PString& errStr ));
	MOCK_METHOD(INT16, getLastHandStates, (std::vector<UINT64>& gameSessionIds, std::vector<aux::StuckHandState>& handStates, PString& errStr));
	MOCK_METHOD(INT16, getGamesessionsByLastHandStatus, (const vector<UINT8>& status, INT32 lastSeconds, std::vector<UINT64>& gameSessionIds, PString& errStr));
	MOCK_METHOD(INT16, getPtHandsByHandIds, (std::vector<UINT64>& handIds, std::vector<aux::PT_HandDetails>& ptHands, PString &errStr));

	MOCK_METHOD(INT16, setTableLogLocation, (UINT64 tableId, CommSrvTime const& createTime, char const* logLocation, PString &sqlErr)); // #CAS-6105
	MOCK_METHOD(INT16, getSpainUserLimits, ( UINT16 hostId, UINT32 userIntId, aux::SpainUserLimits& spainUserLimits, PString &errStr ));
	MOCK_METHOD(INT16, setSpainUserLimits, ( UINT16 hostId, UINT32 userIntId, const aux::SpainUserLimits& spainUserLimits, PString& errStr ));
	MOCK_METHOD(INT16, closeSpainUserLimits, ( UINT16 hostId, UINT32 userIntId, UINT64 lastGameSessionId, CommSrvTime& lastGameEndTime, BYTE lastGameEndStatus, CommSrvTime& lastGameEndTimeUTC, PString& errStr ));
	MOCK_METHOD(INT16, adjustSpainUserLimitsEndTime, ( UINT16 hostId, UINT32 userIntId, UINT64 lastGameSessionId, CommSrvTime &lastGameEndTime, PString &errStr ));
	MOCK_METHOD(INT16, clearSpainUserLimits, ( UINT16 hostId, UINT32 userIntId, PString &errStr ));
	MOCK_METHOD(INT16, clearSpainUserLimitsBySessionId, (UINT64 lastGameSessionId, PString& errStr));

	MOCK_METHOD(INT16, getTableInfoState, (UINT64 tableId, aux::TableDef& table, UINT32& vendorId, PString& errStr));
	MOCK_METHOD(INT16, getTableDef, (UINT64 tableId, aux::TableDef& tableDef, PString& errStr));
	MOCK_METHOD(INT16, getTableDefsByTableIds, (std::vector<UINT64>& tableIds, std::vector<aux::TableDef>& tableDefs, PString& errStr));

	MOCK_METHOD(INT16, forceCloseTablesAndCleanStates, (std::vector<UINT64>& tableIds, const CommSrvTime& closeTime, PString& sqlErr));
	MOCK_METHOD(INT16, getObsoleteLdTableTypes, (std::vector<aux::TableTypeDef>& tableTypes, PString &sqlErr));

	MOCK_METHOD(std::set<UINT32>, getObsoletedTableTypeIds, ());
	MOCK_METHOD(std::set<UINT32>, getObsoletedTableTemplateIds, ());
	MOCK_METHOD(INT16, getObsoleteButInuseTTTTIds, (std::set<UINT32>& tableTypeIds, std::set<UINT32>& templateIds, PString &sqlErr));
	MOCK_METHOD(INT16, deleteTableType, (UINT32 tableTypeId, PString& sqlErr));
	MOCK_METHOD(INT16, deleteTableTemplate, (UINT32 tableTemplateId, PString& sqlErr));

	MOCK_METHOD(INT16, getJackpotGameNames, (UINT32 jpKey, std::vector<PString>& gameNames, PString &sqlErr));		//PYR-57152
	MOCK_METHOD(INT16, getGameVariantName, (UINT16 gameType, UINT16 variantType, PString& name, PString &sqlErr));				//PYR-57152

	MOCK_METHOD(INT16, insertStuckGame, (UINT64 gameSessionId, UINT16 gameType, UINT16 variantType, bool playForFun, CommSrvTime createTime, UINT16 reason, PString& sqlErr));
	MOCK_METHOD(INT16, updateStuckGame, (const aux::AdmUserInfo& adminUser, UINT64 gameSessionId, bool playForFun, UINT16 status,  UINT16 actionsCompleted, INT64 credit, UINT16 closeType, PString& sqlErr));
	MOCK_METHOD(INT16, getStuckGames, (UINT16 queryType, const vector<aux::P_PNameValue>& criterias, vector<aux::StuckGameInfo>& stuckGames, PString& sqlErr));
	MOCK_METHOD(INT16, getInterruptedGameCounts, (UINT16 queryType, const vector<aux::P_PNameValue> criterias, vector<Dbm::dbm::InterruptedGameCount>& ufgCounts, PString& sqlErr));
	MOCK_METHOD(INT16, getGameSessionsToFinalize, (INT32 idleTime, std::vector<aux::P_GameHand>& idleGames, PString& sqlErr));
	MOCK_METHOD(INT16, cleanUpGameStatusChangeLogs, (UINT32 limit, const UINT64 annotationChangeID, const vector<UINT64>& logIds, vector<UINT64>& changeIds, PString& sqlErr));

	MOCK_METHOD(bool, scriptExists, (const char* sectionName, const char* objectId));
	MOCK_METHOD(bool, sectionScriptExists, (const aux::SectionScript& sectionScript));
	MOCK_METHOD(INT16, obsoleteTableType, (const vector<aux::TableTypeToObsolete>& tableTypesToObsolete, const PString &changeBy, std::vector<aux::TableTypeDef> &tableTypesObsoleted, PString& sqlErr));

	MOCK_METHOD(INT16, uploadTabeTypes, (const vector<aux::TableTypeDef>& ttAdded, const vector<aux::TableTypeDef>& ttObsoleted, const PString &changeBy, PString& sqlErr));
	MOCK_METHOD(INT16, uploadTabeTypesNoCommit, (const CommSrvTime& currentTime, const vector<aux::TableTypeDef>& ttAdded, const vector<aux::TableTypeDef>& ttObsoleted, PString& sqlErr));
	
	MOCK_METHOD(INT16, getSnInLastMsgsTable, ());	//PYR-71001
	MOCK_METHOD(void, checkoutUgd, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_CHECKOUT_UGD& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_CHECKOUT_UGD& reply));	//PYR-71001
	MOCK_METHOD(void, checkinUgd, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_CHECKIN_UGD& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_CHECKIN_UGD& reply));	//PYR-71001
	MOCK_METHOD(void, retrieveInterruptedGameCheckoutUgd, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_GET_INTERRUPTED_GAME_CHECKOUT_UGD& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_GET_INTERRUPTED_GAME_CHECKOUT_UGD& reply));	//PYR-71001
	MOCK_METHOD(void, saveInterruptedGameCheckinUgd, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_SAVE_INTERRUPTED_GAME_CHECKIN_UGD& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_SAVE_INTERRUPTED_GAME_CHECKIN_UGD& reply));	//PYR-71001
	MOCK_METHOD(void, updateInterruptedGameCheckinUgd, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_UPDATE_INTERRUPTED_GAME_STATUS_CHECKIN_UGD& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_UPDATE_INTERRUPTED_GAME_STATUS_CHECKIN_UGD& reply));
	MOCK_METHOD(void, updateUgdContent, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_UPDATE_UGD_CONTENT req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_UPDATE_UGD_CONTENT reply));

	template<typename T>																																																																									//====re-transmit ===																																					//====re-transmit ===
	bool InsertLastMsgNoCommit(UINT64 hostReqId, const PString& channelId, INT32 msgId, T& reply) { return false; }
	MOCK_METHOD(void, saveResponse, (UINT64 hostReqId, Atf::MessageProtocol const& reply));
	template<typename T>
	void getReTransMsgResponse(UINT64 hostReqId, const PString& channelId, INT32 msgId, T& reply) { return false; }

	MOCK_METHOD(void, getUserAppData, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_GET_USER_APP_DATA& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_GET_USER_APP_DATA& reply));
	MOCK_METHOD(void, setUserAppData, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_SET_USER_APP_DATA& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_SET_USER_APP_DATA& reply));

	MOCK_METHOD(void, i18nAddOrUpdateMessages, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_I18N_ADD_OR_UPDATE_MESSAGES& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_I18N_ADD_OR_UPDATE_MESSAGES& reply));
	MOCK_METHOD(void, i18nUpdateStatus, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_I18N_UPDATE_STATUS& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_I18N_UPDATE_STATUS& reply));
	MOCK_METHOD(void, i18nGetMessages, (Dbm::dbm::Protocol_AUX_DBM_MSG_Q_I18N_GET_MESSAGES& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_I18N_GET_MESSAGES& reply));

	MOCK_METHOD(void, upsertGCAnnotations, (const Dbm::dbm::Protocol_AUX_DBM_MSG_Q_UPSERT_GC_ANNOTATIONS& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_UPSERT_GC_ANNOTATIONS& reply));
	MOCK_METHOD(void, upsertGCAnnotationNames, (const Dbm::dbm::Protocol_AUX_DBM_MSG_Q_UPSERT_GC_ANNOTATION_NAMES& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_UPSERT_GC_ANNOTATION_NAMES& reply));

	MOCK_METHOD(void, innerUpsertGCAnnotationsNoCommit, (const vector<aux::GCAnnotation>& annotations, const PString &changeBy, const CommSrvTime& changeTime, INT64 changeID));

	MOCK_METHOD(INT16, getNonObsoleteTableTypes, (std::vector<aux::TableTypeDef> &tableTypes, PString& sqlErr));

	MOCK_METHOD(void, updateGameStatusChangeLogs, (const Dbm::dbm::Protocol_AUX_DBM_MSG_Q_UPDATE_GAME_STATUS_CHANGE_LOGS& req, Dbm::dbm::Protocol_AUX_DBM_MSG_A_UPDATE_GAME_STATUS_CHANGE_LOGS& reply));

	MOCK_METHOD(INT16, checkAnnotationsEx4Ptr, (const std::vector<Dbm::dbm::CheckPtReportData>& data, PString& errStr));

public:

	MOCK_METHOD(void, init, (AuxDbmServerObject* obj, int dbmId_, bool readOnlyMode_));
	MOCK_METHOD(void, readIniFileStatic, ());
	MOCK_METHOD(bool, openDataStorage_impl, (const char* fullFileName, const char* sectionName, const char* dbName, const char* dbConnectionParams));
	bool openDataStorage(const char* fullFileName, const char* sectionName, const char* dbName = nullptr, const char* dbConnectionParams = nullptr)
	{
		return openDataStorage_impl(fullFileName, sectionName, dbName, dbConnectionParams);
	}
	MOCK_METHOD(void, commit, ());
	MOCK_METHOD(void, rollbackOnError, ());
	MOCK_METHOD(void, setAutoCommitTrue, ());
	MOCK_METHOD(void, setAutoCommitFalse, ());

private:

	MOCK_METHOD(void, extCommit, (), (override));
	MOCK_METHOD(void, extRollback, (), (override));
	MOCK_METHOD(void, extSetAutoCommit, (const bool isOn), (override));
};

#endif // MainDbmManager_mock_h__
