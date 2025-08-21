#include "GenericLobbyTestSuite.h"

#include <AuxLobbyServerObject.h>

#include "commlib2a/MockCommInterface.h"
#include "plib/MockPIniFile.h"

#include "atf/FakeServer.h"
#include "auxcommon/MockAuxgenerictypes.h"

using namespace ::testing;

class TestAuxGameRestriction : public GenericLobbyTestSuite
{
protected:

	void SetUp() override
	{
		GenericLobbyTestSuite::SetUp();
		mockAuxgenerictypes = new MockAuxgenerictypes();
	}

    void TearDown() override
    {
		GenericLobbyTestSuite::TearDown();
		if (mockAuxgenerictypes)
		{
			delete mockAuxgenerictypes;
			mockAuxgenerictypes = nullptr;
		}
    }

    void ExpectMaxGameCountResult(
        aux::HostType hostId,
        aux::GamingSite siteId,
        int currentGameCount,
        int gameLimitForHost,
        int gameLimitForSite,
        auxclienterr::ClientErrorCode expectedErrorCode
    )
    {
        using namespace ::testing;
        MockCommInterface commInterface;

        AuxLobbyServerObject lobbyServer(commInterface);

		expectConnects(lobbyServer);
        CommMsgBody initMsg;
        
        EXPECT_TRUE(lobbyServer._safeInit(initMsg));

		unsigned userIntId = 1;

		addUser(hostId, userIntId);
		submitUsersToServer();

        AuxLobbyTableTypePtr lobbyTableType(new AuxLobbyTableType());
        AuxLobbyPlayerPtr lobbyPlayer(new AuxLobbyPlayer("player", userIntId, hostId));

        LobbyLoginSessionPtr loginSession(new LobbyLoginSession(lobbyPlayer));
        loginSession->hostId = hostId;
        loginSession->siteId = siteId;

        INT16 errorCode = auxclienterr::ERROR_CLIENT_NOERROR;
        PString errorMessage;
        Atf::MsgBodyWithJSON body;
        auto outParameter = std::tie(errorCode, errorMessage, body);
        INT16 result = AuxGameRestriction(
            &lobbyServer,
            loginSession,
            lobbyTableType
        ).checkMaxGameCount(outParameter);

        EXPECT_EQ(errorCode, expectedErrorCode);
        EXPECT_EQ(result, expectedErrorCode);
    }
};

TEST_F(TestAuxGameRestriction, checkMaxGameCount_nonGgnNotRestricted)
{
	EXPECT_CALL(*mockAuxgenerictypes, isGgnHost(aux::HOST_POKERSTAR)).WillRepeatedly(Return(false));

    auto gameLimitForHost = INT32_MAX;
    auto gameLimitForSite = INT32_MAX;
    ON_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.PS", _)).WillByDefault(Return(gameLimitForHost));
    ExpectMaxGameCountResult(
        aux::HOST_POKERSTAR,
        aux::GAMING_SITE_UK,
        1, gameLimitForHost, gameLimitForSite,
        auxclienterr::ERROR_CLIENT_NOERROR
    );
}

TEST_F(TestAuxGameRestriction, checkMaxGameCount_nonGgnHostRestricted)
{
	EXPECT_CALL(*mockAuxgenerictypes, isGgnHost(aux::HOST_POKERSTAR)).WillRepeatedly(Return(false));
    ExpectMaxGameCountResult(
        aux::HOST_POKERSTAR,
        aux::GAMING_SITE_UK,
        1, 1, INT32_MAX,
        auxclienterr::ERROR_CLIENT_OVER_MAX_GAME_LIMIT
    );
}

TEST_F(TestAuxGameRestriction, checkMaxGameCount_nonGgnSiteRestricted)
{
	EXPECT_CALL(*mockAuxgenerictypes, isGgnHost(aux::HOST_POKERSTAR)).WillRepeatedly(Return(false));

    ExpectMaxGameCountResult(
        aux::HOST_POKERSTAR,
        aux::GAMING_SITE_UK,
        1, INT32_MAX, 1,
        auxclienterr::ERROR_CLIENT_OVER_MAX_GAME_LIMIT
    );
}

TEST_F(TestAuxGameRestriction, checkMaxGameCount_ggnNotRestricted)
{
	EXPECT_CALL(*mockAuxgenerictypes, isGgnHost(aux::HOST_PADDYPOWER)).WillRepeatedly(Return(true));

    auto gameLimitForHost = INT32_MAX;
    auto gameLimitForSite = INT32_MAX;
    ON_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.PPB", _)).WillByDefault(Return(gameLimitForHost));

    ExpectMaxGameCountResult(
        aux::HOST_PADDYPOWER,
        aux::GAMING_SITE_UK,
        1, gameLimitForHost, gameLimitForSite,
        auxclienterr::ERROR_CLIENT_NOERROR
    );
}

TEST_F(TestAuxGameRestriction, checkMaxGameCount_ggnHostRestricted)
{
	EXPECT_CALL(*mockAuxgenerictypes, isGgnHost(aux::HOST_PADDYPOWER)).WillRepeatedly(Return(true));

    ExpectMaxGameCountResult(
        aux::HOST_PADDYPOWER,
        aux::GAMING_SITE_UK,
        1, 1, INT32_MAX,
        auxclienterr::ERROR_CLIENT_OVER_MAX_GAME_LIMIT
    );
}

TEST_F(TestAuxGameRestriction, checkMaxGameCount_ggnSiteRestricted)
{
	EXPECT_CALL(*mockAuxgenerictypes, isGgnHost(aux::HOST_PADDYPOWER)).WillRepeatedly(Return(true));
    ExpectMaxGameCountResult(
        aux::HOST_PADDYPOWER,
        aux::GAMING_SITE_UK,
        1, INT32_MAX, 1,
        auxclienterr::ERROR_CLIENT_OVER_MAX_GAME_LIMIT
    );
}
