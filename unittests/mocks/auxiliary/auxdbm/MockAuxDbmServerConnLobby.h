#ifndef MockAuxDbmServerConnLobby_h__
#define MockAuxDbmServerConnLobby_h__

#include "UserDefStructs.h"
#include "../../../../auxiliary/auxdbm/AuxDbmServerObject.h"
#include <gmock/gmock.h>

class MockAuxDbmServerConnLobby : public AuxDbmServerConnLobby
{
public:
	MockAuxDbmServerConnLobby() : AuxDbmServerConnLobby(nullptr) {}
	
	MOCK_METHOD(void, postMsg_impl, (const Atf::MessageProtocol& msg, bool trace));
	MOCK_METHOD(void, postMsgWithId_impl, (UINT32 msgId, const Atf::MessageProtocol& msg, bool trace));
	MOCK_METHOD(void, postGMsg, (UINT32 reqId, UINT32 msgId, CommMsgBody& body), (override));
	MOCK_METHOD(void, postGMsg_impl, (UINT32 reqId, const Atf::MessageProtocol& msg, bool trace));
	void postMsg(const Atf::MessageProtocol& msg, bool trace = true) override
	{
		return postMsg_impl(msg, trace);
	}
	void postMsgWithId(UINT32 msgId, const Atf::MessageProtocol& msg, bool trace = true) override
	{
		return postMsgWithId_impl(msgId, msg, trace);
	}
	void postGMsg(UINT32 reqId, const Atf::MessageProtocol& msg, bool trace = true) override
	{
		return postGMsg_impl(reqId, msg, trace);
	}
	MOCK_METHOD(void, traceOutgoing, (UINT32 msgId, const CommMsgBody& body), (override));
	MOCK_METHOD(bool, isInAtfTraceLogContext, (), (const));
	MOCK_METHOD(void, setInAtfTraceLogContext, (bool b));
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));

	MOCK_METHOD(void, post, (UINT32 msgId, CommMsgBody& body), (override));
	MOCK_METHOD(void, setTraceMarker, (const char *newTraceMarker));
	MOCK_METHOD(const char*, getTraceMarker, (), (const));
	MOCK_METHOD(void, setUserIdForLogging, (const char *userId_));
	MOCK_METHOD(const char*, getUserIdForLogging, (), (const));
	MOCK_METHOD(bool, isPeerGConnection, (), (const));

	MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
	MOCK_METHOD(void, _processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
protected:
	MOCK_METHOD(void, _traceConnected, (), (override));
	MOCK_METHOD(void, _traceDisconnected, (int errCode, const char* errMsg), (override));
};

#endif	// MockAuxDbmServerConnLobby_h__