#include "GenericServerObjectSuite.h"
#include "integrationserverobject.h"
#include "AuxAdminServerObject.h"

#include "ServerObjectsExpects.h"

#include "commlib2a/MockCommInterface.h"
#include "atf/MockAtfCommObjectImpl.h"
#include "atf/MockService.h"
#include "atf/FakeServer.h"
#include "atf/FakeConnection.h"
#include "auxservercommon/MockAuxReefAccessor.h"


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

	}
};

TEST_F(TestAdminAndISServers, init_is_server)
{   
    //AuxIntegrationServerObject::init() initializes the container only, no services are started.
	expects::ExpectISInits();
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxis")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxapp"));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "is"));
	EXPECT_CALL(*fakeConnection, clientPostMsg("AUX_REEF_MSG_Q_SEND", _));

	MockCommInterface commIs;
    AuxIntegrationServerObject isServer(commIs);
	CommMsgBody msgIsInit;
	EXPECT_TRUE(isServer._safeInit(msgIsInit));
	EXPECT_EQ(0, fakeServer->serviceMap.size());
}

TEST_F(TestAdminAndISServers, init_admin_server)
{
	expects::ExpectAdminInits();
    EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "admin")).Times(AtLeast(2));
    EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxadmininternal")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxapp"));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "AdminCleanup"));
    EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxtable")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxserver"));

	MockCommInterface commAdmin;
	AuxAdminServerObject adminServer(commAdmin);
	CommMsgBody msgAdminInit;
	EXPECT_TRUE(adminServer._safeInit(msgAdminInit));
	EXPECT_EQ(0, fakeServer->serviceMap.size());


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

TEST_F(TestAdminAndISServers, processDeleteIsSuspendRequests)
{
	// Test data
	UINT64 appSessionId = 1111;
	UINT32 userIntId = 2222;
	std::string channelId = "R28649363";

	expects::ExpectAdminInits();
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "admin")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxadmininternal")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxapp"));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "AdminCleanup"));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxtable")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxserver"));

	MockCommInterface commAdmin;
	AuxAdminServerObject adminServer(commAdmin);
	CommMsgBody msgAdminInit;
	adminServer._safeInit(msgAdminInit);

	AuxAdminServerConnection adminConnection(&adminServer, true);
	
	vector<const char*> rights = { AUX_ADM_PRIV_MANAGE_IS_REQUESTS };
	adminConnection.setAdminRights(appSessionId, userIntId, rights);


    Adm::Adm::Protocol_AUX_ADM_MSG_Q_DEL_IS_SUSPEND_REQUESTS reqDelSuspend;
    reqDelSuspend.channelIds.push_back(channelId.c_str());

    // For this type of request we must provide the type of request explicitly
	CommMsgBody msgDelSuspend;
	msgDelSuspend.composeUINT32(AUX_ADM_MSG_Q_DEL_IS_SUSPEND_REQUESTS);
    reqDelSuspend.composeMsg(msgDelSuspend);

	EXPECT_CALL(*mockService, serviceStarted("DelIsSuspend"));
	adminServer.processPortalMessage(AUX_ADM_MSG_Q_DEL_IS_SUSPEND_REQUESTS, msgDelSuspend, &adminConnection);

    fakeServer->sendRequest("DelIsSuspend");
}