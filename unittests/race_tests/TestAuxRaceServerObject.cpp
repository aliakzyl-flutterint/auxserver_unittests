
#include "GenericServerObjectSuite.h"
#include "AuxRaceServerObject.h"

#include "plib/MockPpIncludeBase.h"
#include "plib/MockPIniFile.h"
#include "atf/MockService.h"
#include "atf/FakeServer.h"

#include "commlib2a/MockCommInterface.h"

#include "FakeRaceData.h"

using namespace testing;
MockPpIncludeBase* mockPpIncludeBase = nullptr;
class TestAuxRaceServerObject : public GenericServerObjectSuite
{
protected:

	void SetUp() override
	{
        mockPpIncludeBase = new MockPpIncludeBase();
		GenericServerObjectSuite::SetUp();
	};

	void TearDown() override
	{
		if (mockPpIncludeBase)
		{
			delete mockPpIncludeBase;
			mockPpIncludeBase = nullptr;
		}
		GenericServerObjectSuite::TearDown();
	}

	void ExpectInit() override
	{
		EXPECT_CALL(*mockPIniFile, getSection(_, "STATICSETTINGS", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICCONNECT", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICSETTINGS", _)).Times(AtLeast(1));

		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", _));
		
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "idDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "idDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "RaceDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "RaceDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "TableDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "TableDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "IntegrationServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "IntegrationServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "NotificationServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "NotificationServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "jackpotServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "jackpotServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));

		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", _)).Times(AtLeast(1));
	}


};

TEST_F(TestAuxRaceServerObject, init)
{
	EXPECT_CALL(*mockService, serviceStarted(StrEq("GADFDB")));

	MockCommInterface mockCommInterface;
	RaceServer::AuxRaceServerObject serverObject(mockCommInterface);
	CommMsgBody initMsg;
	EXPECT_TRUE(serverObject._safeInit(initMsg));
    EXPECT_EQ(1, fakeServer->serviceMap.size());
}

TEST_F(TestAuxRaceServerObject, get_data_from_db)
{
	int raceId = 12;
	FakeRaceData frd;
    frd.init(raceId);
	EXPECT_CALL(*mockService, serviceStarted(StrEq("GADFDB")));

	MockCommInterface mockCommInterface;
	RaceServer::AuxRaceServerObject serverObject(mockCommInterface);
	CommMsgBody initMsg;
	serverObject._safeInit(initMsg);


	EXPECT_CALL(*mockService, serviceStarted(StrEq("RSS")));
	
    CommMsgBody dbmRacesMsg;
    frd.dbmRaces.composeMsg(dbmRacesMsg);
	fakeServer->triggerOnReply2("GADFDB", 0, dbmRacesMsg);
	EXPECT_EQ(2, fakeServer->serviceMap.size());
	//serverObject.processNeedDataFromDbmReplyMessage(dbmReply);
	
	EXPECT_CALL(*mockService, serviceStarted(StrEq("GetXRates")));
	CommMsgBody dbmRaceSessionsMsg;
    frd.dbmRaceSessions.composeMsg(dbmRaceSessionsMsg);
    fakeServer->triggerOnReply("RSS", AUX_RACE_DBM_MSG_A_GET_LIMITED_RACE_SESSIONS, dbmRaceSessionsMsg);
    fakeServer->triggerOnExit("RSS");

	//RaceServer::AuxLobbyConn conn(&serverObject);
 //   CommMsgBody msg_raceOptIn;
	//RaceServer::Lobby::Protocol_AUX_RACE_MSG_Q_RACE_OPTIN request;
	//request.hostId = 1;
	//request.raceId =  raceId;
	//request.composeMsg(msg_raceOptIn);
 //   serverObject.processLobbyMessage(&conn, AUX_RACE_MSG_Q_RACE_OPTIN, msg_raceOptIn);
}