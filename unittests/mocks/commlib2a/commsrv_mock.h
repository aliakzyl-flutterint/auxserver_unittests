#ifndef commsrv_mock_h_included
#define commsrv_mock_h_included

#include "ppinclude.h"
#include "commmsgbody.h"
#include "commqueue.h"
#include "commidmap.h"
#include "commsubscr.h"
#include "commtime.h"
#include "ppiofile.h"
#include "commmsgheader.h"
#include <gmock/gmock.h>

#define SERVER_START_VER_STR "ver"

class CommServerObject
{
public:
	CommServerObject( _CommInterface& inter_ ) {}

	virtual void init( CommMsgBody& body ) {}

	using AsyncCall = RefAsyncCall;
	MOCK_METHOD(UINT32, postTimerMessage_impl, (UINT32 msgId, CommMsgBody& body, int msec, AsyncCall* asyncCall));
	UINT32 postTimerMessage( UINT32 msgId, CommMsgBody& body, int msec, AsyncCall* asyncCall = nullptr)
	{
		return postTimerMessage_impl(msgId, body, msec, asyncCall);
	}
	MOCK_METHOD(bool, deleteTimerMessage, (UINT32 handle));

	MOCK_METHOD(int, getInQueueSize, (), (const));
	MOCK_METHOD(int, getOutQueueSize, (), (const));
	MOCK_METHOD(UINT64, getWaitInQueueTime_impl, (UINT64 *readTime, UINT64 *writeTime));
	UINT64 getWaitInQueueTime(UINT64 *readTime = 0, UINT64 *writeTime = 0)
	{
		return getWaitInQueueTime_impl(readTime, writeTime);
	}
	MOCK_METHOD(const char*, getIdentification, (), (const));

	MOCK_METHOD(int, getNumberOfTimers, (), (const));
	virtual void processTimerMessage(UINT32 handle, UINT32 msgId, CommMsgBody& body) {}
	virtual void processTimerAsyncCall(UINT32 handle, UINT32 msgId, CommMsgBody& body, AsyncCall* asyncCall) {}
	virtual void processMessage( _CommMsg& msg ) = 0;
	MOCK_METHOD(_CommInterface&, getInterface, ());
	MOCK_METHOD(bool, exited, (), (const));
	MOCK_METHOD(void, exit, ());

	virtual void shutdown() {}
	virtual bool terminated() { return false; }
	virtual bool setConnInfoFromIni() const { return false; }
	virtual ~CommServerObject() {}

public:
	MOCK_METHOD(bool, _safeInit, (CommMsgBody& bod));
	MOCK_METHOD(bool, _safeProcessMessage, (_CommMsg& msg));
	MOCK_METHOD(bool, _safeProcessTimerMessage, (UINT32 handle, UINT32 msgId, CommMsgBody& body));
	MOCK_METHOD(void, _safeShutdown, ());
	MOCK_METHOD(int, _safeTerminated, ());
};

class CommServerObjectFactory
{
public:
	virtual CommServerObject* createServerObject( _CommInterface& inter ) const = 0;
	virtual  ~CommServerObjectFactory() {}
};

//****************************************************************************

class CommServerConnection;
class CommServerGuard
{
protected:
	CommServerConnection* conn = nullptr;
	const char* _name = nullptr;

public:
	CommServerGuard( const char* name_ ) {}
	MOCK_METHOD(void, _setConnection, (CommServerConnection* conn_));
	virtual ~CommServerGuard() {}

public:
	MOCK_METHOD(const char*, name, (), (const));
	virtual const char* currentName() const {}

public://overridable
	virtual void processFirstRequest( CommMsgParser& parser ) = 0;
	virtual void processAddRequest( CommMsgParser& parser ) = 0;

	virtual void processOutBlock( CommMsgBody& dst, CommMsgBody& src ) = 0;
	virtual void processInBlock( CommMsgBody& dst, CommMsgParser& src ) = 0;


	virtual bool gotUserAuth(CommMsgParser* parser, UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody) { return false; }
	virtual void delegateUserAuth(UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody ) { }

	virtual bool gotGuardUserInfo(CommMsgParser* parser, UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody) { return false; }

	virtual bool checkUserAuth( CommMsgParser* parser ) const { return false; }

	virtual const char* getPlainTextPassword_useWithExtremeCaution() const
	{
		return nullptr;
	}

public:
	virtual bool isSimple() const { return false; }
	virtual void encryptMsg(const CommMsgBody& src, PBlock& dst) const {}
	virtual void decryptMsg(const BYTE * block, size_t len, CommMsgBody& dst) const {}
	virtual bool isEncryptionInit() const { return false; }
	virtual size_t getKeyLen() const { return 0; }

protected:
	MOCK_METHOD(void, _postGuardError, (UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody));
	MOCK_METHOD(void, _postGuardAddResponse, (const CommMsgBody& body));
	MOCK_METHOD(void, _postGuardRequestGranted, (const CommMsgBody& body, const CommMsgBody* infoMsgBody));
};

class CommServerGuardFactory
{
public:
	virtual CommServerGuard* createGuard(const vector< const char* >& guardNames) = 0;
	virtual ~CommServerGuardFactory() {}
};

class CommServerConnectionFactory
{
public:
	BYTE authPriority = 0;
	BYTE normalPriority = 0;
	bool clientPriorityAllowed = false;

public:
	CommServerConnectionFactory( CommServerGuardFactory& guardFactory_ ) {}
	virtual ~CommServerConnectionFactory() {}
	virtual void addGuardFactory(CommServerGuardFactory& guardFactory_) {}
	MOCK_METHOD(CommServerGuard*, createGuard, (const vector< const char* >& guardNames));
public:
	virtual CommServerConnection* createConnection() = 0;
};


class CommServerConnectionPool;
// !!! CommServerConnection have to keep all private members, because we have commsrvconn_mock.cpp and we should keep binary compatibility !!!
class CommServerConnection
{
private:
	friend class CommServerGuard;
	CommServerConnectionPool* pool = nullptr;

private:
	friend class CommServerConnectionPool;
	friend class CommServerConnectionEx;
	friend class CommRedundantServerConnection;
	friend class CommProxyServerConnectionPool;
	friend class CommProxyServerConnection;
	CommServerGuard* guard = nullptr;
	PString server;
	PString serverObject;
	ConnInfo clientConnInfo;

	PString factoryType;
	int state = 0;
	BYTE priority = 0;
	UINT32 thisId = 0;
	UINT32 peerId = 0;
	UINT32 sessionId = 0;
	bool qMonitor = false;
	bool rtMonitor = false;
	bool inPreConnectedMap = false;
	bool closePending = false;

	BYTE normalPriority = 0;
	vector< PString > physAddresses;
	UINT32 version = 0;
public:
	CommServerConnection() {}
	virtual ~CommServerConnection() {}

	MOCK_METHOD(bool, isConnected, (), (const));
	MOCK_METHOD(bool, isClosePending, (), (const));
	MOCK_METHOD(UINT32, id, (), (const));
	MOCK_METHOD(BYTE, getPriority, (), (const));
	MOCK_METHOD(const char*, getServer, (), (const));
	MOCK_METHOD(const char*, getServerObject, (), (const));
	MOCK_METHOD(const ConnInfo&, getClientConnInfo, (), (const));
	MOCK_METHOD(const char*, getServerConnType, (), (const));
	MOCK_METHOD(UINT32, getVersion, (), (const));
	MOCK_METHOD(const CommServerGuard*, getGuard, (), (const));

	MOCK_METHOD(bool, isPreConnected, (), (const));
protected:
	MOCK_METHOD(CommServerConnectionPool*, _getPool, ());

public:
	MOCK_METHOD(int, connPathLen, (), (const));
	MOCK_METHOD(const char*, connPathPoint, (int i), (const));
	MOCK_METHOD(bool, forceDisconnectClient, ());

	virtual void post(UINT32 msgId, CommMsgBody& body) {}
	MOCK_METHOD(void, monitorQuality, ());
	MOCK_METHOD(void, monitorRoundTrip, ());
	MOCK_METHOD(void, monitorIsAlive, ());

	virtual void processMessage(UINT32 msgId, const CommMsgBody& body) {}
	virtual void connected() {}
	virtual void qualityUpdated(int quality) {}
	virtual void roundTripUpdated(UINT32 lastRoundTrip) {}
	virtual void isAlive() {}

	virtual void closedOrDisconnected(int errCode, const char* errMsg) {}

	virtual void logExtStats() {}

public:
	virtual void getUserAuth(const char* guardType, const char* user, CommMsgBody& clientExtra, CommMsgBody& request) {}
	virtual void getUserAuth(const char* guardType, UINT32 userIntId, CommMsgBody& clientExtra, CommMsgBody& request) {}

	MOCK_METHOD(bool, gotUserAuth_impl, (CommMsgParser* parser, UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody));
	MOCK_METHOD(void, delegateUserAuth_impl, (UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody));
	bool gotUserAuth(CommMsgParser* parser, UINT16 errCode = 0, const char* errMsg = 0, const CommMsgBody* errMsgBody = 0)
	{
		return gotUserAuth_impl(parser, errCode, errMsg, errMsgBody);
	}
	void delegateUserAuth(UINT16 errCode = 0, const char* errMsg = 0, const CommMsgBody* errMsgBody = 0)
	{
		return delegateUserAuth(errCode, errMsg, errMsgBody);
	}

	MOCK_METHOD(bool, checkUserAuth, (CommMsgParser* parser), (const));
	virtual void getGuardUserInfo(const char* guardType, const char* user, CommMsgBody& clientExtra, CommMsgBody& request) {}
	MOCK_METHOD(bool, gotGuardUserInfo_impl, (CommMsgParser* parser, UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody));
	bool gotGuardUserInfo(CommMsgParser* parser, UINT16 errCode = 0, const char* errMsg = 0, const CommMsgBody* errMsgBody = 0)
	{
		return gotGuardUserInfo_impl(parser, errCode, errMsg, errMsgBody);
	}
private:
    CommServerConnection(const CommServerConnection&) = delete;
    CommServerConnection& operator=(const CommServerConnection&) = delete;
};

class CommServerConnectionEx : public CommServerConnection
{
	struct _Item
	{
		UINT32 currentNumber;
		CommMsgBody body;
	};
	typedef list<_Item*> _List;
public:
	CommServerConnectionEx() {}
	virtual ~CommServerConnectionEx() {}
	virtual void post(UINT32 msgId, CommMsgBody& body) {}
	MOCK_METHOD(bool, setPollTime, (INT32 pollTime_));

	typedef _List::iterator iterator;
	MOCK_METHOD(size_t, _size, (), (const));
	MOCK_METHOD(iterator, _begin, ());
	MOCK_METHOD(iterator, _end, ());
	MOCK_METHOD(iterator, _extractMsgIdAndBodyAndErase, (iterator it, UINT32& msgId, CommMsgBody& body));
};


class CommServerConnectionPool
{
public:
	enum eTimeType
	{
		normalTime,
		recordingType,
		replayingType
	};

public:
	MOCK_METHOD(void, setTypeOfTime, (eTimeType type));
	MOCK_METHOD(time_t, messageTime, (), (const));
	MOCK_METHOD(void, messageSrvLocalTime, (CommSrvTime & t), (const));
	MOCK_METHOD(void, _setMessageTime, (time_t sec));
	MOCK_METHOD(void, _setMessageSrvLocalTime, (const CommSrvTime & t));

	class ConnectionIterator
	{
	};

public:
	CommServerConnectionPool(_CommInterface& inter_ ) {}
	MOCK_METHOD(void, registerFactory, (const char* name, CommServerConnectionFactory& factory));
	MOCK_METHOD(void, unregisterFactory, (const char* name));
	virtual ~CommServerConnectionPool() {}
	MOCK_METHOD(void, deleteAllConnections, ());

	MOCK_METHOD(CommServerConnection*, findConnection, (UINT32 connId));
	MOCK_METHOD(const CommServerConnection*, findConnection, (UINT32 connId), (const));
	MOCK_METHOD(CommServerConnection*, firstConnection, (ConnectionIterator& i));
	MOCK_METHOD(CommServerConnection*, nextConnection, (ConnectionIterator& i));
	MOCK_METHOD(size_t, numberOfConnections, (), (const));


	MOCK_METHOD(void, initRecordReplay, (const char * name));
	MOCK_METHOD(void, closeRecordReplay, ());

	MOCK_METHOD(void, disconnect_impl, (CommServerConnection* conn, UINT16 errCode, const char * errMessage));
	void disconnect(CommServerConnection* conn, UINT16 errCode = 0, const char * errMessage = 0)
	{
		return disconnect_impl(conn, errCode, errMessage);
	}

public:
	MOCK_METHOD(bool, _processMessage, (_CommMsg& msg));
	
	virtual bool _aboutToConnect(const CommMsgBody & body, const char * connType) { return false; }
};

#if 0
template< class Conn >
class CommServerConnectionFactoryEx
{
public:
	virtual Conn* createConnection() {}
};

template< class Conn >
class CommServerConnectionPoolEx : public CommServerConnectionPool
{
public:
	CommServerConnectionPoolEx( _CommInterface& inter_ ) : CommServerConnectionPool( inter_ ) {}
	MOCK_METHOD(void, registerFactory, (const char* name, CommServerConnectionFactoryEx< Conn >& factoryEx);

public:
	MOCK_METHOD(Conn*, findConnection, (UINT32 connId));
	MOCK_METHOD(Conn*, firstConnection, (ConnectionIterator& i));
	MOCK_METHOD(Conn*, nextConnection, (ConnectionIterator& i));

	MOCK_METHOD(void, disconnect, (Conn* conn));
};
#endif

//****************************************************************************

class CommServerPublisherPool;

class CommServerPublisher : public CommSubscription
{
public:
	struct UpdateMsg
	{
	public:
		MOCK_METHOD(bool, shouldBePosted, (), (const));
		MOCK_METHOD(const CommMsgBody&, getUpdateMsgBody, (), (const));
	};

	BYTE priority = 0;
public:
	CommServerPublisher() {}
	MOCK_METHOD(bool, isPublished, (), (const));
	MOCK_METHOD(const char*, publishedAs, (), (const));
	MOCK_METHOD(const UINT32, getNumberOfSubscribers, (), (const));

	MOCK_METHOD(void, startUpdateMsg, (UpdateMsg& updateMsg), (const));

	MOCK_METHOD(int, appendNode, (const int* path, int pathLen, UpdateMsg* updateMsg));
	MOCK_METHOD(int, appendLeaf, (const int* path, int pathLen, CommMsgBody& msg, UpdateMsg* updateMsg));
	MOCK_METHOD(void, updateLeaf, (const int* path, int pathLen, CommMsgBody& msg, UpdateMsg* updateMsg));
	MOCK_METHOD(void, removeLeaf, (const int* path, int pathLen, UpdateMsg* updateMsg));
	MOCK_METHOD(void, removeNode, (const int* path, int pathLen, UpdateMsg* updateMsg));

	static void attachMsg(UINT32 attachId, const CommMsgBody& attachment, UpdateMsg* updateMsg) {}

	MOCK_METHOD(void, finishUpdateMsg, (UpdateMsg& updateMsg), (const));
	MOCK_METHOD(void, postUpdate, (UpdateMsg& update));
	MOCK_METHOD(void, startCountNumberOfSubscribers, ());
	MOCK_METHOD(void, stopCountNumberOfSubscribers, ());
};

class CommServerPublisherPool
{
public:
	CommServerPublisherPool(_CommInterface& inter_) {}
	MOCK_METHOD(void, publish, (const char* name, CommServerPublisher& publisher));
	MOCK_METHOD(bool, havePublisher, (const char* name), (const));
	MOCK_METHOD(void, unpublish, (const char* name));
	MOCK_METHOD(void, _postUpdate, (const CommServerPublisher& publisher, CommServerPublisher::UpdateMsg& update));

public:
	MOCK_METHOD(bool, _processMessage, (_CommMsg& msg));
	virtual bool _aboutToSubscribe(const CommMsgBody & body, const char * channel) { return false; }
	virtual void _afterUnsubscribe(const char * channel) {}
	
	MOCK_METHOD(void, processSubscrRequest, (CommMsgBody & body));
};

#endif
