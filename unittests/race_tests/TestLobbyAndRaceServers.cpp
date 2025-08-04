#include "GenericServerObjectSuite.h"
#include "AuxRaceServerObject.h"
#include "AuxLobbyServerObject.h"

#include "ServerObjectsExpects.h"
//#include "plib/MockPIniFile.h"

#include "atf/MockService.h"
#include "atf/FakeServer.h"
#include "atf/FakeConnection.h"

#include "commlib2a/MockCommInterface.h"

using namespace testing;
class TestLobbyAndRaceServers : public GenericServerObjectSuite
{
protected:
	void SetUp() override
	{
		GenericServerObjectSuite::SetUp();
        fakeConnection = new FakeConnection();
	};

	void TearDown() override
	{
		GenericServerObjectSuite::TearDown();
        if (fakeConnection)
        {
            delete fakeConnection;
            fakeConnection = nullptr;
        }
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

	RaceServer::AuxLobbyConn lobby2race(&raceServer);
	//fakeConnection->connectServices(&lobbyServer, &lobby2race);

	EXPECT_CALL(*fakeConnection, postGMsg(StrEq("TB "), _, _));

    auto* gConn = new LobbyServerTableGConn(&lobbyServer, "TB");
	CommMsgBody usrAuth;
	Lobby::Table::TableConnectInfo tbl;
	tbl.table.tableId = 301;
	tbl.composeMsg(usrAuth);
	CommMsgBody dummy;
	gConn->getUserAuth(_COMM_NULL_GUARD_WITH_INFO_NAME, "testid", usrAuth, dummy);

	Lobby::Table::Protocol_AUX_LOBBY_MSG_Q_PLAYER_SIT playerSit;
	CommMsgBody msgPlayerSit;
	playerSit.gameSessionId = 1;
	playerSit.userId = "user2";
	playerSit.userIntId = 2;
	playerSit.loginSessionId = 2000 + playerSit.userIntId;
	playerSit.tableId = 301;
	playerSit.seat = 1;
	playerSit.composeMsg(msgPlayerSit);
    lobbyServer.processTableMessage(gConn, AUX_LOBBY_MSG_Q_PLAYER_SIT, msgPlayerSit);

}