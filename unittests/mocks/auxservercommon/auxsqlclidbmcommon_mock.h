#ifndef auxsqlclidbmcommon_mock_h__
#define auxsqlclidbmcommon_mock_h__

#include "auxdbmcommon_mock.h"
#include "../auxcommon/auxdbcommon_mock.h"
#include "../protocols/MockOlapMessageProcessor.h"
#include <gmock/gmock.h>

class AuxCommDbmServerObjectWithSqlCli : public AuxCommDbmServerObject
{
public:
	MOCK_METHOD(void, registerAdminConnectionFactoryAndSqlCli, (AuxDatabaseManagerCommon* dbmManager, UINT32 appOlapReplyMessageIds[], size_t size));

protected:
	Atf::SharedPointer<MockOlapMessageProcessor> olapMessageHelper;
	MOCK_METHOD(void, processExecDirectStatement, (AuxCommServerConnection* conn, UINT32 requestId, const CommMsgBody& msgParser));
	MOCK_METHOD(void, processExecDirectStatementOlap, (AuxCommServerConnection* conn, UINT32 requestId, const CommMsgBody& msgParser));

public:
	AuxCommDbmServerObjectWithSqlCli(_CommInterface& i) : AuxCommDbmServerObject(i) {}
};

#endif // auxsqlclidbmcommon_mock_h__