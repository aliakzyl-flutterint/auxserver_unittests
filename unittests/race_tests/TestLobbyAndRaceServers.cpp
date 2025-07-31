#include "GenericServerObjectSuite.h"
#include "AuxRaceServerObject.h"
#include "AuxLobbyServerObject.h"

#include "ServerObjectsExpects.h"
//#include "plib/MockPIniFile.h"

#include "atf/MockService.h"
#include "atf/FakeServer.h"

#include "commlib2a/MockCommInterface.h"

using namespace testing;
class TestLobbyAndRaceServers : public GenericServerObjectSuite
{
protected:
	void SetUp() override
	{
		GenericServerObjectSuite::SetUp();
	};

	void TearDown() override
	{
		GenericServerObjectSuite::TearDown();
	}

	void ExpectInit() override
	{
        
	}
};

TEST_F(TestLobbyAndRaceServers, init_two_servers)
{
	expects::ExpectAuxRaceInits();
	EXPECT_CALL(*mockService, serviceStarted(StrEq("GADFDB")));
	MockCommInterface commRace;
	RaceServer::AuxRaceServerObject raceServer(commRace);
	CommMsgBody msgRaceInit;
	EXPECT_TRUE(raceServer._safeInit(msgRaceInit));
	EXPECT_EQ(1, fakeServer->serviceMap.size());

	expects::ExpectLobbyInits();
	EXPECT_CALL(*mockService, serviceStarted(StrEq("InitLobby")));
	MockCommInterface commLobby;
	AuxLobbyServerObject lobbyServer(commLobby);
	expects::ExpectLobbyConnects(lobbyServer);
	CommMsgBody msgLobbyInit;
	EXPECT_TRUE(lobbyServer._safeInit(msgLobbyInit));
	EXPECT_EQ(2, fakeServer->serviceMap.size());
}

TEST_F(TestLobbyAndRaceServers, processPlayerSeated)
{
	expects::ExpectAuxRaceInits();
	EXPECT_CALL(*mockService, serviceStarted(StrEq("GADFDB")));
	MockCommInterface commRace;
	RaceServer::AuxRaceServerObject raceServer(commRace);
	CommMsgBody msgRaceInit;
	raceServer._safeInit(msgRaceInit);

	expects::ExpectLobbyInits();
	EXPECT_CALL(*mockService, serviceStarted(StrEq("InitLobby")));
	MockCommInterface commLobby;
	AuxLobbyServerObject lobbyServer(commLobby);
	expects::ExpectLobbyConnects(lobbyServer);
	CommMsgBody msgLobbyInit;
	lobbyServer._safeInit(msgLobbyInit);
    auto* gConn = new LobbyServerTableGConn(&lobbyServer, "TB");

	// Lobby::Table::Protocol_AUX_LOBBY_MSG_Q_PLAYER_SIT playerSit;
	// CommMsgBody msgPlayerSitted;
	// playerSit.gameSessionId = 1;
	// playerSit.composeMsg(msgPlayerSitted);
 //    lobbyServer.processTableMessage(gConn, AUX_LOBBY_MSG_Q_PLAYER_SIT, msgPlayerSitted);
}