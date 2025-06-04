
#include <gtest/gtest.h>

//#include "../mocks/ExcludeNonMockHeaders.h"
//#include "../mocks/protocols/OlapCommon_mock.h"
//#include "../mocks/auxiliary/auxdbm/MainDbmManager_mock.h"
//#include "../mocks/auxservercommon/auxsqlclidbmcommon_mock.h"
//
//#include "../../auxiliary/auxdbm/AuxDbmServerObject.h"
//
//#include "../mocks/auxiliary/auxdbm/MockAuxDbmServerConnLobby.h"
//#include "../mocks/commlib2a/MockCommInterface.h"




//using ::testing::_;
//using ::testing::DoAll;
//using ::testing::Return;
//using ::testing::SetArgPointee;
//using ::testing::SetArgReferee;

// Uncomment when CAST-15034_multi_trip_table_type_retrieval_v2 will be merged to MainDev (again)
/*
CommMsgBody createNeedInitTableTypesMsgBody(UINT32 requestId, UINT32 beginTableTypeId, UINT32 maxReturnSize)
{
	Dbm::dbm::Protocol_AUX_DBM_MSG_Q_NEED_INIT_TABLE_TYPES needInitTableTypesMessage;
	CommMsgBody body;
	needInitTableTypesMessage.beginTableTypeId = beginTableTypeId;
	needInitTableTypesMessage.maxReturnSize = maxReturnSize;
	needInitTableTypesMessage.composeMsg(body);
	
	BYTE* p = body._createPrefix(4);
	CommMsgBody::writeUINT32(p, requestId);
	
	return body;
}

MATCHER_P(IsEqInitTableTypesReply, arg2, "")
{
	const Dbm::dbm::Protocol_AUX_DBM_MSG_A_NEED_INIT_TABLE_TYPES& msg  = static_cast<const Dbm::dbm::Protocol_AUX_DBM_MSG_A_NEED_INIT_TABLE_TYPES&>(arg);
	const Dbm::dbm::Protocol_AUX_DBM_MSG_A_NEED_INIT_TABLE_TYPES& msg2 = static_cast<const Dbm::dbm::Protocol_AUX_DBM_MSG_A_NEED_INIT_TABLE_TYPES&>(arg2);
	return (msg.equals(msg2));
}

void CommonTestProcessLobbyInitTableTypes(INT16 errCode, PString errStr, UINT32 numTableTypes, bool isLastRecords)
{
	const UINT32 requestId = 12345;
	const UINT32 beginTableTypeId = 1000000;
	const UINT32 maxReturnSize = 100;
	Dbm::dbm::Protocol_AUX_DBM_MSG_A_NEED_INIT_TABLE_TYPES initTableTypesReply;
	initTableTypesReply.errCode = errCode;
	initTableTypesReply.errStr = errStr;
	for (int i = 0; i < numTableTypes; ++i) {
		aux::TableTypeDef tableType;
		tableType.tableTypeId = i;
		initTableTypesReply.tableTypes.push_back(tableType);
	}
	initTableTypesReply.isLastRecords = isLastRecords;
	
	MockCommInterface inter;
	AuxDbmServerObject dbmServerObject(inter);
	MockAuxDbmServerConnLobby conn;
	
	// We need to "load" dynamic config,
	// otherwise dynamicConfig pointer will be empty and innerProcessLobbyMessage()->getOverspanStr()->isOverspan() will throw exception
	const PIniFile iniFileData;
	dbmServerObject.preloadDynamicConfig(iniFileData, nullptr);
	dbmServerObject.applyDynamicConfig();
	
	MainDbmManager *dbManagerMain = MainDbmManager::getLastCreatedObject();
	ASSERT_NE(dbManagerMain, nullptr);
	EXPECT_CALL(*dbManagerMain, getInUseTableTypes_impl(_, _, _, beginTableTypeId, maxReturnSize))
			.Times(1)
			.WillOnce(DoAll(SetArgReferee<0>(initTableTypesReply.tableTypes),
							SetArgReferee<1>(initTableTypesReply.errStr),
							SetArgPointee<2>(initTableTypesReply.isLastRecords),
							Return(initTableTypesReply.errCode)));
	
	EXPECT_CALL(conn, postGMsg_impl(requestId, IsEqInitTableTypesReply(initTableTypesReply), _))
			.Times(1);
	
	const CommMsgBody body = createNeedInitTableTypesMsgBody(requestId, beginTableTypeId, maxReturnSize);
	dbmServerObject.innerProcessLobbyMessage(AUX_DBM_MSG_Q_NEED_INIT_TABLE_TYPES, body, &conn);
}

TEST(TestAuxDbmServerObject, TestProcessLobbyInitTableTypes_ReturnSomeRecords)
{
	CommonTestProcessLobbyInitTableTypes(0, "", 100, false);
}

TEST(TestAuxDbmServerObject, TestProcessLobbyInitTableTypes_ReturnLastRecords)
{
	CommonTestProcessLobbyInitTableTypes(0, "", 3, true);
}

TEST(TestAuxDbmServerObject, TestProcessLobbyInitTableTypes_ReturnError)
{
	CommonTestProcessLobbyInitTableTypes(-1, "Error message text", 0, false);
}

TEST(TestAuxDbmServerObject, TestProcessLobbyInitTableTypes_ReturnErrorAndSomeTableTypes)
{
	CommonTestProcessLobbyInitTableTypes(-1, "Error message text", 1, false);
}
*/