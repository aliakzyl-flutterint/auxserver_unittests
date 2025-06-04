
#include "JackpotServerObject.h"
#include "commlib2a/MockCommInterface.h"
#include "commlib2a/MockServerStartParams.h"
#include "plib/MockPIniFile.h"
#include "atf/MockAtfCommObjectImpl.h"

#include "atf/FakeServer.h"
#include "atf/MockService.h"
#include "auxservercommon/MockAuxReefAccessor.h"

#include <vector>

using namespace testing;
FakeServer* fakeServer = nullptr;
MockService* mockService = nullptr;
MockPIniFile* mockPIniFile = nullptr;
MockAtfCommObjectImpl* mockAtfCommObjectImpl = nullptr;
MockServerStartParams* mockServerStartParams = nullptr;

class TestJackpotServerObject : public Test
{
protected:
	const std::string iniFileName = "TestJackpotIniFileName";
	const std::string defaultValue = "testDefaultValue";
	const std::string hundredStr = "100";

protected:

	void SetUp() override
	{
		fakeServer = new FakeServer();
		mockService = new MockService();
		mockPIniFile = new MockPIniFile();
		mockAtfCommObjectImpl = new MockAtfCommObjectImpl();
		mockServerStartParams = new MockServerStartParams();
	};

	void expectInitCalls()
	{
		EXPECT_CALL(*mockServerStartParams,
			parseServerStartParams(_, _, _)).WillOnce(
				Invoke([this](ServerStartParams* serverStartParams, CommMsgParser& parser, const char* iniFileName_)
					{
						serverStartParams->fullIniFileName = this->iniFileName.c_str();
					}));
		EXPECT_CALL(*mockPIniFile, _load(_, iniFileName)).Times(AtLeast(1));

		EXPECT_CALL(*mockPIniFile, getSection(_, "STATICSETTINGS", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICSETTINGS", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSection(_, "STATICCONNECT", _)).Times(AtLeast(1));
		
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSectionIntProperty("DYNAMICSETTINGS", _, _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICCONNECT", _)).Times(AtLeast(1));


		// Expected some non-empty strings
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICCONNECT", "jsaAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICCONNECT", "integrationServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICCONNECT", "idDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICCONNECT", "jackpotDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));

		// System Id
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", "sysId")).WillRepeatedly(Return(hundredStr.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionIntProperty("STATICSETTINGS", "sysId", _)).WillRepeatedly(Return(100));

		EXPECT_CALL(*mockAtfCommObjectImpl, connect(_, _, _)).Times(AtLeast(1));

		EXPECT_CALL(*mockAuxReefAccessor, init(_)).Times(2); //reefAccessor and stateAccessor
	}

	void expectTelemetryConfig()
	{
		EXPECT_CALL(*mockPIniFile, getSection(_, "LOGGER", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSectionIntProperty("LOGGER", _, _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("LOGGER", _)).Times(AtLeast(1));
		ON_CALL(*mockPIniFile, getSectionIntProperty("LOGGER", "useLogger", _)).WillByDefault(Return(1));
		ON_CALL(*mockPIniFile, getSectionProperty("LOGGER", "loggerAddress")).WillByDefault(Return(defaultValue.c_str()));
		ON_CALL(*mockPIniFile, getSectionProperty("LOGGER", "logStationName")).WillByDefault(Return(defaultValue.c_str()));
	}

	void TearDown() override
	{
		if (fakeServer)
		{
			delete fakeServer;
			fakeServer = nullptr;
		}
		if (mockService)
		{
			delete mockService;
			mockService = nullptr;
		}
		if (mockPIniFile)
		{
			delete mockPIniFile;
			mockPIniFile = nullptr;
		}
		if (mockAtfCommObjectImpl)
		{
			delete mockAtfCommObjectImpl;
			mockAtfCommObjectImpl = nullptr;
		}
		if (mockServerStartParams)
		{
			delete mockServerStartParams;
			mockServerStartParams = nullptr;
		}
	}

};

TEST_F(TestJackpotServerObject, test_PerformanceCounter)
{
	expectInitCalls();
	expectTelemetryConfig();
	MockCommInterface mockCommInterface;
	AuxJackpotServerObject serverObject(mockCommInterface);
	CommMsgBody initMsg;
	EXPECT_TRUE(serverObject._safeInit(initMsg));

	serverObject.jpServerManager.jpRefNameVsCounters[PString("Jeannies_Magic_Lamp_bluePot3_CAD_CAON_PM")].currentPoolValueInCents = 10;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("Jeannies_Magic_Lamp_greenPot2_CAD_CAON_PM")].currentPoolValueInCents = 20;

	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersForgottenV2DK_RM")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersForgottenV2SE_RM")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersForgottenV2UK_RM")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersLegendaryV2DK_RM")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersLegendaryV2SE_RM")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersLegendaryV2UK_RM")].currentPoolValueInCents = 30;

	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersMythicalV2DK_RM")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersMythicalV2SE_RM")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("MultiC_YGG_JackpotRaidersMythicalV2UK_RM")].currentPoolValueInCents = 30;

	serverObject.jpServerManager.jpRefNameVsCounters[PString("SKW_StarsONDaily_1662385642822__daily-1_CAON")].currentPoolValueInCents = 30;
	serverObject.jpServerManager.jpRefNameVsCounters[PString("Wreck_of_Riches_WoRWhitePot2_CAD_CAON_PM")].currentPoolValueInCents = 30;

	std::vector<PNameValue> perfData;
	serverObject.performanceCounter.getPerformanceData(perfData);

	std::unordered_map<std::string, int> name_lengths;

	for (auto& p : perfData)
	{
		name_lengths[p.name.c_str()] = p.name.length();
	}

	std::vector<decltype(name_lengths)::value_type> exceeding_keys;
	std::copy_if(name_lengths.begin(), name_lengths.end(), std::back_inserter(exceeding_keys), [](const auto& p) { return p.second > 63; });

	EXPECT_EQ(23, exceeding_keys.size());
}