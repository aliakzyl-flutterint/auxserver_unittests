
#include "GenericServerObjectSuite.h"
#include "AuxRaceServerObject.h"

#include "ServerObjectsExpects.h"
#include "plib/MockPpIncludeBase.h"
#include "atf/MockService.h"
#include "atf/FakeServer.h"

#include "commlib2a/MockCommInterface.h"

#include "FakeRaceData.h"
#include "atf/FakeConnection.h"

using namespace testing;
MockPpIncludeBase* mockPpIncludeBase = nullptr;
class TestAuxRaceServerObject : public GenericServerObjectSuite
{
protected:

	void SetUp() override
	{
        mockPpIncludeBase = new MockPpIncludeBase();
		fakeConnection = new FakeConnection();
		GenericServerObjectSuite::SetUp();

	};

	void TearDown() override
	{
		if (mockPpIncludeBase)
		{
			delete mockPpIncludeBase;
			mockPpIncludeBase = nullptr;
		}
		if (fakeConnection)
		{
			delete fakeConnection;
			fakeConnection = nullptr;
		}
		GenericServerObjectSuite::TearDown();

	}

	void ExpectInit() override
	{
        expects::ExpectAuxRaceInits();
	}
};

TEST_F(TestAuxRaceServerObject, init)
{
	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));

	MockCommInterface mockCommInterface;
	RaceServer::AuxRaceServerObject raceServer(mockCommInterface);
	CommMsgBody initMsg;
	EXPECT_TRUE(raceServer._safeInit(initMsg));
    EXPECT_EQ(1, fakeServer->serviceMap.size());
	EXPECT_EQ(0, fakeConnection->connections.size());

	EXPECT_CALL(*mockService, serviceStarted("GetXRates"));
	raceServer.resumedInit();
	EXPECT_EQ(6, fakeConnection->connections.size());
	EXPECT_TRUE(fakeConnection->connections.count("admin"));
	EXPECT_TRUE(fakeConnection->connections.count("auxlobby"));
	EXPECT_TRUE(fakeConnection->connections.count("auxtable"));
	EXPECT_TRUE(fakeConnection->connections.count("scheduler"));
	EXPECT_TRUE(fakeConnection->connections.count("shadow"));
	EXPECT_TRUE(fakeConnection->connections.count("trustedAdmin"));
}

// TEST_F(TestAuxRaceServerObject, create_race)
// {
// 	int raceId = 5;
// 	FakeRaceData frd;
//
// 	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));
//
// 	MockCommInterface mockCommInterface;
// 	EXPECT_CALL(mockCommInterface, _getInQueueSize()).Times(AtLeast(1))
// 	.WillRepeatedly(Return(0));
//
// 	RaceServer::AuxRaceServerObject serverObject(mockCommInterface);
// 	CommMsgBody initMsg;
// 	serverObject._safeInit(initMsg);
//
// 	// connections
// 	RaceServer::AuxSchedulerConn schedConn(&serverObject);
// 	RaceServer::AuxLobbyConn lobbyConn(&serverObject);
//
// 	RaceServer::Scheduler::Protocol_AUX_RACE_MSG_Q_CREATE_RACE createRaceRqst;
//     createRaceRqst.race = frd.createRace(raceId);
// 	CommMsgBody createRaceMsg;
//     createRaceRqst.composeMsg(createRaceMsg);
// 	schedConn.processMessage(AUX_RACE_MSG_Q_CREATE_RACE, createRaceMsg);
// }


// TEST_F(TestAuxRaceServerObject, race_opt_in_4play)
// {
// 	int raceId = 6;
//
// 	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));
//
// 	MockCommInterface mockCommInterface;
// 	EXPECT_CALL(mockCommInterface, _getInQueueSize()).Times(AtLeast(1))
// 		.WillRepeatedly(Return(0));
//
// 	RaceServer::AuxRaceServerObject serverObject(mockCommInterface);
// 	CommMsgBody initMsg;
// 	serverObject._safeInit(initMsg);
//
// 	EXPECT_CALL(*mockService, serviceStarted("RSS"));
// 	EXPECT_CALL(*mockService, serviceStarted("GetXRates"));
//
// 	FakeRaceData frd;
//     frd.addDbmRace(raceId);
// 	CommMsgBody dbmRacesMsg;
// 	frd.dbmRaces.composeMsg(dbmRacesMsg);
// 	fakeServer->triggerOnReply2("GADFDB", 0, dbmRacesMsg);
// 	fakeServer->triggerOnExit("RSS");
//
// 	// connections
// 	RaceServer::AuxLobbyConn lobbyConn(&serverObject);
//
// 	// 2 users opt in for play
//     EXPECT_CALL(*mockService, serviceStarted("OptIn")).Times(2);
//
// 	EXPECT_CALL(*mockPpIncludeBase, PCurrentUTCTime(_))
// 	.WillRepeatedly(Invoke([](struct tm* tm) {
// 		tm->tm_year = 2025 - 1900; // Year since 1900
// 		tm->tm_mon = 5; // June (0-based)
// 		tm->tm_mday = 10;
// 		tm->tm_hour = 10;
// 		tm->tm_min = 1;
// 		tm->tm_sec = 29;
// 	}));
//
// 	CommMsgBody optInUser1Msg;
// 	auto optInUser1Rqst = frd.createOptUser(raceId, 101);
// 	optInUser1Rqst.composeMsg(optInUser1Msg);
// 	serverObject.processLobbyMessage(&lobbyConn, AUX_RACE_MSG_Q_RACE_OPTIN_4_PLAY, optInUser1Msg);
//
// 	CommMsgBody optInUser2Msg;
// 	auto optInUser2Rqst = frd.createOptUser(raceId, 213);
// 	optInUser2Rqst.composeMsg(optInUser2Msg);
// 	serverObject.processLobbyMessage(&lobbyConn, AUX_RACE_MSG_Q_RACE_OPTIN_4_PLAY, optInUser2Msg);
// }