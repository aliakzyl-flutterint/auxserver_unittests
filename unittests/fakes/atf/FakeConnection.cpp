#include "FakeConnection.h"
#include "atf/MockService.h"

#include "AtfCommServerGConn.h"

FakeConnection* fakeConnection = nullptr;

void Atf::AtfServerReverseGConnection::connected()
{
}

void Atf::AtfServerReverseGConnection::closedOrDisconnected(int errCode, const char* errMsg)
{
}

void Atf::AtfCommObjectImpl::registerConnectionFactory(const char* name, CommServerConnectionFactory& factory)
{
	fakeConnection->connections[name] = &factory;
}

void Atf::AtfServerReverseGConnection::postGMsg(UINT32 reqId, const Atf::MessageProtocol& msg)
{
	std::string traceMarker(this->_traceMarker.c_str());
	fakeConnection->reversePostGMsg(traceMarker, reqId, msg);
}

UINT32 Atf::AtfCommClientGConnection::postMsg(const Atf::MessageProtocol& msg, AsyncCall* call /* = 0 */, bool trace /* = true */)
{
    std::string msgIdStr = msg.getMsgIdString();
    fakeConnection->clientPostMsg(msgIdStr, msg);
	return 0;
}

void Atf::AtfCommServerConnection::postGMsg(UINT32 reqId, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
	std::string msgIdStr = msg.getMsgIdString();
	fakeConnection->serverPostMsg(msgIdStr, reqId, msg);
}

UINT32 Atf::AtfCommClientGConnection::post(UINT32 msgId, CommMsgBody& body, AsyncCall* call /* = 0 */)
{
	std::string traceMarker(this->_traceMarker.c_str());
    return fakeConnection->post(traceMarker, msgId, body);
}

void Atf::AtfServerReverseGConnection::traceOutgoing(UINT32 msgId, const CommMsgBody& body, UINT32 serverReqId)
{
}

CommServerConnection* Atf::AtfServerReverseGConnectionFactory::_AtfCommServerConnectionFactory::createConnection()
{
	return nullptr;
}
