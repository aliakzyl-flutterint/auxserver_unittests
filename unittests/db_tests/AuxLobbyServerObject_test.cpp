#include <gtest/gtest.h>

#include "../mocks/ExcludeNonMockHeaders.h"
#include "../mocks/commlib2a/commsrv_mock.h"
#include "../mocks/commlib2a/commcli_mock.h"
#include "../mocks/commlib2a/commgrdnull_mock.h"
#include "../mocks/commlib2a/MockCommInterface.h"
#include "../mocks/protocols/counters_mock.h"
#include "../mocks/atf/AtfCommServerObject_mock.h"
#include "../mocks/auxiliary/auxlobby/AuxLobbyServerObject_mock.h"

using ::testing::Return;

class TestAuxLobbyServerObject: public ::testing::Test
{
protected:

    void ExpectMaxGameCountResult(
        aux::HostType hostId,
        aux::GamingSite siteId,
        int currentGameCount,
        int gameLimitForHost,
        int gameLimitForSite,
        auxclienterr::ClientErrorCode expectedErrorCode
    )
    {
        MockCommInterface commInterface;

        AuxLobbyServerObject lobbyServer(commInterface);
        lobbyServer.dynamicConfig = std::make_shared<AuxLobbyDynamicConfig>();

        AuxLobbyTableTypePtr lobbyTableType(new AuxLobbyTableType());
        AuxLobbyPlayerPtr lobbyPlayer(new AuxLobbyPlayer("player", 0, hostId));

        LobbyLoginSessionPtr loginSession(new LobbyLoginSession(lobbyPlayer));
        loginSession->hostId = hostId;
        loginSession->siteId = siteId;

        EXPECT_CALL(
            lobbyPlayer->gameLaunchRestriction,
            getNumOfGameInPlayingOrReserved()
        ).WillOnce(Return(currentGameCount));
        EXPECT_CALL(
            lobbyServer.dynamicConfig->maxGamePerPlayerConfig,
            getMaxGameNumberPerPlayer(hostId)
        ).WillOnce(Return(gameLimitForHost));
        EXPECT_CALL(
            lobbyServer.dynamicConfig->maxGamePerPlayerConfig,
            getMaxGameNumberPerPlayerBySiteId(siteId)
        ).WillOnce(Return(gameLimitForSite));

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


TEST_F(TestAuxLobbyServerObject, Test_checkMaxGameCount_nonGgnNotRestricted)
{
    ASSERT_TRUE(!isGgnHost(aux::HOST_POKERSTAR));
    ExpectMaxGameCountResult(
        aux::HOST_POKERSTAR,
        aux::GAMING_SITE_UK,
        1, INT32_MAX, INT32_MAX,
        auxclienterr::ERROR_CLIENT_NOERROR
    );
}

TEST_F(TestAuxLobbyServerObject, Test_checkMaxGameCount_nonGgnHostRestricted)
{
    ASSERT_TRUE(!isGgnHost(aux::HOST_POKERSTAR));
    ExpectMaxGameCountResult(
        aux::HOST_POKERSTAR,
        aux::GAMING_SITE_UK,
        1, 1, INT32_MAX,
        auxclienterr::ERROR_CLIENT_OVER_MAX_SLOT_LIMIT
    );
}

TEST_F(TestAuxLobbyServerObject, Test_checkMaxGameCount_nonGgnSiteRestricted)
{
    ASSERT_TRUE(!isGgnHost(aux::HOST_POKERSTAR));
    ExpectMaxGameCountResult(
        aux::HOST_POKERSTAR,
        aux::GAMING_SITE_UK,
        1, INT32_MAX, 1,
        auxclienterr::ERROR_CLIENT_OVER_MAX_SLOT_LIMIT
    );
}

TEST_F(TestAuxLobbyServerObject, Test_checkMaxGameCount_ggnNotRestricted)
{
    ASSERT_TRUE(isGgnHost(aux::HOST_PADDYPOWER));
    ExpectMaxGameCountResult(
        aux::HOST_PADDYPOWER,
        aux::GAMING_SITE_UK,
        1, INT32_MAX, INT32_MAX,
        auxclienterr::ERROR_CLIENT_NOERROR
    );
}

TEST_F(TestAuxLobbyServerObject, Test_checkMaxGameCount_ggnHostRestricted)
{
    ASSERT_TRUE(isGgnHost(aux::HOST_PADDYPOWER));
    ExpectMaxGameCountResult(
        aux::HOST_PADDYPOWER,
        aux::GAMING_SITE_UK,
        1, 1, INT32_MAX,
        auxclienterr::ERROR_CLIENT_OVER_MAX_SLOT_LIMIT
    );
}

TEST_F(TestAuxLobbyServerObject, Test_checkMaxGameCount_ggnSiteRestricted)
{
    ASSERT_TRUE(isGgnHost(aux::HOST_PADDYPOWER));
    ExpectMaxGameCountResult(
        aux::HOST_PADDYPOWER,
        aux::GAMING_SITE_UK,
        1, INT32_MAX, 1,
        auxclienterr::ERROR_CLIENT_NOERROR
    );
}
