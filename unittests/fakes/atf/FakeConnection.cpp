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
void Atf::AtfServerReverseGConnection::postGMsg(UINT32 reqId, const Atf::MessageProtocol& msg)
{
	std::string traceMarker(this->_traceMarker.c_str());
	fakeConnection->postGMsg(traceMarker, reqId, msg);

	;
	if (const auto it = fakeConnection->m_receivers.find(traceMarker); it!=fakeConnection->m_receivers.end())
	{
		CommMsgBody msgBody;
		msg.composeMsg(msgBody);
		it->second->processMessage(reqId, msgBody);
	}
}

void Atf::AtfServerReverseGConnection::traceOutgoing(UINT32 msgId, const CommMsgBody& body, UINT32 serverReqId)
{
}

CommServerConnection* Atf::AtfServerReverseGConnectionFactory::_AtfCommServerConnectionFactory::createConnection()
{
	return nullptr;
}

void FakeConnection::connectServices(const std::string& senderTraceMarker, Atf::AtfCommServerConnection* receiver)
{
	m_receivers.insert({senderTraceMarker, receiver});
}

