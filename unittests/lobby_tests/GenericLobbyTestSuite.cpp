
#include "GenericLobbyTestSuite.h"

#include <AuxLobbyServerObject.h>

#include "ServerObjectsExpects.h"
#include "atf/MockAtfCommObjectImpl.h"
#include "atf/FakeServer.h"

using namespace testing;

void GenericLobbyTestSuite::SetUp()
{
	GenericServerObjectSuite::SetUp();
}

void GenericLobbyTestSuite::TearDown()
{
	GenericServerObjectSuite::TearDown();
}

void GenericLobbyTestSuite::ExpectInit()
{
    expects::ExpectLobbyInits();
}

void GenericLobbyTestSuite::expectConnects(AuxLobbyServerObject& obj)
{
	using namespace testing;
	obj.staticConfig.staticConnect.dbmAddress.set(dbmAddress.c_str());
	obj.staticConfig.staticConnect.dbmInstance.set(dbmInstance.c_str());
	obj.staticConfig.staticConnect.roOltpDbmAddress.set(roOltpDbmAddress.c_str());
	obj.staticConfig.staticConnect.roOltpDbmInstance.set(roOltpDbmInstance.c_str());
	obj.staticConfig.staticConnect.idDbmAddress.set(idDbmAddress.c_str());
	obj.staticConfig.staticConnect.idDbmInstance.set(idDbmInstance.c_str());
	obj.staticConfig.staticConnect.authIntegrationServerAddress.set(authIntegrationServerAddress.c_str());
	obj.staticConfig.staticConnect.authIntegrationServerInstance.set(authIntegrationServerInstance.c_str());
	obj.staticConfig.staticConnect.integrationServerAddress.set(integrationServerAddress.c_str());
	obj.staticConfig.staticConnect.integrationServerInstance.set(integrationServerInstance.c_str());

	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(dbmAddress.c_str()), StrEq(dbmInstance.c_str()), StrEq(connType.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(roOltpDbmAddress.c_str()), StrEq(roOltpDbmInstance.c_str()), StrEq(connType.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(idDbmAddress.c_str()), StrEq(idDbmInstance.c_str()), StrEq(connAuxApp.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(authIntegrationServerAddress.c_str()), StrEq(authIntegrationServerInstance.c_str()), StrEq(connType.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(integrationServerAddress.c_str()), StrEq(integrationServerInstance.c_str()), StrEq(connType.c_str())));
}

void GenericLobbyTestSuite::addUser(unsigned hostId, unsigned userIntId)
{
	IS::GGNLiveLoginSessionInfo user;
	user.hostId = hostId;
	user.userIntId = userIntId;

	this->users.push_back(user);
}

void GenericLobbyTestSuite::submitUsersToServer()
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
