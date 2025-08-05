#include "GenericServerObjectSuite.h"
#include "AuxRaceServerObject.h"
#include "AuxLobbyServerObject.h"

#include "ServerObjectsExpects.h"

#include "abeserver/AbeServerObject.h"
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
	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));
	MockCommInterface commRace;
	RaceServer::AuxRaceServerObject raceServer(commRace);
	CommMsgBody msgRaceInit;
	EXPECT_TRUE(raceServer._safeInit(msgRaceInit));
	EXPECT_EQ(1, fakeServer->serviceMap.size());

	expects::ExpectLobbyInits();
	EXPECT_CALL(*mockService, serviceStarted("InitLobby"));
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
	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));
	MockCommInterface commRace;
	RaceServer::AuxRaceServerObject raceServer(commRace);
	CommMsgBody msgRaceInit;
	raceServer._safeInit(msgRaceInit);


	expects::ExpectLobbyInits();
	EXPECT_CALL(*mockService, serviceStarted("InitLobby"));
	MockCommInterface commLobby;
	AuxLobbyServerObject lobbyServer(commLobby);
	expects::ExpectLobbyConnects(lobbyServer);
	CommMsgBody msgLobbyInit;
	lobbyServer._safeInit(msgLobbyInit);

	EXPECT_CALL(*mockService, serviceStarted("GetXRates"));
	raceServer.resumedInit();
	EXPECT_TRUE(fakeConnection->connections.count("auxlobby"));

	RaceServer::AuxLobbyConn lobby2race(&raceServer);

	EXPECT_CALL(*fakeConnection, reversePostGMsg("TB ", _, _)).WillOnce(
		Invoke([&](const std::string& traceMarker, UINT32 reqId, const Atf::MessageProtocol& msg)
		{
			auto* real_msg = dynamic_cast<const Lobby::Table::Protocol_AUX_LOBBY_MSG_A_PLAYER_SIT*>(&msg);
            EXPECT_TRUE(real_msg != nullptr);
			EXPECT_EQ(0, real_msg->errStr.length());
			EXPECT_EQ(0, real_msg->errCode);
		})
		);

	EXPECT_CALL(*fakeConnection, clientPostMsg("RC_BIND", _)).WillOnce(
		Invoke([&](const std::string& msgIdStr, const Atf::MessageProtocol& msg)
		{	
            auto* real_msg = dynamic_cast<const RaceServer::Lobby::Protocol_AUX_RACE_MSG_Q_RACE_BIND*>(&msg);
            EXPECT_TRUE(real_msg != nullptr);
            EXPECT_EQ(1, real_msg->gameSessionId);
            EXPECT_EQ(2, real_msg->userIntId);
            EXPECT_EQ(301, real_msg->tableId);
            EXPECT_EQ(2002, real_msg->loginSessionId);
            auto raceConn = fakeConnection->createConnection<RaceServer::AuxLobbyConn>("auxlobby");

			CommMsgBody msgBody;
			msg.composeMsg(msgBody);
			raceConn->processMessage(AUX_RACE_MSG_Q_RACE_BIND, msgBody);
		})
	);

	EXPECT_CALL(*fakeConnection, serverPostMsg("RC_BIND", _, _)).WillOnce(
		Invoke([&](const std::string& msgIdStr, UINT32 reqId, const Atf::MessageProtocol& msg)
		{
			auto* reply = dynamic_cast<const RaceServer::Lobby::Protocol_AUX_RACE_MSG_A_RACE_BIND*>(&msg);
			EXPECT_TRUE(reply != nullptr);
			EXPECT_EQ(auxservererr::SERVER_ERROR_NO_ERROR, reply->errCode);
		})
		);

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