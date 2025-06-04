#include "AtfUniSeqId.h"
#include "AtfCommPlayerConns.h"
#include "auxcommon/UniqueSeqId.h"
#include "auxservercommon/TableScriptParser2.h"
#include "auxservercommon/StatusCheckServer.h"
#include "auxservercommon/AuxTableAlertReporter.h"

Atf::AbstractUniqueSequenceNumber::AbstractUniqueSequenceNumber(const char* category)
{ }

Atf::AbstractUniqueSequenceNumber::~AbstractUniqueSequenceNumber()
{
}

UINT64 Atf::AbstractUniqueSequenceNumber::getNextSeqId()
{
	return 0;
}

bool Atf::AbstractUniqueSequenceNumber::hasMoreSeqIds() const
{
	return false;
}

void Atf::AbstractUniqueSequenceNumber::init(AtfCommObjectImpl* obj_, AtfCommClientGConnection* conn_)
{
}

void UniqueSequenceNumber::composeDbmRequestMsg(const char* category, UINT32 reqSize, UINT32& reqMsgIdOut, CommMsgBody& reqBodyOut, UINT32& replyMsgIdOut)
{
}

INT16 UniqueSequenceNumber::parseDbmReplyMsg(UINT32 replyMsgId, const CommMsgBody& body, std::vector< std::pair<UINT64, UINT64> >& chunksOut, PString& errStrOut)
{
	return 0;
}

void UniqueSequenceNumber::init(Atf::AtfCommObjectImpl* obj_, Atf::AtfCommClientGConnection* conn_)
{
}

void TableScriptParser2::getJackpotKeys(const vector< aux::P_PNameValue >& props, vector<UINT32>& jpKeys)
{
}

const char* const Atf::AtfCommPlayerOrCipwaConnection::cipwaConnTyeSuffix = "_cipwa";

void myPLogAlways_internal(_In_z_ _Printf_format_string_ const char* format, ...)
{
}

void Atf::AtfCommObjectImpl::_exit()
{
}

UINT32 Atf::AtfCommObjectImpl::getNumberOfRunningServices() const
{
	return 0;
}

void Atf::AtfCommObjectImpl::reloadHeLoggerSettings()
{
}

void StatusServerPerformanceCounter::init(StatusServer* statusServer_)
{
}

StatusServer& StatusServer::init(CommServerConnectionPool& srvpool)
{
	return *this;
}

void AuxTableAlertReporter::init(UINT64 tableId, const PString& address, const PString& instance)
{ }

void AuxTableAlertReporter::sendAlert(const PString& alertType, const PString& data, const PString& details, bool urgent /*= false*/, bool log /*= true*/)
{
}