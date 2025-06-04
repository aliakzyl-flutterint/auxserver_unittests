#ifndef auxdbmcommon_mock_h__
#define auxdbmcommon_mock_h__


#include "../../../auxiliary/auxcommon/auxdbmstmt.h"
#include "AuxCommServerObject_mock.h"
#include "../protocols/dbmserverobjectcommon_mock.h"
#include "../../../atf/PerformanceCounter.h"
#include "../atf/AtfCommServerObject_mock.h"
#include <gmock/gmock.h>

class OlapServer;

class AuxCommDbmServerObject : public DbmServerObjectCommon, public Atf::AtfCommObjectImpl, public AuxServerCommonImpl
{
public:
	AuxCommDbmServerObject(_CommInterface& i) : DbmServerObjectCommon(i) , AtfCommObjectImpl(i), AuxServerCommonImpl(this) {}
	MOCK_METHOD(void, processMessage, (_CommMsg& msg), (override));
	MOCK_METHOD(void, processTimerMessage, ( UINT32 handle, UINT32 msgId, CommMsgBody& body ), (override));
	MOCK_METHOD(bool, deleteTimerMessage, ( UINT32 handle ));
	MOCK_METHOD(UINT32, postTimerMessage, ( UINT32 msgId, CommMsgBody& body, int msec ));
	MOCK_METHOD(void, exit, ());
	MOCK_METHOD(void, init, (CommMsgBody& msg), (override));

protected:
	MOCK_METHOD(bool, initOlap, (OlapServer& olapServer, const char* iniFileName));
};

class OlapServerReporter : public Atf::OlapServerReporter
{
public:
	OlapServerReporter() {}
	MOCK_METHOD(void, init, (OlapServer* olapServer_));
	MOCK_METHOD(void, reportQueue, (CommMonitorLoggerObject* heLogger, CommMsgBody& reportBody), (override));
	MOCK_METHOD(void, reportSavedMessage, (CommMonitorLoggerObject* heLogger, CommMsgBody& reportBody), (override));
};


template<class PSQLVALUETYPE, class CVALUETYPE>
class GenericSimpleDeleteStmt : public AuxDbmStatement/*WithLog*/
{
public:
	GenericSimpleDeleteStmt(DatabaseManagerCommon& man, const char *tableName_, const char* idColName_) : AuxDbmStatement(man) {}
	MOCK_METHOD(void, init, (CVALUETYPE id_));
};

template<class PSQLVALUETYPE, class CVALUETYPE>
class GenericBatchDeleteStmt : public AuxDbmStatement/*WithLog*/
{
public:
	GenericBatchDeleteStmt(DatabaseManagerCommon& man, const char *tableName_, const char* colName_, const char* comparison_) : AuxDbmStatement(man) {}
	MOCK_METHOD(void, init, (CVALUETYPE value_));
};

template<class PSQLVALUETYPE, class CVALUETYPE, class PSQLSELECTVALUETYPE, class CSELECTVALUETYPE>
class GenericSimpleSelectStmt : public AuxDbmStatement/*WithLog*/
{
public:
	GenericSimpleSelectStmt(DatabaseManagerCommon& man, const char *tableName_, const char* colName_, const char* comparison_, const char* selectColName_, bool checkNull=true)
		:AuxDbmStatement(man)
	{
	}
	MOCK_METHOD(void, init, (CVALUETYPE value_));
	MOCK_METHOD(void, executeAndReturnList, (std::vector<CSELECTVALUETYPE> &selectValues));
	MOCK_METHOD(void, executeAndReturnStrList, (std::vector<CSELECTVALUETYPE> &selectValues));
};

template<class PSQLVALUETYPE, class PSQLVALUETYPE2, class CVALUETYPE, class CVALUETYPE2, class PSQLSELECTVALUETYPE, class CSELECTVALUETYPE>
class GenericSimpleSelectStmt2Criteria : public AuxDbmStatement/*WithLog*/
{
public:
	GenericSimpleSelectStmt2Criteria(DatabaseManagerCommon& man, const char *tableName_, const char* colName_, const char* comparison_, const char* colName2_, const char* comparison2_, const char* selectColName_)
		:AuxDbmStatement(man)
	{
	}
	MOCK_METHOD(void, init, (CVALUETYPE value_, CVALUETYPE2 value2_));
	MOCK_METHOD(void, executeAndReturnList, (std::vector<CSELECTVALUETYPE> &selectValues));
};

class GetLastCropDateStmt : public AuxDbmStatement
{
public:
	PSqlDate		cropDate_;
public:
	GetLastCropDateStmt(DatabaseManagerCommon& man, const char* tableName)
		: AuxDbmStatement(man)
	{
	}
	MOCK_METHOD(void, init, (UINT32 cropType));
};

class SaveLastCropDateStmt : public AuxDbmStatement
{
public:
	SaveLastCropDateStmt(DatabaseManagerCommon& man, const char* tableName)
		: AuxDbmStatement(man)
	{
	}
	MOCK_METHOD(void, init, (UINT32 cropType, UINT32 sysId, const CommSrvDate& cropDate, const CommSrvTime& finishedTime));
};


class OlapReplicator;
class RollBackableDatabaseManager: public DatabaseManagerCommon
{
public:
	RollBackableDatabaseManager() {}
	virtual ~RollBackableDatabaseManager() {}
protected:
	MOCK_METHOD(void, init, (CommServerObjectWithOlapInteface* dbmObj));

	MOCK_METHOD(void, initReplicator, (const char* olapMessagesTableName, const char* olapMessagesObjectName, const char* olapLastMsgOrdinalPropName));
	MOCK_METHOD(INT16, getIntProperty, (const char* propName, int& propValue, PString& sqlErr), (override));
	MOCK_METHOD(INT16, saveIntProperty, (const char* propName, int propValue, PString& sqlErr), (override));
	MOCK_METHOD(void, commit, ());

public:
	MOCK_METHOD(void, rollbackOnError, ());
public:
	template <typename _T>
	INT16 commitNoCommitDbRequest(_T &req, PString &errStr)
	{
	}
};

class AuxDbmExceptionPerformanceCounter : public Atf::PerformanceCounter
{
public:
	INT32 numDeadlocks = 0;
	INT32 numOutOfDeadlockAttempts = 0;
	INT32 numDisconnects = 0;
public:
	AuxDbmExceptionPerformanceCounter() : numDeadlocks(0), numOutOfDeadlockAttempts(0), numDisconnects(0) {}
	virtual ~AuxDbmExceptionPerformanceCounter() {};

	MOCK_METHOD(void, reset, (), (override));
	MOCK_METHOD(void, getPerformanceData, (std::vector<PNameValue>& data), (override));
};

template<class O, class D>
class AuxDbmExceptionSafeHelper
{
public:
	AuxDbmExceptionPerformanceCounter performanceCounter;
	
	AuxDbmExceptionSafeHelper(O& o, D& d, PString& f, const char* s = "MAINSTORAGE") {}

	template<class C, class F> 
	void processMessage(UINT32 msgId, const CommMsgBody& body, C* conn, F func)
	{
	}
};

template<class O, class D>
class AuxDbmExceptionSafeHelperEsl
{
public:
	AuxDbmExceptionPerformanceCounter performanceCounter;

	AuxDbmExceptionSafeHelperEsl(O& o, D& d) {}

	template<class C, class F> 
	void processMessage(UINT32 msgId, const CommMsgBody& body, C* conn, F func)
	{
	}
};



#endif // auxdbmcommon_mock_h__