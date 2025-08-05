#include "ServerObjectsExpects.h"

#include "AuxLobbyServerObject.h"
#include "atf/MockAtfCommObjectImpl.h"
#include "plib/MockPIniFile.h"

using namespace testing;

namespace
{
	std::string defaultValue = "testDefaultValue";
	std::string hundredValue = "100";
	std::string connType = "auxlobby";
	std::string connAuxApp = "auxapp";
	std::string dbmAddress = "testDbmAddress";
	std::string dbmInstance = "testDbmInstance";
	std::string roOltpDbmAddress = "testRoOltpDbmAddress";
	std::string roOltpDbmInstance = "testRoOltpDbmInstance";
	std::string idDbmAddress = "testIdDbmAddress";
	std::string idDbmInstance = "testIdDbmInstance";
	std::string authIntegrationServerAddress = "testAuthIntegrationServerAddress";
	std::string authIntegrationServerInstance = "testAuthIntegrationServerInstance";
	std::string integrationServerAddress = "testIntegrationServerAddress";
	std::string integrationServerInstance = "testIntegrationServerInstance";
}

void expects::ExpectAuxRaceInits()
{
	EXPECT_CALL(*mockPIniFile, getSection(_, "STATICSETTINGS", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICCONNECT", _)).Times(AtLeast(1));
	EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICSETTINGS", _)).Times(AtLeast(1));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", _));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "idDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "idDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "RaceDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "RaceDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "TableDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "TableDbmInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "IntegrationServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "IntegrationServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "NotificationServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "NotificationServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "jackpotServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "jackpotServerInstance")).WillRepeatedly(Return(defaultValue.c_str()));

	EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", _)).Times(AtLeast(1));
}

void expects::ExpectLobbyInits()
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

void expects::ExpectLobbyConnects(AuxLobbyServerObject& tstObj)
{
	tstObj.staticConfig.staticConnect.dbmAddress.set(dbmAddress.c_str());
	tstObj.staticConfig.staticConnect.dbmInstance.set(dbmInstance.c_str());
	tstObj.staticConfig.staticConnect.roOltpDbmAddress.set(roOltpDbmAddress.c_str());
	tstObj.staticConfig.staticConnect.roOltpDbmInstance.set(roOltpDbmInstance.c_str());
	tstObj.staticConfig.staticConnect.idDbmAddress.set(idDbmAddress.c_str());
	tstObj.staticConfig.staticConnect.idDbmInstance.set(idDbmInstance.c_str());
	tstObj.staticConfig.staticConnect.authIntegrationServerAddress.set(authIntegrationServerAddress.c_str());
	tstObj.staticConfig.staticConnect.authIntegrationServerInstance.set(authIntegrationServerInstance.c_str());
	tstObj.staticConfig.staticConnect.integrationServerAddress.set(integrationServerAddress.c_str());
	tstObj.staticConfig.staticConnect.integrationServerInstance.set(integrationServerInstance.c_str());

	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(dbmAddress.c_str()), StrEq(dbmInstance.c_str()), StrEq(connType.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(roOltpDbmAddress.c_str()), StrEq(roOltpDbmInstance.c_str()), StrEq(connType.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(idDbmAddress.c_str()), StrEq(idDbmInstance.c_str()), StrEq(connAuxApp.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(authIntegrationServerAddress.c_str()), StrEq(authIntegrationServerInstance.c_str()), StrEq(connType.c_str())));
	EXPECT_CALL(*mockAtfCommObjectImpl, connect(StrEq(integrationServerAddress.c_str()), StrEq(integrationServerInstance.c_str()), StrEq(connType.c_str())));
}
