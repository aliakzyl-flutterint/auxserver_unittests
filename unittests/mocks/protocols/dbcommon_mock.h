#ifndef dbcommon_mock_h_included
#define	dbcommon_mock_h_included


///////// headers to use ODBC ////////////////
#include "ppinclude.h"
#ifdef PWIN32
	#include	<windows.h>

	#ifdef USE_ODBC
		#if defined USE_DB2_CLI
			#error "Error: Both ODBC and CLI interfaces defined"
		#endif
	#elif !defined USE_DB2_CLI
		#define USE_DB2_CLI
	#endif

	#ifdef USE_DB2_CLI
		#include "sqlcli.h"
		#include "sqlcli1.h"
	#else
		#include	"sqltypes.h"
		#include	"sql.h"
		#include	"sqlext.h"
	#endif

	#ifndef PWIN64
		#ifndef SQLLEN
			#define SQLLEN	SQLINTEGER
		#endif
	#endif
#elif defined (PPOSIX)
	#include	"sqlcli.h"
	#include	"sqlcli1.h"
#endif

#include	"ppstring.h"
#include	"pplib.h"

#include	"dbmgenerator_mock.h"
#include	"olapmsghandler.h"
#include	"sqlerror.h"
#include	"counters_mock.h"

#include <gmock/gmock.h>

class	PDbDisconnectError
{
public:
	PDbDisconnectError(const char* msg_) {}
	MOCK_METHOD(const char*, why, (), (const));
};

class	PDbDeadlockError
{
public:
	PDbDeadlockError(const char* msg_) {}
	MOCK_METHOD(const char*, why, (), (const));
};

class	PDbFederatedDeadInternalConnectError
{
public:
	const PString sqlError;
	PDbFederatedDeadInternalConnectError(const char* msg_) : sqlError(msg_) {}
};

class OlapReplicator;
class OlapManager;
class CommServerObjectWithOlapInteface;
class CommMsgBody;

struct EndMarkerData
{
	UINT32 transId;
	PString endTransStr;

	EndMarkerData(UINT32 transId_, const char* endTransStr_)
		: transId(transId_), endTransStr(endTransStr_)
	{
	}
};

enum eTableNames
{
	eTableName_Cashtrans,
//	eTableName_Transfers,
};

#define DEPLOYMENT_SECTION_NAME		"DEPLOYMENT" // host specific info is in this section
#define STATICSETTINGS_SECTION_NAME	"STATICSETTINGS"
#define DB_LOCKTIMEOUT_PARAM_NAME "locktimeout" // PYR-35295
#define DB_DEADLOCK_RETRIES_PARAM_NAME "maxdeadlockretries" // PYR-37539
#define DB_RECONNECT_ATTEMPTS_PARAM_NAME "reconnectattempts"
#define DB_DEFAULT_PARAL_PARAM_NAME "default_paral" // PYR-49252
#define DB_MAX_PARAL_PARAM_NAME "max_paral" // PYR-49252
#define DB_LOGIN_TIMEOUT_PARAM_NAME "login_timeout_seconds" // FITSS-3652



enum eDBConnectionStatus
{
	eDBConnectionStatus_Disconnected = 0, // all handles closed - AFTER DatabaseManagerCommon::closeDataStorage
	eDBConnectionStatus_Connecting = 1, // BEFORE (at the beginning of) DatabaseManagerCommon::openDataStorage
	eDBConnectionStatus_Connected = 2, // AFTER (at the end of) DatabaseManagerCommon::openDataStorage
	eDBConnectionStatus_DbDisconnectError = 3, // If DB SqlState is mapped to disconnect error
	eDBConnectionStatus_Closing = 4, // BEFORE (at the beginning of) DatabaseManagerCommon::closeDataStorage
};

struct DatabaseConnectionListener
{
	virtual void databaseConnectionStatus(eDBConnectionStatus status) = 0;
};

class DatabaseManagerCommon
{
	friend class OlapReplicator;
	friend class OlapManager;
	friend class OlapServer;
	friend class TransactionalOutbox;

protected:
	SQLHENV		henv = SQL_NULL_HENV;
	SQLHDBC		hdbc = SQL_NULL_HDBC;
	int			maxDbReconnectAttempts = 0;
	PString		schemaStr;
	bool		globalAutoCommitFlag = false;
	PString		dsName;
	INT32		lockTimeout = 0;
	INT32		maxDbDeadlockRetries = 0;
	PString		defaultParallelismDegree; // PYR-49252
	PString		maxParallelismDegree; // PYR-49252

	PString		forUpdateClause;
	DbmGenerator generator;
	virtual const DbmGenerator::Generator* getGenerators( size_t& generatorsSize ) const
	{
		return nullptr;
	}
	virtual const char* const * getMonotonicGenerators( size_t& arraySize ) const
	{
		return nullptr;
	}
	eHost hostId = eHost_Unknown;
	INT32 remainingIdsThreshold = 0;
	INT32 requiredIdsBuffer = 0;
	bool useMasterGenerator = false;

	static constexpr bool postToIceUsesReplicator_DEFAULT = true;
	bool postToIceUsesReplicator = postToIceUsesReplicator_DEFAULT;

	MOCK_METHOD(void, readDbCommonDynamicConfig, (const PIniFile& iniFile));
	MOCK_METHOD(bool, addIceMsgToReplication, (UINT32 msgId, UINT32 userIntId, const CommMsgBody& iceBody, CommServerObjectWithOlapInteface* dbmObj));

public:
	enum eStmtFailureLogging
	{
		eStmtFailureLogging_Off = 0,
		eStmtFailureLogging_All = 1,
		eStmtFailureLogging_AllButAllowedForOlap = 2,
	};
	MOCK_METHOD(void, readStmtFailureLoggingState, (const PIniFile::Section& section));
	MOCK_METHOD(bool, isStmtFalureLoggingOn, (const PString& sqlState), (const));
	MOCK_METHOD(eStmtFailureLogging, getStmtFailureLogging, (), (const));
protected:
	MOCK_METHOD(void, addObjectNameToGenerator, (const char* objectName, bool local));
	MOCK_METHOD(void, addMonotonicGenerator, (const char* objectName));

	MOCK_METHOD(void, _openDataStorage, (const char* fullFileName, const char* sectionName, const char* eslDbName, const char* eslDbConnParams));
	MOCK_METHOD(void, _openDataStorageFromIniFile, (const PIniFile& iniFile, const char* sectionName, const char* eslDbName, const char* eslDbConnParams));
	MOCK_METHOD(void, setLockTimeout, ());
	MOCK_METHOD(void, setParallelismDegree, (const char* parallelismDegree));
	MOCK_METHOD(void, setDefaultParallelismDegree, ());
	MOCK_METHOD(void, setMaxParallelismDegree, ());
	MOCK_METHOD(bool, setDefaultParallelismDegreeNoThrow, ());
	MOCK_METHOD(bool, setMaxParallelismDegreeNoThrow, ());

public:
	DatabaseManagerCommon() {}
/*lint -save -e1740 */
	virtual ~DatabaseManagerCommon() {}
/*lint -restore */
	enum CheckModifier {
		eCheckNotSuccess,
		eCheckError,
		eCheckErrorOrInfo //,
		//eCheckHwm
	};
	MOCK_METHOD(int, getMaxDbReconnectAttempts, (), (const));
	MOCK_METHOD(INT32, getMaxDbDeadlockRetries, (), (const));
	MOCK_METHOD(eHost, getHostId, (), (const));

	MOCK_METHOD(bool, useSharedIds, (), (const));
	MOCK_METHOD(bool, isUseMasterGenerator, (), (const));
	MOCK_METHOD(bool, isMonotonicByUserId, (const char* objectName), (const));

public:
	struct SqlErrDetail
	{
		SQLRETURN sqlRetCode;
		bool haveToCheck;
		static const INT32 SqlStateSize = 6;
		SQLCHAR SqlState[SqlStateSize];
		PString sqlErr;
		PString sqlStateLst;

		SqlErrDetail(SQLRETURN retcode) {}
		MOCK_METHOD(void, checkRetCode, (SQLSMALLINT HandleType, SQLHSTMT hstmt, CheckModifier modifier));
		MOCK_METHOD(bool, hasError, (), (const));
		MOCK_METHOD(void, raiseOnError, (), (const));
	};


protected:
	virtual void checkRetcode(SQLSMALLINT HandleType, SQLRETURN retcode, SQLHANDLE handle, CheckModifier modifier) const {}

	MOCK_METHOD(void, setAutoCommit, (bool bOn));
	MOCK_METHOD(bool, isAutoCommit, (), (const));
	MOCK_METHOD(void, rollback, ());
	MOCK_METHOD(void, commit, ());
public:
	MOCK_METHOD(bool, openDataStorage_impl, (const char* fullFileName, const char* sectionName, const char* eslDbName, const char* eslDbConnParams));
	MOCK_METHOD(bool, openDataStorage_impl, (const PIniFile& iniFile, const char* sectionName, const char* eslDbName, const char* eslDbConnParams));
	bool openDataStorage(const char* fullFileName, const char* sectionName, const char* eslDbName = nullptr, const char* eslDbConnParams = nullptr)
	{
		return openDataStorage_impl(fullFileName, sectionName, eslDbName, eslDbConnParams);
	}
	bool openDataStorage(const PIniFile& iniFile, const char* sectionName, const char* eslDbName = nullptr, const char* eslDbConnParams = nullptr)
	{
		return openDataStorage_impl(iniFile, sectionName, eslDbName, eslDbConnParams);
	}
	
	MOCK_METHOD(void, closeDataStorage, ());
	MOCK_METHOD(const char*, getDsName, (), (const));

	MOCK_METHOD(void, checkStmtRetcode, (SQLRETURN retcode, SQLHSTMT hstmt, CheckModifier modifier), (const));
	MOCK_METHOD(void, checkDbcRetcode_impl, (SQLRETURN retcode, SQLHDBC hdbc_, CheckModifier modifier = eCheckNotSuccess), (const));
	void checkDbcRetcode(SQLRETURN retcode, SQLHDBC hdbc_, CheckModifier modifier = eCheckNotSuccess) const
	{
		return checkDbcRetcode_impl(retcode, hdbc_, modifier);
	}


	MOCK_METHOD(SQLHDBC, getHdbc, (), (const));
/*lint -save -e1536 */
	MOCK_METHOD(DbmGenerator&, _getGenerator, ());
/*lint -restore */
	MOCK_METHOD(UINT32, getNextId, (const char* objectName));
	MOCK_METHOD(UINT64, getNextId64, (const char* objectName));
	virtual bool isMainThreadManager() const { return false; }
	virtual bool isMainObjectManager() const { return false; }
	MOCK_METHOD(void, getNext2Ids64, (const char* objectName, UINT64& id1, UINT64& id2));
	MOCK_METHOD(void, getNext2Ids, (const char* objectName, UINT32& id1, UINT32& id2));
	MOCK_METHOD(UINT64, getNextId64UnCached, (const char* objectName));

	MOCK_METHOD(const char*, getForUpdateClause, (), (const));
	virtual INT16 getIdRange(const char* objectName, INT32 rangeSize, UINT64& startId, UINT64& endId, PString& sqlErr) { return 0; }
	MOCK_METHOD(bool, initConnectionToMasterGenerator, (IdRangeClientConnection* idRangeConn, DbmGenerator::DbmGeneratorCallback* initFinishedCallback));

public:
	MOCK_METHOD(const char*, getMsgTableName, (), (const));
	MOCK_METHOD(const char*, getMsgObjectName, (), (const));
	MOCK_METHOD(const char*, getOrdinalPropName, (), (const));
	MOCK_METHOD(OlapManager*, _getOlapManager, ());
	virtual	INT16 getIntProperty(const char* propName, int& propValue, PString& sqlErr) { return 0; }
	virtual	INT16 saveIntProperty(const char* propName, int propValue, PString& sqlErr) { return 0; }
	
	MOCK_METHOD(void, commitTransactionMessages, (CommServerObjectWithOlapInteface* dbmObj));
	MOCK_METHOD(void, rollbackTransactionMessages, ());
	MOCK_METHOD(void, insertTransactionUpdate, (const UINT32 msgId, CommMsgBody& body, BYTE msgMask, const OlapMsgSysInfo& sysInfo));
	MOCK_METHOD(void, insertTransactionUpdatesAtFront, (list<struct LogMessage>&& logMsgList));
	virtual void allOlapsInDirectSend(bool inDirectSend) {};
	virtual bool getLicenseIdByUserIntId(UINT32 userIntId, UINT32& licenseId) { return false; }
	virtual bool getUtcTimeForOlap( CommUtcTime& utcTime ) const { return false; }
	virtual UINT32 getDbmId() const { return 0; }
protected:
	MOCK_METHOD(void, setReplicator, (OlapReplicator* repl));
public:
	MOCK_METHOD(void, setSendEndMarker_impl, (UINT32 endTransInt_, const char* endTransStr_));
	void setSendEndMarker(UINT32 endTransInt_ = 0, const char* endTransStr_ = "")
	{
		return setSendEndMarker_impl(endTransInt_, endTransStr_);
	}

	virtual const char* getTableName(eTableNames tableNameEnum) const { return ""; }
	virtual void ensureCanProcessUserRelatedTables(UINT32 licenseId, UINT32 userIntId) const {}

public: 
	MOCK_METHOD(void, resetRoundtripCounter, ());
	MOCK_METHOD(void, incrementRountripCounter, ());
	MOCK_METHOD(UINT32, getRoundtripCounter, (), (const)); 
public:
	virtual bool dbmSupportsRetryOnFederatedDeadConnection() const { return false; }
public:
	MOCK_METHOD(INT16, getCurrentDbTimestamp, (CommSrvTime& timestamp, UINT32& nanoseconds, PString& sqlErr));
	MOCK_METHOD(INT16, prepareOltpPause, (INT32 oltpDbId, INT16 sourcesCount, const vector<INT32>& dbmIds, CommServerObjectWithOlapInteface& dbmObj, PString& sqlErr));
	MOCK_METHOD(INT16, verifyOltpPausePrepared, (INT32 oltpDbId, const vector<INT32>& dbmIds, PString& sqlErr));
	MOCK_METHOD(INT16, startOltpPause, (const vector<INT32>& dbmIds, CommServerObjectWithOlapInteface& dbmObj, CommUtcTime& heartbeatStart, PString& sqlErr, function<INT16(const CommSrvTime&,UINT32,PString&)> verifyTime));
	MOCK_METHOD(INT16, stopOltpPause, (const vector<INT32>& dbmIds, CommServerObjectWithOlapInteface& dbmObj, CommUtcTime& heartbeatEnd, PString& sqlErr));
	MOCK_METHOD(INT16, completeOltpPause, ( const vector<INT32>& dbmIds, CommServerObjectWithOlapInteface& dbmObj, PString& sqlErr));

protected:
	MOCK_METHOD(void, setConnectionStatus, (eDBConnectionStatus newStatus), (const));
public:
	MOCK_METHOD(eDBConnectionStatus, getConnectionStatus, (), (const));
	MOCK_METHOD(bool, registerConnectionListener, (DatabaseConnectionListener* listener));
	MOCK_METHOD(bool, unregisterConnectionListener, (DatabaseConnectionListener* listener));

 	/*struct SqlPerformanceCounters
	{
		TicksAccumulator sqlCloseCursor;
		TicksAccumulator sqlExecute;
		TicksAccumulator sqlCommit;
	} sqlPerformanceCounters;*/

	//mutable INT32 stmtFailureCount = 0;

	MOCK_METHOD(void, composeDbCommonForHeLogger, (const HeLogger& heLogger, CommMsgBody& reportBody));
};

#ifdef POSTGRES
#define SQL_WARNING_NON_OPTIMAL_PLAN	"54001"
#else
#define SQL_WARNING_NON_OPTIMAL_PLAN	"01602"
#endif

inline bool errorStateAllowedForOlap (const PString& sqlState)
{
	return sqlState.equals("23505")       // constraint
		|| sqlState.equals("02000")       // nothing to update
		|| sqlState.equals(SQL_WARNING_NON_OPTIMAL_PLAN) // warning "non-optimal plan"
		|| sqlState.equals("77777")       // PYR-23400: artificial error state
		|| sqlState.equals("77778")       // PYR-23400: artificial error state (for future use)
		;
}

#define RECONNECT_SLEEP		1000

template <class T>
void dbmConnectOnInit(T& dbManager, const char* fullFileName, const char* sectionName)
{
}

template <class T>
void dbmConnectOnInit(T& dbManager, const char* fullFileName, const char* sectionName, const char* eslDbName, const char* eslDbConnParams)
{
}

#endif //dbcommon_mock_h_included
