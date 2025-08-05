#include "AtfCipwaConn.h"
#include "AtfCommServerObject.h"
#include "AtfCommPlayerConns.h"
#include "Service.h"
#include "telemetry/gateway/client.h"

void Atf::_AtfCipwaConnection::_wrapJSonStringAsMsgBody(const PString& jsonString, CommMsgBody& msg, size_t minCompressLength)
{}

void Atf::_AtfCipwaConnection::_unwrapJSonStringFromMsgBody(const CommMsgBody& msg, PString& jsonString)
{ }

bool Atf::_AtfCipwaConnection::_guessJSonStringMsgBodyFormat(const CommMsgBody& body)
{
	return false;
}

Atf::AtfCommObjectImpl::AtfCommObjectImpl(_CommInterface& i, unique_ptr<CommClientConnectionPool>&& cliPool_)
	: cliPool(nullptr)
	, serverPool(i)
	, clientPool(*cliPool)
	, publishPool(i)
	,heLoggerReporter(nullptr)
{
}

CommServerConnectionPool::CommServerConnectionPool(_CommInterface& inter_)
{
}

CommServerConnectionPool::~CommServerConnectionPool()
{}

CommServerPublisherPool::CommServerPublisherPool(_CommInterface& inter_)
{
}

Atf::AtfCommObjectImpl::~AtfCommObjectImpl()
{
}

void Atf::AtfCommObjectImpl::onTimer(UINT32 handle, UINT32 msgId, const CommMsgBody& body)
{
}

void Atf::AtfCommObjectImpl::_processMessage(_CommMsg& msg)
{ }

CommServerConnection* Atf::AtfCommObjectImpl::findConnectionById(UINT32 connId)
{
	return nullptr;
}

void Atf::AtfCommObjectImpl::_processTimerMessage(UINT32 handle, UINT32 msgId, CommMsgBody& body)
{
}

void Atf::AtfCommObjectImpl::registerPlayerOrCipwaConnectionFactory(const char* name, Atf::AtfCommPlayerOrCipwaConnectionFactory& factory, bool supportCIPWA)
{
}

void Atf::AtfCommObjectImpl::dynamicConnect(AtfCommClientConnection& conn, const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName /* for logging purpose only */)
{}

void Atf::AtfCommObjectImpl::dynamicConnect(AtfCommClientGConnection& gconn, const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName /* for logging purpose only */)
{}

void Atf::AtfCommObjectImpl::dynamicConnect(const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName /* for logging purpose */, CommClientConnection& conn)
{
}

void Atf::AtfCommObjectImpl::publish(AtfCommServerPublisherInterface& publisher, const char* name, bool autoFlushUpdate, bool supportCIPWA)
{
}

void Atf::AtfCommObjectImpl::publish(CommServerPublisherPool& myPublisherPool, AtfCommServerPublisherInterface& publisher, const char* name, bool autoFlushUpdate, bool supportCIPWA)
{
}
void Atf::AtfCommObjectImpl::myPLog_internal(_In_z_ _Printf_format_string_ const char* format, ...) const
{
}

void Atf::AtfCommObjectImpl::myPLogDebug_internal(_In_z_ _Printf_format_string_ const char* format, ...) const
{}

void Atf::AtfCommObjectImpl::myPLogAlways_internal(_In_z_ _Printf_format_string_ const char* format, ...) const
{}

void Atf::AtfCommObjectImpl::myPLogValist(_In_z_ _Printf_format_string_ const char* format, va_list args) const
{}

void Atf::AtfCommObjectImpl::myPLogMsgProt(const Atf::MessageProtocol& prot, const char* logMarker) const
{}

Atf::ServiceMsgDispatcher* Atf::AtfCommObjectImpl::getMsgDispatcher()
{
	return nullptr;
}
void  Atf::AtfCommObjectImpl::addCondition(ServiceCondition* condition)
{
}
void Atf::AtfCommObjectImpl::processServiceEvent(UINT32 eventType, const void* evt /*= NULL*/)
{
}

void Atf::AtfCommObjectImpl::registerAtfServerGConnectionFactory(const char* name, AtfServerReverseGConnectionFactory& gfactory)
{
}

void Atf::AtfCommObjectImpl::invalidServerGConnectionTag(const char* connTag)
{
}

Atf::ServiceReplyWaitableOnReliableConnection::~ServiceReplyWaitableOnReliableConnection()
{
}

Atf::AtfCommClientGConnection::AtfCommClientGConnection(AtfCommObjectImpl* obj, CommClientGuardFactory& guardFactory, const char* connTraceMarker)
	: CommClientGConnection(guardFactory), atfServerObj(nullptr), _inAtfTraceLog(false)
{ }
Atf::AtfCommClientGConnection::~AtfCommClientGConnection()
{
}

void Atf::AtfCommClientGConnection::setTraceMarker(const char* newTraceMarker)
{}

void Atf::AtfCommClientGConnection::traceOutgoing(UINT32 msgId, UINT32 reqId)
{
}

UINT32 Atf::AtfCommClientGConnection::post(UINT32 msgId, CommMsgBody& body, AsyncCall* call /* = 0 */)
{
	return 0;
}

UINT32 Atf::AtfCommClientGConnection::asyncSend(const MessageProtocol& msg, std::function<void(UINT32 reqId, UINT32 replyMsgId, const CommMsgBody& replyMsgBody)> callbackFunc, bool trace /*= true */)
{
	return 0;
}

void Atf::AtfCommClientGConnection::processGMessage(UINT32 requestId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call)
{
}

void Atf::AtfCommClientGConnection::_processGMessage(UINT32 requestId, UINT32 msgId, const CommMsgBody& body)  // the default implementation if subclass does not implement processGMessage(...) or _processGMessage(...) function
{
}

void Atf::AtfCommClientGConnection::connected()
{
}

bool Atf::AtfCommClientGConnection::closedOrDisconnected(int errCode, const char* errMsg)
{
	return false;
}

bool Atf::AtfCommClientGConnection::closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody)
{
	return false;
}

void Atf::AtfCommClientGConnection::_traceConnected()
{
}

void Atf::AtfCommClientGConnection::_traceDisconnected(int errCode, const char* errMsg)
{}

Atf::AtfCommServerConnection::AtfCommServerConnection(AtfCommObjectImpl* obj_, bool isPeerGConnection_, const char* connTraceMarker)
	: atfServerObj(nullptr), _isPeerGConnection(isPeerGConnection_), _inAtfTraceLog(false)
{
}

void Atf::AtfCommServerConnection::setTraceMarker(const char* newTraceMarker)
{
}

void Atf::AtfCommServerConnection::postMsg(const Atf::MessageProtocol& msg, bool trace /* = true */)
{
}

void Atf::AtfCommServerConnection::postMsgWithId(UINT32 msgId, const MessageProtocol& msg, bool trace /* = true */)
{
}

void Atf::AtfCommServerConnection::postGMsg(UINT32 reqId, UINT32 msgId, CommMsgBody& body)
{}


void Atf::AtfCommServerConnection::traceOutgoing(UINT32 msgId, const CommMsgBody& body)
{ }

void Atf::AtfCommServerConnection::post(UINT32 msgId, CommMsgBody& body)
{
}

void Atf::AtfCommServerConnection::processMessage(UINT32 msgId, const CommMsgBody& body)
{
}

void Atf::AtfCommServerConnection::_processMessage(UINT32 msgId, const CommMsgBody& body)  // the default implementation if subclass does not implement processMessage(...) or _processMessage(...) function
{
}

void Atf::AtfCommServerConnection::connected()
{
}

void Atf::AtfCommServerConnection::closedOrDisconnected(int errCode, const char* errMsg)
{
}

void Atf::AtfCommServerConnection::_traceConnected()
{
}

void Atf::AtfCommServerConnection::_traceDisconnected(int errCode, const char* errMsg)
{
}

Atf::ServiceReplyWaitableOnReliableConnection::ServiceReplyWaitableOnReliableConnection()
{
}

void Atf::Service::setServiceReturnMsg(UINT32 resMsgId, CommMsgBody& resMsg)
{ }

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnection& conn, UINT32 msgId, CommMsgBody& body)
{
	return 0;
}

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnection& conn, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
	return 0;
}

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnectionEx& conn, UINT32 msgId, CommMsgBody& body)  // GConnection only
{
	return 0;
}

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnectionEx& conn, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
	return 0;
}

// it is the application's responsibility to make sure that the logic connection (conn) is connected (after connected() call back) when this function is called
void Atf::Service::sendMsgToServer(AtfCommClientConnection& conn, const MessageProtocol& msg, UINT32 replyMsgId, UINT32 disconnectNotifMsgId /*= DEFAULT_MSGID_FOR_SERVICE_RELIABLE_CONNECTION_DISCONNECT*/, bool trace /*= true*/)
{
}

// it is the application's responsiblity to make sure that the logic connection (conn) is connected (after connected() call back) when this function is called
void Atf::Service::sendMsgToClient(AtfCommServerConnection& conn, const MessageProtocol& msg, UINT32 replyMsgId, UINT32 disconnectNotifMsgId /*= DEFAULT_MSGID_FOR_SERVICE_RELIABLE_CONNECTION_DISCONNECT*/, bool trace /*= true*/)
{
}

// it is the application's responsiblity to make sure that the logic connection (conn) is connected (after connected() call back) when this function is called
void Atf::Service::sendMsgToGClient(AtfCommServerConnection& conn, UINT32 reqId, const MessageProtocol& msg, UINT32 replyMsgId, UINT32 disconnectNotifMsgId /*= DEFAULT_MSGID_FOR_SERVICE_RELIABLE_CONNECTION_DISCONNECT*/, bool trace /*= true*/)
{
}

void Atf::Service::sendMsgToGClient(AtfCommServerConnection& conn, UINT32 reqId, UINT32 msgId, CommMsgBody& body, UINT32 replyMsgId, UINT32 disconnectNotifMsgId /*= DEFAULT_MSGID_FOR_SERVICE_RELIABLE_CONNECTION_DISCONNECT*/)
{
}

void Atf::Service::sendMsgToClient(AtfCommServerConnectionEx& conn, const MessageProtocol& msg, UINT32 replyMsgId, UINT32 disconnectNotifMsgId /*= DEFAULT_MSGID_FOR_SERVICE_RELIABLE_CONNECTION_DISCONNECT*/, bool trace /*= true*/)
{
}

void Atf::Service::sendMsgToGClient(AtfCommServerConnectionEx& conn, UINT32 reqId, const MessageProtocol& msg, UINT32 replyMsgId, UINT32 disconnectNotifMsgId /*= DEFAULT_MSGID_FOR_SERVICE_RELIABLE_CONNECTION_DISCONNECT*/, bool trace /*= true*/)
{
}

void Atf::Service::sendMsgToGClient(AtfCommServerConnectionEx& conn, UINT32 reqId, UINT32 msgId, CommMsgBody& body, UINT32 replyMsgId, UINT32 disconnectNotifMsgId /*= DEFAULT_MSGID_FOR_SERVICE_RELIABLE_CONNECTION_DISCONNECT*/)
{
}
bool Atf::Service::filterServiceReplyMsg(UINT32 msgId, const CommMsgBody& body)
{
	return false;
}

void Atf::Service::postMsgToClient(UINT32 connId, UINT32 msgId, CommMsgBody& body)
{
}

void Atf::Service::postMsgToClient(UINT32 connId, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
}

void Atf::Service::postMsgToClient(UINT32 connId, UINT32 msgId, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
}

void Atf::Service::postMsgToGClient(UINT32 connId, UINT32 reqId, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
}

void Atf::Service::atfGPostMsgToClientGConn(const char* tag, UINT32 reqId, const Atf::MessageProtocol& msg, UINT32 replyMsgId, bool trace /* = true */)
{
}

void Atf::Service::myPLog_internal(_In_z_ _Printf_format_string_ const char* format, ...) const
{ }

void Atf::Service::myPLogDebug_internal(_In_z_ _Printf_format_string_ const char* format, ...) const
{
}

void Atf::Service::registerPlayerMsg(UINT32 msgId, const PString& user, UINT32 connId, UINT32 msgIdForServiceCallBack)
{
}
void Atf::Service::unregisterPlayerMsg(UINT32 msgId, const PString& user, UINT32 connId)
{
}

void Atf::Service::registerServiceEvent(UINT32 eventType, UINT32 msgId, BYTE level)
{
}
UINT32 Atf::Service::startTimer(UINT32 msgId, INT32 timeOutInSec)
{
	return 0;
}

void Atf::Service::restartTimer(UINT32& handle, UINT32 msgId, INT32 timeOutInSec)
{
}
void Atf::Service::stopTimer(UINT32& handle)
{
}
void Atf::Service::timerStarted(UINT32 /*timerHandle*/, bool isRecurringTimer)
{
}

void Atf::Service::timerStopped(UINT32 /*timerHandle*/, INT64 /*timeUsedInMSec*/, bool isRecurringTimer, bool /*isTimerCancelled*/)
{
}

bool Atf::Service::deleteServiceCondition(UINT32 serviceConditionId)
{
	return false;
}

Atf::ServiceTempBufWrapper::ServiceTempBufWrapper(AtfCommObjectImpl* obj, UINT32 nextServiceSeq, Service* parentService, const char* childServiceName)
{
}
Atf::ServiceTempBufWrapper::~ServiceTempBufWrapper()
{
}

const char* Atf::SimpleServiceClazz::formatStateName(int stateId) const
{
	return "";
}

void Atf::SimpleServiceClazz::cleanUpWhenException()
{
}

INT32 Atf::SimpleServiceClazz::getNextStateByName(const char* nextStateName) const
{
	return 0;
}

void Atf::SimpleServiceClazz::_beginProcessMessage()
{
}

void Atf::SimpleServiceClazz::_endProcessMessage(int nextState)
{
}

void Atf::SimpleServiceClazz::setNextState(int nextState)
{
}

void Atf::SimpleServiceClazz::directGotoNewState(int newState)
{
}

UINT32 Atf::SimpleServiceClazz::waitServiceCondition(ServiceCondition* cond)
{
	return 0;
}

void Atf::AtfCommPlayerOrCipwaConnection::postMsg(const Atf::MessageProtocol& msg, bool trace /* = true */)
{ }

void Atf::AtfCommPlayerOrCipwaConnection::postMsgWithId(UINT32 msgId, const MessageProtocol& msg, bool trace /* = true */)
{ }

void Atf::AtfCommPlayerOrCipwaConnection::post(UINT32 msgId, Atf::MsgBodyWithJSON& msg, bool trace)
{ }

void Atf::AtfCommPlayerOrCipwaConnection::post(UINT32 msgId, CommMsgBody& body)
{ }

void Atf::AtfCommPlayerOrCipwaConnection::traceOutgoing(UINT32 msgId, const CommMsgBody& body)
{ }

UINT32 Atf::AtfCommObjectImpl::_postTimerMessage(UINT32 msgId, CommMsgBody& body, int msec, const TimerObject* timer)
{
	return 0;
}
bool Atf::AtfCommObjectImpl::_deleteTimerMessage(UINT32 handle)
{
	return false;
}

void Atf::AtfCommObjectImpl::addTimerServer(TimerObject* timer)
{
}

void Atf::AtfCommObjectImpl::removeTimerServer(UINT32 timerObjectId)
{ }

bool Atf::AtfCommObjectImpl::isValidTimerServer(UINT32 timerObjectId) const
{
	return false;
}

namespace pokerstars::telemetry::gateway
{
	class ClientToGatewayConnection : public CommClientConnection
	{
	};
	Client::Client(const Config& config, CommClientConnectionPool& cliPool)
		: config_(config)
		, cliPool_(cliPool)
	{
	}
	Client::~Client()
	{
	}
}