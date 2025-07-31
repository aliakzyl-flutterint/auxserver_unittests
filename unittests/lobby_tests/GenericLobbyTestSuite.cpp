
#include "GenericLobbyTestSuite.h"

#include <AuxLobbyServerObject.h>

#include "ServerObjectsExpects.h"
#include "atf/FakeServer.h"
#include "atf/MockService.h"

using namespace testing;

void GenericLobbyTestSuite::SetUp()
{
	GenericServerObjectSuite::SetUp();
	EXPECT_CALL(*mockService, serviceStarted(StrEq("InitLobby")));
}

void GenericLobbyTestSuite::TearDown()
{
	GenericServerObjectSuite::TearDown();
}

void GenericLobbyTestSuite::ExpectInit()
{
    expects::ExpectLobbyInits();
}

void GenericLobbyTestSuite::expectConnects(AuxLobbyServerObject& tstObj)
{
	expects::ExpectLobbyConnects(tstObj);

}

void GenericLobbyTestSuite::addUser(unsigned hostId, unsigned userIntId)
{
	IS::GGNLiveLoginSessionInfo user;
	user.hostId = hostId;
	user.userIntId = userIntId;

	this->users.push_back(user);
}

void GenericLobbyTestSuite::submitUsersToServer() const
{
	IS::GameServer::Protocol_AUX_IS_MSG_A_GET_GGN_LIVE_LOGIN_SESSIONS response;
	response.errCode = 0;
	response.errStr = "";

	for (auto& user: users)
	{
		response.liveLoginSessions.push_back(user);
	}

	CommMsgBody msg;
	response.composeMsg(msg);
	fakeServer->triggerOnReply2("InitLobby", AUX_IS_MSG_A_GET_GGN_LIVE_LOGIN_SESSIONS, msg);
}
