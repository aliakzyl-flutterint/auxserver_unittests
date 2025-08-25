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

namespace
{	
	template<typename T>
	CommMsgBody removeReqId(const CommMsgBody& body)
	{
		CommMsgParser parser(body);
		UINT32 reqId;
		parser.parseUINT32(reqId);
		T reply;
		reply.parseMsg(parser);

		CommMsgBody newMsg;
		reply.composeMsg(newMsg);
		return newMsg;
	}

}


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

	void FakeISRequests(AuxIntegrationServerObject* isServer)
	{
		IS::RaceServer::Protocol_AUX_IS_MSG_Q_RACE_RESULT msg;
		msg.hostId = aux::HostType::HOST_SKYBETMARS;
		auto activeRequest = new PlayerRaceResultServerRequest(isServer, 0, msg.getMsgId(), 1, msg);
		activeRequest->setChannelId(channelId.c_str());
		activeRequest->lifeCycle->setStatus(IS_REQUEST_STATUS_SUSPENDED_PERMANENTLY);
		isServer->mapActiveIntegrationServerRequests.insert(channelId.c_str(), activeRequest);
		auto gameServerRequest = new PlayerRaceResultServerRequest(isServer, 0, msg.getMsgId(), 2, msg);
		gameServerRequest->lifeCycle->setStatus(IS_REQUEST_STATUS_UNKNOWN);
		activeRequest->setChannelId(channelId.c_str());
		isServer->mapGameServerRequestQueues.insert(channelId.c_str(), {gameServerRequest});
	}

	// Test data
	const UINT64 appSessionId = 1111;
	const UINT32 userIntId = 2222;
	const std::string channelId = "R28649363";
	const std::string DelIsSuspendService = "DelIsSuspend";
};

TEST_F(TestAdminAndISServers, init_is_server)
{   
    //AuxIntegrationServerObject::init() initializes the container only, no services are started.
	expects::ExpectISInits();
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxgameis")).Times(AtLeast(2));
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
}

TEST_F(TestAdminAndISServers, processDeleteIsSuspendRequests)
{

	expects::ExpectAdminInits();
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "admin")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxadmininternal")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxapp"));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "AdminCleanup"));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxtable")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxserver"));

    // Init the admin server
	MockCommInterface commAdmin;
	AuxAdminServerObject adminServer(commAdmin);
	CommMsgBody msgAdminInit;
	adminServer._safeInit(msgAdminInit);

    // Init the IS server
	expects::ExpectISInits();
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxgameis")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxis")).Times(AtLeast(2));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "auxapp"));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, "is"));
    EXPECT_CALL(*fakeConnection, clientPostMsg("AUX_REEF_MSG_Q_SEND", _)).Times(AtLeast(1));

	EXPECT_CALL(*fakeConnection, post_callback("idb", AUX_DBM_MSG_Q_IS_NEED_DATA, _, _));
	EXPECT_CALL(*fakeConnection, findConnection("")).Times(AtLeast(1));

	MockCommInterface commIs;
	AuxIntegrationServerObject isServer(commIs);
	CommMsgBody msgIsInit;
	isServer._safeInit(msgIsInit);
    FakeISRequests(&isServer);
	
	// Init connections
	AuxAdminServerConnection adminConnection(&adminServer, true);	
	vector<const char*> rights = { AUX_ADM_PRIV_MANAGE_IS_REQUESTS };
	adminConnection.setAdminRights(appSessionId, userIntId, rights);

	AuxIntegrationServerConnection backConn(&isServer);

	// Request
    Adm::Adm::Protocol_AUX_ADM_MSG_Q_DEL_IS_SUSPEND_REQUESTS reqDelSuspend;
    reqDelSuspend.channelIds.push_back(channelId.c_str());
    // For this type of request we must provide the type of request explicitly
	CommMsgBody msgDelSuspend;
	msgDelSuspend.composeUINT32(AUX_ADM_MSG_Q_DEL_IS_SUSPEND_REQUESTS);
    reqDelSuspend.composeMsg(msgDelSuspend);

	EXPECT_CALL(*mockService, serviceStarted(DelIsSuspendService));
	adminServer.processPortalMessage(AUX_ADM_MSG_Q_DEL_IS_SUSPEND_REQUESTS, msgDelSuspend, &adminConnection);

	EXPECT_CALL(*fakeConnection, findConnection("IS: ")).WillRepeatedly(
		[&backConn](const std::string&)
		{
			return &backConn;
		}
	);

	EXPECT_CALL(*fakeConnection, post_callback("is", AUX_IS_MSG_Q_DEL_IS_SUSPEND_REQUESTS, _, _)).WillRepeatedly(
		[&isServer, &backConn](const std::string& traceMarker, UINT32 msgId, const CommMsgBody& body, RefAsyncCall*) {
            isServer.processServerMessage(msgId, body, &backConn);
			return 0;
        });

	EXPECT_CALL(*fakeConnection, post_callback("ppb", AUX_BOA_MSG_Q_RACE_RESULT, _, _)).WillRepeatedly(
		[&isServer, &backConn](const std::string& traceMarker, UINT32 msgId, const CommMsgBody& body, RefAsyncCall* callback) {
			BackofficeAdaptor::IS::Protocol_AUX_BOA_MSG_A_RACE_RESULT boaReply;
			boaReply.errorCode = auxservererr::ServerErrorCode::SERVER_ERROR_SERVICE_ILLEGAL_STATE;
			CommMsgBody replyBody;
			boaReply.composeMsg(replyBody);
			callback->processReply(0, msgId, replyBody);
			return 0;
		});

	EXPECT_CALL(*fakeConnection, post("ISR", AUX_IS_MSG_A_DEL_IS_SUSPEND_REQUESTS, _)).WillRepeatedly(
		[this](const std::string& traceMarker, UINT32 msgId, const CommMsgBody& body) {
			CommMsgBody newMsg = removeReqId<IS::AdminServer::Protocol_AUX_IS_MSG_A_RESEND_IS_SUSPEND_REQUESTS>(body);
			fakeServer->triggerOnReply(DelIsSuspendService, msgId, newMsg);
			fakeServer->triggerOnExit(DelIsSuspendService);
			return 0;
		});

	EXPECT_CALL(*mockService, serviceStarted("adminAuditLogService"));

	EXPECT_CALL(*mockService, postMsgToGClient(DelIsSuspendService, _, _))
		.WillRepeatedly(
			[](const std::string& serviceName, unsigned reqId, CommMsgBody& msg)
			{
				Adm::Adm::Protocol_AUX_ADM_MSG_A_DEL_IS_SUSPEND_REQUESTS response;
				response.parseMessage(msg);
				//EXPECT_EQ(auxservererr::SERVER_ERROR_SYSTEM, response.errCode);
				EXPECT_EQ(0, response.errCode);
			}
		);
    fakeServer->sendRequest(DelIsSuspendService);
}