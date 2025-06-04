
#include "GenericLobbyTestSuite.h"

#include <AuxLobbyServerObject.h>
#include "atf/MockAtfCommObjectImpl.h"
#include "atf/FakeServer.h"
#include "plib/MockPIniFile.h"

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
	EXPECT_CALL(*mockPIniFile, getSection(_, "STATICSETTINGS", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICSETTINGS", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "STATICCONNECT", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "CLIENTCONNINFO", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICCONNECT", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "TABLEPLACEMENTRULES", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "SPINDELAYSETTINGS", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "DISABLEDSPINFEATURESSETTINGS", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "GERMANYBREAKSETTINGS", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "PRIZEGAME", _)).Times(AtLeast(1));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "myId"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "dynamicLogLevel"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "initStatusPs"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "initStatusFt"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "initStatusSbg"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "initStatusBfair"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "initStatusPpwr"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "initStatusSbm"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "initStatusFd"));

	// Expected some non-empty strings
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "tableDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "tableDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "itTableDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "itTableDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "hhIceTableDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "hhIceTableDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "itHhIceTableDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "itHhIceTableDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "integrationDispatcherServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "integrationDispatcherServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "entropyServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "entropyServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "rgMessageRouterAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "rgMessageRouterInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "dfpServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "dfpServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "tableMonitorServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "tableMonitorServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "vttmServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "vttmServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "multitabletypes")).WillRepeatedly(Return(defaultValue.c_str()));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "expiredTimeFinishedPromoSec"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "expiredTimeLmhSec"));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "javaHomePath"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "javaXcBinaryHomePath"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "javaXcTempPath"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "slot.extraPlayTimeLimitSetting"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "lite.extraPlayTimeLimitSetting"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "sessionTimeLimitInMinutes"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "minutesToDeclareSessionStuck"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "rcPauseGameForSites"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "closeHandBetBackSites"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "gameConnectTimeoutSeconds"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "minIntervalPlayerRequestHandHistoryInSeconds"));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("CLIENTCONNINFO", "ShadowLobbyAddress"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("CLIENTCONNINFO", "ShadowLobbyInstance"));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "vendorMsgTimeoutToBetBackInMinutes"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "maxExposureForSlots"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "ssj.testSetting"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "maxTableDeferRemoveTimeSeconds")).WillRepeatedly(Return(hundredValue.c_str()));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "UserAppDataKeys"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "useSpainVerifiedforMarketing"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "useUKGCPromoBan"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "disabledVendors"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "vendorsWithDemoMode"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "disabledBuyoutFeatureSites"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "checkHiddenGame"));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", "autoRemoveHiddenInterruptedGame"));

	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxSlotGamesPerPlayer.FT", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxSlotGamesPerPlayer.PS", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxSlotGamesPerPlayer.SKY", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxSlotGamesPerPlayer.SIM", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxSlotGamesPerPlayer.PSV", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxSlotGamesPerPlayer.PPB", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxSlotGamesPerPlayer.FD", _));

	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.FT", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.PS", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.SKY", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.SIM", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.PPB", _));
	EXPECT_CALL(*mockPIniFile, getSectionIntProperty(_, "maxGamesPerPlayer.FD", _));
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
