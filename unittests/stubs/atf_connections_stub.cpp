#include "AtfCommServerGConn.h"

void Atf::AtfServerReverseGConnection::connected()
{
}

void Atf::AtfServerReverseGConnection::closedOrDisconnected(int errCode, const char* errMsg)
{
}
void Atf::AtfServerReverseGConnection::postGMsg(UINT32 reqId, const Atf::MessageProtocol& msg)
{
}

void Atf::AtfServerReverseGConnection::traceOutgoing(UINT32 msgId, const CommMsgBody& body, UINT32 serverReqId)
{
}

CommServerConnection* Atf::AtfServerReverseGConnectionFactory::_AtfCommServerConnectionFactory::createConnection()
{
	return nullptr;
}