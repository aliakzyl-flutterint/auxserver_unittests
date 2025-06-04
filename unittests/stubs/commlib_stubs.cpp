#include "commcli.h"
#include "commsrv.h"
#include "commssl.h"
#include "commmonitorlogger.h"

void CommMsgHeader::reset()
{
	bodyVersion = 0;
	timerAsyncCall = nullptr;
}

void CommServerObject::_safeShutdown()
{
}

int CommServerObject::_safeTerminated()
{
	return 0;
}

CommClientConnection::CommClientConnection(CommClientGuardFactory& guardFactory_):
	clientId(0)
{
	guardFactory = &guardFactory_;
}

CommClientConnection::~CommClientConnection()
{
}


bool CommClientConnection::closedOrDisconnected(int errCode, const char* errMsg)
{
	return true;
}

void CommClientConnection::post(UINT32 msgId, CommMsgBody& body)
{ }

void CommClientConnection::processQualityRequest()
{
}
void CommClientConnection::postQualityUpdate(BYTE quality_)
{
}

void CommClientConnection::processKeepAliveRequest()
{
}

void CommClientConnection::postKeepAlive()
{
}

CommClientGConnection::CommClientGConnection(CommClientGuardFactory& guardFactory_)
	: conn(guardFactory_)
{
}

CommClientGConnection::_ConnHandler::_ConnHandler(CommClientGuardFactory& guardFactory_)
	: CommClientConnection(guardFactory_)
{
}

void CommClientGConnection::_ConnHandler::processMessage(UINT32 msgId, const CommMsgBody& body)
{
}

void CommClientGConnection::_ConnHandler::connected()
{
}

void CommClientGConnection::_ConnHandler::qualityUpdated(int quality)
{
}

bool CommClientGConnection::_ConnHandler::closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody)
{
	return true;
}
UINT32 CommClientGConnection::post(UINT32 msgId, /*non-const!*/ CommMsgBody& body, /* new */ AsyncCall* call)
{
	return 0;
}

void CommClientGConnection::cancelPost(UINT32 requestId)
{
}

void CommClientGConnection::reserve(UINT32 size)
{
}

CommClientGConnection::~CommClientGConnection()
{
}

ConnInfo::ConnInfo() : pimpl(nullptr)
{
}

ConnInfo::~ConnInfo() = default;

CommServerConnection::CommServerConnection()
{

}

CommServerConnection::~CommServerConnection()
{
}

void CommServerConnection::post(UINT32 msgId, CommMsgBody& body)
{
}

void CommServerConnection::logExtStats()
{ }

void CommServerConnectionPool::disconnect(CommServerConnection* conn, UINT16 errCode, const char* errMessage)
{ }

CommSSLChksumSHA256::CommSSLChksumSHA256()
{
}

CommSSLChksumSHA256::~CommSSLChksumSHA256()
{
}
void CommSSLChksumSHA256::addData(const BYTE* data, size_t sz)
{
}

void CommSSLChksumSHA256::chksum(PBlock& ret)
{
}

void CommSSLSystemInfo::decodePasswordEx(PString& ret, const char* passwrd)
{ }

void CommMonitorLoggerObject::compose(CommMsgBody& msg, const char* strParameterName, const char* strValue) const
{ }

void CommCgi::urlEncode(PString& ret, const char* s, const char* sEnd)
{ }

void CommClientConnectionPool::connect(CommClientConnection& conn, const char* server, const char* serverObject, const char* serverConnType, const ConnInfo* connInfo)
{ }

void CommClientConnectionPool::disconnect(CommClientConnection& conn)
{ }

void CommSSL::generateRandomBytes(BYTE* buf, size_t sz)
{ }

void CommSSLSystemInfo::encodePasswordEx(PString& ret, int encodingId, const char* passwrd)
{ }