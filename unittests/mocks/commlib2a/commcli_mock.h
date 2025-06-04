#ifndef commcli_mock_h_included
#define commcli_mock_h_included

#include "ppinclude.h"
#include "ppstring.h"
#include "pptime.h"
#include "pplogfile.h"
#include "commmsgbody.h"
#include "commqueue.h"
#include "commidmap.h"
#include "commconn.h"
#include "commsubscr.h"
#include "commmsgheader.h"
#include "asynccall.h"
#include <gmock/gmock.h>

class CommServerConnection;


class CommClientAuthCallback
{
public:
	virtual void auth(PString &user, PString &pwd, PString  &sid, CommMsgBody & extra) = 0;
	virtual void auth(UINT32 &userIntId, PString &pwd, PString  &sid, CommMsgBody & extra) {}
};

class CommClientGuard
{
public:
	CommClientGuard(const char* name_) {}

public:
	const char* name() const { return nullptr; }

public:
	virtual void composeFirstRequest(CommMsgBody& msgBody) = 0;
	virtual bool processResponse(CommMsgBody& msgBody, CommMsgParser& parser) = 0;
	virtual bool processGranted(CommMsgParser& parser) = 0;
	virtual void composeGuardNameList(CommMsgBody& msgBody) const = 0;

	virtual void processOutBlock(CommMsgBody& dst, CommMsgBody& src) = 0;
	virtual void processInBlock(CommMsgBody& dst, CommMsgParser& src) = 0;
	virtual void encryptMsg(const CommMsgBody& src, PBlock& dst) const {}
	virtual void decryptMsg(const BYTE * block, size_t len, CommMsgBody& dst) const {}
	virtual bool isEncryptionInit() const { return false; }

public:
	virtual bool isSimple() const { return false; }

	virtual ~CommClientGuard() {}
};

class CommClientGuardAuth
{
public:
	virtual ~CommClientGuardAuth() {}

};

class CommClientGuardFactory
{
public:
	CommClientGuardFactory() {}
	virtual ~CommClientGuardFactory() {}
	
	virtual CommClientGuardAuth* auth() { return nullptr; } 
	virtual void composeGuardNameList(CommMsgBody& msgBody) const = 0;
	virtual CommClientGuard* createGuard(const char* guardName, CommClientGuardAuth* guardAuth) = 0;

private:
	CommClientGuardFactory(const CommClientGuardFactory& other) = delete;
	CommClientGuardFactory& operator=(const CommClientGuardFactory& other) = delete;
};

class CommClientConnectionPool;
class CommClientConnection
{
public:
	CommClientConnection(CommClientGuardFactory& guardFactory_) {}
	virtual ~CommClientConnection() {}

	MOCK_METHOD(bool, isMyGuardFactory, (const CommClientGuardFactory& guardFactory_), (const));
	MOCK_METHOD(bool, isConnected, (), (const));
	MOCK_METHOD(bool, poolEquals, (const CommClientConnectionPool* pool_), (const));
	MOCK_METHOD(bool, isClosePending, (), (const));
	MOCK_METHOD(void, setPriority, (BYTE priority_));
	MOCK_METHOD(BYTE, getPriority, (), (const));
	MOCK_METHOD(UINT32, id, (), (const));
	MOCK_METHOD(const char*, getServer, (), (const));
	MOCK_METHOD(const char*, getServerObject, (), (const));
	MOCK_METHOD(const char*, getServerConnType, (), (const));
	MOCK_METHOD(const ConnInfo&, getConnInfo, (), (const));
	MOCK_METHOD(const CommClientGuard*, getGuard, (), (const));

	MOCK_METHOD(UINT32, getVersion, (), (const));

public:
	virtual void post(UINT32 msgId, CommMsgBody& body) {}
	MOCK_METHOD(void, monitorQuality, ());

	virtual void processMessage(UINT32 msgId, const CommMsgBody& body) {}
	virtual void connected() {}
	virtual void connectedWithInfo(CommMsgBody *infoBody) {}
	virtual void qualityUpdated(int quality) {}
	virtual bool closedOrDisconnected(int errCode, const char* errMsg) { return false; }
	virtual bool closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody ) { return false; }
	virtual void processQualityRequest() {}
	MOCK_METHOD(void, postQualityUpdate, (BYTE quality_));
	virtual void processKeepAliveRequest() {}
	MOCK_METHOD(void, postKeepAlive, ());

private:
	CommClientConnection(const CommClientConnection& other) = delete;
	CommClientConnection& operator=(const CommClientConnection& other) = delete;
	
	virtual void _clearAll() {}
};

class CommClientConnectionEx : public CommClientConnection
{
private:
	struct _Item
	{
		UINT32 currentNumber;
		CommMsgBody body;
	};
	typedef list< _Item* > _List;

public:
	CommClientConnectionEx(CommClientGuardFactory& guardFactory_) : CommClientConnection(guardFactory_) {}
	virtual ~CommClientConnectionEx() {}
	
	virtual void post(UINT32 msgId, CommMsgBody& body) {}
	MOCK_METHOD(bool, setPollTime, (INT32 pollTime_));

	typedef _List::iterator iterator;

	MOCK_METHOD(size_t, _size, (), (const));
	MOCK_METHOD(iterator, _begin, ());
	MOCK_METHOD(iterator, _end, ());
	MOCK_METHOD(iterator, _extractMsgIdAndBodyAndErase, (iterator it, UINT32& msgId, CommMsgBody& body));
};

class CommClientGConnection 
{
public:
	using AsyncCall = RefAsyncCall;

public:
	class _ConnHandler : public CommClientConnection
	{
	public:
		_ConnHandler(CommClientGuardFactory& guardFactory_) : CommClientConnection(guardFactory_) {}
		MOCK_METHOD(void, _init, (CommClientGConnection* gConn_));
		MOCK_METHOD(CommClientGConnection*, getGconn, ());
		MOCK_METHOD(bool, isActuallyConnected, (), (const));

	public:
		MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
		MOCK_METHOD(void, connected, (), (override));
		MOCK_METHOD(void, qualityUpdated, (int quality), (override));
		MOCK_METHOD(bool, closedOrDisconnected, (int errCode, const char* errMsg, CommMsgBody* errMsgBody), (override));
	};
private:
	struct _Item
	{
		_Item(UINT32 _msgId, CommMsgBody& _body, AsyncCall* _call) {}
		~_Item() {}
		UINT32 msgId = 0;
		CommMsgBody patchedBody;
		AsyncCall* call = nullptr;
	};

public:
	typedef list< _Item* >::const_iterator const_iterator;

public:
	CommClientGConnection(CommClientGuardFactory& guardFactory_) {}
	virtual ~CommClientGConnection() {}
	
	MOCK_METHOD(CommClientConnection&, underlyingConnection, ());
	MOCK_METHOD(const CommClientConnection&, underlyingConnection, (), (const));
	MOCK_METHOD(bool, isActuallyConnected, (), (const));
	virtual UINT32 post(UINT32 msgId, CommMsgBody& body, AsyncCall* call = 0) { return 0; }
	virtual void cancelPost(UINT32 requestId) {}
	
	MOCK_METHOD(void, reserve, (UINT32 size));

public:
	MOCK_METHOD(size_t, _size, (), (const));
	MOCK_METHOD(const_iterator, _begin, (), (const));
	MOCK_METHOD(const_iterator, _end, (), (const));
	static UINT32 _getRequestId(const_iterator it) { return 0; }
	static UINT32 _getMsgId(const_iterator it) { return 0; }
	static void _getMsgBody(const_iterator it, CommMsgBody& ret) {}
	static AsyncCall* _getCall(const_iterator it ) { return nullptr; }
	MOCK_METHOD(const_iterator, _getIterator, (UINT32 reqId), (const));

	MOCK_METHOD(void, _clearAll, ());

public:
	virtual void processGMessage(UINT32 requestId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call) {}
	virtual void connected() {}
	virtual void qualityUpdated(int quality) {}
	virtual bool closedOrDisconnected(int errCode, const char* errMsg) { return false; }
	virtual bool closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) { return false; }
	virtual bool beforeGConnectedPost(UINT32 msgId, CommMsgBody& body) { return false; }
};

class CommClientGConnectionEx
{
public:
	using AsyncCall = RefAsyncCall;

private:
	struct _Item
	{
		_Item(UINT32 _msgId, CommMsgBody& _body, AsyncCall* _call) {}
		~_Item() {}
		UINT32 msgId = 0;
		UINT32 requestId = 0;
		CommMsgBody patchedBody;
		AsyncCall* call = nullptr;
	};

public:
	typedef list< _Item* >::const_iterator const_iterator;

public:
	CommClientGConnectionEx(CommClientGuardFactory& guardFactory_) {}
	virtual ~CommClientGConnectionEx() {}
	
	MOCK_METHOD(CommClientConnectionEx&, underlyingConnection, ());
	MOCK_METHOD(const CommClientConnectionEx&, underlyingConnection, (), (const));
	MOCK_METHOD(bool, isActuallyConnected, (), (const));
	virtual UINT32 post( UINT32 msgId, CommMsgBody& body, AsyncCall* call = 0) {}
	MOCK_METHOD(void, cancelPost, (UINT32 requestId));
	MOCK_METHOD(bool, setPollTime, (INT32 pollTime_));

public:
	MOCK_METHOD(size_t, _size, (), (const));
	MOCK_METHOD(const_iterator, _begin, (), (const));
	MOCK_METHOD(const_iterator, _end, (), (const));
	static UINT32 _getRequestId(const_iterator it) { return 0; }
	static UINT32 _getMsgId(const_iterator it) { return 0; }
	static void _getMsgBody(const_iterator it, CommMsgBody& ret) {}
	static AsyncCall* _getCall(const_iterator it) { return nullptr; }
	MOCK_METHOD(const_iterator, _getIterator, (UINT32 reqId), (const));
	MOCK_METHOD(const_iterator, _erase, (const_iterator it));

	MOCK_METHOD(void, _clearAll, ());

public:
	virtual void processGMessage(UINT32 requestId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call) {}
	virtual void connected() {}
	virtual void qualityUpdated( int quality ) {}
	virtual bool closedOrDisconnected(int errCode, const char* errMsg) { return false; }
	virtual bool closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) { return false; }
};


class CommClientConnectionPool
{
public:
	class ConnectionIterator
	{
	};
public:
	CommClientConnectionPool(_CommInterface& inter_) {}
	MOCK_METHOD(void, connect_impl, (CommClientConnection& conn, const char* server, const char* serverObject, const char* serverConnType, const ConnInfo* connInfo));
	void connect(CommClientConnection& conn, const char* server, const char* serverObject, const char* serverConnType = "", const ConnInfo* connInfo = nullptr)
	{
		return connect_impl(conn, server, serverObject, serverConnType, connInfo);
	}
	MOCK_METHOD(void, disconnect, (CommClientConnection& conn));
	virtual ~CommClientConnectionPool() {}

public:
	MOCK_METHOD(CommClientConnection*, firstConnection, (ConnectionIterator& i));
	MOCK_METHOD(CommClientConnection*, nextConnection, (ConnectionIterator& i));
	MOCK_METHOD(CommClientConnection*, findConnection, (UINT32 connId));

public:
	MOCK_METHOD(bool, _processMessage, (_CommMsg& msg));

	class CommEmbeddedMessageOnTheFlyCallback
	{
	public:
		virtual void callback( const _CommMsg & msg) = 0;
	};

	static void _getEmbeddedMessageOnTheFly( const _CommMsg& msg, UINT32 subscrMsgId, CommEmbeddedMessageOnTheFlyCallback & callBack) {}
};

//****************************************************************************

class CommClientSubscriberPool;
class CommClientSubscriber : public CommSubscription
{
public:
	CommClientSubscriber() {}
	~CommClientSubscriber() {}

	MOCK_METHOD(bool, isSubscribed, (), (const));
	MOCK_METHOD(bool, poolEquals, (const CommClientSubscriberPool* pool_), (const));
	MOCK_METHOD(UINT32, id, (), (const));
	MOCK_METHOD(const char*, getServer, (), (const));
	MOCK_METHOD(const char*, getServerObject, (), (const));
	MOCK_METHOD(const char*, getServerChannel, (), (const));

public:
	virtual void beginTrans() {}
	virtual void commitTrans() {}

	virtual void synchronized() {}
	virtual void desynchronized() {}

	virtual bool closed(int errCode, const char* errMsg) {}

protected://safety wrappers
	MOCK_METHOD(void, _safeBeginTrans, ());
	MOCK_METHOD(void, _safeCommitTrans, ());
	MOCK_METHOD(void, _safeSynchronized, ());
	MOCK_METHOD(void, _safeDesynchronized, ());
	MOCK_METHOD(bool, _safeClosed, (int errCode, const char* errMsg));
};

class CommClientSubscriberPool
{
public:
	CommClientSubscriberPool(_CommInterface& inter_) {}
	MOCK_METHOD(void, subscribe, (CommClientSubscriber& subscr, const char* server, const char* serverObject, const char* serverChannel));
	MOCK_METHOD(void, unsubscribe, (CommClientSubscriber& subscr));
	MOCK_METHOD(void, freeze, (CommClientSubscriber& subscr));
	MOCK_METHOD(void, defrost, (CommClientSubscriber& subscr));
	MOCK_METHOD(void, subscribeFrozen, (CommClientSubscriber& subscr, const char* server, const char* serverObject, const char* serverChannel));
	~CommClientSubscriberPool() {}

public:
	MOCK_METHOD(bool, hasSubscribers, (), (const));

public:
	static void parseMessageOnTheFly( CommSubscription::OnTheFlyCallback& callback, const _CommMsg& msg, UINT32 subscrId = 0 );
	bool _processMessage( _CommMsg& msg );
};

#endif
