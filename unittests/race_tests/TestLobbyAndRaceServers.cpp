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

	void populateLobbyData() const
	{
		Dbm::dbm::Protocol_AUX_DBM_MSG_A_NEED_INIT_DATA initDataRes;
		CommMsgBody msg1;
		initDataRes.composeMsg(msg1);
		fakeServer->triggerOnReply("InitLobby", AUX_DBM_MSG_A_NEED_INIT_DATA, msg1);

		IS::GameServer::Protocol_AUX_IS_MSG_A_GET_GGN_LIVE_LOGIN_SESSIONS reply2;
		reply2.errCode = 0;
		reply2.errStr = "";

		std::vector< IS::GGNLiveLoginSessionInfo > users(3);
		users[0].hostId = 1;
		users[0].userIntId = 1;
		users[0].loginSessionId = 101;
		users[1].hostId = 1;
		users[1].userIntId = 2;
		users[1].loginSessionId = 102;
		users[2].hostId = 1;
		users[2].userIntId = 3;
		users[2].loginSessionId = 103;

		for (auto& user: users)
		{
			reply2.liveLoginSessions.push_back(user);
		}

		CommMsgBody msg2;
		reply2.composeMsg(msg2);
		fakeServer->triggerOnReply2("InitLobby", AUX_IS_MSG_A_GET_GGN_LIVE_LOGIN_SESSIONS, msg2);

		CommMsgBody msg3;
		fakeServer->triggerOnReply3("InitLobby", DEFAULT_MSGID_FOR_SERVICE_TIMEDOUT, msg3);
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
	populateLobbyData();

	RaceServer::AuxLobbyConn lobby2race(&raceServer);
	//fakeConnection->connectServices(&lobbyServer, &lobby2race);

	EXPECT_CALL(*fakeConnection, postGMsg(StrEq("TB "), _, _));

    auto* gConn = new LobbyServerTableGConn(&lobbyServer, "TB");

	Lobby::Table::Protocol_AUX_LOBBY_MSG_Q_PLAYER_SIT playerSit;
	CommMsgBody msgPlayerSit;
	playerSit.gameSessionId = 1;
	playerSit.userIntId = 2;
	playerSit.loginSessionId = 102;
	playerSit.composeMsg(msgPlayerSit);
    lobbyServer.processTableMessage(gConn, AUX_LOBBY_MSG_Q_PLAYER_SIT, msgPlayerSit);

}