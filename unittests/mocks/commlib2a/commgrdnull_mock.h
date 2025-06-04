#ifndef commgrdnull_mock_h
#define commgrdnull_mock_h

#include "ppinclude.h"
#include "pperror.h"
#include "pplogfile.h"

#include "commmsgbody.h"
#include "commqueue.h"
#include "commcli_mock.h"
#include "commsrv_mock.h"
#include <gmock/gmock.h>

#define _COMM_NULL_GUARD_NAME "NULL"

class CommClientNullGuard : public CommClientGuard
{
public:
	CommClientNullGuard(const CommMsgBody& extra_) : CommClientGuard(_COMM_NULL_GUARD_NAME) {}

public:
	MOCK_METHOD(void, composeFirstRequest, (CommMsgBody& msgBody), (override));
	MOCK_METHOD(bool, processResponse, (CommMsgBody& msgBody, CommMsgParser& parser), (override));
	MOCK_METHOD(bool, processGranted, (CommMsgParser& parser), (override));
	MOCK_METHOD(void, composeGuardNameList, (CommMsgBody& msgBody), (const, override));


	MOCK_METHOD(void, processOutBlock, (CommMsgBody& dst, CommMsgBody& src), (override));
	MOCK_METHOD(void, processInBlock, (CommMsgBody& dst, CommMsgParser& src), (override));
};

class CommClientNullGuardFactory : public CommClientGuardFactory
{
public:
	MOCK_METHOD(void, setAuth, (const CommMsgBody & extra_));
	MOCK_METHOD(CommClientGuardAuth*, auth, (), (override));
	MOCK_METHOD(void, composeGuardNameList, (CommMsgBody& msgBody), (const, override));
	MOCK_METHOD(CommClientGuard*, createGuard, (const char* guardName, CommClientGuardAuth*), (override));
};

//****************************************************************************

class CommServerNullGuard : public CommServerGuard
{
public:
	CommServerNullGuard() : CommServerGuard(_COMM_NULL_GUARD_NAME) {}

public:
	MOCK_METHOD(void, processFirstRequest, (CommMsgParser& parser), (override));
	MOCK_METHOD(void, processAddRequest, (CommMsgParser& parser), (override));

	MOCK_METHOD(void, processOutBlock, (CommMsgBody& dst, CommMsgBody& src), (override));
	MOCK_METHOD(void, processInBlock, (CommMsgBody& dst, CommMsgParser& src), (override));
	MOCK_METHOD(bool, gotUserAuth, (CommMsgParser* parser, UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody), (override));
	MOCK_METHOD(void, delegateUserAuth, (UINT16 errCode, const char* errMsg, const CommMsgBody* errMsgBody), (override));
};

class CommServerNullGuardFactory : public CommServerGuardFactory
{
public:
	MOCK_METHOD(CommServerGuard*, createGuard, (const vector< const char* >& guardNames), (override));
};

#endif
