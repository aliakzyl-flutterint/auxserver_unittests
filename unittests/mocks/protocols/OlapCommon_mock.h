#ifndef olapcommon_mock_h_included
#define	olapcommon_mock_h_included

#include "../commlib2a/commsrv_mock.h"
#include "../commlib2a/commgrdnull_mock.h"
#include "counters_mock.h"
#include "pyrtime.h"
#include "dbcommon_mock.h"
#include "dbmserverobjectcommon_mock.h"

#include <gmock/gmock.h>

class CommServerObjectWithOlapInteface;
class OlapStruct;

typedef DatabaseManagerCommon DatabaseManagerCommonWithOlap;

class DbmToOlapClientConn : public CommClientGConnection
{
protected:
	CommServerObjectWithOlapInteface* obj = nullptr;
	OlapStruct* olap = nullptr;
public:
	DbmToOlapClientConn(CommClientGuardFactory& guardFactory, CommServerObjectWithOlapInteface* obj_, OlapStruct* olap_)
	: CommClientGConnection( guardFactory/*, true*/ )
	{
	}
	MOCK_METHOD(void, processGMessage, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body, CommClientGConnection::AsyncCall* call), (override));
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(bool, closedOrDisconnected, (int errCode, const char * errStr), (override));
	MOCK_METHOD(UINT32, getOlapId, (), (const)); 
	MOCK_METHOD(OlapStruct*, getOlap, ());
};

#define USER_ACCOUNT_MSG_MASK (1 << 1)
#define ICE_MSG_MASK (1 << 3) // 8

enum eOlapSyncMode
{ 
	eSyncNormal = 1,
	eSyncUsersOnly,
	eSyncFull,
	eSyncIce,
 };


class OlapServer;

class OlapStruct
{
public:

	OlapStruct(OlapServer*	olapServer_)
	{
	}
	~OlapStruct()
	{
	}
	bool saveMessageOnError = false;

	MOCK_METHOD(eHost, getHostId, (), (const));
};


#define MSG_BODY_LEN		16001
#define MSG_ERRDESCR		251

class SaveMessageStmt;
class GetMessageStmt;
class GetFirstMessageStmt;

// PYR-22086
enum eOlapProtocolVersion
{
	eOlapProtocolVersionLegacy = 0,
	eOlapProtocolVersionSysInfo = 1
};

class OlapManager
{
public:

	OlapManager()
	{
	}
	~OlapManager()
	{
	}
	MOCK_METHOD(void, init, (DatabaseManagerCommon* manager_));
	MOCK_METHOD(void, prepareStatements, (DatabaseManagerCommon& manager));
	MOCK_METHOD(void, deleteStatements, ());
	MOCK_METHOD(void, saveQueueToOlap, (OlapStruct& olap));
};

class EslResolver;

class OlapServer
{
protected:
	vector<OlapStruct*> olapVector;
public:

	CommServerObjectWithOlapInteface* obj = nullptr;

	OlapServer()
	{
	}
    virtual	~OlapServer()
	{
	}

	MOCK_METHOD(void, reportQueue, (const HeLogger* heLogger, CommMsgBody& reportBody));
	MOCK_METHOD(void, reportSavedMessage, (const HeLogger* heLogger, CommMsgBody& reportBody));
	MOCK_METHOD(void, reportTobStats, (const HeLogger* heLogger, CommMsgBody& reportBody));
	MOCK_METHOD(void, reportToHercules, (const HeLogger* heLogger, CommMsgBody& reportBody));

	MOCK_METHOD(bool, readFromIniFile, (const char* iniFileName));
	MOCK_METHOD(bool, readFromIniFile, (const PIniFile& iniFile));

	virtual	void postToOlap(UINT32 msgId, const CommMsgBody& body, bool sendAlwaysDirect, bool isPlayReplicaSync, BYTE msgMask, const OlapMsgSysInfo& msgSysInfo) {}

	MOCK_METHOD(void, postToIce, (UINT32 msgId, UINT32 userIntId, const CommMsgBody& body));

	MOCK_METHOD(void, postProtobuf, (UINT32 msgId, const PBlock& payload));

	MOCK_METHOD(UINT32, connectToOlapAll, (CommClientConnectionPool& cliPool, CommClientNullGuardFactory& guardCliFactory));
	MOCK_METHOD(void, disconnectFromOlapAll, (CommClientConnectionPool& cliPool));
	MOCK_METHOD(void, init_impl, (CommServerObjectWithOlapInteface*	obj_, DatabaseManagerCommonWithOlap* manager_, const EslResolver* eslResolver_));
	void init(CommServerObjectWithOlapInteface*	obj_, DatabaseManagerCommonWithOlap* manager_, const EslResolver* eslResolver_ = nullptr)
	{
		return init_impl(obj_, manager_, eslResolver_);
	}
	MOCK_METHOD(void, processSendSavedMessages, (OlapStruct* olap, bool& toBeContinued));
	MOCK_METHOD(void, saveMessage, (UINT32 msgId, const CommMsgBody& body, int fromQueue, INT16 errCode, const char* errDescr, UINT32 olapId));
	MOCK_METHOD(void, saveQueueToOlapAll, ()); 
	MOCK_METHOD(OlapStruct*, getOlapById, (UINT32 olapId), (const));
	MOCK_METHOD(void, olapInDirectSendMode, (UINT32 olapId, bool inDirectSend));
	MOCK_METHOD(eHost, getHostId, (), (const));
	MOCK_METHOD(UINT64, getNextUniqueMsgId, ());
	MOCK_METHOD(void, processCommonOlapMessage, (UINT32 msgId, CommMsgParser& parser, DbmToOlapClientConn* conn));
	MOCK_METHOD(void, saveOlapMessageOnError, (UINT32 reqId, UINT32 msgId, CommMsgParser& parser, DbmToOlapClientConn* conn));
	using QueueSizeMap_t = unordered_map<UINT32, size_t>;
	MOCK_METHOD(void, getQueueSizes, (QueueSizeMap_t& queueSizes), (const));

	MOCK_METHOD(void, rollback, ());
};

#define PROP_LAST_MSG_ORDINAL_OLAP 	"LastMsgOrdinalOlap"
#define OLAPMESSAGES_TABLE_NAME	"MESSAGES"
#define OLAPMESSAGES_OBJECT_NAME "OlapMessages"

enum ProcessGenericMessageStatus
{
	processGenericMessageNormal			= 0, 
//	processGenericMessageRunIntoLock	= 1, 
//	processGenericMessagePostedToWorker	= 2, 
	processGenericMessageError			= 3,
    processGenericMessageDelayed        = 4,
	processGenericMessagePostedToChildObject = 5,
};

// PYR-32351
inline bool isMultiObjectMsgStatus( int msgStatus )
{
	return msgStatus == processGenericMessageDelayed || msgStatus == processGenericMessagePostedToChildObject;
}

class CommServerObjectWithOlapInteface
{
public:
	virtual ~CommServerObjectWithOlapInteface() {};

	virtual void postToOlap(UINT32 msgId, const CommMsgBody& body, bool sendAlwaysDirect, bool isPlayReplicaSync, BYTE msgMask, const OlapMsgSysInfo& msgSysInfo) = 0;
	virtual void processOlapMessage( UINT32 reqId, UINT32 msgId, const CommMsgBody& body, DbmToOlapClientConn* conn ) = 0;
	virtual bool addSpecialTicks( TicksAccumulator& acc, UINT32& t, UINT32& n, const HiresCounter& counter, int msgStatus ) const = 0;
	virtual void addMessageTicks(const HiresCounter& counter, int msgStatus) = 0;
	virtual void addInQueueSize( UINT32 sz ) = 0;
	virtual const char* getTraceModifier( int msgStatus ) = 0;
	virtual int getCommServerInQueueSize() const = 0;
	virtual vector<UINT32> getDbmIdsAsVector() const { return {}; }
};

class CommServerObjectWithOlap : public DbmServerObjectCommon, public CommServerObjectWithOlapInteface
{
protected:
	OlapServer olapServer;
	int replayMode = 0;
	bool useMsgTime = false;
	SrvTime msgSrvTime;
	time_t  msgTimeT = 0;
public:
	
	CommServerObjectWithOlap(_CommInterface& inter_) : DbmServerObjectCommon(inter_)
	{
	}
	MOCK_METHOD(int, getCommServerInQueueSize, (), (const, override));
	MOCK_METHOD(void, dynamicInit, (const PIniFile& iniFile), (override));
	MOCK_METHOD(void, processOlapMessage, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body, DbmToOlapClientConn* conn), (override));

protected:
	MOCK_METHOD(void, saveOlapMessageOnError, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body, DbmToOlapClientConn* conn));
	MOCK_METHOD(void, reportToHeLogger, (const CommMonitorLoggerObject& heLogger, CommMsgBody& reportBody), (override));
};


class InTransactionUpdates
{
protected:
	typedef list< LogMessage > _List;
	_List				preparedMessages;
public:
	InTransactionUpdates() {};
	MOCK_METHOD(void, commit, (CommServerObjectWithOlapInteface* dbmObj));
    MOCK_METHOD(void, rollback, ());
    MOCK_METHOD(void, insertMessage, (const UINT32 msgId, CommMsgBody& body, BYTE msgMask, const OlapMsgSysInfo& sysInfo));
	MOCK_METHOD(void, insertTransactionUpdatesAtFront, (list<LogMessage>&& logMsgList));
	MOCK_METHOD(void, setSequenceEnd, ());
	MOCK_METHOD(size_t, getSize, (), (const));
};

class OlapMessageProcessor
{
public:
	OlapMessageProcessor(const UINT32 *arr, UINT32 sizeArr) {}

	MOCK_METHOD(void, processOlapMessage, (UINT32 msgId, CommMsgParser &parser, DbmToOlapClientConn* conn, UINT32 reqId, OlapServer& olapServer), (const));

	MOCK_METHOD(bool, isAllowedMessage, (const UINT32 msgId), (const));
};

static bool isPCIPayloadOlapMsgId(UINT32 msgId) { return false; }

#endif //olapcommon_mock_h_included
