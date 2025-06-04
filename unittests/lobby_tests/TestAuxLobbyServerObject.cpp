
#include <AuxLobbyServerObject.h>

#include "GenericLobbyTestSuite.h"

#include "commlib2a/MockCommInterface.h"
#include "atf/MockService.h"
#include "atf/FakeServer.h"

using namespace testing;

class TestAuxLobbyServerObject : public GenericLobbyTestSuite
{
protected:

	void SetUp() override
	{
		GenericLobbyTestSuite::SetUp();
	}

	void TearDown() override
	{
		GenericLobbyTestSuite::TearDown();
	}

	void expectServicesStarted()
	{
		EXPECT_CALL(*mockService, serviceStarted(StrEq("InitLobby")));
	}
};

TEST_F(TestAuxLobbyServerObject, test_init)
{
	
	MockCommInterface mockCommInterface;
	AuxLobbyServerObject tstObj(mockCommInterface);

	expectConnects(tstObj);
	expectServicesStarted();

	CommMsgBody initMsg;
	
	EXPECT_TRUE(tstObj._safeInit(initMsg));

	EXPECT_EQ(1, fakeServer->serviceMap.size());

	EXPECT_EQ(1, fakeServer->serviceMap.count("InitLobby"));
}

TEST_F(TestAuxLobbyServerObject, test_onreply2)
{
	MockCommInterface mockCommInterface;
	AuxLobbyServerObject tstObj(mockCommInterface);

	expectConnects(tstObj);
	expectServicesStarted();

	CommMsgBody initMsg;

	EXPECT_TRUE(tstObj._safeInit(initMsg));

	addUser(11, 222);
	submitUsersToServer();
}