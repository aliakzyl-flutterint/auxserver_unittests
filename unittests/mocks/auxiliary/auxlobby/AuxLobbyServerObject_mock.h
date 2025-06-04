#ifndef AuxLobbyServerObject_mock_h__
#define AuxLobbyServerObject_mock_h__

#include <tuple>
#include <memory>
#include <sstream>
#include <iostream>
#include <map>

#include "../../protocols/auxHandHistory.h"
#include "../../protocols/msgchecker/MsgChecker.h"

#include "../../atf/CommGrdNullWithInfo.h"
#include "../../atf/AtfCommServerGConn.h"
#include "../../atf/Service.h"

#include "../../auxprotocols/AuxCommonDefs.h"
#include "../../auxservercommon/AuxCommServerObject_mock.h"
#include "../../../auxiliary/auxservercommon/AuxServerCommonDefs.h"
#include "../../../auxiliary/auxservercommon/auxconfigcommon.h"

#include "../../../auxiliary/auxcommon/auxgenerictypes.h"
#include "../../../auxiliary/auxcommon/UniqueSeqId.h"
#include "../../../auxiliary/auxcommon/CommGrdHostAuth.h"
#include "../../../auxiliary/auxcommon/CommGrdAuxToken.h"
#include "../../../auxiliary/auxcommon/auxgenerictypes.h"
#include "../../../auxiliary/auxcommon/MainDomainObjects.h"
#include "../../../auxiliary/auxcommon/AuxDbm.h"
#include "../../../auxiliary/auxcommon/auxgenericfunctions.h"

#include "../../../auxiliary/auxprotocols/LobbyClientProtocols.h"
#include "../../../auxiliary/auxprotocols/LobbyServerProtocols.h"
#include "../../../auxiliary/auxprotocols/blackjackprotocols.h"
#include "../../../auxiliary/auxprotocols/MainDbmProtocols.h"
#include "../../../auxiliary/auxprotocols/ShadowLobbyClientProtocols.h"
#include "../../../auxiliary/auxprotocols/blackjackprotocols.h"
#include "../../../auxiliary/auxprotocols/LobbyServerProtocols.h"
#include "../../../auxiliary/auxprotocols/isprotocols.h"
#include "../../../auxiliary/auxprotocols/ShadowLobbyProtocols.h"
#include "../../../auxiliary/auxprotocols/ShadowLobbyClientProtocols.h"
#include "../../../auxiliary/auxprotocols/LobbyClientProtocols.h"
#include "../../../auxiliary/auxprotocols/TableServerProtocols.h"
#include "../../../auxiliary/auxprotocols/AuxServerErrors.h"
#include "../../../auxiliary/auxprotocols/AuxClientErrors.h"
#include "../../../auxiliary/auxprotocols/HandIdDbmProtocols.h"
#include "../../../auxiliary/auxprotocols/WebProtocols.h"
#include "../../../auxiliary/auxprotocols/ISAssistantProtocols.h"
#include "../../../auxiliary/auxprotocols/AuxTablePropNames.h"
#include "../../../auxiliary/auxprotocols/JackpotServerProtocols.h"
#include "../../../auxiliary/auxprotocols/NotificationProtocols.h"
#include "../../../auxiliary/auxprotocols/RaceServerProtocols.h"
#include "../../../auxiliary/auxprotocols/QueryDbmProtocols.h"
#include "../../../auxiliary/auxprotocols/AuxUserSettingsDbmProtocols.h"
#include "../../../auxiliary/auxprotocols/ISAssistantProtocols.h"
#include "../../../auxiliary/auxprotocols/VTTMServerProtocols.h"

#include "../../auxprotocols/HHServerProtocols.h"
#include "../../auxprotocols/CommonProtocolStructs.h"

#include "../../../auxiliary/auxservercommon/TableScriptParser2.h"
#include "../../../auxiliary/auxservercommon/AuxReefAccessor.h"
#include "../../../auxiliary/auxolapax/auxOax.h"
#include "../../../auxiliary/auxserverprotocols/ServerCommonProtocolStructs.h"
#include "../../../auxiliary/auxserverprotocols/CdlDbmProtocols.h"
#include "../../../auxiliary/auxprotocols/AdmProtocols.h"

#include "loginhelper.h"
#include "LobbyPerformanceCounters.h"

#include "AuxLobbyBlackjack.h"
#include "AuxLobbyRoulette.h"
#include "AuxLobbyDoubleBallRoulette.h"
#include "AuxLobbyHeadsUpHoldem.h"
#include "AuxLobbyBaccarat.h"
#include "AuxLobbyICGame.h"
#include "counters.h"
#include "../protocols/gsl.h" 

#include <gmock/gmock.h>

#define RG_MSG_CHECKER_LIMIT_FILE	"sanity.rgproxy.limit"
#define LD_MSG_CHECKER_LIMIT_FILE	"sanity.ldproxy.limit"
#define LITE_MSG_CHECKER_LIMIT_FILE	"sanity.ictable.limit"
#define TABLE_MSG_CHECKER_LIMIT_FILE "sanity.table.limit"
#define PTLD_MSG_CHECKER_LIMIT_FILE  "sanity.ptldproxy.limit"

#define TIMER_MSGID_CHECK_TABLE            (MSG_TIMER_USER_INTERNAL_BEGIN + 1)
#define TIMER_INTERVAL_CHECK_TABLE_SEC      30

#define TIMER_MSGID_CHECK_SHADOWUPDATE     (MSG_TIMER_USER_INTERNAL_BEGIN + 2)
#define TIMER_INTERVAL_CHECK_SHADOWUPDATE_SEC  10

#define TIMER_MSGID_CHECK_PROM_CANCEL_DONE            (MSG_TIMER_USER_INTERNAL_BEGIN + 3)
#define TIMER_INTERVAL_CHECK_PROM_CANCEL_DONE_SEC      10

#define TIMER_MSGID_CHECK_TABLE_CLOSE_AND_GET_CONFIRM	(MSG_TIMER_USER_INTERNAL_BEGIN + 4)
#define TIMER_MSGID_CHECK_TABLE_CLOSE					(MSG_TIMER_USER_INTERNAL_BEGIN + 5)
#define TIMER_MSGID_CHECK_TABLES_CLOSE					(MSG_TIMER_USER_INTERNAL_BEGIN + 6)
#define TIMER_MSGID_CHECK_WAIT_CLOSE_TABLES				(MSG_TIMER_USER_INTERNAL_BEGIN + 7)
#define TIMER_MSGID_CHECK_WAIT_PLAYER_LEFT_TABLE		(MSG_TIMER_USER_INTERNAL_BEGIN + 8)
#define TIMER_INTERVAL_CHECK_TABLE_CLOSE				10
#define MAX_TABLE_CLOSE_WAIT_TIME						200 // must be greater than RG/LD table force close time

#define NON_SEAT_RESERV_SEC_ON_RESERVATION_FAILURE				10
#define LOBBY_PLAYER_DELAYED_REMOVE_TIME_SEC					60
#define LOBBY_MAX_SEAT_RESERVATION_TIME_SEC						300 // must be greater than table defined MAX_SEAT_RESERVATION_TIME_SEC
#define LOBBY_MAX_LAUNCH_KEY_LIFE_TIME_SEC						600
#define LOBBY_MIN_INTERVAL_PLAYER_REQUEST_HAND_HISTORY_SEC		60
#define LOBBY_VENDOR_MSG_TIMEOUT_TO_DECLARE_STUCK_SESSION_MIN	2*MINUTES_IN_AN_HOUR
#define LOBBY_MAX_EXPOSURE_FOR_SLOTS                            200000000
#define LOBBY_MIN_INTERVAL_PLAYER_LEFT_TABLE_SEC		(60 * 3)
#define MAX_UNUSED_SP_TABLE_LIVE_SEC		(60 * 10)

#define AUX_SLOTS_TABLE_EXTRA_PROP_NAME_extraPlayTimeLimitSetting				"extraPlayTimeLimitSetting"
#define AUX_SLOTS_TABLE_EXTRA_PROP_NAME_vendorMsgTimeoutToDeclareSessionStuck	"vendorMsgTimeoutToDeclareSessionStuck"
#define AUX_SLOTS_TABLE_EXTRA_PROP_NAME_rgPlayerIdSuffix						"rgPlayerIdSuffix"
#define AUX_SLOTS_TABLE_EXTRA_PROP_NAME_stuckSessionInfo						"stuckSessionInfo"

#define AUX_LOBBY_INTERNAL_MSG_PLAYER_LEFT (AUX_MSG_INTERNAL_MESSAGE_BEGIN + 4)

#define DEFAULT_MAX_TABLE_DEFER_REMOVE_TIME_SECONDS 30
#define MAX_DELAY_TO_CHANGE_SYSTEM_STATUS_TO_RUNNING 30

#define EVENT_CONNECTION_REPLACED 1
#define EVENT_CONNECTION_DISCONNECTED_ON_INVALID_TOKEN 2

class AuxLobbyServerObject;
struct AuxLobbyTableData;
struct AuxLobbyTableType;
struct CasinoMSPromotion;

typedef Atf::SharedPointer<AuxLobbyTableData> AuxLobbyTableDataPtr;
typedef Atf::SharedPointer<AuxLobbyTableType> AuxLobbyTableTypePtr;

typedef std::pair<INT32, std::string>  HHCodeStringPair;
typedef std::map<INT32, HHCodeStringPair> HHCodeStringPairMap;

#define EMPTY_RESTRICTION_TABLE_ID 0
class AuxPlayerFsbTable
{
public:
	enum FsbTableStatus
	{
		ftsNone,
		ftsApplied,
		ftsReserved,
		ftsPlaying
	};

	FsbTableStatus status;
	UINT64 tableId;
	UINT32 exclusiveTableTypeId;

	AuxPlayerFsbTable() : status(ftsNone), tableId(0), exclusiveTableTypeId(0)
	{
	}

	MOCK_METHOD(void, applied, ());
	MOCK_METHOD(void, appliedExclusiveTableType, (UINT32 tableTypeId_));
	MOCK_METHOD(void, reserved, (UINT64 table));
	MOCK_METHOD(void, playing, (UINT64 table));
	MOCK_METHOD(void, closed, ());
	//void reconnect(const PString& auxUserId, AuxLobbyServerObject const *  serverObject);
};

class AuxLobbyStaticConfig
{
public:
	AuxLobbyStaticConfig() {}
	struct StaticConnect 
	{
		auxcfg::Required<PString> lobbyServerAddress;
		auxcfg::Optional<PString> lobbyServerInstance;

		auxcfg::Required<PString> dbmAddress;
		auxcfg::Optional<PString> dbmInstance;

		auxcfg::Optional<PString> roOltpDbmAddress;
		auxcfg::Optional<PString> roOltpDbmInstance;

		auxcfg::Required<PString> integrationServerAddress;
		auxcfg::Optional<PString> integrationServerInstance;

		auxcfg::Required<PString> authIntegrationServerAddress;
		auxcfg::Optional<PString> authIntegrationServerInstance;

		auxcfg::Optional<PString> jackpotServerAddress;
		auxcfg::Optional<PString> jackpotServerInstance;

		auxcfg::Optional<PString> jackpotLogicServerAddress;
		auxcfg::Optional<PString> jackpotLogicServerInstance;

		auxcfg::Optional<PString> hhServerAddress;
		auxcfg::Optional<PString> hhServerInstance;

		auxcfg::Optional<PString> proAssistantAddress;
		auxcfg::Optional<PString> proAssistantInstance;

		auxcfg::Optional<PString> userSettingsDbmAddress;
		auxcfg::Optional<PString> userSettingsDbmInstance;

		auxcfg::Required<PString> idDbmAddress;
		auxcfg::Optional<PString> idDbmInstance;

		auxcfg::Optional<PString> cdlDbmAddress;
		auxcfg::Optional<PString> cdlDbmInstance;

		auxcfg::Optional<PString> adminServerAddress;
		auxcfg::Optional<PString> adminServerInstance;

		//auxcfg::Required<PString> raceServerAddress;
		auxcfg::Optional<PString> raceServerAddress; // for compatible testing 
		auxcfg::Optional<PString> raceServerInstance;

		MOCK_METHOD(void, load, (const AuxEslResolver* esl));
		MOCK_METHOD(void, load, (const auxcfg::IniSection& section));

		MOCK_METHOD(void, log, ());
	} staticConnect;

	/*struct StaticTableservers
	{
		auxcfg::Required<PString> serverOrder;
		std::vector<PString> tableServerAddrs;
		std::list< std::pair<std::function<bool(AuxLobbyTableTypePtr tableType)>, std::vector<UINT8> > > rules;

		void load(const auxcfg::IniSection& section) { ; }
	}staticTableservers;*/

	struct StaticSettings
	{
		auxcfg::Optional<INT32> initStatusPs;
		auxcfg::Optional<INT32> initStatusFt;
		auxcfg::Optional<INT32> initStatusSbg;
		auxcfg::Optional<INT32> initStatusBfair;
		auxcfg::Optional<INT32> initStatusPpwr;
		auxcfg::Optional<INT32> initStatusSBM;
		auxcfg::Optional<INT32> initStatusFd;

		MOCK_METHOD(void, load, (const auxcfg::IniSection& section));

	} staticSettings;

	MOCK_METHOD(void, load, (const AuxEslResolver* esl, const PIniFile& ini));
};

class AuxLobbyDynamicConfig
{
public:
	struct DynamicSettingsConnInfo
	{
		auxcfg::Required<PString> tableDbmAddress;
		auxcfg::Optional<PString> tableDbmInstance;
		auxcfg::Optional<PString> itTableDbmAddress;
		auxcfg::Optional<PString> itTableDbmInstance;
		auxcfg::Optional<PString> hhIceTableDbmAddress;
		auxcfg::Optional<PString> hhIceTableDbmInstance;
		auxcfg::Optional<PString> itHhIceTableDbmAddress;
		auxcfg::Optional<PString> itHhIceTableDbmInstance;
		auxcfg::Required<PString> IDSAddress;
		auxcfg::Optional<PString> IDSInstance;
		auxcfg::Required<PString> entropyAddress;
		auxcfg::Optional<PString> entropyInstance;
		auxcfg::Required<PString> rgMessageRouterAddress;
		auxcfg::Optional<PString> rgMessageRouterInstance;
		auxcfg::Optional<PString> dfpServerAddress;
		auxcfg::Optional<PString> dfpServerInstance;
		auxcfg::Required<PString> tableMonitorServerAddress;
		auxcfg::Optional<PString> tableMonitorServerInstance;
		auxcfg::Optional<PString> vttmServerAddress;
		auxcfg::Optional<PString> vttmServerInstance;
		MOCK_METHOD(void, load, (const auxcfg::IniSection& section, const AuxEslResolver* esl));

	} dynamicSettingsConnInfo;

	struct DynamicConnect
	{		
		auxcfg::Optional<PString> roOlapDbmServerAddress;
		auxcfg::Optional<PString> roOlapDbmServerInstance;
		auxcfg::Optional<PString> vttmServerAddress;
		auxcfg::Optional<PString> vttmServerInstance;

		MOCK_METHOD(void, load, (const AuxEslResolver* esl));
		MOCK_METHOD(void, load, (const auxcfg::IniSection& section));

		MOCK_METHOD(void, log, ());
	} dynamicConnect;

	struct TableDispathRules
	{
		typedef std::function<bool(AuxLobbyTableTypePtr tableType)> Categorizer;
		std::vector<std::string> serverVect;
		std::map<std::string, INT32> serverCapacities;
		std::list<std::pair<Categorizer, INT32> > tableWeights;
		std::list<std::pair<Categorizer, std::vector<std::string> > > rules; //(trigger, server[])[]

		MOCK_METHOD(void, load, (const auxcfg::IniSection& section));
		MOCK_METHOD(INT32, getServerIndex, (const char* serverAddr), (const));
		static const Categorizer& getCategorizer(const char*name);
	}tableDispathRules;

	class SpeedConfig
	{
		map<UINT32, vector<Atf::MsgBodyWithJSONPtr>> speedConfigs;  // key is game type id
	public:
		MOCK_METHOD(void, loadFromIniConfig, (const PIniFile::Section* section));
		MOCK_METHOD(Atf::MsgBodyWithJSONPtr, getSpeedConfig, (UINT32 gameTypeId, BYTE speed));
	}gameSpeedConfigs;

	class SpinDelayConfig
	{
		map<UINT32, vector<aux::SpinDelayTime>> spinDelaySettingsSlots;  // key is site id
		map<UINT32, vector<aux::SpinDelayTime>> spinDelaySettingsLive;  // key is site id
	public:
		MOCK_METHOD(void, load, (const auxcfg::IniSection& section));
		MOCK_METHOD(void, getTableSpinDelaySettings, (UINT64 sites, std::vector<aux::SpinDelayTime>& tableSpinDelaySettings, bool forSlots));
	}spinDelayConfig;

	class DisabledSpinFeaturesConfig
	{
		map<UINT32, aux::DisabledSpinFeatures> disabledSpinFeaturesSettings;  // key is site id
	public:
		MOCK_METHOD(void, load, (const auxcfg::IniSection& section));
		MOCK_METHOD(void, getTableDisabledSpinFeaturesSettings, (UINT64 sites, std::vector<aux::DisabledSpinFeatures>& tableDisabledSpinFeaturesSettings));
	}disabledSpinFeaturesConfig;

	class GermanyBreakConfig
	{
	public:
		aux::BreakConfig breakSetting;
		MOCK_METHOD(void, load, (const auxcfg::IniSection& section));
	}germanyBreakConfig;

	class MaxGamePerPlayerConfig
	{
		int maxSlotNumPerPlayerFT;
		int maxSlotNumPerPlayerPS;
		int maxSlotNumPerPlayerSKY;
		int maxSlotNumPerPlayerSIM;
		int maxSlotNumPerPlayerPSV;
		int maxSlotNumPerPlayerPPB;
		int maxSlotNumPerPlayerFD;

		int maxGameNumPerPlayerFT;
		int maxGameNumPerPlayerPS;
		int maxGameNumPerPlayerSKY;
		int maxGameNumPerPlayerSIM;	
		int maxGameNumPerPlayerPPB;
		int maxGameNumPerPlayerFD;
	public:
		MaxGamePerPlayerConfig(){}
		MOCK_METHOD(void, loadFromIniConfig, (const PIniFile::Section* section));
		MOCK_METHOD(int, getMaxSlotNumberPerPlayer, (UINT32 hostId), (const));
		MOCK_METHOD(int, getMaxGameNumberPerPlayer, (UINT32 hostId), (const));
		MOCK_METHOD(int, getMaxGameNumberPerPlayerBySiteId, (UINT32 siteId), (const));
	}maxGamePerPlayerConfig;
	
	class MaxTotalBetPerHandConfig
	{
		ConfigPerHostAndSiteHelper<PString> maxTotalBetPerHand;

	public:
		MOCK_METHOD(void, loadFromIniConfig, (const PIniFile::Section* dynamicSection));
		MOCK_METHOD(INT32, getMaxTotalBetPerHand, (UINT32 hosts, UINT32 sites, INT32 age, UINT16 gameType), (const));
	} maxTotalBetPerHandConfig;	//CAD-6126

	struct  
	{
		auxcfg::Optional<PString> shadowLobbyAddr;
		auxcfg::Optional<PString> shadowLobbyInst;
	} clientConnInfo; // TODO: is it still necessary, to be reviewed, danielj 5/11/2020

	struct CasinoNames
	{
		PString casinoNameInRealFunMode;
		PString casinoNameInDemoMode;

		CasinoNames(const PString& casinoNameInRealFunMode_, const  PString& casinoNameInDemoMode_)
			: casinoNameInRealFunMode(casinoNameInRealFunMode_), casinoNameInDemoMode(casinoNameInDemoMode_)
		{}
	};

	std::vector<PString> multitableConfig;

	auxcfg::Optional<UINT32> expiredTimeFinishedPromoSec;
	auxcfg::Optional<UINT32> expiredTimeLmhSec;

	auxcfg::Optional<PString> javaHomePath;
	auxcfg::Optional<PString> javaXcBinaryHomePath;
	auxcfg::Optional<PString> javaXcTempPath;
	auxcfg::Optional<PString> slotExtraPlayTimeLimitSetting;
	auxcfg::Optional<PString> liteExtraPlayTimeLimitSetting;

	auxcfg::Optional<INT32> sessionTimeLimitInMinutes;	//PYR-46315
	auxcfg::Optional<INT32> minutesToDeclareSessionStuck; //PYR-46315 sessionTimeLimitInMinutes+minutesToDeclareSessionStuck < 7 days
	auxcfg::Optional<UINT32> gameConnectTimeoutSeconds;	// #PYR-50557 - game attachment timeout (for 3rd party slots) or table login timeout (for Lite)
	auxcfg::Optional<INT32> minIntervalPlayerRequestHandHistoryInSeconds;
	auxcfg::Optional<UINT32> maxTableDeferRemoveTimeSeconds;
	auxcfg::Optional<PString> rcPauseGameForSites;

	vector<PString> userAppDataKeysConfig;

	map<UINT16, CasinoNames> vendorCasinoNames; //vendorId + casinoName
	map<UINT16, UINT32> vendorMsgTimeoutToDeclareSessionStuck;	//PYR-57534, in minutes
	auxcfg::Optional<INT64> maxExposureForSlots; // PYR - 70365
	auxcfg::Optional<PString> ssjTestSetting;  //PYR-94780

	auxcfg::Optional<bool>  useVerifiedforMarketingInSpainPromoBan;  //CAD-39531
	auxcfg::Optional<bool>  useUKGCPromoBan;  //CAST-798

	std::set<UINT16> disabledVendors;

	std::set<UINT16> vendorsWithDemoMode;
	std::set<UINT32> disabledBuyoutFeatureSites;
	bool checkHiddenGameForGameLaunching = false;
	bool autoRemoveHiddenInterruptedGame = false;

	//bool hideInternalIp;// = clientConnInfoSettings != nullptr;
	MOCK_METHOD(void, load, (const AuxEslResolver* esl, const PIniFile& ini, const AuxLobbyStaticConfig& staticConfig));
};

class AuxGameLaunchRestriction
{
public:
	enum RestictionStatus
	{
		//rtsNone,
		rtsApplied,
		rtsReserved,
		rtsPlaying,
		rtsHolding,
	};
	struct GameRestriction
	{
		AuxLobbyTableTypePtr tableType;
		UINT64 tableId;
		UINT64 ufgId;
		RestictionStatus status;

		GameRestriction(const AuxLobbyTableTypePtr tableType_, const UINT64 ufgId_): tableType(tableType_), ufgId(ufgId_), tableId(EMPTY_RESTRICTION_TABLE_ID), status(rtsApplied) {};
	};

private:
	std::list<GameRestriction> restrictions;
public:			
	AuxGameLaunchRestriction() 
	{
		clear();
	}

	MOCK_METHOD(void, clear, ());

	MOCK_METHOD(void, applied, (AuxLobbyTableTypePtr tableType, UINT64 ufgId));
	MOCK_METHOD(void, reserved, (AuxLobbyTableTypePtr tableType, UINT64 tableId, UINT64 ufgId));
	MOCK_METHOD(void, playing, (UINT64 tableId));
	MOCK_METHOD(void, holding, (UINT64 tableId));
	MOCK_METHOD(void, remove, (AuxLobbyTableTypePtr tableType, UINT64 ufgId));
	MOCK_METHOD(void, remove, (UINT64 tableId));
	MOCK_METHOD(void, reconnect, (const PString& auxUserId, AuxLobbyServerObject const *  serverObject));

	MOCK_METHOD(int, getNumOfGameInPlayingOrReserved, (), (const));
	MOCK_METHOD(int, getNumOfSlotTableInPlayingOrReserved, (), (const));

	MOCK_METHOD(const GameRestriction*, getRealSlotRestriction, (), (const));

	MOCK_METHOD(const GameRestriction*, getRestriction, (AuxLobbyTableTypePtr tableType), (const));
	MOCK_METHOD(const GameRestriction*, getRestriction, (UINT64 tableId), (const));
	MOCK_METHOD(const GameRestriction*, getRestrictionByUfg, (UINT64 ufgId), (const));
	MOCK_METHOD(bool, hasPendingRestrictionTable, (), (const));
	MOCK_METHOD(const GameRestriction*, getUgdRestriction, (AuxLobbyTableTypePtr tableType, AuxServer::DataScope dataScope), (const));

	static bool conflict( AuxLobbyTableTypePtr existingTableType, AuxLobbyTableTypePtr tableType );
	static bool needToCheckSlotPerPlayerConfig(AuxLobbyTableTypePtr tableType);
};

struct CodeErrorPair
{
	INT32  errCode;
	std::string err;
};

struct PendingExclusiveRequest
{
	UINT32 msgId;
	PString key;
	UINT32 connId;

	PendingExclusiveRequest(UINT32 msgId_, const PString& key_, UINT32 connId_)
		: msgId(msgId_), key(key_), connId(connId_)
	{}
};

struct AuxLobbyPlayer;
typedef Atf::SharedPointer<AuxLobbyPlayer> AuxLobbyPlayerPtr;

struct AuxPlayerOnTable 
{
	AuxLobbyTableDataPtr table;
	UINT64 loginSessionId; //PYR-120242
	UINT32 siteId;
	UINT32 clientPlatformId;
	UINT32 ugcConnId;	
	PString launchKey;
	Atf::SharedPointer<PendingExclusiveRequest> pendingExclusiveRequest; // PYR-89503 

	MOCK_METHOD(bool, isReadyToRemove, ());

	AuxPlayerOnTable(AuxLobbyPlayerPtr ptr): player_(ptr), loginSessionId(0), gameSessionId_(0), ugcConnId(0), table(nullptr) {}
	MOCK_METHOD(AuxLobbyPlayerPtr, player, ());
	MOCK_METHOD(UINT64, gameSessionId, ());
	MOCK_METHOD(void, setGameSessionId, (UINT64 gsid));
private:
	AuxLobbyPlayerPtr player_;
	UINT64 gameSessionId_; //PYR-75578
};

typedef Atf::SharedPointer<AuxPlayerOnTable> AuxPlayerOnTablePtr;

struct LobbyLoginSession
{
	AuxLobbyPlayerPtr player;

	UINT32 hostId;
	UINT32 siteId;
	UINT32 clientPlatformId;

	UINT64 loginSessionId;
	time_t logoutTime;
	time_t timeToLogout;

//	PString appSessionRef; don't care at the moment
	PString hostTokenHash; //store hash for comparison and reduction of size, SHA256, 64-char Hex 
	PString xcToken; //we need to store this for re-connection

	PString country;
	PString city;
	PString state;	// state of country
	UINT32 imageId;
	PString email;
	bool isEmailInvalidated;
	PString dispName;
	UINT64 appSessionId;
	bool limitedMode;	//PYR-83087

	std::map<UINT32, PString> playerConnections; // connId->token hash
	std::set<UINT32> ugcPlayerConnections;
	PString appSessionRef;

	bool userAgeVerified = false;
	bool userAuthenticated = false;
	CommSrvTime userAccountCreateTime;
	UINT32 flagError = 0;

	UINT32 boUserControlBits = 0; //CAST-13919

	LobbyLoginSession(AuxLobbyPlayerPtr ptr) {
		player = ptr;
		hostId = 0;
		siteId = 0;
		clientPlatformId = 0;
		loginSessionId = 0;
		logoutTime = 0;
		timeToLogout = 0;
		isEmailInvalidated = false;
		appSessionId = 0;
		limitedMode = false;
	}

	MOCK_METHOD((std::map<UINT32, PString>::iterator), findPlayerConnByHostTokenHash, (const PString& hostTokenHash));
};

typedef Atf::SharedPointer<LobbyLoginSession> LobbyLoginSessionPtr;

struct AuxLobbyPlayer
{
	PString auxUserId;
	UINT32 userIntId;
	BYTE hostId;
	INT32 age = 0; //CAST-18876
	INT32 boBetLimit = 0; //FSP-5665

	INT32 numUserAuth;
	bool authInProgress;

	time_t lastRequestHandHistoreyTime;
	std::map<UINT64, AuxPlayerOnTablePtr> tables; // [table id, AuxPlayerOnTable] //PYR-75578
	std::set<UINT64> disconnectedInHandTableIds;
	std::set<UINT64> disconnectedTableIds;
	std::set<UINT64> stuckOrLockTableIds;

	std::map<UINT64, LobbyLoginSessionPtr> loginSessionsById; //[loginSessionId, LobbyLoginSessionPtr]
//	PStringMap<LobbyLoginSessionPtr> loginSessionsByHostToken; //[hostToken, LobbyLoginSessionPtr]
//	PStringMap<LobbyLoginSessionPtr> loginSessionsByXcToken; //[xcToken, LobbyLoginSessionPtr]

	AuxGameLaunchRestriction gameLaunchRestriction;
	AuxPlayerFsbTable fsbTable;

	void dumpTableInfo();

	AuxLobbyPlayer( const char *auxUserId_, 
		UINT32 userIntId_, 
		BYTE hostId_)
	{
		auxUserId = auxUserId_;
		userIntId = userIntId_;
		hostId = hostId_;

		numUserAuth = 0;
		authInProgress = false;
	}

	MOCK_METHOD(bool, hasNoLoginSessions, (), (const));

	MOCK_METHOD(void, addLoginSession, (LobbyLoginSessionPtr session));

	MOCK_METHOD(LobbyLoginSessionPtr, findLoginSessionById, (UINT64 loginSessionId), (const));

	MOCK_METHOD(LobbyLoginSessionPtr, findLoginSessionByHostToken, (const char* hostToken), (const));
	
	MOCK_METHOD(LobbyLoginSessionPtr, findLoginSessionByAppSession, (const char* appSessionRef), (const));

	MOCK_METHOD(void, addTable, ( AuxLobbyTableDataPtr table, UINT64 gameSessionId, UINT64 loginSessionId, UINT32 siteId, UINT32 clientPlatformId ));
	MOCK_METHOD(void, removeTable, ( AuxLobbyTableDataPtr table, bool lockRestriction, bool isFroce));
	MOCK_METHOD(void, unlockTableRestriction, (AuxLobbyTableDataPtr table));

	MOCK_METHOD(bool, inTable, (), (const)); 

	MOCK_METHOD(bool, canBeRemoved, (), (const));

	MOCK_METHOD(void, updateHandStatus, (UINT64 tableId, const aux::P_UpdateHandStatus& hsUpdate));

	MOCK_METHOD(void, addStuckOrLockTable, (UINT64 tableId));

	MOCK_METHOD(void, removeStuckOrLockTable, (UINT64 tableId));

	MOCK_METHOD(bool, isPlayerOnTable, (UINT64 tableId));

	MOCK_METHOD(void, setPlayerOnTable, (UINT64 tableId, AuxLobbyPlayerPtr player));

	MOCK_METHOD(AuxPlayerOnTablePtr, getPlayerOnTable, (UINT64 tableId));

	MOCK_METHOD(void, removePlayerOnTable, (UINT64 tableId));

	MOCK_METHOD(bool, isPlayerSitOnTable, (UINT64 tableId));
};

typedef Atf::SharedPointer<DailyLocalScheduleTimeRanges> DailyLocalScheduleTimeRangesPtr;

struct AuxLobbyUniquePlayer
{
	UINT16 boId;
	UINT32 userIntId;
	PStringMap<AuxLobbyPlayerPtr> players;
	AuxLobbyUniquePlayer(UINT16 boId_, UINT32 userIntId_)
	{
		boId = boId_;
		userIntId = userIntId_;
		players.clear();
	}
};

typedef Atf::SharedPointer<AuxLobbyUniquePlayer> AuxLobbyUniquePlayerPtr;

struct AuxLobbyTableType
{
	UINT32 tableTypeId;
	PString tableTypeName;
	UINT32 gameTypeId;
	BYTE playType;
	BYTE playForFun;
	UINT16 variantType;
	UINT32 minBet;
	UINT32 maxBet;
	PString name;
	PString currency;
	BYTE showCity;
	BYTE maxSeats;
	BYTE maxBettingSpotsPerPlayer;
	BYTE sideBetType;
	BYTE speed;
	bool isObsolete;
	UINT32 hosts;
	UINT64 sites;
	UINT32 minTables;
	UINT32 maxTables;
	vector< aux::P_PNameValue > extraTableTypeProps;
	UINT16 vendorId;
	UINT32 clientPlatforms;
	UINT16 features;
    PString minClientVer;
    PString minOsVer;
    PString minBrowserVer;
	UINT16 technologies;
	UINT32 initMinBuyIn;
	PString noCountries;
	vector<AuxLobbyTableTypePtr> peerTableTypePtrs;
	PString tableTypeRefName;
	PString schedule;
	DailyLocalScheduleTimeRangesPtr scheduleTimeRangersPtr;
	vector<UINT32> jpKeys;
	UINT32 clientPlatformsFSB;
	INT32 defaultBet;
	UINT16 ugdType;
	UINT32 rgRestriction;

	AuxLobbyTableType() 
	{
		tableTypeId = 0;
		tableTypeName.clear();
		gameTypeId = 0;
		minBet = 0;
		maxBet = 0;
		playType = 0;
		playForFun = 0;
		variantType = 0;
		showCity = 0;
		maxSeats = 0;
		maxBettingSpotsPerPlayer = 0;
		sideBetType = 0;
		minTables = 1;
		maxTables = 0;
		speed = 0;
		isObsolete = false;
		extraTableTypeProps.clear();
		vendorId = 0;
		clientPlatforms = 1;
		features = 0;
        minClientVer.clear();
        minOsVer.clear();
        minBrowserVer.clear();
		technologies = 1;
		peerTableTypePtrs.clear();
		tableTypeRefName.clear();
		schedule.clear();
		jpKeys.clear();
		clientPlatformsFSB = 1;
		defaultBet = 0;
		ugdType = AuxServer::UGD_TYPE_NONE;
		hosts = 0;
		sites = 0;
		initMinBuyIn = 0;
		rgRestriction = aux::GAME_LAUNCH_RESTRICTION_TYPE_NO_RESTRICTION;
	}

	AuxLobbyTableType(const aux::TableTypeDef& t);

	MOCK_METHOD(void, setPeerTableTypes, (vector<AuxLobbyTableTypePtr>&& peerTableTypePtrs));

	MOCK_METHOD(const char*, getExtraPropValue, (const char* name));
	MOCK_METHOD(bool, isLiveDealerDirectLaunchTableType, ());
	MOCK_METHOD(bool, isPlaytechNonDirectLaunchGameTableType, ());
	MOCK_METHOD(void, toTableTypeDef, (aux::TableTypeDef& tableTypeDef));
};

enum TableLiveState
{
	TABLE_NOT_STARTED = 0,
	TABLE_IS_RUNNING,
	TABLE_IS_CLOSING,
	TABLE_CLOSED
};

enum TableRunningStateBit
{
	TABLE_BIT_LOCK = 1,
	TABLE_BIT_STUCK = 2
};

struct PendingTableMsg 
{
	UINT32 msgId;
	CommMsgBody msgBody;

	PendingTableMsg(UINT32 msgId_, const CommMsgBody& msgBody_)
	{
		msgId = msgId_;
		msgBody.copyFrom(msgBody_);
	}
};

struct AuxLobbyTableData
{
	AuxLobbyServerObject* obj;

	UINT64 tableId;
	PString tableConnTag;
	PString tableName;
	PString serverAddr;
	PString serverIP;
	PString serverObject;
	UINT32	dbmId;
	UINT32 tableServerConnId;
	BYTE liveState;
	bool isRestorationMode;
	bool isDirty;
	bool hidden;
	bool createdForRestoration;
	bool isBusy;
	UINT16 runningState;
	bool hasBeenUsed;
	CommSrvTime createTime;
	AuxLobbyTableTypePtr tableType;
	AuxPlayerOnTablePtr users[ HARDEST_MAX_PLAYERS ];
	bool seatConfirmed[ HARDEST_MAX_PLAYERS ];
	time_t seatReservFailureTime;   // don't try to reserve a seat when this field is not reset
	BYTE dealingState;
	// table statistics data
	UINT32 stats_avgBet;
	UINT32 stats_numRounds;
	BYTE stats_activeSeats;
	UINT32 fsbId;
	//do we need rollType here? by now, tableserver will get it from balance update;
	
	AuxPlayerOnTablePtr restrictionLockedPlayer; // PYR-47497 only apply to single user table so far.
	std::list<PString> restrictedPlayers;

	PString stuckUserId;	// PYR-57534 - single user table only
	
	bool hasBeenUsedByPlayer;

	struct SeatReservInfo
	{
		INT8 seat;  // -1 when seat reservation starts from Lobby, valid seat number when seat reservation starts from Table
		UINT32 reservKey;  // non-zero when seat reservation starts from Lobby, zero when seat reservation starts from Table
		time_t reservTime; // time when this object is created
		bool claimed;

		SeatReservInfo(UINT32 key) 
			: seat(-1), reservKey(key), reservTime(plib_time(0)) , claimed(false)
		{
		}

		SeatReservInfo(INT8 seat, UINT32 key) 
			: seat(seat), reservKey(key), reservTime(plib_time(0)) , claimed(false)
		{
		}
	};
	list<SeatReservInfo> reservedSeats;

	list<PendingTableMsg> pendingPostMessages;

	AuxLobbyTableData(AuxLobbyServerObject* obj) : obj(obj)
	{
		tableId = 0;
		dbmId = 0;
		tableServerConnId = 0;
		liveState = TABLE_NOT_STARTED;
		isRestorationMode = false;
		isDirty = false;
		hidden = false;
		createdForRestoration = false;
		hasBeenUsed = false;
		isBusy = false;
		runningState = 0;
		seatReservFailureTime = 0;
		stats_avgBet = 0;
		stats_numRounds = 0;
		stats_activeSeats = 0;
		dealingState = aux::DEALING_NORMAL;
		for (int i = 0; i < HARDEST_MAX_PLAYERS; ++i) 
		{
			users[i].assign(nullptr);
			seatConfirmed[i] = false;
		}
		fsbId = 0;
		hasBeenUsedByPlayer = false;
	}
	AuxLobbyTableData(AuxLobbyServerObject* obj, const aux::TableDef& t, AuxLobbyTableTypePtr type) : obj(obj)
	{
		tableId = t.tableId;
		tableName = t.tableName;
		dbmId = 0;
		tableServerConnId = 0;
		liveState = TABLE_NOT_STARTED;
		isRestorationMode = false;
		isDirty = false;
		hidden = false;
		createdForRestoration = false;
		hasBeenUsed = false;
		isBusy = false;
		runningState = 0;
		tableType = type;
		seatReservFailureTime = 0;
		stats_avgBet = 0;
		stats_numRounds = 0;
		stats_activeSeats = 0;
		dealingState = aux::DEALING_NORMAL;
		for (int i = 0; i < HARDEST_MAX_PLAYERS; ++i) 
		{
			users[i].assign(nullptr);
			seatConfirmed[i] = false;
		}
		fsbId = 0;
	//	ugdType = AuxServer::UGD_TYPE_NONE;
		hasBeenUsedByPlayer = false;
	}

	virtual ~AuxLobbyTableData();

	MOCK_METHOD(bool, needToPublish, (), (const));

	MOCK_METHOD(UINT32, getTableTypeId, (), (const));
	MOCK_METHOD(UINT32, getGameTypeId, (), (const));
	MOCK_METHOD(BYTE, getPlayType, (), (const));
	MOCK_METHOD(BYTE, getPlayForFun, (), (const));
	MOCK_METHOD(BYTE, getSpeed, (), (const));
	MOCK_METHOD(BYTE, getNumOfSeats, (), (const));
	MOCK_METHOD(UINT16, getVendorId, (), (const));
	MOCK_METHOD(UINT16, getTechnologies, (), (const));

	MOCK_METHOD(UINT16, getVariantType, (), (const));

	MOCK_METHOD(aux::RgSettings, getRgSettings, (), (const));

	MOCK_METHOD(void, created, (UINT32 connId));
	MOCK_METHOD(bool, isLive, (), (const));
	MOCK_METHOD(void, setTableLock, ());
	MOCK_METHOD(void, setTableUnlock, ());
	MOCK_METHOD(void, setTableLockAndStuck, (const char* rgUserId));
	MOCK_METHOD(bool, isTableLocked, (), (const));
	MOCK_METHOD(bool, isTableStuck, (), (const));
	MOCK_METHOD(bool, isTableLockedOrStuck, (), (const));
	MOCK_METHOD(bool, isTableNormal, (), (const));
	MOCK_METHOD(bool, isUserStuck, (const PString& rgUserId));
	MOCK_METHOD(void, reserveSeat, (UINT32 key));
	MOCK_METHOD(void, reserveSeat, (INT8 seat, UINT32 key));
	MOCK_METHOD(void, cancelReservedSeat, (UINT32 key));
	MOCK_METHOD(void, claimReservedSeat, (UINT32 key));
	MOCK_METHOD(void, cancelReservedSeat, (INT8 seat, UINT32 key));
	MOCK_METHOD(void, claimReservedSeat, (INT8 seat, UINT32 key));
	MOCK_METHOD(void, updateDealingState, (BYTE state));
	MOCK_METHOD(void, removeObsoleteSeatReservations, (time_t now));
	MOCK_METHOD(void, setFsbId, (UINT32 fsbId_));
	MOCK_METHOD(void, setRestorationMode, (bool inPlayAloneMode, const PString& userId, INT8 seat, UINT32 reservKey));

	MOCK_METHOD(bool, isOverLongUnUsedSPTable, (const time_t& now), (const));

	MOCK_METHOD(bool, isEmpty, (), (const));

	MOCK_METHOD(bool, notOccupied, (), (const));

	MOCK_METHOD(bool, hasEmptySeat, (), (const));

	MOCK_METHOD(BYTE, getNumOfPlayers, (), (const));

	MOCK_METHOD(BYTE, getNumOfConfirmedSeatedPlayers, (), (const));

	MOCK_METHOD(vector<INT8>, getSeatsOccupied, (), (const));

	MOCK_METHOD(bool, isUsedSPTable, (), (const));

	MOCK_METHOD(void, removeUser, (INT8 seat, bool lockRestriction));

	MOCK_METHOD(void, unLockRestrictionLockedPlayer, ());

	MOCK_METHOD(bool, hasRestrictionLockedPlayer, (const PString& auxUserId));

	MOCK_METHOD(void, addRestrictedPlayer, (const PString& auxUserId));

	MOCK_METHOD(void, removeRestrictedPlayer, (const PString& auxUserId));

	MOCK_METHOD(const AuxPlayerOnTable*, getPlayerByGamesession, (UINT64 gamesessionId));

public:
	// Private -- this really should be placed in a common utility file
	static PString getValueFromProps(const char *name, const vector< aux::P_PNameValue >& props, const char* defaultValue = "")
	{
		for (auto prop : props)
		{
			if (prop.name.equals(name))
			{
				return prop.value;
			}
		}
		return defaultValue;
	}
	static UINT32 getUintValueFromProps(const char *name, const  vector< aux::P_PNameValue >& props, UINT32 defaultValue)
	{
		UINT32 retValue = defaultValue;
		PString valueString = getValueFromProps(name, props);
		if(valueString.length() && isInteger(valueString.c_str()))
		{
			retValue = p_atoi64(valueString.c_str());
		}

		return retValue;
	}

	static UINT64 getUint64ValueFromProps(const char *name, const  vector< aux::P_PNameValue >& props, UINT64 defaultValue)
	{
		UINT64 retValue = defaultValue;
		PString valueString = getValueFromProps(name, props);
		if(valueString.length() && isInteger(valueString.c_str()))
		{
			retValue = p_atoi64(valueString.c_str());
		}

		return retValue;
	}

	MOCK_METHOD(bool, isSlotsGame, (), (const));
};

class LobbyVendorStatusStatsInfo
{
	map<UINT16, BYTE> vendorsStatus; // vendorId is key
public:
	bool isDirty;

	LobbyVendorStatusStatsInfo()
	{
		isDirty = false;
	}
	MOCK_METHOD(void, setVendorsStatus, ((const map<UINT16, BYTE>&) vendorsStatus_));
	MOCK_METHOD(void, convertToShadowVendorStatus, (ShadowLobbyC::Client::VendorStatusInfo& globalVendorStatus));
};

class GlobalStatistics
{
	struct HostStatistics
	{
		struct Data
		{
			UINT32 totalPayFunPlayers;
			UINT32 totalRealMoneyPlayers;
		};
		BYTE hostId;
		map<UINT32, Data> sitesData;  // siteId is key
	};
	vector<HostStatistics> vHostStatistics;
public:
	bool isDirty;

	GlobalStatistics()
	{
		isDirty = false;
	}
	MOCK_METHOD(void, seatAdded, (BYTE hostId, UINT32 siteId, AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, seatRemoved, (BYTE hostId, UINT32 siteId, AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, convertToShadowGlobalInfo, (ShadowLobbyC::Client::GlobalShadowInfo& globalShadowInfo));
};


class LobbyPlayerOrCipwaConnBase : public AuxPlayerOrCipwaConnection   // peer connection is not G connection
{
protected:
	AuxLobbyServerObject* obj;
public:
	LobbyPlayerOrCipwaConnBase( AuxLobbyServerObject* obj_, bool fromWeb_ = true );
	MOCK_METHOD(const char *, getUser, ()); 
	MOCK_METHOD(UINT64, getTableId, ());
	MOCK_METHOD(void, setTableId, (UINT64 tid));
public:
	LobbyLoginSessionPtr playerLoginSession;
	const bool fromWeb;
private:
	UINT64 tableId;
};

class LobbyServerConnBase : public AuxCommServerConnection   // peer connection is not G connection
{
protected:
	AuxLobbyServerObject* obj;
public:
	LobbyServerConnBase( AuxLobbyServerObject* obj_ );
};

class LobbyServerConnBasePeerG : public AuxCommServerConnection  // peer connection is a G connection
{
protected:
	AuxLobbyServerObject* obj;
public:
	LobbyServerConnBasePeerG( AuxLobbyServerObject* obj_ );
};

class LobbyServerTableGConn : public Atf::AtfServerReverseGConnection
{
	Lobby::Table::TableConnectInfo* pTbInfo;
	AuxLobbyTableDataPtr table;
	AuxLobbyServerObject* obj;
	UINT64 tableId;
public:
	LobbyServerTableGConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") 
		: AtfServerReverseGConnection(true), 
		obj(obj_), 
		tableId(0),
		pTbInfo(nullptr)
	{ setTraceMarker(connTraceMarker); }
protected:
	~LobbyServerTableGConn() {}
public:
	MOCK_METHOD(void, processSGMessage, ( UINT32 msgId, const CommMsgBody& body, Atf::AtfServerGConnAsyncCall* call, UINT32 serverReqId ), (override));
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, closedOrDisconnected, ( int errCode, const char* errMsg ), (override));
	MOCK_METHOD(UINT64, getTableId, (), (const));
	MOCK_METHOD(UINT32, dbmId, (), (const));
	MOCK_METHOD(const char*, tableName, (), (const));
	MOCK_METHOD(void, setTable, (AuxLobbyTableDataPtr tbl));
	MOCK_METHOD(void, getUserAuth, ( const char* guardType, const char* id, CommMsgBody& clientExtra, CommMsgBody& request ));
};

class AuxLobbyServerTableGConnFactory : public Atf::AtfServerReverseGConnectionFactory
{
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerTableGConnFactory( CommServerGuardFactory& guardFactory )
		: AtfServerReverseGConnectionFactory( guardFactory )
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(Atf::AtfServerReverseGConnection*, createServerGConnection, (), (override));
};

class LobbyServerPlayerConn : public LobbyPlayerOrCipwaConnBase
{
	AuxLobbyServerObject* obj;
	const bool fromCDL;
public:
	LobbyServerPlayerConn(AuxLobbyServerObject* obj_, bool fromWeb_, bool fromCDL_, const char *connTraceMarker = "");
	~LobbyServerPlayerConn();
	MOCK_METHOD(void, processMessage, ( UINT32 msgId, const CommMsgBody& body ), (override));
	MOCK_METHOD(void, getUserAuth, ( const char* guardType, const char* user_, CommMsgBody& clientExtra, CommMsgBody& request ), (override));
	MOCK_METHOD(void, closedOrDisconnected, ( int errCode, const char* errMsg ), (override));
};

class AuxLobbyServerPlayerConnFactory : public AuxPlayerOrCipwaConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
	const bool fromWeb;
	const bool fromCDL;
public:
	AuxLobbyServerPlayerConnFactory( CommServerGuardFactory& guardFactory, bool fromWeb_, bool fromCDL_ )
		: AuxPlayerOrCipwaConnectionFactory( guardFactory ), obj( 0 ), fromWeb(fromWeb_), fromCDL(fromCDL_)
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(AuxPlayerOrCipwaConnection*, createConnection, (), (override));
};

class LobbyServerShadowConn : public LobbyServerConnBasePeerG
{
public:
	LobbyServerShadowConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") : LobbyServerConnBasePeerG(obj_) { setTraceMarker(connTraceMarker); }
	~LobbyServerShadowConn()	{ }
	MOCK_METHOD(void, processMessage, ( UINT32 msgId, const CommMsgBody& body ), (override));
	MOCK_METHOD(void, closedOrDisconnected, ( int errCode, const char* errMsg ), (override));
};

class AuxLobbyServerShadowConnFactory : public CommServerConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerShadowConnFactory( CommServerGuardFactory& guardFactory )
		: CommServerConnectionFactory( guardFactory ), obj( 0 )
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

// This is a connection shared by all web sessions
class LobbyServerWebGWConn : public LobbyServerConnBasePeerG
{
public:
	LobbyServerWebGWConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") : LobbyServerConnBasePeerG(obj_) { setTraceMarker(connTraceMarker); }
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
	MOCK_METHOD(void, processMessage, ( UINT32 msgId, const CommMsgBody& body ), (override));
};

class AuxLobbyServerWebGWConnFactory : public CommServerConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerWebGWConnFactory( CommServerGuardFactory& guardFactory )
		: CommServerConnectionFactory( guardFactory ), obj( 0 )
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

class LobbyServerDeliveryConn : public LobbyServerConnBasePeerG
{
public:
	LobbyServerDeliveryConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") : LobbyServerConnBasePeerG(obj_) { setTraceMarker(connTraceMarker); }
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
	MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
};

class AuxLobbyServerDeliveryConnFactory : public CommServerConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerDeliveryConnFactory(CommServerGuardFactory& guardFactory)
		: CommServerConnectionFactory(guardFactory), obj(0)
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

//PYR-50101, connection from DGE entropy server
class LobbyServerDgeConn : public LobbyServerConnBasePeerG
{
public:
	LobbyServerDgeConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") : LobbyServerConnBasePeerG(obj_) { setTraceMarker(connTraceMarker); }
	~LobbyServerDgeConn()	{ }
	MOCK_METHOD(void, processMessage, ( UINT32 msgId, const CommMsgBody& body ), (override));
};

class AuxLobbyServerDgeConnFactory : public CommServerConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerDgeConnFactory( CommServerGuardFactory& guardFactory )
		: CommServerConnectionFactory( guardFactory ), obj( 0 )
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

class LobbyServerAbeConn : public LobbyServerConnBasePeerG
{
protected:
	AuxLobbyServerObject* lobbyServerObj;
public:
	LobbyServerAbeConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") : LobbyServerConnBasePeerG(obj_), lobbyServerObj(obj_){ setTraceMarker(connTraceMarker); }
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
	~LobbyServerAbeConn() { }
};

class AuxLobbyServerAbeConnFactory : public CommServerConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerAbeConnFactory(CommServerGuardFactory& guardFactory)
		: CommServerConnectionFactory(guardFactory), obj(0)
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection,(), (override));
};

class AuxHandHistoryConn : public AuxCommClientGConnection
{
public:
	AuxHandHistoryConn(AuxLobbyServerObject * obj, CommClientGuardFactory& guardFactory);
	~AuxHandHistoryConn() { }
	MOCK_METHOD(void, processGMessage, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call), (override));
private:
	AuxLobbyServerObject * obj;
};

//PYR-56430, connection from config query
/*class LobbyServerConfigConn : public LobbyServerConnBase
{
public:
	LobbyServerConfigConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") : LobbyServerConnBase(obj_) { setTraceMarker(connTraceMarker); }
	~LobbyServerConfigConn()	{ }
	void processMessage( UINT32 msgId, const CommMsgBody& body ) override;
};*/

// PYR-75562 Casino Races
class AuxRaceServerConn : public AuxCommClientGConnection
{
public:
	AuxRaceServerConn(AuxLobbyServerObject * obj, CommClientGuardFactory& guardFactory);
	~AuxRaceServerConn() { }
	MOCK_METHOD(void, onAuxConnected, (), (override));
	MOCK_METHOD(void, processGMessage, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call), (override));
private:
	AuxLobbyServerObject * obj;
};

/*class AuxLobbyServerConfigConnFactory : public CommServerConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerConfigConnFactory( CommServerGuardFactory& guardFactory )
		: CommServerConnectionFactory( guardFactory ), obj( 0 )
	{
	}
	void init(AuxLobbyServerObject* obj_)
	{
		obj = obj_;
	}
	CommServerConnection* createConnection()  override
	{		
		return new LobbyServerConfigConn( obj, "cipwa" );
	}
};*/

class LobbyServerGGNDataFeedConn : public LobbyServerConnBasePeerG
{
public:
	LobbyServerGGNDataFeedConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "") : LobbyServerConnBasePeerG(obj_) { setTraceMarker(connTraceMarker); }
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
	MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
};


class AuxLobbyServerGGNDataFeedConnFactory : public CommServerConnectionFactory
{
protected:
	AuxLobbyServerObject* obj;
public:
	AuxLobbyServerGGNDataFeedConnFactory(CommServerGuardFactory& guardFactory)
		: CommServerConnectionFactory(guardFactory), obj(0)
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

class TableNamePool
{
public:
	enum CategoryId
	{
		DEFAULT = 0,
		PS_SPAIN = 1,
	};
private:
	struct CategoryNames
	{
		std::map<UINT32, PString> names;
		std::map<UINT32, PString>::iterator currentIndex;
	};
public:
	MOCK_METHOD(void, addName, (UINT16 categoryId, PString name, UINT32 prioirty));
	MOCK_METHOD(void, clearNames, ());
	MOCK_METHOD(void, getName, (AuxLobbyTableDataPtr table, PString &name));
	MOCK_METHOD(void, returnName, (BYTE playType, const char* name));
	MOCK_METHOD(void, addNameInUse, (PString& name));
public:
	TableNamePool();
	~TableNamePool();
private:	
	std::map<UINT16, CategoryNames> categoryNames;
	std::map<PString, UINT32, PStringCmp> namesInUse;
};

#define RULE_TARGET_CASINO 1
#define RULE_TARGET_HOST 2
#define RULE_TARGET_SITE 3
#define RULE_TARGET_VENDOR 4
#define RULE_TARGET_GAME_TYPE 5
#define RULE_TARGET_VARIANT_TYPE 6
#define RULE_TARGET_MONEY_TYPE 7

#define DISABLERULE_IT_TYPE vector<GameManagementData::DisableRule>::iterator
#define EXCEPTION_IT_TYPE vector<GameManagementData::Exception>::iterator
#define DISABLETABLESTATUS_IT_TYPE std::set<GameManagementData::DisableRule::DisableTableStatus>::iterator

template<typename T, typename K> bool checkScopeByBitMask(T values, K mask_)
{
	if(values.size() == 0) {
		return true;
	} else {
		for(auto& value : values) {
			K itBit = 1;
			itBit = itBit << ( value -1 );
			if ((itBit & mask_) != 0) {
				return true;
			}
		}
	}
	return false;
}

typedef std::set<UINT32> ScopeValue;

struct GameManagementData
{
	GameManagementData() : updatedTime(0), processingFlag(false)  {};	

	struct DisableRule
	{
		UINT32 id;
		BYTE target;	// 1: CASINO 2:HOST 3:SITE 4:VENDOR 5:GAME_TYPE 6:VARIANT_TYPE 7: MONEY_TYPE 0: MULTI_TARGET
		
		ScopeValue walletScope;
		ScopeValue hostScope;
		ScopeValue siteScope;
		ScopeValue vendorScope;
		ScopeValue gameTypeScope;
		ScopeValue variantTypeScope;
		ScopeValue tabletypeScope;
		ScopeValue moneyTypeScope;

		BYTE status;

		enum DisableTableStatusType { DISABLE_REQUEST = 0, DISABLED = 1 };
		struct DisableTableStatus
		{
			UINT64 tableId;
			DisableTableStatusType status;

			DisableTableStatus(UINT64 tableId_) : tableId(tableId_), status(DISABLE_REQUEST) {}
			DisableTableStatus(UINT64 tableId_, DisableTableStatusType status_): tableId(tableId_), status(status_) {}
			
			bool operator<(const DisableTableStatus status_) const {
				if (tableId < status_.tableId) return true;
				if (tableId > status_.tableId) return false;
				return status < status_.status;
			}
		};

		std::set<DisableTableStatus> disabledTablesByRule;

		DISABLETABLESTATUS_IT_TYPE findDisableTableByTableId(UINT64 tableId_);
	};

	struct Exception
	{
		UINT32 id;
		BYTE type;		//  1: ip. 2. aux user id.
		PString value;
	};

	vector<DisableRule> disableRules; // works on table
	vector<Exception> exceptions; // works on client

	UINT64 updatedTime;
	bool processingFlag;

	//void processTableDied(AuxLobbyTableDataPtr table_);
	//bool addDisableTable(AuxLobbyTableDataPtr table_);
	MOCK_METHOD(bool, needToDisable, (AuxLobbyTableDataPtr table_), (const));
	MOCK_METHOD(bool, needToDisable, (AuxLobbyTableDataPtr table_, set<UINT32>& ruleIds_), (const));

	MOCK_METHOD(bool, needToDisable, (AuxLobbyTableTypePtr tableType_), (const));
	MOCK_METHOD(bool, needToDisable, (AuxLobbyTableTypePtr tableType_, AuxLobbyPlayerPtr player_), (const));
	MOCK_METHOD(bool, needToDisable, (AuxLobbyTableTypePtr tableType_, AuxLobbyPlayerPtr player_, set<UINT32>* ruleIds_), (const));

	MOCK_METHOD(bool, needToDisable, ( UINT16 hostId_, UINT64 siteId_, const PString& ip, const PString& auxUserId), (const));

	MOCK_METHOD(void, init, (const vector< aux::GameManagementRule >& rules, const vector< aux::GameManagementException >& exceptions));
	MOCK_METHOD(void, refresh, (const vector< aux::GameManagementRule>& updatedRules, const vector< aux::GameManagementException>& exceptions, const vector< aux::GameManagementRule>& addedRules, bool bInit));

	MOCK_METHOD(bool, waitToApply, (UINT64 minDelayInsec), (const));
	MOCK_METHOD(bool, waitToApply, (), (const));
	MOCK_METHOD(void, setObj, (AuxLobbyServerObject* obj_));

	MOCK_METHOD(const DISABLERULE_IT_TYPE, getDisableRuleByRuleId, (UINT32 id_));
	MOCK_METHOD(const EXCEPTION_IT_TYPE, getExceptionByExceptionId, (UINT32 id_));
	MOCK_METHOD(bool, isInDisableList, (UINT64 tableId_));
	MOCK_METHOD(bool, isInDisableList, (UINT64 tableId_, DisableRule::DisableTableStatusType& type));

	MOCK_METHOD(bool, inProcessing, (), (const));
	MOCK_METHOD(void, startProcess, ());
	MOCK_METHOD(void, completeProcess, ());
private:
	MOCK_METHOD(bool, checkScopeByValue, (ScopeValue sv, UINT32 v_), (const));

	MOCK_METHOD(void, insertGameManagementRule, (const aux::GameManagementRule& rule_, bool bInit));
	MOCK_METHOD(void, insertGameManagementException, (const aux::GameManagementException& exception_, bool bInit));

	MOCK_METHOD(void, parseRuleData, (const PString& scopeString, ScopeValue& scopeValue));

	MOCK_METHOD(bool, isInExceptionList, (AuxLobbyPlayerPtr player_), (const));
	MOCK_METHOD(bool, isInExceptionList, (const PString& ip, const PString& auxUserId), (const));

	AuxLobbyServerObject* obj;
};

struct HostSystemInfo
{
	BYTE status;

	//extraInfo contains following fields when status == 2 || status == 3
	bool timeSpecified;
	UINT64 beginTime;    //maintenance begin time in UTC
	UINT16 durationInMins;     //maintenance duration in Minutes
	aux::BackofficeType boId;

	HostSystemInfo() : status(0), timeSpecified(false), beginTime(0), durationInMins(0) {}
	HostSystemInfo(const reef::objs::HostSystemStatus& s);
	MOCK_METHOD(void, convertToReefObject, (reef::objs::HostSystemStatus& s));
	
	MOCK_METHOD(void, convertToShadowSystemInfo, (ShadowLobbyC::Client::HostSystemInfo& hostSystemInfo), (const));

	MOCK_METHOD(void, onSystemShutdown, ());

	MOCK_METHOD(void, onHostDisabled, ());

	map<UINT32, std::set<UINT32>> listOfDisableSiteIds;

	MOCK_METHOD(void, onActiveSiteDisableRule, (UINT32 ruleId, set<UINT32> siteIds));

	MOCK_METHOD(void, onInactiveSiteDisableRule, (UINT32 ruleId));
};

class AuxGameRestriction
{
public:
	typedef std::tuple<INT16&, PString&, Atf::MsgBodyWithJSON&> CheckResult;
	typedef INT16 (AuxGameRestriction::*CheckFn)(CheckResult&) const;

	AuxGameRestriction(const AuxLobbyServerObject* serverObject_, LobbyLoginSessionPtr session_, AuxLobbyTableTypePtr tableType_, UINT64 raceId_ = 0)
		:serverObject(serverObject_), session(session_), tableType(tableType_), raceId(raceId_)
	{
	}

	MOCK_METHOD(INT16, launchingFsbGameCheckUfgs, (const vector<Dbm::dbm::InterruptedGameClientDef>& ufgs, CheckResult& result), (const));
	MOCK_METHOD(INT16, launchingGameCheckUfgs, (const vector<Dbm::dbm::InterruptedGameClientDef>& ufgs, CheckResult& result), (const));

	template<int N>
	INT16 batchCheck(const CheckFn (&checkFns)[N], CheckResult& result) const
	{
		if(std::get<0>(result))
			return std::get<0>(result);

		for(int i = 0; i<N; ++i)
		{
			if( (this->*checkFns[i])(result) )
				break;
		}
		return std::get<0>(result);
	}

	MOCK_METHOD(INT16, checkCountries, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkClientPlatformCompatibility, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkHostCompatibility, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkSiteCompatibility, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkTableEnable, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkObsolete, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkSchedule, (CheckResult& result), (const));
	INT16 checkMaxGameCount(CheckResult& result) const; // Being tested, no need to mock here
	MOCK_METHOD(INT16, checkFsbMaxGameCount, (CheckResult& result), (const));

	MOCK_METHOD(INT16, checkVendorReady, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkSlotsConflict, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkSlotsPerPlayer, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkFsbSlotsPerPlayer, (CheckResult& result), (const));

	MOCK_METHOD(INT16, checkFsbPlatform, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkUgdConflict, (CheckResult& result), (const));
	MOCK_METHOD(INT16, checkFsbConflict, (CheckResult& result), (const));
private:
	MOCK_METHOD(INT16, composeUgdConflict, (CheckResult& result, AuxLobbyPlayerPtr mplayer, UINT32 tableTypeId, UINT64 tableId, bool isPlayingTable), (const));
	MOCK_METHOD(INT16, composeFsbUfgConflict, (const Dbm::dbm::InterruptedGameClientDef& ufg, CheckResult& result), (const));
	MOCK_METHOD(INT16, composeUfgConflict, (const Dbm::dbm::InterruptedGameClientDef& ufg, CheckResult& result), (const));
	INT16 setResult(CheckResult& result, INT16 errCode, const char* errStr = "") const
	{
		std::get<0>(result) = errCode;
		std::get<1>(result) = errStr;
		return errCode;
	}

private:
	const AuxLobbyServerObject* serverObject;

	LobbyLoginSessionPtr session;
	AuxLobbyTableTypePtr tableType;
	UINT64 raceId;
};


//PYR-57534
struct StuckTableData
{
	bool notifyState;
	UINT32 gameType;
	UINT16 variantType;

	StuckTableData() : notifyState(false), gameType(0), variantType(0) 
	{}
};
struct UserStuckTables
{
	std::map<UINT64, StuckTableData> stuckTables;
};

struct GameSetupData
{
	virtual ~GameSetupData() {}
};

struct PtldSetupData : public GameSetupData
{
	const UINT32 tableTypeId; //the table type id which matches the tableProperties
	const Atf::MsgBodyWithJSON tableProperties;

	PtldSetupData(UINT32 tableTypeId_, const Atf::MsgBodyWithJSON& tableProperties_)
		: tableTypeId(tableTypeId_), tableProperties(tableProperties_)
	{}
};

struct RaceSetupData : public GameSetupData
{
	const UINT64 raceId;
	const std::shared_ptr<aux::GameVariantCompact> raceGameData;	
	RaceSetupData(UINT64 raceId, std::shared_ptr<aux::GameVariantCompact> raceGameData = nullptr) : raceId(raceId), raceGameData(raceGameData) {}
};

struct ExclusiveFsbSetupData : public GameSetupData
{
	const UINT32 tableTypeId;
	const UINT32 fsbId;
	ExclusiveFsbSetupData(UINT32 tableTypeId_, UINT32 fsbId_) : tableTypeId(tableTypeId_), fsbId(fsbId_) {}
};

//PYR-55812
struct GameSetup
{
	UINT8 type; //aux::NewGameSetupType
	bool inUse;
	UINT64 tableId; //the table launched with this setup
	time_t timeSetup;
	PString userId;

	GameSetupData *data;

	GameSetup(UINT8 type_, const PString& userId_, GameSetupData* data_, UINT64 tableId_ = 0, bool inUse_ = false)
	{
		type = type_;
		userId = userId_;
		inUse = inUse_;
		data = data_;
		tableId = tableId_;

		timeSetup = plib_time(0);

		PASSERT(data);
	}

	~GameSetup()
	{
		debugPLog("[Debug ] GameSetup data clean up");
		delete data;
	}
};

typedef PStringMap<Atf::SharedPointer<GameSetup>> GameSetupMap;

enum HHErrorType
{
	hhErrorNoError,
	hhErrorNonPSUser,
	hhErrorNoSuchUser,
	hhErrorEmptyEmail,
	hhErrorInvalidate,
	hhErrorLimitReached,
	hhErrorServerNotSupport,
};

class AuxLobbyServerUgcConn : public LobbyPlayerOrCipwaConnBase
{
	friend class AuxLobbyServerObject;

private:
	PString guardType;
public:
	AuxLobbyServerUgcConn(AuxLobbyServerObject* obj_, const char *connTraceMarker = "");
	~AuxLobbyServerUgcConn();

	MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
	MOCK_METHOD(void, getUserAuth, (const char* guardType_, const char* user_, CommMsgBody& clientExtra, CommMsgBody& request), (override));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
	MOCK_METHOD(void, connected, (), (override));
	MOCK_METHOD(void, onUgcRemoved, ());
};

class AuxLobbyServerUgcConnFactory : public AuxPlayerOrCipwaConnectionFactory
{
public:
	AuxLobbyServerObject * obj;
public:
	AuxLobbyServerUgcConnFactory(CommServerGuardFactory& guardFactory)
		: AuxPlayerOrCipwaConnectionFactory(guardFactory), obj(0)
	{
	}
	MOCK_METHOD(void, init, (AuxLobbyServerObject* obj_));
public:
	MOCK_METHOD(AuxPlayerOrCipwaConnection *, createConnection, (), (override));
};

class TablePlacementMng
{
public:
	struct LoadInfo
	{
		float capacity=1;
		INT32 totalTableWeight=0;
		MOCK_METHOD(INT32, adjust, (INT32 weight));
		MOCK_METHOD(float, load, (), (const));
	};
	std::map<std::string, LoadInfo> loadInfos;
	const AuxLobbyDynamicConfig::TableDispathRules* dispatchRules;

	MOCK_METHOD(void, setRules, (const AuxLobbyDynamicConfig::TableDispathRules& dispatchRules_));

	MOCK_METHOD(void, resetLoad, ());
	MOCK_METHOD((std::pair<const char*, INT32>), allocLoad, (AuxLobbyTableTypePtr tableType));
	MOCK_METHOD((std::pair<const char*, INT32>), allocLoad, (AuxLobbyTableTypePtr tableType, UINT32 tableId));
	MOCK_METHOD(INT32, claimLoad, (const char* placementName, INT32 weight));
	MOCK_METHOD(INT32, releaseLoad, (const char* placementName, INT32 weight));
};


struct LDTTWithPeersInfoByVendor
{
	bool changed;
	map<UINT32, AuxLobbyTableTypePtr> ldTableTypes;
};

class AuxLobbyServerObject : public AuxCommServerObject 
{
	friend class LobbyPerformanceCounter;
	friend struct CasinoMSPromotion;
	friend class AuxGameRestriction;
	friend class AuxGameLaunchRestriction;
	friend class AuxPlayerFsbTable;
	friend class LobbyServerWebGWConn;
	friend class AuxLobbyServerUgcConn;
	friend class AuxLobbyUtil;
	friend class LobbyServerTableGConn;
	friend class LobbyServerPlayerConn;
	friend struct AuxLobbyUniquePlayer;
	friend struct AuxLobbyTableData;

	enum LobbyInitPhase
	{
		INIT_PHASE_ZERO,
		INIT_PHASE_CHECKING_RECOVERY,
		INIT_PHASE_TABLE_RECOVERY,		
		INIT_PHASE_END_NORMAL,
		INIT_PHASE_END_WITH_RECOVERY
	};

private:
	LobbyInitPhase initPhase;
	time_t lastTableRecoverTime;

	// static CommServerNullGuardFactory nullGuardFactoryS;
	// static CommClientNullGuardFactory nullGuardFactoryC;
	// static CommServerHostAuthGuardFactory hostAuthGuardFactory;
	// static CommServerNullWithInfoGuardFactory nullWithInfoGuardFactoryS;
	// static CommServerAuxTokenGuardFactory guardFactoryAuxToken;	

	// AuxLobbyServerTableGConnFactory tableConnFactory;
	// AuxLobbyServerPlayerConnFactory playerConnFactory;
	// AuxLobbyServerPlayerConnFactory cdlAuthPlayerConnFactory;
	// AuxLobbyServerPlayerConnFactory webPlayerConnFactory;
	// AuxLobbyServerShadowConnFactory shadowConnFactory;
	// AuxLobbyServerWebGWConnFactory webGWConnFactory;		// From Web Gateway and shared by all web sessions
	// AuxLobbyServerDgeConnFactory dgeConnFactory;	//PYR-50101
	// //AuxLobbyServerConfigConnFactory configConnFactory;	//PYR-56430
	// AuxLobbyServerDeliveryConnFactory deliveryConnFactory;
	// AuxLobbyServerUgcConnFactory ugcPlayerConnFactory;
	// AuxLobbyServerAbeConnFactory abeConnFactory;
	// AuxLobbyServerGGNDataFeedConnFactory ggnDataFeedConnFactory;

	//std::vector<std::unique_ptr<AuxGConnWithoutUnsolicitedMsg> > tableFactories;
	std::map<std::string, std::unique_ptr<AuxGConnWithoutUnsolicitedMsg> > tableFactories;

	// AuxHandHistoryConn handHistoryServerConn;
	// AuxGConnWithoutUnsolicitedMsg dbmConn;
	// AuxGConnWithoutUnsolicitedMsg roDbmConn;
	// AuxGConnWithoutUnsolicitedMsg idDbmConn;
	// AuxGConnWithoutUnsolicitedMsg authIntegrationServerConn;
	// AuxGConnWithoutUnsolicitedMsg integrationServerConn;
	// AuxGConnWithoutUnsolicitedMsg userSettingsDbmConn;
	// AuxGConnWithoutUnsolicitedMsg cdlDbmConn;
	// AuxGConnWithoutUnsolicitedMsg adminServerConn;
	// AuxGConnWithoutUnsolicitedMsg jackpotServerConn;
	// AuxGConnWithoutUnsolicitedMsg vttmConn;

	// AuxRaceServerConn raceServerConn;
	// AuxGConnWithoutUnsolicitedMsg roOlapDbmConn;

	// AuxPropertyPublisher propertyPublisher;
	// AuxPropertyPublisher cmsPublishers[7];

	pair<PString, PString> handIdDbmParam;
	vector< pair<PString, PString> > tableDbmParams;

	map<UINT32, AuxLobbyTableTypePtr> tableTypes;
	vector<AuxLobbyTableTypePtr> obsoleteLdTableType;
	map<UINT16, LDTTWithPeersInfoByVendor> ldttWithPeersMap;
	map<UINT64, AuxLobbyTableDataPtr> tables;
	PStringMap<AuxLobbyPlayerPtr> players;
	map<std::pair<UINT16,UINT32>, AuxLobbyUniquePlayerPtr> uniPlayers;
	PStringMap<UserStuckTables> mapStuckTables; // auxUserId + UserStuckTables
	// TableNamePool namePool;

	//[GameTypeId][GameVarientId] <==> [list Of tableType]
	//PYR-75578 speed up find race qualified tableType
	map<UINT32, map<UINT16, std::list<AuxLobbyTableTypePtr>>> tableTypesByGame;

	std::map<PString, std::list<AuxLobbyTableTypePtr>, PStringCmp> tableTypesByRefName;

	map<UINT16, BYTE> vendorsStatus;

	// UniqueSequenceNumber loginSessionIdSeqObj;
	// UniqueSequenceNumber tranxIdSeqObj;
	// UniqueSequenceNumber hostReqIdObj;
	// UniqueSequenceNumber tableIdObj;
	// UniqueSequenceNumber gameDisableRuleIdObj;

	// TablePlacementMng tablePlacementMng;
	// LocalSeqNo reservSeatSeqObj;   // no need to be globally unique

	enum ShadowConnType { None = 0, DISPLAY = 1 };
	vector< pair< UINT32, ShadowConnType > > shadowConnId;

	// LobbyPerformanceCounter performanceCounter;

	bool useSeparateFactoryForPM;
	bool useSeparateFactoryForPS;

	UINT32 launchKeyIndex;	//PYR-55812
	GameSetupMap mapGameSetup; //PYR-55812

	GlobalStatistics globalStatistics;
    LobbyVendorStatusStatsInfo lobbyVendorStatusInfo;

	GameManagementData gameManagementData;
	std::map<aux::BackofficeType, HostSystemInfo> hostSystemInfos;
	CompactableBi<reef::objs::HostSystemStatus> hostSystemsStatus; // PYR-134560 key: [UINT64(AuxServer::BackofficeType)]
	HostSystemInfo& getHostSystemInfo(UINT16 boId);

	//PYR-53608
	CommMsgBody msgRg;
	CommMsgBody msgLd;
	CommMsgBody msgLite;
	CommMsgBody msgTable;
	CommMsgBody msgPtLd;

	MOCK_METHOD(void, updateDisableTableStatusMap, (UINT64 tableId_, GameManagementData::DisableRule::DisableTableStatusType status_));
	MOCK_METHOD(void, checkAndRemoveDisableTables, (UINT64 tableId_));

	UINT64 nextPendingExclusiveReqId;

	std::map<UINT64, time_t> deferRemoveTables; // [tableId] <=> [close time]
	CompactableConsumer<aux::RaceStaticInfo> raceStaticInfos; // key: [race id]
	MOCK_METHOD(const std::shared_ptr<aux::RaceStaticInfo>, getRaceStaticInfo, (UINT64 raceId));
private:
	ServletHandler<AuxReefAccessor> reefAccessor;
public:
	AuxLobbyServerObject(_CommInterface& inter)
	: AuxCommServerObject(inter),
	// loginSessionIdSeqObj(AUX_ID_GENERATOR_LOGINSESSIONID),
	// tranxIdSeqObj(AUX_ID_GENERATOR_MONEYTRANXID),
	// hostReqIdObj(AUX_ID_GENERATOR_HOSTREQID),
	// tableIdObj(AUX_ID_GENERATOR_XC_TABLES),
	// gameDisableRuleIdObj(AUX_ID_GENERATOR_XC_GAME_DISABLE_RULE_ID),
	adminUpdatedHostSystemInfo(false),
	useSeparateFactoryForPM(false),
	useSeparateFactoryForPS(false),
	launchKeyIndex(0),
	nextPendingExclusiveReqId(1),
	initPhase(LobbyInitPhase::INIT_PHASE_ZERO),
	lastTableRecoverTime(0),
	ugcConns(AUX_REEF_COMPACTABLE_OBJ_UGC),
	tableLoadInfo("tbPlacement", CompactableConsumerBase::ONETIME_SNAPSHOT),
	raceStaticInfos(AUX_REEF_COMPACTABLE_OBJ_RACE_STATIC_INFO, CompactableConsumerBase::CONTINOUSE_SYNC),
	hostSystemsStatus(AUX_REEF_COMPACTABLE_OBJ_HOST_SYSTEM_INFO, CompactableConsumerBase::ONETIME_SNAPSHOT)
	{}
	~AuxLobbyServerObject(){}

	//bool isShutdown;
	//bool isPaused;
	bool adminUpdatedHostSystemInfo;

	AuxLobbyStaticConfig staticConfig;
	std::shared_ptr<AuxLobbyDynamicConfig> dynamicConfig;

	MOCK_METHOD(void, preloadStaticConfig, (const PIniFile& ini, const AuxEslResolver* esl));
	MOCK_METHOD(void, preloadDynamicConfig, (const PIniFile& ini, const AuxEslResolver* esl));
	MOCK_METHOD(void, init, ());
	MOCK_METHOD(void, applyDynamicConfig, (bool rereadIni));

	MOCK_METHOD(void, onTimer, ( UINT32 timerHandle, UINT32 msgId, const CommMsgBody& body ));

	MOCK_METHOD(void, processHostTokenAuth, (LobbyPlayerOrCipwaConnBase* conn, const PString& user, const CommMsgBody& request, UINT64 tableId, const PString& appSessionRef, BYTE connectBack));
	MOCK_METHOD(void, processAuxTokenAuth, (LobbyPlayerOrCipwaConnBase* conn, const PString& user, const CommMsgBody& request, UINT64 tableId));
	MOCK_METHOD(void, onLobbyUgcConnConnected, (AuxLobbyServerUgcConn* conn));
	MOCK_METHOD(void, startAddNotifyUgcConnService, (AuxLobbyServerUgcConn* conn));
	MOCK_METHOD(void, startRemoveUgcConnService, (AuxLobbyServerUgcConn* conn));
	MOCK_METHOD(void, tableConnected, ( LobbyServerTableGConn* conn ));
	MOCK_METHOD(void, tableClosedOrDisconnected, (LobbyServerTableGConn* conn));
	MOCK_METHOD(void, processTableMessage, ( LobbyServerTableGConn* conn, UINT32 msgId, const CommMsgBody& body ));
	MOCK_METHOD(void, processUserMessage, ( LobbyServerPlayerConn* conn, UINT32 msgId, const CommMsgBody& body ));
	MOCK_METHOD(void, processShadowMessage, ( LobbyServerShadowConn* conn, UINT32 msgId, const CommMsgBody& body ));
	MOCK_METHOD(void, processWebGWMessage, ( LobbyServerWebGWConn* conn, UINT32 msgId, const CommMsgBody& body ));
	MOCK_METHOD(void, processHandHistoryMessage, (AuxHandHistoryConn* conn, UINT32 msgId, const CommMsgBody& body));
	MOCK_METHOD(void, processRaceServerMessage, (AuxRaceServerConn* conn, UINT32 msgId, const CommMsgBody& body));
	MOCK_METHOD(void, processUgcMessage, (AuxLobbyServerUgcConn* conn, UINT32 msgId, const CommMsgBody& body));
	MOCK_METHOD(void, processDeliveryMessage, (LobbyServerDeliveryConn* conn, UINT32 msgId, const CommMsgBody& body));
	MOCK_METHOD(void, processGGNDataFeedMessage, (LobbyServerGGNDataFeedConn* conn, UINT32 msgId, const CommMsgBody& body));
	MOCK_METHOD(void, postClientUgcNotification, (UINT32 connId, const PString& auxUserId, const Atf::MessageProtocol& msg));
	MOCK_METHOD(void, postClientUgcNotification, (AuxLobbyServerUgcConn* conn, const Atf::MessageProtocol& msg));
	MOCK_METHOD(void, shadowDisconnected, ( UINT32 id ));
	MOCK_METHOD(void, loginSessionEnd, ( LobbyLoginSessionPtr session ));
	MOCK_METHOD(void, disconnectUgcPlayerConnection, (LobbyLoginSessionPtr session, UINT32 connId, BYTE reason));
	MOCK_METHOD(void, disconnectLobbyPlayerConnection, (LobbyLoginSessionPtr session, UINT32 connId, BYTE reason));

	//bool isShutdownOrPause(aux::SystemStatusType status) { return status== aux::STATUS_SHUTTINGDOWN || status== aux::STATUS_PAUSED; }
	MOCK_METHOD(bool, isAnyBoPaused, (), (const));
	/*UINT16 getShutdownOrPause(UINT32 hostId) {
		auto it = hostSystemInfos.find(getBoRepresent(hostId));
		if(it != )
	}*/

	MOCK_METHOD(bool, hasTable, (UINT64 tableId));
	MOCK_METHOD(void, closeOutOfControlTable, (AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, requestDissolveOocTable, (LobbyServerTableGConn* conn));
	MOCK_METHOD(void, processOocTableMessage, (LobbyServerTableGConn* conn, UINT32 msgId, const CommMsgBody& body));
	MOCK_METHOD(void, processReefEvent, (const reef::Event& evt));
	MOCK_METHOD(void, recoverTable, (Lobby::Table::TableConnectInfo& tbInfo));
	MOCK_METHOD(void, logoutAllExistingLoginSessions, (AuxLobbyPlayerPtr existingPlayerObj));
	MOCK_METHOD(void, logoutLoginSessionOnTokenInvalid, (LobbyLoginSessionPtr lsession));
	MOCK_METHOD((std::map<std::string, UINT32>), getTableLoadInfos, ());

	MOCK_METHOD(INT16, checkPromoEnabled, (LobbyLoginSessionPtr session, PString& errMsg));
	MOCK_METHOD(bool, isPromoEnabled, (LobbyLoginSessionPtr session));
private:
	MOCK_METHOD(void, postTableMsg, ( AuxLobbyTableDataPtr table, UINT32 reqId, const Atf::MessageProtocol& msg ));
	MOCK_METHOD(void, requestInitDataAndProceedLobbyRestartProcedures, ());

	MOCK_METHOD(void, unbindRaceSession, (RaceServer::Lobby::RaceBindInfo& bindInfo));
	MOCK_METHOD(void, resetHostSystemStatusInReef, ());
	MOCK_METHOD(void, updateHostSystemInfoWhenLobbyRecoveryStart, ());
	MOCK_METHOD(void, finishLobbyInit, ());
	MOCK_METHOD(void, notifyShadowLobbySystemRunning, ());
	MOCK_METHOD(void, requestCreateTable, (AuxLobbyTableDataPtr table, const PString& initTableState, const PString& user));
	MOCK_METHOD(void, requestCreateTable, (AuxLobbyTableTypePtr type, bool createdForRestoration, UINT32 fsbId, const PString& user));
	MOCK_METHOD(void, confirmPassivatedTableToActive, (UINT64 tableId_));

	MOCK_METHOD(void, requestDissolveTable, (AuxLobbyTableDataPtr table, UINT32 reason, UINT32 serverModuleType, const char* build));
	MOCK_METHOD(void, requestHideTable, (AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, requestShowHiddenTable, (AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, requestTableStatusChange, (AuxLobbyTableDataPtr table, UINT16 targetStatus));

	MOCK_METHOD(void, processTableDied, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processTableStatusChanged, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processPlayerSeated, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processPlayerSeatedRgConfirm, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processPlayerLeft, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processClientClosed, (LobbyServerTableGConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUpdateHandStatus, (LobbyServerTableGConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUpdateTableGameEvent, (LobbyServerTableGConn* conn, const CommMsgBody& body));
	MOCK_METHOD(INT16, validateUserAuthRequest, (HostAuthRequestData& authData, PString& validateErrorStr, aux::PSClientHostInfo& psClientHostInfo));
	MOCK_METHOD(void, processFindTableToPlay, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(void, innerProcessFindTableToPlay, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));	
	MOCK_METHOD(void, processFindTableByTableType, (LobbyPlayerOrCipwaConnBase* conn, const LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_Q_FIND_TABLE_TO_PLAY2& req));
	MOCK_METHOD(bool, getTableTypeByTableTypeId, (const PString& tableTypeRefName, UINT32 tableTypeId, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyTableTypePtr& tableType));
	MOCK_METHOD(bool, getTableTypeByRaceGameData, (const aux::GameVariantCompact& gameData, const aux::RaceStaticInfo& raceInfo, LobbyLoginSessionPtr session, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyTableTypePtr& tableType));
	MOCK_METHOD(bool, getTableTypeByRaceTemplate, (const aux::RaceStaticInfo& raceInfo, UINT32 reqTableTypeId, LobbyLoginSessionPtr session, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyTableTypePtr& tableType));
	MOCK_METHOD(bool, checkTableTypeByTableTypeId, (const PString& launchKey, UINT32 fsbId, const LobbyLoginSessionPtr session, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyTableTypePtr& tableType, UINT64 raceId));
	MOCK_METHOD(void, processFindTableByRaceId, (LobbyPlayerOrCipwaConnBase* conn, const PString& launchKey, UINT64 raceId, UINT32 reqTableTypeId));
	MOCK_METHOD(void, startFindTableByTableTypeService, (AuxLobbyTableTypePtr type, LobbyLoginSessionPtr session, UINT32 connId, UINT32 fsbId, const PString& launchKey, UINT64 raceId));
	MOCK_METHOD(bool, validateUserAppDataKeys, (vector<PString>& keys));

	//PYR-120242 function to process SBG FindTableToPlay service
	MOCK_METHOD(void, innerProcessSBGFindTableToPlay, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(AuxLobbyTableTypePtr, findSBGTableTypeByRefName, (const PString& tableTypeRefName, bool nonObsolete), (const));
	MOCK_METHOD(bool, getSBGTableTypeByRefName, (const PString& reqTableTypeRefName, UINT32 tableTypeId, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyTableTypePtr& tableType));
	MOCK_METHOD(bool, checkSBGLiveGame, (const LobbyLoginSessionPtr session, AuxLobbyTableTypePtr reqTableType, const LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_Q_FIND_TABLE_TO_PLAY2& request, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));
	MOCK_METHOD(bool, checkSBGDisconnectedGame, (const LobbyLoginSessionPtr session, AuxLobbyTableTypePtr reqTableType, const LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_Q_FIND_TABLE_TO_PLAY2& request, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));
	
	MOCK_METHOD(bool, checkSBGRestriction, (const LobbyLoginSessionPtr session, AuxLobbyTableTypePtr tableType, const PString& launchKey, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));

	//CAD-18422 process PPB FindTableToPlay service
	MOCK_METHOD(void, innerProcessPPBFindTableToPlay, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(bool, getPPBTableTypeByParams, (const LobbyLoginSessionPtr session, const LobbyC::Client::PPBTableTypeParams& ppbParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyTableTypePtr& tableType));
	MOCK_METHOD(bool, checkPPBLiveGame, (const LobbyLoginSessionPtr session, const LobbyC::Client::PPBTableTypeParams& ppbParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));
	MOCK_METHOD(bool, checkPPBDisconnectedGame, (const LobbyLoginSessionPtr session, const LobbyC::Client::PPBTableTypeParams& ppbParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));
	MOCK_METHOD(bool, checkPPBGamesLimit, (const LobbyLoginSessionPtr session, const LobbyC::Client::PPBTableTypeParams& ppbParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));
	
	MOCK_METHOD(void, innerProcessFdFindTableToPlay, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(bool, getFdTableTypeByParams, (const LobbyLoginSessionPtr session, const LobbyC::Client::FanDuelTableTypeParams& fdParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyTableTypePtr& tableType));
	MOCK_METHOD(bool, checkFdLiveGame, (const LobbyLoginSessionPtr session, const LobbyC::Client::FanDuelTableTypeParams& fdParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));
	MOCK_METHOD(bool, checkFdDisconnectedGame, (const LobbyLoginSessionPtr session, const LobbyC::Client::FanDuelTableTypeParams& fdParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));
	MOCK_METHOD(bool, checkFdGamesLimit, (const LobbyLoginSessionPtr session, const LobbyC::Client::FanDuelTableTypeParams& fdParams, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply));

	MOCK_METHOD(void, processGetUserAppData, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processSetUserAppData, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));

	MOCK_METHOD(void, processUserMsgFindPlayerTables, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgFindTableToPlay, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetUserAppData, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgSetUserAppData, (LobbyPlayerOrCipwaConnBase* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetHandHistory, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetUserSettings, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgSetUserSettings, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetUserFSBs, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetFirstFSBToPlay, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetPlayerGeoStatus, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetMyRaces, (LobbyServerPlayerConn*  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgRaceOptin, (LobbyServerPlayerConn*  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetMyLastCompletedRaces, (LobbyServerPlayerConn*  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetRaceFullLeaderboard, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetMyCompletedRaceLeaderboardByPage, (LobbyServerPlayerConn*  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetActiveRaceLeaderBoardByPage, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetUFGs, (LobbyServerPlayerConn*  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgGetTableForRestoringGame, (LobbyServerPlayerConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUserMsgCheckEsGameSessionMessage, (LobbyServerPlayerConn* conn, const CommMsgBody& body));

	MOCK_METHOD(HHCodeStringPair, createHHRequestValidationReply, (HHErrorType err), (const));
	MOCK_METHOD(void, validateHHRequest, (AuxLobbyPlayerPtr player, HHServer::HHReplyDeliveryMethod deliveryMethod, HHCodeStringPair& cep));
	MOCK_METHOD(void, validateHHRequest, (LobbyLoginSessionPtr session, HHServer::HHReplyDeliveryMethod deliveryMethod, HHCodeStringPair& cep));
	MOCK_METHOD(void, processValidateHandHistory, (AuxHandHistoryConn* conn, const CommMsgBody& body));


	MOCK_METHOD(void, processShadowInitData, (LobbyServerShadowConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, notifyShadows, ( ShadowConnType type, const Atf::MessageProtocol& msg));

	MOCK_METHOD(void, processUpdateTableState, ( LobbyServerTableGConn const *  conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processLockTable, (LobbyServerTableGConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processUnLockTable, (LobbyServerTableGConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processTableStuck, (LobbyServerTableGConn* conn, const CommMsgBody& body));
	
	MOCK_METHOD(void, processAdminMessage, ( AuxCommServerConnection* conn, UINT32 msgId, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminCreateTableTypes, ( AuxCommServerConnection const *  conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminUploadTableTypeScripts, (AuxCommServerConnection const *  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processAdminObsoleteTableType, (AuxCommServerConnection const *  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processAdminGdkCommLogs, (AuxCommServerConnection* const conn, const CommMsgBody& body));

	MOCK_METHOD(void, processAdminDisableGames, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminEnableGames, ( AuxCommServerConnection* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processAdminFinalizeGame, (AuxCommServerConnection*  conn, const CommMsgBody& body));

	//void requestGameManagementData();
	MOCK_METHOD(void, processAdminGameManagement, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminGameManagementNew, (AuxCommServerConnection* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processAdminGetGameManagementData, ( AuxCommServerConnection const *  conn, const CommMsgBody& body));

	MOCK_METHOD(bool, findTableTypesMeetingCriteria, (bool findToDisable, const aux::TableTypeSelectionCriteria& criteria, vector<AuxLobbyTableTypePtr>& tableTypesMeetCriteria, INT16& errCode, PString& errMsg));
	MOCK_METHOD(void, requestEnableGames, (const AuxCommServerConnection* conn, UINT32 reqId,const  vector<UINT32> & tableTypeIds));
	MOCK_METHOD(void, requestDisableGames, (const AuxCommServerConnection* conn, UINT32 reqId,const  vector<UINT32> & tableTypeIds));

	MOCK_METHOD(void, reserveSeatToPlayer, ( AuxLobbyTableDataPtr table, const PString& user, const PString& launchKey, aux::InterruptedGameDef* interruptedGameDef ));
	MOCK_METHOD(AuxLobbyTableDataPtr, findTableWithAvailableSeat, ( UINT32 tableTypeId, set<UINT64> *excludeTables ));
	MOCK_METHOD(AuxLobbyTableDataPtr, findEmptyTable, ( UINT32 tableTypeId, set<UINT64> *excludeTables ));

	MOCK_METHOD(void, processTableCancelReservedSeat, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processTableClaimReservedSeat, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processTableReservSeat, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	
	MOCK_METHOD(void, processTableSwitchRunningMode, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processTableStatisticsUpdate, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));

	MOCK_METHOD(void, checkTables, ());
	MOCK_METHOD(void, checkShadowUpdates, ());

	MOCK_METHOD(void, setTableNames, (const vector< aux::NamesDef >& nameDefs, const vector< aux::XcTableNamesDef >& xcTableNameDefs));
	MOCK_METHOD(void, initVendorsStatus, ());
	MOCK_METHOD(void, updateVendorsStatus, ());
	MOCK_METHOD(void, updateVendorStatus, (UINT16 vendorId, BYTE status));

	MOCK_METHOD(void, composeGameSpecConfigMsg, (AuxLobbyTableTypePtr type, Atf::MsgBodyWithJSON& body, bool configSpeedParameters, const PString& auxUserId));

	MOCK_METHOD(AuxLobbyTableTypePtr, findTableType, (UINT32 tableTypeId), (const));
	MOCK_METHOD(AuxLobbyTableTypePtr, findTableType, (const PString& tableTypeRefName), (const));
	MOCK_METHOD(AuxLobbyTableDataPtr, findTable, (UINT64 tableId), (const));
	MOCK_METHOD(AuxLobbyPlayerPtr, findUser, ( const char* auxUserId ), (const));
	MOCK_METHOD(void, addUser, (AuxLobbyPlayerPtr player));
	MOCK_METHOD(void, addUserTable, (const char* auxUserId, AuxLobbyTableDataPtr table, UINT64 gameSessionId, UINT64 loginSessionId, UINT32 siteId, UINT32 clientPlatformId));
	MOCK_METHOD(void, removeUserTable, ( const char* auxUserId, UINT64 tableId, bool lockRestriction ));
	MOCK_METHOD(void, tryRemoveUser, (AuxLobbyPlayerPtr player));
	MOCK_METHOD(void, forceRemoveAllPlayersFromTable, (AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, doPlayerRemoveTable, (AuxLobbyPlayerPtr player, AuxLobbyTableDataPtr table, bool lockRestriction, bool isFroce));
	MOCK_METHOD(void, addUserStuckTable, (const char* auxUserId, UINT64 tableId, const AuxLobbyTableTypePtr type));
	MOCK_METHOD(void, removeUserStuckTable, (const char* auxUserId, UINT64 tableId, const AuxLobbyTableTypePtr type));
	MOCK_METHOD(void, notifiedUserHasStuckTable, (const char* auxUserId, const AuxLobbyTableTypePtr type));
	MOCK_METHOD(UINT64, getUserLastConflictStuckTableIdIfAny, (const PString& auxUserId, const AuxLobbyTableTypePtr type, bool& notifyPlayer));
	MOCK_METHOD(void, getUserStuckInfo4ComposeGameSpec, (const PString& auxUserId, const AuxLobbyTableTypePtr type, PString& rgUserSuffix, Atf::MsgBodyWithJSON& stuckSessionInfoMsg));

	MOCK_METHOD(void, removeAllPlayersRestrictionOnTable, (AuxLobbyTableDataPtr table));

	MOCK_METHOD(void, processGetUFGs, ( LobbyServerPlayerConn const *  conn, const CommMsgBody& body));

	MOCK_METHOD(void, processGetTableForRestoringGame, ( LobbyServerPlayerConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, runGetTableForRestoringService, ( UINT32 connId, UINT32 reqTableTypeId, UINT64 reqUfgId, LobbyLoginSessionPtr session, bool childService ));
	MOCK_METHOD(void, reserveASeatByTableTypeId, ( UINT32 tableTypeId, const char* user, aux::InterruptedGameDef* interruptedGameDef, set<UINT64> *excludeTables, UINT32 fsbId, PString launchKey));
	MOCK_METHOD(void, addNewTableTypes, ( const vector< aux::TableTypeDef >& tableTypeDefs ));
	MOCK_METHOD(void, addNewTableTypesAndObsoleteExists, ( const vector< aux::TableTypeDef >& tableTypeDefsAdded, const vector< aux::TableTypeDef >& tableTypeObsoleted));	
	MOCK_METHOD(void, obsoleteTableTypes, ( const vector< UINT32 >& tableTypeIds ));
	MOCK_METHOD(void, unobsoleteTableTypes, ( const vector< UINT32 >& tableTypeIds ));
	MOCK_METHOD(void, addNewTableToShadow, (AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, removeTableFromShadow, (UINT64 tableId));
	MOCK_METHOD(void, removeTable, (UINT64 tableId));
	MOCK_METHOD(void, enableGamesByTableTypes, ( const vector< UINT32 >& tableTypeIds ));
	MOCK_METHOD(void, disableGamesByTableTypes, ( const vector< UINT32 >& tableTypeIds ));

	MOCK_METHOD(void, updateShadowGlobalSiteInfo, ());
	//void updateShadowPsSystemInfo();
	//void updateShadowFtSystemInfo();
	MOCK_METHOD(void, updateShadowPsSystemInfo, (const set<UINT32>& disableSiteIds), (const));
	MOCK_METHOD(void, updateTableShadowStatic, (AuxLobbyTableDataPtr table));
	MOCK_METHOD(void, broadcastTableSpeedUpdate, ());
	MOCK_METHOD(void, updateShadowSystemInfo, (const HostSystemInfo& hsi));
	//PString getValueFromProps(const char *name, vector< aux::P_PNameValue >& props);
	

	MOCK_METHOD(bool, isLiveDealerTableTypeWithPeers, (AuxLobbyTableTypePtr tableTypePtr));
	MOCK_METHOD(void, refreshLiveDealerPeerTableTypes, ());

	MOCK_METHOD(void, initGameManagementData, (vector<aux::GameManagementRule>& rules, vector<aux::GameManagementException>& exceptions));
	MOCK_METHOD(void, updateGameManagementData, (vector<aux::GameManagementRule>& updatedRules, vector<aux::GameManagementException>& updatedExceptions, vector<aux::GameManagementRule>& addedRules, vector<UINT32>& removedRules));
	MOCK_METHOD(void, onGameManagementRuleUpdated, ());

	MOCK_METHOD(void, onActiveSiteDisableRule, (const GameManagementData::DisableRule& rule));
	MOCK_METHOD(void, onInactiveSiteDisableRule, (const GameManagementData::DisableRule& rule));
	MOCK_METHOD(void, startReloadPassivatedTables, (aux::GamingSiteGroup siteGroup));
	MOCK_METHOD(void, startReloadPassivatedTables, ());

	MOCK_METHOD(void, createTableFactories, ());
	MOCK_METHOD((std::pair<const char*, INT32>), dispatchTable, (AuxLobbyTableTypePtr tableType));
	MOCK_METHOD(INT32, releaseTableOccupied, (const char* factory, INT32 weight));
	MOCK_METHOD(AuxGConnWithoutUnsolicitedMsg&, getTableConnectionFactory, (const char* serverAddr));
	MOCK_METHOD(PString, getTableObjectFactoryType, (AuxLobbyTableTypePtr tableType));
	//void readMultiTableConfig(const PIniFile::Section* staticSettingsSection);
	MOCK_METHOD(bool, isMultiTableFactoryType, (AuxLobbyTableTypePtr tableType));

	static const char* getIPFromAdress(const char* str_IP, PString& ipAddrBuff );
	MOCK_METHOD(UINT32, getVendorMsgTimeoutToDeclareSessionStuck, (UINT16 vendorId));
	MOCK_METHOD(PString, getVendorCasinoName, (const AuxLobbyTableTypePtr& tableType), (const));

	MOCK_METHOD(void, startRaceUnBindService, (UINT16 hostId, UINT32 userIntId, AuxLobbyTableDataPtr table, UINT64 gameSessionId));
	MOCK_METHOD(void, startRaceCloseTableService, (AuxLobbyTableDataPtr table));
	//void startRaceUgcConnectedService(AuxLobbyPlayerPtr player, AuxLobbyTableDataPtr table, UINT64 gameSessionId, UINT64 raceId);
	MOCK_METHOD(void, unbindPlayerOnTableRace, (const PString& auxUserId, UINT64 tableId));

	MOCK_METHOD(void, processRaceNotifPlaying, (const CommMsgBody& body));
	MOCK_METHOD(void, processRaceNotifRaceAwUpdated, (const CommMsgBody& body));
	MOCK_METHOD(void, processRaceNotifRaceEnded, (const CommMsgBody& body));

	//PYR-89503
	MOCK_METHOD(void, processGetExclusiveFsb, (AuxLobbyServerUgcConn* conn, const CommMsgBody& body));
	MOCK_METHOD(bool, replyErrorWhenHostNotAvailable, (LobbyPlayerOrCipwaConnBase* conn, UINT32 msgId));
public:
	ShadowLobbyC::Client::TableShadowInfo& convertDataStruct(AuxLobbyTableDataPtr table, ShadowLobbyC::Client::TableShadowInfo& ts);
	ShadowLobbyC::Client::TableStaticShadowInfo& convertDataStruct(AuxLobbyTableDataPtr table, ShadowLobbyC::Client::TableStaticShadowInfo& ts);
	static ShadowLobbyC::Client::TableDynamicShadowInfo& convertDataStruct(AuxLobbyTableDataPtr table, ShadowLobbyC::Client::TableDynamicShadowInfo& td);
	MOCK_METHOD(bool, validateTableType, (const aux::TableTypeDef& type), (const));
	MOCK_METHOD(bool, ignoreTableType, (const aux::TableTypeDef& type), (const));
	MOCK_METHOD(void, processAuthNowQuery, ( LobbyServerWebGWConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminStopDealing, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminResumeDealing, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminCloseTables, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(bool, findTablesMeetingCriteria, (const aux::TableSelectionCriteria& criteria, vector<AuxLobbyTableDataPtr>& tablesMeetCriteria, INT16& errCode, PString& errMsg));
	MOCK_METHOD(void, processTableDealingStateUpdate, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminKickPlayer, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminShutDown, ( AuxCommServerConnection*  conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminGetTableStatus, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminGetTableNumByRuleId, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminGetHostSystemInfo, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(void, processAdminUpdateHostSystemInfo, ( AuxCommServerConnection* conn, const CommMsgBody& body ));
	MOCK_METHOD(INT16, verifyUpdateHostSystemInfo, (Lobby::Adm::Protocol_AUX_LOBBY_ADMIN_Q_UPDATE_HOST_SYSTEM_INFO req, PString& errStr));
	MOCK_METHOD(void, updateHostSystemInfo, (Lobby::Adm::Protocol_AUX_LOBBY_ADMIN_Q_UPDATE_HOST_SYSTEM_INFO req, HostSystemInfo& hsi));
	MOCK_METHOD(void, processAdminStopTables, (AuxCommServerConnection* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processAdminRestartTable, (AuxCommServerConnection const *  conn, const CommMsgBody& body));
	MOCK_METHOD(void, getTableDefAndStartTable, (UINT64 tableId));
	MOCK_METHOD(void, processAdminRestartTables, (AuxCommServerConnection const *  conn, const CommMsgBody& body));
	MOCK_METHOD(void, processAdminCleanupSession, (AuxCommServerConnection * conn, const CommMsgBody& body));
	MOCK_METHOD(void, processAdminCloseTableAndGetConfirm, (AuxCommServerConnection const *  conn, const CommMsgBody& body));

	MOCK_METHOD(void, requestISToClosAllLoginSessions, (bool systemShutdown, CommSrvTime timeBefore));
	MOCK_METHOD(void, requestVttmAction, ( vttm::SysCommandType action));
	MOCK_METHOD(void, getVttmStatusAndReturnReply, (AuxCommServerConnection* conn, UINT32 reqId, const Lobby::Adm::Protocol_AUX_LOBBY_ADMIN_A_GET_HOST_SYSTEM_INFO& resp));
	MOCK_METHOD(void, processTableCrashed, (UINT64 tableId));
	MOCK_METHOD(void, processAdminCloseTablesByBuild, ( AuxCommServerConnection* conn, const CommMsgBody& body ));

	MOCK_METHOD(void, processDeliveryRequest, (LobbyServerDeliveryConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processDeliveryNotificationAcked, (LobbyServerDeliveryConn* conn, const CommMsgBody& body));

	MOCK_METHOD(void, processGGNDataFeedForActiveTableTypes, (LobbyServerGGNDataFeedConn* conn, const CommMsgBody& body));

	template<typename _T>
	void foreachTable(_T const& call) const
	{
		for (const auto& item : tables)
		{
			if(!call(item.second.ptr()))
				break;
		}
	}
	template<typename _T>
	void foreachUser(_T const& call)
	{
		for(auto& player : players) 
		{
			PASSERT5(player.second != nullptr);
			if(!call(player.second.ptr()))
				break;
		}
	}

	MOCK_METHOD(bool, isVendorReady, ( UINT16 vendorId ), (const));
	MOCK_METHOD(BYTE, getVendorStatus, ( UINT16 vendorId ));
	MOCK_METHOD(void, notifyTablesUpdateVendorStatus, (UINT16 vendorId, BYTE status));
	MOCK_METHOD(void, updateShadowVendorStatusInfo, ());
	
	MOCK_METHOD(void, broadcastTableNotification, (list<UINT64> const& tableIds, Atf::SharedPointer<Atf::MessageProtocol> msg));

	MOCK_METHOD(void, doAuxShutDown, ());
	//void prepareShutDown(AuxCommServerConnection* conn, UINT32 requestId, const CommMsgBody& msgBody);

	MOCK_METHOD(void, initCriticalComponents, ());

	//PYR-50101
	MOCK_METHOD(void, processDgeMessage, ( LobbyServerDgeConn* conn, UINT32 msgId, const CommMsgBody& body ));
	MOCK_METHOD(void, processDgeResetRnCache, ( LobbyServerDgeConn* conn, const CommMsgBody& body ));

	//PYR-51171
	MOCK_METHOD(UINT64, allocateTableId, ());

	//PYR-53556 
	MOCK_METHOD(void, informJpDbmTableClosed, (UINT64 tableId));
	
	//PYR-53607
	MOCK_METHOD(void, doAuxPause, ());
	MOCK_METHOD(void, doAuxResume, ());
	template<typename _T, typename _C>
	void sendReplySystemErrorMsg(_T& t, _C* c, UINT32 reqId)
	{
		t.errCode = auxservererr::SERVER_ERROR_SYSTEM_BUSY;
		t.errDesc = "system paused";
		c->postGMsg(reqId, t);
	}

	template<typename _T, typename _C>
	void sendReplySystemErrorMsg2(_T& t, _C* c, UINT32 reqId)
	{
		t.errCode = auxservererr::SERVER_ERROR_SYSTEM_BUSY;
		t.errStr = "system paused";
		c->postGMsg(reqId, t);
	}
	//PYR-53608
	MOCK_METHOD(void, broadcastMsgCheckSettingsUpdate, ());

	MOCK_METHOD(void, checkLoginSessions, ());

	//PYR-55812
	MOCK_METHOD(PString, getGameLaunchKey, ());
	MOCK_METHOD(void, checkLaunchKeys, ());
	MOCK_METHOD(bool, checkAndSetLaunchKeyInUse, ( const PString& launchKey, UINT32 tableTypeId, UINT32 fsbId, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& reply, AuxLobbyPlayerPtr player ));
	MOCK_METHOD(bool, checkAndSetRaceLaunchKeyInUse, (const PString& launchKey, UINT64 raceId, LobbyC::Client::Protocol_AUX_LOBBY_CLIENT_MSG_A_FIND_TABLE_TO_PLAY2& replyToClient, AuxLobbyPlayerPtr player));
	MOCK_METHOD(void, processSetupNewGame, ( LobbyServerTableGConn* conn, const CommMsgBody& body ));
	MOCK_METHOD(AuxLobbyTableTypePtr, findMatchingTableType, ( AuxLobbyTableDataPtr fromTable, const Lobby::RgTable::Protocol_AUX_LOBBY_MSG_Q_SETUP_NEW_GAME& setupRequest));
	MOCK_METHOD(UINT32, findMatchingPTLDLobbyTableType, ( UINT16 variantType ));
	MOCK_METHOD(void, removeGameLaunchKeyFromMap, (const PString& gameLaunchKey));
	MOCK_METHOD(void, removeGameLaunchKeyFromMap, (AuxLobbyPlayerPtr player, UINT64 tableId));
	static bool playtechLdTablePropsAreEqual(const aux::PlaytechLdTableProps& p1, const aux::PlaytechLdTableProps& p2);
	MOCK_METHOD((std::pair<UINT16, UINT32>), getBoIdUserIntIdPair, (AuxLobbyPlayerPtr player), (const));

	UINT32 abeServerConnID;

private:
	std::set<UINT32> sharedWebGWConnIds;	// authentication channels are shared. These channels are also for CDL notifications
	MOCK_METHOD(void, notifyWebGWTableTypeChanged, ());				// currently notifies table type change only. So there is no parameter 
	MOCK_METHOD(void, notifyWebGWRaceChanged, (BYTE hostId, UINT32 userIntId, const aux::RaceStaticInfo& raceInfo));		// 
	MOCK_METHOD(void, notifyWebGWUserAppDataChanged, (BYTE hostId, UINT32 userIntId, const vector<aux::UserAppDataItem>& items));
	MOCK_METHOD(void, sendNotificationToAllWebGWs, (const Lobby::WebGW::Protocol_AUX_LOBBY_WEBGW_MSG_NOTIFICATION& msg));
	static HHCodeStringPairMap hhErrorToClient; //PYR-61146

	//	PYR-57867  
	//std::map<UINT32, aux::UgcConnection> ugcConns;
	CompactableProducer<aux::UgcConnection> ugcConns;
	CompactableBi<reef::events::TablePlacement> tableLoadInfo;
	MOCK_METHOD(void, processNotificationAckMessage, (AuxLobbyServerUgcConn* conn, const CommMsgBody& body));	
	MOCK_METHOD(void, processRacePlayMessage, (AuxLobbyServerUgcConn* conn, const CommMsgBody& body));
	MOCK_METHOD(void, processGetNextRaceMessage, (AuxLobbyServerUgcConn* conn, const CommMsgBody& body));	// PYR-100905

	//PYR-89503
	MOCK_METHOD(UINT64, getNextPendingExclusiveReqId, ());
	MOCK_METHOD(void, generateRaceBindingRequest, (RaceServer::Lobby::Protocol_AUX_RACE_MSG_Q_RACE_BIND& request, const LobbyLoginSessionPtr& session, UINT64 tableId, UINT64 gameSessionId, UINT64 raceId));	
};

class MainDbmAsyncCall : public CommClientGConnection::AsyncCall
{
public:
	MainDbmAsyncCall(AuxLobbyServerObject* so, UINT64 tId) : serverObject(so), tableId(tId) {}

	MOCK_METHOD(void, processReply, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body));

private :
	AuxLobbyServerObject* serverObject;
	UINT64 tableId;
};

class AuxLobbyServerObjectFactory : public CommServerObjectFactory
{
public:
	MOCK_METHOD(CommServerObject*, createServerObject, (_CommInterface& inter), (const));
};

class AuxLobbyUtil
{
public:
	static void copyInfoFromTable(aux::CashTableInfo_M& tableInfo, const AuxLobbyTableDataPtr table){}
	static void createAlreadyTablePlayingErrorReply(AuxLobbyTableDataPtr table, bool isPlayingTable, INT16& errCode, PString& errStr, Atf::MsgBodyWithJSON& extraErrMsg, UINT64 raceId = 0){}
	static bool isQualifiedRaceGame(const AuxLobbyServerObject* serverObject, const aux::RaceStaticInfo& raceInfo, AuxLobbyTableTypePtr tableType, LobbyLoginSessionPtr session){return false;}
	static bool isQualifiedTableTypeByRaceInfo(const AuxLobbyServerObject* serverObject, const aux::RaceStaticInfo& raceInfo, AuxLobbyTableTypePtr tableType, LobbyLoginSessionPtr session){return false;}
	static bool isQualifiedRaceTable(AuxLobbyTableDataPtr table){return false;}

	template <class T>
	static void createRacePlayClientErrorReply(const AuxLobbyServerObject* serverObject, INT16 errCode, Atf::MsgBodyWithJSON extraErrMsg, UINT64 tableId, UINT64 raceId, T& clientReply)
	{
		if (errCode == auxservererr::SERVER_ERROR_RACE_ALREADY_PLAYING || errCode == auxservererr::SERVER_ERROR_RACE_ALREADY_PLAYING_IN_ANOTHER_GAME)
		{
			auto raceTable = serverObject->findTable(tableId);

			if (raceTable)
			{
				clientReply.extraErrMsg.composeUINT64("raceId", raceId);

				clientReply.extraErrMsg.composeUINT32("tableTypeId", raceTable->tableType->tableTypeId);
				clientReply.extraErrMsg.composeUINT64("tableId", raceTable->tableId);
				clientReply.extraErrMsg.composeBOOL("isPlayingTable", true);
				clientReply.extraErrMsg.composeString("tableName", raceTable->tableName.c_str());
				clientReply.extraErrMsg.composeString("serverAddress", raceTable->serverAddr.c_str());
				clientReply.extraErrMsg.composeString("serverObject", raceTable->serverObject.c_str());
				clientReply.extraErrMsg.composeUINT32("gameTypeId", raceTable->getGameTypeId());
				clientReply.extraErrMsg.composeBYTE("maxSeats", raceTable->getNumOfSeats());
				clientReply.extraErrMsg.composeBYTE("playType", raceTable->getPlayType());
				clientReply.extraErrMsg.composeUINT16("technologies", raceTable->tableType->technologies);
				clientReply.extraErrMsg.composeUINT16("vendorId", raceTable->tableType->vendorId);

				PString rgGameLoaderUrl = AuxLobbyTableData::getValueFromProps(AUX_TABLE_PROP_NAME_rgGameLoaderUrl, raceTable->tableType->extraTableTypeProps);
				PString rgGameConfig = AuxLobbyTableData::getValueFromProps(AUX_TABLE_PROP_NAME_rgGameConfig, raceTable->tableType->extraTableTypeProps);

				clientReply.extraErrMsg.composeString("rgGameLoaderUrl", rgGameLoaderUrl);
				clientReply.extraErrMsg.composeString("rgGameConfig", rgGameConfig);

				clientReply.extraErrMsg.composeUINT32("fsbId", raceTable->fsbId);

				if (errCode == auxservererr::SERVER_ERROR_RACE_ALREADY_PLAYING_IN_ANOTHER_GAME)
				{
					clientReply.errCode = auxclienterr::ERROR_CLIENT_RACE_ALREADY_PLAYING_IN_ANOTHER_GAME;
					clientReply.errStr = "has playing race in another game";
				}
				else
				{
					clientReply.errCode = auxclienterr::ERROR_CLIENT_RACE_ALREADY_PLAYING;
					clientReply.errStr = "has playing race";
				}				
			}
			else
			{
				if (errCode == auxservererr::SERVER_ERROR_RACE_ALREADY_PLAYING_IN_ANOTHER_GAME)
				{
					clientReply.errCode = auxclienterr::ERROR_CLIENT_RACE_ALREADY_PLAYING_IN_ANOTHER_GAME;
					clientReply.errStr = "has playing race in another game";
				}
				else
				{
					clientReply.errCode = auxclienterr::ERROR_CLIENT_GENERAL_SYSTEM_ERROR;
				}
			}			
		}
		else if (errCode == auxservererr::SERVER_ERROR_RACE_RESTRICTED)
		{ 
			clientReply.errCode = auxclienterr::ERROR_CLIENT_RACE_RESTRICTED;
			clientReply.errStr = "race restricted";
			clientReply.extraErrMsg = extraErrMsg;
		}
		else
		{
			auxservererr::convertGenericError(errCode, clientReply.errCode);
		}
	}

	static void getCashTableInfo(aux::CashTableInfo_M& tableInfo, const AuxLobbyTableDataPtr& table);

	static bool isMultiLoginSessionHost(UINT16 hostId)
	{
		return isGgnHost(hostId);
	}
};
#endif
