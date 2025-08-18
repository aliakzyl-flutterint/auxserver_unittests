#include "GenericServerObjectSuite.h"
//#include "AuxRaceServerObject.h"
//#include "AuxLobbyServerObject.h"
//
//#include "ServerObjectsExpects.h"
//
//#include "abeserver/AbeServerObject.h"
//#include "atf/MockService.h"
//#include "atf/FakeServer.h"
//#include "atf/FakeConnection.h"
//
//#include "commlib2a/MockCommInterface.h"

using namespace testing;
class TestAdminAndISServers : public GenericServerObjectSuite
{
protected:
	void SetUp() override
	{
		//GenericServerObjectSuite::SetUp();
	};

	void TearDown() override
	{
		//GenericServerObjectSuite::TearDown();
	}

	void ExpectInit() override
	{
	}
};

TEST_F(TestAdminAndISServers, init_two_servers)
{
	//expects::ExpectAuxRaceInits();
	//EXPECT_CALL(*mockService, serviceStarted("GADFDB"));
	//MockCommInterface commRace;
	//RaceServer::AuxRaceServerObject raceServer(commRace);
	//CommMsgBody msgRaceInit;
	//EXPECT_TRUE(raceServer._safeInit(msgRaceInit));
	//EXPECT_EQ(1, fakeServer->serviceMap.size());

	//expects::ExpectLobbyInits();
	//EXPECT_CALL(*mockService, serviceStarted("InitLobby"));
	//MockCommInterface commLobby;
	//AuxLobbyServerObject lobbyServer(commLobby);
	//expects::ExpectLobbyConnects(lobbyServer);
	//CommMsgBody msgLobbyInit;
	//EXPECT_TRUE(lobbyServer._safeInit(msgLobbyInit));
	//EXPECT_EQ(2, fakeServer->serviceMap.size());
}