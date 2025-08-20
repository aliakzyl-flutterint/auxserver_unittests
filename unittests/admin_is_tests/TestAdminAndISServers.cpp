#include "GenericServerObjectSuite.h"
#include "integrationserverobject.h"

#include "ServerObjectsExpects.h"

#include "commlib2a/MockCommInterface.h"
#include "atf/MockAtfCommObjectImpl.h"
#include "atf/MockService.h"
#include "atf/FakeServer.h"
#include "atf/FakeConnection.h"


using namespace testing;
class TestAdminAndISServers : public GenericServerObjectSuite
{
protected:
	void SetUp() override
	{
		fakeConnection = new FakeConnection();
		GenericServerObjectSuite::SetUp();
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
		expects::ExpectISInits();
		EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxis")).Times(AtLeast(2));
		EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxapp"));
		EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "is"));
		EXPECT_CALL(*fakeConnection, clientPostMsg("AUX_REEF_MSG_Q_SEND", _));
	}
};

TEST_F(TestAdminAndISServers, init_is_container)
{   
    //AuxIntegrationServerObject::init() initializes the container only, no services are started.
	MockCommInterface commIs;
    AuxIntegrationServerObject isServer(commIs);
	CommMsgBody msgIsInit;
	EXPECT_TRUE(isServer._safeInit(msgIsInit));
	EXPECT_EQ(0, fakeServer->serviceMap.size());
}

TEST_F(TestAdminAndISServers, init_admin_server)
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