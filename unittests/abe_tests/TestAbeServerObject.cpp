
#include "AbeServerObject.h"
#include "commlib2a/MockCommInterface.h"
#include "commlib2a/MockServerStartParams.h"
#include "plib/MockPIniFile.h"
#include "plib/MockPpIncludeBase.h"
#include "atf/MockAtfCommObjectImpl.h"

#include "atf/FakeServer.h"
#include "atf/MockService.h"
#include "auxservercommon/MockAuxReefAccessor.h"

#include <vector>

using namespace testing;
FakeServer* fakeServer = nullptr;
MockService* mockService = nullptr;
MockPIniFile* mockPIniFile = nullptr;
MockPpIncludeBase* mockPpIncludeBase = nullptr;
MockAtfCommObjectImpl* mockAtfCommObjectImpl = nullptr;
MockServerStartParams* mockServerStartParams = nullptr;

class TestAbeServerObject : public Test
{
protected:
	const std::string iniFileName = "TestAbeIniFileName";
	const std::string defaultValue = "testDefaultValue";
protected:

	void SetUp() override
	{
		fakeServer = new FakeServer();
		mockService = new MockService();
		mockPIniFile = new MockPIniFile();
		mockPpIncludeBase = new MockPpIncludeBase();
		mockAtfCommObjectImpl = new MockAtfCommObjectImpl();
		mockServerStartParams = new MockServerStartParams();

		init();
	};

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
		if (mockPpIncludeBase)
		{
			delete mockPpIncludeBase;
			mockPpIncludeBase = nullptr;
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

	void expectInitCalls()
	{
		EXPECT_CALL(*mockServerStartParams,
			parseServerStartParams(_, _, _)).WillOnce(
				Invoke([this](ServerStartParams* serverStartParams, CommMsgParser& parser, const char* iniFileName_)
					{
						serverStartParams->fullIniFileName = this->iniFileName.c_str();
					}));
		EXPECT_CALL(*mockPIniFile, _load(_, iniFileName)).Times(AtLeast(1));


		EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICCONNECT", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSection(_, "STATICSETTINGS", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSection(_, "DYNAMICSETTINGS", _)).Times(AtLeast(1));


		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("STATICSETTINGS", _)).Times(AtLeast(1));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICSETTINGS", _)).Times(AtLeast(1));

		// Expected some non-empty strings
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "idDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "AbeDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "IntegrationServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "EntropyServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "lobbyServerAddress")).WillRepeatedly(Return(defaultValue.c_str()));
		EXPECT_CALL(*mockPIniFile, getSectionProperty("DYNAMICCONNECT", "TableDbmAddress")).WillRepeatedly(Return(defaultValue.c_str()));
	}

	AbeServerObject::BonusTemplatePtr createTestBonusTemplate(UINT32 templateId)
	{
		auto bonusTemplate = std::make_shared<AbeServerObject::BonusTemplate>();
		bonusTemplate->dbBonusTemplate.dbBonusTemplate.bonusTemplateId = templateId;
		bonusTemplate->expirySpec.expiryType = 0; // BE_EXPIRY_BY_NEXT_DAY_UTC
		CommUtcTime validFrom, validUntil;
		validFrom._year = 2000;
		validFrom._month = 6;
		validFrom._day = 1;
		validFrom._hour = 0;
		validFrom._minute = 0;
		validFrom._second = 0;

		validUntil._year = 2100;
		validUntil._month = 7;
		validUntil._day = 30;
		validUntil._hour = 23;
		validUntil._minute = 59;
		validUntil._second = 59;

		bonusTemplate->dbBonusTemplate.dbBonusTemplate.validFromUtc = validFrom;
		bonusTemplate->dbBonusTemplate.dbBonusTemplate.validUntilUtc = validUntil;
		return bonusTemplate;
	}

	aux::BOUser user;
	AbeServerObject::BonusTemplatePtr bonusTemplate;
	AbeServerObject::SoTDUserProcessingInfo userInfo;
	aux::AbeBonus abeBonus;

	void init()
	{
		// Add bonus templates
		UINT32 templateId = 12345;
		bonusTemplate = createTestBonusTemplate(templateId);
		user.boId = 1001;
		user.userIntId = 1;

		int bonusId = 67890;
		AbeServerObject::UserSotdBonus usrBonus(user.boId, user.userIntId, bonusId, 1);
		abeBonus.bonus.bonusId = bonusId;
		
		userInfo.cached = true;
		userInfo.bonuses[usrBonus.bonusId] = abeBonus;
	}

};

TEST_F(TestAbeServerObject, issueBonusToPlayer_bonus_issued)
{
	expectInitCalls();

	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));

	MockCommInterface mockCommInterface;
	AbeServerObject serverObject(mockCommInterface);
	CommMsgBody initMsg;
	EXPECT_TRUE(serverObject._safeInit(initMsg));

	EXPECT_CALL(*mockPpIncludeBase, PCurrentUTCTime(_))
		.WillRepeatedly(Invoke([](struct tm* tm) {
		tm->tm_year = 2025 - 1900; // Year since 1900
		tm->tm_mon = 5; // June (0-based)
		tm->tm_mday = 10;
		tm->tm_hour = 10;
		tm->tm_min = 1;
		tm->tm_sec = 29;
			}));

	CommUtcTime targetTimeUtc;  
	targetTimeUtc._year = 2025; targetTimeUtc._month = 6; targetTimeUtc._day = 10;
	targetTimeUtc._hour = 10; targetTimeUtc._minute = 1; targetTimeUtc._second = 30;

	serverObject.addBonusTemplateById(bonusTemplate);
	serverObject.soTDUserRequests[user] = userInfo;	

	INT16 errCode = 0;
	PString errStr;
	auto bonus = std::make_shared<AbeServerObject::Bonus>();
	serverObject.issueBonusToPlayer(user, bonusTemplate->dbBonusTemplate.dbBonusTemplate.bonusTemplateId, 1, targetTimeUtc, "issuer", bonus, errCode, errStr);

	ASSERT_EQ(errCode, 0);
}

TEST_F(TestAbeServerObject, issueBonusToPlayer_bonus_rejected)
{
	expectInitCalls();

	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));

	MockCommInterface mockCommInterface;
	AbeServerObject serverObject(mockCommInterface);
	CommMsgBody initMsg;
	EXPECT_TRUE(serverObject._safeInit(initMsg));

	EXPECT_CALL(*mockPpIncludeBase, PCurrentUTCTime(_))
		.WillRepeatedly(Invoke([](struct tm* tm) {
		tm->tm_year = 2025 - 1900; // Year since 1900
		tm->tm_mon = 5; // June (0-based)
		tm->tm_mday =11;
		tm->tm_hour = 10;
		tm->tm_min = 1;
		tm->tm_sec = 29;
			}));

	CommUtcTime targetTimeUtc;
	targetTimeUtc._year = 2025; targetTimeUtc._month = 6; targetTimeUtc._day = 10;
	targetTimeUtc._hour = 10; targetTimeUtc._minute = 1; targetTimeUtc._second = 30;

	serverObject.addBonusTemplateById(bonusTemplate);
	serverObject.soTDUserRequests[user] = userInfo;

	INT16 errCode = 0;
	PString errStr;
	auto bonus = std::make_shared<AbeServerObject::Bonus>();
	serverObject.issueBonusToPlayer(user, bonusTemplate->dbBonusTemplate.dbBonusTemplate.bonusTemplateId, 1, targetTimeUtc, "issuer", bonus, errCode, errStr);

	ASSERT_EQ(errCode, auxservererr::SERVER_ERROR_ABE_BONUS_OVER_LIMIT);
}

TEST_F(TestAbeServerObject, issueBonusToPlayer_day_change_ahead_issued)
{
	expectInitCalls();

	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));

	MockCommInterface mockCommInterface;
	AbeServerObject serverObject(mockCommInterface);
	CommMsgBody initMsg;
	EXPECT_TRUE(serverObject._safeInit(initMsg));

	// The bonus server might be a split of a second behind
	EXPECT_CALL(*mockPpIncludeBase, PCurrentUTCTime(_))
		.WillRepeatedly(Invoke([](struct tm* tm) {
		tm->tm_year = 2025 - 1900; // Year since 1900
		tm->tm_mon = 5; // June (0-based)
		tm->tm_mday = 11;
		tm->tm_hour = 23;
		tm->tm_min = 59;
		tm->tm_sec = 59;
			}));

	// The target is already the next day
	CommUtcTime targetTimeUtc;
	targetTimeUtc._year = 2025; targetTimeUtc._month = 6; targetTimeUtc._day = 12;
	targetTimeUtc._hour = 0; targetTimeUtc._minute = 0; targetTimeUtc._second = 0;

	serverObject.addBonusTemplateById(bonusTemplate);
	serverObject.soTDUserRequests[user] = userInfo;

	INT16 errCode = 0;
	PString errStr;
	auto bonus = std::make_shared<AbeServerObject::Bonus>();
	serverObject.issueBonusToPlayer(user, bonusTemplate->dbBonusTemplate.dbBonusTemplate.bonusTemplateId, 1, targetTimeUtc, "issuer", bonus, errCode, errStr);

	ASSERT_EQ(errCode,0);
}

TEST_F(TestAbeServerObject, issueBonusToPlayer_day_change_delayed_rejected)
{
	expectInitCalls();

	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));

	MockCommInterface mockCommInterface;
	AbeServerObject serverObject(mockCommInterface);
	CommMsgBody initMsg;
	EXPECT_TRUE(serverObject._safeInit(initMsg));

	// The bonus server might be a split of a second behind
	EXPECT_CALL(*mockPpIncludeBase, PCurrentUTCTime(_))
		.WillRepeatedly(Invoke([](struct tm* tm) {
		tm->tm_year = 2025 - 1900; // Year since 1900
		tm->tm_mon = 5; // June (0-based)
		tm->tm_mday = 11;
		tm->tm_hour = 0;
		tm->tm_min = 0;
		tm->tm_sec = 0;
			}));

	// The target is already the next day
	CommUtcTime targetTimeUtc;
	targetTimeUtc._year = 2025; targetTimeUtc._month = 6; targetTimeUtc._day = 10;
	targetTimeUtc._hour = 23; targetTimeUtc._minute = 59; targetTimeUtc._second = 59;

	serverObject.addBonusTemplateById(bonusTemplate);
	serverObject.soTDUserRequests[user] = userInfo;

	INT16 errCode = 0;
	PString errStr;
	auto bonus = std::make_shared<AbeServerObject::Bonus>();
	serverObject.issueBonusToPlayer(user, bonusTemplate->dbBonusTemplate.dbBonusTemplate.bonusTemplateId, 1, targetTimeUtc, "issuer", bonus, errCode, errStr);

	ASSERT_EQ(errCode, auxservererr::SERVER_ERROR_ABE_BONUS_OVER_LIMIT);
}

//TEST_F(TestAbeServerObject, issueBonusToPlayerFromServer)
//{
//	expectInitCalls();
//
//	EXPECT_CALL(*mockService, serviceStarted("GADFDB"));
//	EXPECT_CALL(*mockService, serviceStarted("SotdSpin"));
//
//	MockCommInterface mockCommInterface;
//	AbeServerObject serverObject(mockCommInterface);
//	CommMsgBody initMsg;
//	EXPECT_TRUE(serverObject._safeInit(initMsg));
//
//	// Init test structures on the fake server
//	auto user = createTestBOUser();
//
//
//	int bonusTemplateId = 12345;
//	int bonusId = 67890;
//	AbeServerObject::UserSotdBonus usrBonus(user.boId, user.userIntId, bonusId, 1);
//	aux::AbeBonus abeBonus;
//	abeBonus.bonus.bonusId = bonusId;
//
//
//	AbeServerObject::SoTDUserProcessingInfo userInfo;
//	userInfo.cached = true;
//	userInfo.bonuses[usrBonus.bonusId] = abeBonus;
//	//userInfo.userStates[bonusTemplateId] = std::vector<aux::DbAbeUserStates>();
//
//	serverObject.soTDUserRequests[user] = userInfo;
//	serverObject.startPlayerSpinService(usrBonus);
//
//	// Trigger the server reply
//	IS::AbeServer::Protocol_AUX_IS_MSG_A_CHECK_USER_FLAGS response;
//	response.errorCode = 0;
//	response.flagError = 0;
//
//	CommMsgBody msg;
//	response.composeMsg(msg);
//	fakeServer->triggerOnReply("SotdSpin", AUX_IS_MSG_A_CHECK_USER_FLAGS, msg);
//}