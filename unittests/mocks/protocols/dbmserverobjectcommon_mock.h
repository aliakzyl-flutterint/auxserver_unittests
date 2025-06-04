#ifndef dbmserverobjectcommon_mock_h_included
#define dbmserverobjectcommon_mock_h_included

#include "../commlib2a/commgrdnull_mock.h"
#include "dbcommon_mock.h"
#include <functional>
#include <gmock/gmock.h>

class DbmServerObjectCommon;
class CommMonitorLoggerObject;

#pragma warning( push )
#pragma warning( disable: 4355 )

#define GENERATOR_CONNECTION	"generator_connection"

class DbmCommonServerConnection : public CommServerConnection
{
protected:
	DbmServerObjectCommon* obj = nullptr;
public:
	DbmCommonServerConnection(DbmServerObjectCommon* obj_) {}
	MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
};

class DbmCommonServerConnFactory : public CommServerConnectionFactory
{
public:
	DbmCommonServerConnFactory( CommServerGuardFactory& guardFactory, DbmServerObjectCommon* obj_ )
		: CommServerConnectionFactory( guardFactory )
	{
	}

	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

class IdRangeClientConnection;

class DbmServerObjectCommon : public CommServerObject
{
protected:
	IdRangeClientConnection* idRangeConn = nullptr;
	class InitGeneratorCallback : public DbmGenerator::DbmGeneratorCallback // to register factories upon generator init
	{
	public:
		InitGeneratorCallback(DbmServerObjectCommon* obj_) {}
		MOCK_METHOD(void, process, (), (override));
	};
	virtual void connectToMasterGenerator(const PIniFile& iniFile) {}

protected:
	DbmServerObjectCommon( _CommInterface& inter_ )
		: CommServerObject( inter_ )
	{
	}

	virtual ~DbmServerObjectCommon() {}

	// Must be called once from static init of server object after dbManager initialization
	MOCK_METHOD(void,  initGenerator, (
			DatabaseManagerCommon* dbManagerCommon_
			, CommServerConnectionPool* srvPool_
			, CommClientConnectionPool* cliPool_
			, CommClientNullGuardFactory* clientGuardFactory_
			, const PIniFile& iniFile
			));

	virtual void reportToHeLogger(const CommMonitorLoggerObject& heLogger, CommMsgBody& reportBody) {}

	MOCK_METHOD(void, setDbManagerCommon, (DatabaseManagerCommon* dbManagerCommon_));
	MOCK_METHOD(void, setOpenDataStorageFunc, (const std::function<bool()>& reconnect_));
	MOCK_METHOD(void, processDbmCommonServerMessageImp, (UINT32 msgId, const CommMsgBody& body, DbmCommonServerConnection& conn));
	
	bool generatorReady = false;
	bool useMasterGenerator = false;
	bool generatorFactoryRegistered = false;

public:
	MOCK_METHOD(void, processDbmCommonServerMessage, (UINT32 msgId, const CommMsgBody& body, DbmCommonServerConnection& conn));
	virtual void dynamicInit(const PIniFile& iniFile) {}
	virtual bool registerAllFactories() { return false; }
	virtual void reportGeneratorConnStatus(bool connected) {}
};

class IdRangeClientConnection : public CommClientGConnection
{
public:
	INT32 idRangeRequestsSent = 0;

	IdRangeClientConnection( CommClientGuardFactory& guardFactory_, DbmServerObjectCommon* obj_ )
		: CommClientGConnection( guardFactory_ )
	{}

	MOCK_METHOD(UINT32, postX, (UINT32 msgId, CommMsgBody& body, AsyncCall* call));

	MOCK_METHOD(bool, closedOrDisconnected, (int errCode, const char* errMsg), (override));
	MOCK_METHOD(bool, getIsConnected, (), (const));

private:
	virtual void processGMessage(UINT32 requestId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call) override {}
};

#pragma warning( pop )

#endif // dbmserverobjectcommon_mock_h_included
