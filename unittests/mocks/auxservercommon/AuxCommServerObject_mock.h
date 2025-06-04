#ifndef AuxCommServerObject_mock_h__
#define AuxCommServerObject_mock_h__

#include "../atf/AtfCommServerObject_mock.h"
#include "../../../atf/AtfTraceLog.h"
#include "../../../atf/AtfCommPlayerConns.h"
#include "../../../atf/AtfServerPublisher.h"
#include "../atf/TimerServer_mock.h"
#include "../../../atf/AtfUtility.h"
#include "../../../atf/PerformanceCounter.h"
#include "../../../atf/AtfPropertyPublisher.h"
#include "StatusCheckServer_mock.h"
#include "../../../auxiliary/auxservercommon/AuxTableAlertReporter.h"
#include "../../../auxiliary/auxservercommon/auxconfigcommon.h"
#include "../../../auxiliary/auxprotocols/LobbyServerProtocols.h"
#include "../../../protocols/srvutils/ServerStartParams.h"
#include "../../../protocols/esl/EslResolver.h"
#include "../../../auxiliary/auxcommon/auxgenerictypes.h"
#include "admincommon.h"
#include <typeinfo>
#include <unordered_set>
#include "../../../auxiliary/auxcommon/reefmsgformat.h"
#include <gmock/gmock.h>

#define TRUSTED_ADMIN_CONNTYPE "trustedAdmin"

#define ESL_CUSTOM_PARAM_BYPROXY "byProxy"
#define ESL_CUSTOM_PARAM_ZONE "zoneConfig"

constexpr const char* AUX_ZONE_NAME_ZONE_PS = "Zone0";
constexpr const char* AUX_ZONE_NAME_ZONE_SHARED = "ZoneS";
constexpr const char* AUX_ZONE_NAME_ZONE_EXTERNAL = "ZoneExt";
constexpr const char* AUX_ZONE_NAME_ZONE_OLAP = "ZoneOLAP";

#define TABLE_ALERT_ATF_FIRST_PARSE_ALERT		"Atf_1_parse"
#define TABLE_ALERT_PAYOUT_EXCEEDS_LIMIT		"Payout_Exceeds_Limit"
#define TABLE_ALERT_ATF_VALIDATION				"AtfValidation"
#define TABLE_ALERT_MAX_EXPOSURE				"MaxExposure"
#define TABLE_ALERT_JAVA_GDK					"JavaGDK"
#define TABLE_ALERT_LOGOUT_XC_ERROR				"Logout_XC_Error"
#define TABLE_ALERT_LOGOUT_VENDOR_ERROR			"Logout_Vendor_Error"
#define TABLE_ALERT_LOGOUT_GAMELOADER_TIMEOUT	"Logout_GameLoader_Timeout"
#define TABLE_ALERT_PT_EMPTY_HANDDETAILS		"PT_Empty_HandDetails"
#define TABLE_ALERT_JP_WITHDRAW_ERROR			"JP_Withdraw_Error"
#define TABLE_ALERT_EXCEEDS_HANDPAYOUTCAP		"Exceed_HandPayoutCap"
#define TABLE_ALERT_RNG_VERSION_ERROR			"RNG_Version_Error"
#define TABLE_ALERT_VENDOR_RETRANSMISSION		"Vendor_Retransmission"
#define TABLE_ALERT_PLAYER_DISCONNECTION		"Player_Disconnection"
#define TABLE_ALERT_UNPROCESSED_PAYOUT		    "PayoutWasNotProcessed"

#define DEFAULT_ENTROPY_BLOCKS_KEEP 1000	// Max length of entropy queue
#define DEFAULT_ENTROPY_BLOCKS_SEND 0		// Entropy blocks to send (0=all)

#define MAX_PT_HAND_DETAILS_MESSAGE_LEN	4000
#define PT_HAND_DETAILS_BET_CANCELLED	"na"

#define SHUTDOWN_TIMER_MSG_ID				999
#define DEFAULT_SHUTDOWN_TIMEOUT_IN_SEC		5

#define MAX_LEGACY_GAME_DISABLE_RULE_ID 10000

//typedef Atf::AtfCommClientConnection AuxCommClientConnection;
//typedef Atf::AtfCommClientGConnection AuxCommClientGConnection;
typedef Atf::AtfCommPlayerOrCipwaConnectionFactory AuxPlayerOrCipwaConnectionFactory;
typedef Atf::AtfCommPlayerOrCipwaConnection AuxPlayerOrCipwaConnection;
typedef Atf::AtfCommServerConnection AuxCommServerConnection;
typedef Atf::AtfCommServerPublisher AuxCommServerPublisher;
typedef Atf::AtfPropertyPublisher AuxPropertyPublisher;
typedef Atf::PerformanceCounter AuxPerformanceCounter;
typedef Atf::OlapServerReporter AuxOlapServerReporter;
typedef Atf::TimerServer TimerServer;
typedef Atf::TimerHandler TimerHandler;
typedef Atf::AtfUtil AuxTool;

class AuxServerCommonImpl;
struct MsgAuthRedirectorToGateway;


class AuxCommClientConnection : public Atf::AtfCommClientConnection
{
public:
	AuxCommClientConnection(Atf::AtfCommObjectImpl* obj, CommClientGuardFactory& guardFactory, const char *connTraceMarker = "" )
		: Atf::AtfCommClientConnection(obj, guardFactory, connTraceMarker )
	{
	}

	MOCK_METHOD(bool, isAuxConnected, ());
protected:
	virtual void onAuxConnected() {}
	virtual void onAuxConnectedWithInfo(CommMsgBody* infoBody) {}
	virtual bool onAuxClosedOrDisconnected(int errCode, const char* errMsg) {}
	virtual bool onAuxClosedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) {}
};

class AuxCommClientGConnection : public Atf::AtfCommClientGConnection
{
public:
	AuxCommClientGConnection(Atf::AtfCommObjectImpl* obj, CommClientGuardFactory& guardFactory, const char *connTraceMarker = "" )
		: Atf::AtfCommClientGConnection(obj, guardFactory, connTraceMarker )
	{
	}

	MOCK_METHOD(bool, isAuxConnected, ()); 
protected:
	virtual void onAuxConnected() {}
	virtual bool onAuxClosedOrDisconnected(int errCode, const char* errMsg) {}
	virtual bool onAuxClosedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) {}
};


class AuxGConnWithoutUnsolicitedMsg : public Atf::AtfGConnWithoutUnsolicitedMsg
{
public:
	AuxGConnWithoutUnsolicitedMsg(Atf::AtfCommObjectImpl* obj, CommClientGuardFactory& guardFactory, const char *connTraceMarker = "" )
	: Atf::AtfGConnWithoutUnsolicitedMsg(obj, guardFactory, connTraceMarker )
	{
	}

	MOCK_METHOD(bool, isAuxConnected, (), (const));

	typedef std::function<void(bool)> StatusChangeCallback;
	MOCK_METHOD(void, listenEstablishStatus_impl, (const StatusChangeCallback& callback, bool includeCurrentStatus));
	void listenEstablishStatus(const StatusChangeCallback& callback, bool includeCurrentStatus = false)
	{
		return listenEstablishStatus_impl(callback, includeCurrentStatus);
	}
protected:
	virtual void onAuxConnected() {}
	virtual bool onAuxClosedOrDisconnected(int errCode, const char* errMsg) {}
	virtual bool onAuxClosedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) {}
};

class AuxCallbackableServerConn : public AuxCommServerConnection
{
public:
	typedef std::function<void(UINT32 requestId, UINT32 msgId, const CommMsgBody& body)> ReplyCall;
	typedef std::function<void(UINT32 requestId, UINT32 error, const char* errStr )> ErrorCall;
	enum ErrorCode
	{
		EC_DISCONNECTED,
		EC_TIMEOUT,
		EC_EXCEPTION,
		EC_UNUSED,
		EC_LAST = EC_UNUSED - 1
	};
protected:
	UINT32 timerId=0;
	INT32 timeout=0;
	UINT32 sn=0;
	typedef std::map<UINT32, std::tuple<time_t, ReplyCall, ErrorCall> > PendingRequests;
	PendingRequests pendingRequests;

	MOCK_METHOD(void, checkPendingRequests, ());

public:
	~AuxCallbackableServerConn() {}

	MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
	MOCK_METHOD(void, cancelWithError, (UINT32 msgSn, UINT32 errCode, const char* errStr));
	MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
	MOCK_METHOD(UINT32, postMsg_impl, (const Atf::MessageProtocol& msg, ReplyCall reply, ErrorCall error, bool trace));
	UINT32 postMsg(const Atf::MessageProtocol& msg, ReplyCall reply, ErrorCall error=ErrorCall(), bool trace = true)
	{
		return postMsg_impl(msg, reply, error, trace);
	}
	MOCK_METHOD(void, setTimeoutInSec, (INT32 timeoutInSec));
	MOCK_METHOD(INT32, getTimeoutInSec, (), (const));
};

class AuxCommServerAdminConnFactory final : public CommServerConnectionFactory
{
protected:
	AuxServerCommonImpl* obj = nullptr;
public:
	AuxCommServerAdminConnFactory( CommServerGuardFactory& guardFactory )
		: CommServerConnectionFactory(guardFactory)
	{
	}
	MOCK_METHOD(void, init, (AuxServerCommonImpl* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};


class AuxCommServerAdminConn final : public AuxCommServerConnection
{
public:
	AuxCommServerAdminConn(AuxServerCommonImpl* obj_) : Atf::AtfCommServerConnection(nullptr, true, "adm") {}
	MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
};

template<typename SrvObj>
class AuxCommServerGenericConnFactory final : public CommServerConnectionFactory
{
	typedef void (SrvObj::*MsgHandler)(AuxCommServerConnection*, UINT32, const CommMsgBody&);
protected:
	SrvObj* obj = nullptr;
public:
	AuxCommServerGenericConnFactory(CommServerGuardFactory& guardFactory)
		: CommServerConnectionFactory(guardFactory)
	{
	}
	MOCK_METHOD(void, init, (SrvObj* obj_));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
	MOCK_METHOD(void, regist, (const char* name, MsgHandler handler_));
};

class AuxCommServerPnpConnFactory : public CommServerConnectionFactory
{
public:
	typedef std::function<void(AuxCommServerConnection*)> HConnected;
	typedef std::function<void(AuxCommServerConnection*, int, const char*)> HDisconnected;
	typedef std::function<void(AuxCommServerConnection*, UINT32, const CommMsgBody&)> HProcessMessage;
	struct ConnHandler
	{
		HConnected hConnected;
		HDisconnected hDisconnected;
		HProcessMessage hProcessMessage;
	} connHandler;
public:
	AuxCommServerPnpConnFactory( CommServerGuardFactory& guardFactory, Atf::AtfCommObjectImpl* obj_, bool isPeerGConnection_=true, const char *connTraceMarker_ = "")
		: CommServerConnectionFactory( guardFactory )
	{
	}
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

template<typename TSvrObj>
class AuxGenericServerObjFactory : public CommServerObjectFactory
{
public:
	MOCK_METHOD(CommServerObject*, createServerObject, (_CommInterface& inter), (const));
};

class AuxGenericConnFactory : public CommServerConnectionFactory
{
public:
	typedef std::function<CommServerConnection*()> Generator;
public:
	AuxGenericConnFactory(CommServerGuardFactory& guardFactory)
		: CommServerConnectionFactory(guardFactory)
	{
	}

	MOCK_METHOD(void, setGenerator, (const Generator& gen));
	MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
};

struct AuxZoneConfig
{
	struct ZoneSettings {
		std::map < std::string, std::unordered_set<aux::BackOffice>> zone2BOs; //zone to backoffices
		auxcfg::Required<std::string> selfZone;
		void load(const auxcfg::IniSection& section);
	} zoneSettings;

	std::map<std::string, std::string> sn2zsn;

	MOCK_METHOD(void, load, (const PIniFile& ini));

	static std::shared_ptr<AuxZoneConfig> load(const ServerStartParams& serverStartParams)
	{
		std::shared_ptr<AuxZoneConfig> zoneConfig;
		return zoneConfig;
	}

	MOCK_METHOD(const std::unordered_set<aux::BackOffice>&, getServingBackoffice, (), (const));
};

class AuxEslResolver
{
public:
	MOCK_METHOD(bool, init, (const ServerStartParams& serverStartParams));
	using ServiceMap_t = std::map<std::string, std::string>;
	MOCK_METHOD(void, setZoneSetting, (const char* selfZone, const ServiceMap_t& serviceMapping));

	MOCK_METHOD(bool, resolveService_impl, (const char* serviceName, PString& addr, PString& inst, const char* targetZone), (const));
	bool resolveService(const char* serviceName, PString& addr, PString& inst, const char* targetZone=nullptr) const
	{
		return resolveService_impl(serviceName, addr, inst, targetZone);
	}
	/*template<typename TA, typename TI>
	bool resolveService(const char* serviceName, TA& address, TI& instance, const char* targetZone=nullptr) const
	{
		return false;
	}*/

	MOCK_METHOD(bool, resolveDatabase, (PString & connStr, const char * const dbName), (const));

	/*static std::string getPrefixByTargetZone(const char* targetZone, const char* selfZone)
	{
		return "";
	}*/

public:
	std::string selfZone;
};

class AuxServlet
{
protected:
	AuxServerCommonImpl* si;
public:
	AuxServlet(AuxServerCommonImpl* serverObj) :si(serverObj) {}
	virtual ~AuxServlet(){}
	virtual void preloadStaticConfig(const PIniFile& ini, const AuxEslResolver* esl) {}
	virtual void preloadDynamicConfig(const PIniFile& ini, const AuxEslResolver* esl) {}
	virtual void init() {}
	virtual void applyDynamicConfig(bool rereadIni = false) {}
	virtual void start() {}
	virtual void stop() {}
};

class AuxCommPerformanceCounter : public Atf::PerformanceCounter
{
public:
	AuxCommPerformanceCounter() {}
	MOCK_METHOD(void, init, (AuxServerCommonImpl* commObject_));
public:
	MOCK_METHOD(void, reset, (), (override));
	MOCK_METHOD(void, getPerformanceData, (std::vector<PNameValue>& data), (override));
};

class AuxTableAlertReporter;
class AuxServerCommonImpl
{
public:
	AuxServerCommonImpl(Atf::AtfCommObjectImpl* obj_) {}
	virtual ~AuxServerCommonImpl() {}
	
	MOCK_METHOD(Atf::AtfCommObjectImpl*, getAtfCommObjectImpl, (), (const));
	MOCK_METHOD(CommClientConnectionPool*, getClientPool, ());

	MOCK_METHOD(void, registerAdminConnectionFactory, ());
	MOCK_METHOD(void, registerTableAlertReporter, (Atf::AtfCommObjectImpl* serverObj, UINT64 tableId, const PString& address, const PString& instance));
	MOCK_METHOD(void, sendTableAlert_impl, (const PString& key, const PString& data, const PString& details, bool urgent, bool log));
	void sendTableAlert(const PString& key, const PString& data, const PString& details, bool urgent = false, bool log = true)
	{
		return sendTableAlert_impl(key, data, details, urgent, log);
	}

	MOCK_METHOD(const PString&, getInitPath, (), (const));
	MOCK_METHOD(const PString&, getMyId, (), (const));
	MOCK_METHOD(void, setMyIdDefault, (const char* myId));
	MOCK_METHOD(bool, setLogLevel, (const char* level));
	MOCK_METHOD(const char*, getLogLevel, (), (const));
	MOCK_METHOD((std::tuple<UINT16, PString>), rereadIni, ());

protected:
	MOCK_METHOD(void, enableTrustedConn, ());
	typedef std::function<void(AuxCommServerConnection*, UINT32, const CommMsgBody&)> TrustedMsgHandler;
	/*template<size_t N>
	void registerTrustedMessage(UINT32 msgId, TrustedMsgHandler handler, const char* const (&rightRequired)[N])
	{
	}*/

	MOCK_METHOD(void, processAdminMessage, (AuxCommServerConnection* conn, UINT32 msgId, const CommMsgBody& body));
	StatusServer statusServer;

protected:
	MOCK_METHOD(void, processKillItself, (AuxCommServerConnection* conn, UINT32 requestId, const CommMsgBody& body));
	MOCK_METHOD(void, processRereadIni, (AuxCommServerConnection* conn, UINT32 requestId, const CommMsgBody& body));
	MOCK_METHOD(void, processUnregisteredTrustedAdminMsg, (AuxCommServerConnection* conn, UINT32 requestId, UINT32 msgId));
	//std::map<UINT32, std::pair<std::list<std::string>, TrustedMsgHandler> > trustedMsgs;
	//MsgAuthRedirectorToGateway* origTrustedAdminMsg = nullptr;

	//AuxCommPerformanceCounter commPerformanceCounter;
public:
	/*template<typename T>
	void dependOn()//bool required=true// by now, optional dependency is not supported
	{
	}

	template<typename T, typename T1, typename ...Args>
	void dependOn()
	{
	}

	template<typename T>
	T* getServlet()
	{
		return nullptr;
	}*/
protected:
	MOCK_METHOD(void, servletsPreloadConfig, (const PIniFile& ini, const AuxEslResolver* esl));

	MOCK_METHOD(void, servletsInit, ());
	MOCK_METHOD(void, servletsApplyDynamicConfig, ());
	MOCK_METHOD(void, servletsStart, ());

protected:
	virtual void preloadStaticConfig(const PIniFile& ini, const AuxEslResolver* esl) {}
	virtual void preloadDynamicConfig(const PIniFile& ini, const AuxEslResolver* esl) {}
	virtual void init() {}
	MOCK_METHOD(void, applyDynamicConfig_impl, (bool rereadIni));
	virtual void applyDynamicConfig(bool rereadIni = false)
	{
		return applyDynamicConfig_impl(rereadIni);
	}

	MOCK_METHOD(void, dynamicInit, ());
	MOCK_METHOD(void, init, (const CommMsgBody& msg));
	MOCK_METHOD(const ServerStartParams&, getStartParams, (), (const));
	MOCK_METHOD(const AuxZoneConfig*, getZoneConfig, (), (const));
	MOCK_METHOD(bool, isByProxy, (), (const));
	MOCK_METHOD(UINT32, getIdAssignedByProxy, (), (const));


	PString configFileName;
	PString configFilePath;
};

template <typename TServlet>
class ServletHandler
{
	AuxServerCommonImpl* si = nullptr;
public:
	ServletHandler() :si(nullptr) {}
	ServletHandler(AuxServerCommonImpl* si) :si(si) {}
	TServlet* operator->() const noexcept
	{
		return si->getServlet<TServlet>();
	}
	TServlet& operator*() const noexcept
	{
		return *si->getServlet<TServlet>();
	}
	TServlet* getServlet() const noexcept
	{
		return si->getServlet<TServlet>();
	}
};

#define ENABLE_SERVLET(svrObj, servletClass) (svrObj->dependOn<servletClass>(), ServletHandler<servletClass>(svrObj))

#define REGISTER_TRUSTEDMESSAGE(msgId, handler, ...) {\
	const char* rights[] = __VA_ARGS__;\
	registerTrustedMessage(msgId, [this](AuxCommServerConnection* conn, UINT32 reqId, const CommMsgBody& body){\
		this->handler(conn, reqId, body);\
	}, rights);}

#define UNWRAP_DIR_AND_LOGSTATION(msgBody) const char* initDir_; PString logStationNameFromDispatcher;\
	{CommMsgParser parser(msgBody);\
	parser.parseString(initDir_);\
	if(!parser.parseEnded()) {\
		parser.parseStringP(logStationNameFromDispatcher);\
		PLog("logger station name [%s] is provided at startup and will override correspondent logger's INI property", logStationNameFromDispatcher.c_str());\
	}}

class AuxCommServerObject : public Atf::AtfCommServerObject, public AuxServerCommonImpl
{
public:
	AuxCommServerObject(_CommInterface& i)
		: AtfCommServerObject(i)
		, AuxServerCommonImpl(this)
	{}

public:
	MOCK_METHOD(void, registerPerformanceCounterAndStatusServer_impl, (const PString &iniFileName, Atf::PerformanceCounter *counter, INT32 reportIntervalInSec, Atf::OlapServerReporter* olapServerReporter, const char* logStationNameFromDispatcher, const char *atfMsgTickerMonitoringNamePrefix));
	void registerPerformanceCounterAndStatusServer (const PString &iniFileName, Atf::PerformanceCounter *counter, INT32 reportIntervalInSec = 0, Atf::OlapServerReporter* olapServerReporter = 0, const char* logStationNameFromDispatcher = 0, const char *atfMsgTickerMonitoringNamePrefix = "")
	{
		return registerPerformanceCounterAndStatusServer_impl(iniFileName, counter, reportIntervalInSec, olapServerReporter, logStationNameFromDispatcher, atfMsgTickerMonitoringNamePrefix);
	}
	MOCK_METHOD(void, registerPerformanceCounterAndStatusServer_impl, (Atf::PerformanceCounter *counter, INT32 reportIntervalInSec));
	void registerPerformanceCounterAndStatusServer (Atf::PerformanceCounter *counter, INT32 reportIntervalInSec = 0)
	{
		return registerPerformanceCounterAndStatusServer_impl(counter, reportIntervalInSec);
	}
	MOCK_METHOD(void, init, (CommMsgBody& msg));
	MOCK_METHOD(void, processKillItself, (AuxCommServerConnection* conn, UINT32 requestId, const CommMsgBody& msg));
	MOCK_METHOD(CommClientConnectionPool*, getClientPool, ());
	MOCK_METHOD(bool, isPanLoggerInitOK, ());
	MOCK_METHOD(PanopticLogger&, getPanopticLogger, ());
protected:
	virtual bool isReadyToShutdown() { return false; }

	MOCK_METHOD(void, setShutdownInProgress, (bool value));
	MOCK_METHOD(bool, isShutdownInProgress, ());
	MOCK_METHOD(bool, isReadyToShutdownByServiceCount, ()); 

	MOCK_METHOD(void, setShutdownTimeout, (int timeout));
	MOCK_METHOD(int, getShutdownTimeout, ());
};

class ReplyIgnoredAsyncCall : public CommClientGConnection::AsyncCall
{
public:
	MOCK_METHOD(void, processReply, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body));
};

class PnPAsyncCall : public CommClientGConnection::AsyncCall
{
public:
	typedef std::function<void(const CommMsgBody&)> ReplyHandler;
	typedef std::function<void(UINT32 reqId, UINT32 msgId, const CommMsgBody&)> ReplyHandlerFull;
	PnPAsyncCall(const ReplyHandler& handler_) : CommClientGConnection::AsyncCall()
	{
	}
	PnPAsyncCall(const ReplyHandlerFull& hFull) : CommClientGConnection::AsyncCall()
	{
	}

	MOCK_METHOD(void, processReply, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body));
};

template<class T>
class TableLobbyGConn : public AuxCommClientGConnection
{
	enum ConnectionStatusType
	{
		DISCONNECTED,
		CONNECTING,
		CONNECTED
	};
public:
	TableLobbyGConn(T* obj, CommClientGuardFactory& guardFactory, const char *traceMarker = "" )
		: AuxCommClientGConnection(obj, guardFactory, traceMarker)
	{}
	MOCK_METHOD(void, processGMessage, (UINT32 reqId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call), (override));
	MOCK_METHOD(void, onAuxConnected, (), (override));
	MOCK_METHOD(bool, onAuxClosedOrDisconnected, (int errCode, const char* errMsg), (override));
	MOCK_METHOD(bool, isLobbyConnected, (), (const));
	MOCK_METHOD(bool, isLobbyDisconnected, (), (const));
	MOCK_METHOD(bool, isLobbyConnecting, (), (const));
	MOCK_METHOD(ConnectionStatusType, connectStatus, ());
	MOCK_METHOD(void, setConnectStatusToConnecting, ());
	MOCK_METHOD(void, setLobbyServerInfo, (PString& lobbyAddress, PString& lobbyInstance));
	MOCK_METHOD(void, setTableId, (UINT64 tableId));
	MOCK_METHOD(void, connectToLobbyServer, ());
	MOCK_METHOD(int, getConnectingDuration, (), (const)); 
};

#ifdef _DEBUG
	#define DEBUG_TRACE_FLAG true
	#define PARSE_PROTO_MSG_EX(protObj, body) PARSE_PROTO_MSG(protObj, body)
	#define PARSE_PROTO_STRUCT_EX(structObj, parser)  PARSE_PROTO_STRUCT(structObj, parser)
	#define debugPLog(x) myPLog(x)
	#define debugPLog2(x,y1) myPLog(x,y1)
	#define debugPLog3(x,y1,y2) myPLog(x,y1,y2)
	#define debugPLog4(x,y1,y2,y3) myPLog(x,y1,y2,y3)
	#define debugPLog5(x,y1,y2,y3,y4) myPLog(x,y1,y2,y3,y4)
	#define debugPLog6(x,y1,y2,y3,y4,y5) myPLog(x,y1,y2,y3,y4,y5)
	#define debugMyPLogInBound(x) myPLogInBound(x)
	#define debugMyPLogOutBound(x) myPLogOutBound(x)
#else
	#define DEBUG_TRACE_FLAG false
	#define PARSE_PROTO_MSG_EX(protObj, body) do { protObj.parseMessage(body); } while(0)
	#define PARSE_PROTO_STRUCT_EX(structObj, parser)   do { structObj.parseMsg(parser); } while(0)
	#define debugPLog(x) 
	#define debugPLog2(x,y1)
	#define debugPLog3(x,y1,y2)
	#define debugPLog4(x,y1,y2,y3)
	#define debugPLog5(x,y1,y2,y3,y4)
	#define debugPLog6(x,y1,y2,y3,y4,y5)
	#define debugMyPLogInBound(x)
	#define debugMyPLogOutBound(x)
#endif

#endif
