#ifndef PYR_ATF_AtfCommServerObject_mock_H__
#define PYR_ATF_AtfCommServerObject_mock_H__

#include "commlib.h"
#include "UserDefStructs.h"
#include "TimerServer_mock.h"
#include "AtfDebugAltLogger.h"
#include "counters.h"
#include "PerformanceCounter.h"
#include "Panoptic/PanopticLogger.h"
#include "ppformatcheck.h"
#include "srvutils/ServerStartParams.h"
#include "telemetry/config.h" 
#include "telemetry/gateway/client.h"
#include <gmock/gmock.h>


#define ATF_PANOPTIC_METRICS


namespace Atf
{
	class Service;
	class ServiceMsgDispatcher;
	class ServiceTempBuffer;
	class ServiceCondition;
	class ServiceConditionChecker;
	class ServiceEventProcessor;
	class ServiceMonitoring;
	class SimpleServiceClazz;
	class AtfCommPlayerOrCipwaConnectionFactory;
	class AtfCommClientConnection;
	class AtfCommServerConnection;
	class AtfCommClientGConnection;
	class AtfCommClientGConnectionEx;
	class AtfCommServerPublisherInterface;
	class AtfCommServerObjectBlockingMode;
	class AtfServerReverseGConnectionFactory;
	class AtfServerGConnectionManager;
	class PerformanceCounter;
	class OlapServerReporter;
	class HeLoggerReporter;

	template<typename T>
	class TTraceIncomingMessageFromServerConnection;
	template<typename T>
	class TTraceIncomingMessageFromClientConnection;
	template<typename T>
	class TTraceConnectedMessage;
	template<typename T>
	class TTraceDisconnectedMessage;
	template<typename T>
	class TTraceGetUserAuthMessage;
	template<typename T>
	class TTraceLogoutMessage;


	class AtfCommObjectImpl : /*public CommServerObject, */public TimerHandler
	{
		friend class SimpleServiceClazz;
		friend class ServiceConditionChecker;
		friend class AtfHeLoggerReporterImpl;

	//============================================================================================================
	// constructor and destructor
	public:
		AtfCommObjectImpl(_CommInterface& i) :
				  serverPool(i),
				  clientPool(i),
				  publishPool(i)
			#ifdef _ATF_CLIENT_SUBSCRIPTION_SUPPORTED_
				  , cliSubscrPool(i)
			#endif
		{
		}
		~AtfCommObjectImpl() {}

	public:
		MOCK_METHOD(void, setCommServerObject, (CommServerObject* srvObj));
		MOCK_METHOD(CommServerObject*, getServerObject, (), (const));
	protected:
		MOCK_METHOD(void, _processMessage, (_CommMsg& msg));
		MOCK_METHOD(void, _processTimerMessage, ( UINT32 handle, UINT32 msgId, CommMsgBody& body));
		virtual bool _processExtraMessage( _CommMsg& msg ) { return false; }
	public:
		MOCK_METHOD(UINT32, _postTimerMessage, (UINT32 msgId, CommMsgBody& body, int msec, const TimerObject* timer));
		MOCK_METHOD(bool, _deleteTimerMessage, (UINT32 handle));
		MOCK_METHOD(void, _exit, ());
		MOCK_METHOD(bool, _atfexited, (), (const));
	public:
		virtual void afterIncomingMessageProcessed() {}
#ifndef _AUTOTEST_HARNESS_
	private:
#endif
		MOCK_METHOD(void, _afterMsgProcessed, ());

	protected:
		CommServerConnectionPool serverPool;
		CommClientConnectionPool clientPool;
		CommServerPublisherPool publishPool;
#ifdef _ATF_CLIENT_SUBSCRIPTION_SUPPORTED_
		CommClientSubscriberPool cliSubscrPool;
#endif
	public:
		MOCK_METHOD(CommServerConnection*, findConnectionById, (UINT32 connId));
		MOCK_METHOD(bool, isPlayerConnection, (const CommServerConnection& conn), (const));
		static bool isServerConnectionEx(const CommServerConnection& conn) { return false; }
		static bool isClientConnectionEx(const CommClientConnection& conn) { return false; }
	public:
		MOCK_METHOD(bool, postMsgToClient, (UINT32 connId, UINT32 msgId, CommMsgBody &msg));
		MOCK_METHOD(bool, postMsgToClient_impl, (UINT32 connId, const MessageProtocol& msg, bool trace));
		MOCK_METHOD(bool, postMsgToClient_impl, (UINT32 connId, UINT32 msgId, const MessageProtocol& msg, bool trace));
		MOCK_METHOD(bool, postMessageToClientG, (UINT32 connId, const UINT32 reqId, const UINT32 msgId, CommMsgBody &msg));
		MOCK_METHOD(bool, postMessageToClientG_impl, (UINT32 connId, const UINT32 reqId, const MessageProtocol& msg, bool trace));
		bool postMsgToClient(UINT32 connId, const MessageProtocol& msg, bool trace = true)
		{
			return postMsgToClient_impl(connId, msg, trace);
		}
		bool postMsgToClient(UINT32 connId, UINT32 msgId, const MessageProtocol& msg, bool trace = true)
		{
			return postMsgToClient_impl(connId, msgId, msg, trace);
		}
		bool postMessageToClientG(UINT32 connId, const UINT32 reqId, const MessageProtocol& msg, bool trace = true)
		{
			return postMessageToClientG_impl(connId, reqId, msg, trace);
		}

		MOCK_METHOD(void, registerConnectionFactory, (const char* name, CommServerConnectionFactory& factory));
		MOCK_METHOD(void, registerPlayerOrCipwaConnectionFactory_impl, (const char* name, AtfCommPlayerOrCipwaConnectionFactory& factory, bool supportCIPWA));
		void registerPlayerOrCipwaConnectionFactory (const char* name, AtfCommPlayerOrCipwaConnectionFactory& factory, bool supportCIPWA = true)
		{
			return registerPlayerOrCipwaConnectionFactory_impl(name, factory, supportCIPWA);
		}
		MOCK_METHOD(void, unregisterConnectionFactory, (const char* name));
		MOCK_METHOD(void, unregisterPlayerOrCipwaConnectionFactory, (const char* name));

		MOCK_METHOD(void, connect_impl, (AtfCommClientGConnection& conn, const char *srvAddr, const char* srvInstance, const char *connType));
		MOCK_METHOD(void, connect_impl, (AtfCommClientGConnectionEx& conn, const char *srvAddr, const char* srvInstance, const char *connType));
		MOCK_METHOD(void, connect_impl, (AtfCommClientConnection& conn, const char *srvAddr, const char* srvInstance, const char *connType));
		MOCK_METHOD(void, connect_impl, (const char *srvAddr, const char* srvInstance, const char *connType, CommClientConnection& conn, const char *logMarker));
		void connect(AtfCommClientGConnection& conn, const char *srvAddr, const char* srvInstance, const char *connType = "")
		{
			return connect_impl(conn, srvAddr, srvInstance, connType);
		}
		void connect(AtfCommClientGConnectionEx& conn, const char *srvAddr, const char* srvInstance, const char *connType = "")
		{
			return connect_impl(conn, srvAddr, srvInstance, connType);
		}
		void connect(AtfCommClientConnection& conn, const char *srvAddr, const char* srvInstance, const char *connType = "")
		{
			return connect_impl(conn, srvAddr, srvInstance, connType);
		}
		void connect(const char *srvAddr, const char* srvInstance, const char *connType, CommClientConnection& conn, const char *logMarker = "")
		{
			return connect_impl(srvAddr, srvInstance, connType, conn, logMarker);
		}
		MOCK_METHOD(void, dynamicConnect_impl, (AtfCommClientConnection& conn, const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName));
		MOCK_METHOD(void, dynamicConnect_impl, (AtfCommClientGConnection& conn, const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName));
		MOCK_METHOD(void, dynamicConnect, (const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName, CommClientConnection& conn));
		void dynamicConnect(AtfCommClientConnection& conn, const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName = "")
		{
			return dynamicConnect_impl(conn, serverAddress, serverInstanceName, serverConnType, serverConnType);
		}
		void dynamicConnect(AtfCommClientGConnection& conn, const char* serverAddress, const char* serverInstanceName, const char* serverConnType, const char* clientConnName = "")
		{
			return dynamicConnect_impl(conn, serverAddress, serverInstanceName, serverConnType, serverConnType);
		}
		
		MOCK_METHOD(void, disconnect_impl, (CommServerConnection* conn, UINT16 errCode, const char *errmsg));
		void disconnect(CommServerConnection* conn, UINT16 errCode = 0, const char *errmsg = "")
		{
			return disconnect_impl(conn, errCode, errmsg);
		}
		MOCK_METHOD(void, disconnect, (CommClientConnection& conn));

	public:
		MOCK_METHOD(void, publish_impl, (AtfCommServerPublisherInterface& publisher, const char* name, bool autoFlushUpdate, bool supportCIPWA));
		MOCK_METHOD(void, publish_impl, (CommServerPublisherPool& myPublisherPool, AtfCommServerPublisherInterface& publisher, const char* name, bool autoFlushUpdate, bool supportCIPWA));
		void publish(AtfCommServerPublisherInterface& publisher, const char* name, bool autoFlushUpdate, bool supportCIPWA = true)
		{
			return publish_impl(publisher, name, autoFlushUpdate, supportCIPWA);
		}
		void publish(CommServerPublisherPool& myPublisherPool, AtfCommServerPublisherInterface& publisher, const char* name, bool autoFlushUpdate, bool supportCIPWA = true)
		{
			return publish_impl(myPublisherPool, publisher, name, autoFlushUpdate, supportCIPWA);
		}
		MOCK_METHOD(void, unpublish, (AtfCommServerPublisherInterface& publisher));

	public:
		MOCK_METHOD(UINT32, addClientGConnectionObject, (AtfCommClientGConnection* gconn));
		MOCK_METHOD(UINT32, addClientGConnectionExObject, (AtfCommClientGConnectionEx* gconn));
		MOCK_METHOD(void, removeClientGConnectionObject, (UINT32 gConnObjId));
		MOCK_METHOD(void, removeClientGConnectionExObject, (UINT32 gConnObjId));
		MOCK_METHOD(AtfCommClientGConnection*, getClientGConnectionObject, (UINT32 gConnObjId));
		MOCK_METHOD(AtfCommClientGConnectionEx*, getClientGConnectionExObject, (UINT32 gConnExObjId));

	public:
		MOCK_METHOD(void, setMyPLogPrefix, (const char *prefix));
		MOCK_METHOD(const char*, getMyPLogPrefix, (), (const));
		MOCK_METHOD(void, setMyPLogLevel, (int newLogLevel));
		MOCK_METHOD(int, getMyPLogLevel, (), (const));

#if defined(ENABLE_PLOG_FORMAT_CHECKS)
	#undef _CHECK_PSTRING_IN_MYPLOG_
#endif

#if defined(_DEBUG) && defined(_CHECK_PSTRING_IN_MYPLOG_) && (_CHECK_PSTRING_IN_MYPLOG_ >= 1)
		void myPLog0( _In_z_ _Printf_format_string_ const char* format, ... ) const {}
		#ifndef ATF_PLOG_MACROS_ONCE
			#define	ATF_PLOG_MACROS_ONCE
			#define myPLogDebug_internal  myPLogDebug
			#define myPLogAlways_internal myPLogAlways
		#endif
#else
	#ifndef ATF_PLOG_MACROS_ONCE
		#define	ATF_PLOG_MACROS_ONCE
		#ifdef ENABLE_PLOG_FORMAT_CHECKS
			#define myPLog(format, ...)       myPLog_internal( ( true ? format : (snprintf(nullptr, 0, format, ##__VA_ARGS__), nullptr)), ##__VA_ARGS__)
			#define myPLogDebug(format, ...)  myPLogDebug_internal( ( true ? format : (snprintf(nullptr, 0, format, ##__VA_ARGS__), nullptr)), ##__VA_ARGS__)
			#define myPLogAlways(format, ...) myPLogAlways_internal( ( true ? format : (snprintf(nullptr, 0, format, ##__VA_ARGS__), nullptr)), ##__VA_ARGS__)
		#else
			#define myPLog_internal       myPLog
			#define myPLogDebug_internal  myPLogDebug
			#define myPLogAlways_internal myPLogAlways
		#endif
	#endif
		// note: never call this function directly, use 'myPLog' macro instead with the same parameters
		void myPLog_internal(_In_z_ _Printf_format_string_ const char* format, ...) const {}
#endif
		void myPLogDebug_internal (_In_z_ _Printf_format_string_ const char* format, ...) const {}
		void myPLogAlways_internal (_In_z_ _Printf_format_string_ const char* format, ...) const {}
		MOCK_METHOD(void, myPLogValist, ( _In_z_ _Printf_format_string_ const char *format, va_list args), (const));
		MOCK_METHOD(void, myPLogMsgProt, ( const MessageProtocol& prot, const char* logMarker), (const));
		MOCK_METHOD(void, myPLogInBound, ( const MessageProtocol& prot), (const));
		MOCK_METHOD(void, myPLogOutBound, ( const MessageProtocol& prot), (const));

	//============================================================================================================
	public:  
		MOCK_METHOD(Timer*, getDefaultTimer, ());
		MOCK_METHOD(void, addTimerServer, (TimerObject* timer));
		MOCK_METHOD(void, removeTimerServer, (UINT32 timerObjectId));
		MOCK_METHOD(bool, isValidTimerServer, (UINT32 timerObjectId), (const));
		virtual void onTimer(UINT32 handle, UINT32 msgId, const CommMsgBody& body) {}

	//============================================================================================================
	public:
		MOCK_METHOD(ServiceMsgDispatcher*, getMsgDispatcher, ());
		MOCK_METHOD(bool, hasMsgDispatcher, (), (const));
		MOCK_METHOD(void, unregisterServiceMsgsFromMsgDispatcher, (Service *service));

	//============================================================================================================
	public:
		MOCK_METHOD(UINT32, getNextServiceSeqId, ());
		MOCK_METHOD(UINT32, peekNextServiceSeqId, ());
		Pointer<ServiceTempBuffer> serviceTmpBuf;

	//============================================================================================================
#ifdef _AUTOTEST_RECORD_
	public:
		MOCK_METHOD(void, setMessageTimeStamp, (UINT32 msgTime));
		MOCK_METHOD(time_t getMessageTimeStamp, (), (const));
		virtual void setAutoTestRecordEnv() {}
		virtual void autoTestRecordTimerMessage(UINT32 handle, UINT32 msgId, const CommMsgBody& body) {}
#else
	public:
		MOCK_METHOD(time_t, getMessageTimeStamp, (), (const));
#endif

	//============================================================================================================
	public:
		MOCK_METHOD(void, startBlockingMode, (CommClientGConnection& conn, UINT32 replyMsgId, UINT64 otherId));
		MOCK_METHOD(bool, isRunningInBlockingMode, (), (const));
		MOCK_METHOD(UINT32, getBlockingModeCheckPoint, (), (const));

	//============================================================================================================
	public:
		MOCK_METHOD(void, monitorServiceStart, (Service* service));
		MOCK_METHOD(void, monitorServiceEnd, (Service* service, int serviceRunningTimeMSec));
		MOCK_METHOD(void, printEntireServiceList, ());
		MOCK_METHOD(bool, isServiceRunningWithName, (const char *serviceNameBase), (const));
		MOCK_METHOD(UINT32, getNumberOfRunningServices, (), (const));
		MOCK_METHOD(UINT32, getNumberOfRunsTooLongServices, (), (const));
		MOCK_METHOD(Service*, findAtfServiceByServiceId, (UINT32 serviceSeqId), (const));

	//============================================================================================================
	public:
		MOCK_METHOD(void, addCondition, (ServiceCondition* condition));
		MOCK_METHOD(bool, removeCondition, (Service* service, UINT32 conditionId));
		MOCK_METHOD(void, removeAllWaitedConditions, (Service* service));
		MOCK_METHOD(const ServiceCondition*, checkDuplicatedCondition, (ServiceCondition* condition), (const));
		MOCK_METHOD(bool, hasHigherPriorityServiceCondition, (BYTE condLevel), (const));
		MOCK_METHOD(UINT32, getNumberOfServiceConditions, (), (const));

	//============================================================================================================
	public: 
		MOCK_METHOD(ServiceEventProcessor*, getServiceEventProcessor, ());
		MOCK_METHOD(bool, hasServiceEventProcessor, (), (const));
		MOCK_METHOD(void, processServiceEvent_impl, (UINT32 eventType, const void* evt));
		void processServiceEvent(UINT32 eventType, const void* evt = NULL)
		{
			return processServiceEvent_impl(eventType, evt);
		}

	//============================================================================================================
	public:
		MOCK_METHOD(AtfServerGConnectionManager*, getAtfServerGConnectionManager, ());
		MOCK_METHOD(void, registerAtfServerGConnectionFactory, (const char* name, AtfServerReverseGConnectionFactory& factory));
		MOCK_METHOD(void, obsoleteServerGConnectionRequestNoException, (const char *connTag, UINT32 serverReqId));
		MOCK_METHOD(void, invalidServerGConnectionTag, (const char *connTag));

	//============================================================================================================
	// for HeLogger common report implementation
	protected:
		using TelemetryConfig = pokerstars::telemetry::config::Config;
		using TelemetryClient = pokerstars::telemetry::gateway::Client;

		TelemetryConfig telemetryConfig;
		TelemetryClient telemetryClient{ telemetryConfig, clientPool };

	public:
		MOCK_METHOD(void, reloadHeLoggerSettings, ());
		MOCK_METHOD(void, registerPerformanceCounter_impl, (const PString &iniFileName, PerformanceCounter *counter, INT32 reportIntervalInSec, OlapServerReporter* olapServerReporter, const char* logStationNameFromDispatcher, const char* atfMsgTickerMonitoringNamePrefix));
		MOCK_METHOD(void, registerPerformanceCounter_impl, (const ServerStartParams& params, const PString &iniFileName, PerformanceCounter *counter, INT32 reportIntervalInSec, OlapServerReporter* olapServerReporter, const char* logStationNameFromDispatcher, const char *atfMsgTickerMonitoringNamePrefix));
		MOCK_METHOD(void, registerPerformanceCounter_impl, (const char* logStationAddressFromESL, const char* logStationInstanceFromESL, const PString& iniFileName, PerformanceCounter& counter, INT32 reportIntervalInSec, OlapServerReporter* olapServerReporter, const char* atfMsgTickerMonitoringNamePrefix));
		MOCK_METHOD(void, registerPerformanceCounter_impl, (const ServerStartParams& params, const char* logStationAddressFromESL, const char* logStationInstanceFromESL, const PString& iniFileName, PerformanceCounter& counter, INT32 reportIntervalInSec, OlapServerReporter* olapServerReporter, const char* atfMsgTickerMonitoringNamePrefix));
		void registerPerformanceCounter(const PString &iniFileName, PerformanceCounter *counter, INT32 reportIntervalInSec = 0, OlapServerReporter* olapServerReporter = nullptr, const char* logStationNameFromDispatcher = nullptr, const char* atfMsgTickerMonitoringNamePrefix = "" )
		{
			return registerPerformanceCounter_impl(iniFileName, counter, reportIntervalInSec, olapServerReporter, logStationNameFromDispatcher, atfMsgTickerMonitoringNamePrefix);
		}
		void registerPerformanceCounter(const ServerStartParams& params, const PString &iniFileName, PerformanceCounter *counter, INT32 reportIntervalInSec = 0, OlapServerReporter* olapServerReporter = nullptr, const char* logStationNameFromDispatcher = nullptr, const char *atfMsgTickerMonitoringNamePrefix = "")
		{
			return registerPerformanceCounter_impl(params, iniFileName, counter, reportIntervalInSec, olapServerReporter, logStationNameFromDispatcher, atfMsgTickerMonitoringNamePrefix);
		}
		void registerPerformanceCounter(const char* logStationAddressFromESL, const char* logStationInstanceFromESL, const PString& iniFileName, PerformanceCounter& counter, INT32 reportIntervalInSec, OlapServerReporter* olapServerReporter = nullptr, const char* atfMsgTickerMonitoringNamePrefix = "")
		{
			return registerPerformanceCounter_impl(logStationAddressFromESL, logStationInstanceFromESL, iniFileName, counter, reportIntervalInSec, olapServerReporter, atfMsgTickerMonitoringNamePrefix);
		}
		void registerPerformanceCounter(const ServerStartParams& params, const char* logStationAddressFromESL, const char* logStationInstanceFromESL, const PString& iniFileName, PerformanceCounter& counter, INT32 reportIntervalInSec, OlapServerReporter* olapServerReporter = nullptr, const char* atfMsgTickerMonitoringNamePrefix = "")
		{
			return registerPerformanceCounter_impl(params, logStationAddressFromESL, logStationInstanceFromESL, iniFileName, counter, reportIntervalInSec, olapServerReporter, atfMsgTickerMonitoringNamePrefix);
		}
		MOCK_METHOD(void, addMorePerformanceCounter, (PerformanceCounter *counter));
		MOCK_METHOD(void, removePerformanceCounter, (PerformanceCounter *counter));
		MOCK_METHOD(void, setAtfPanopticLogger, (IPanopticLogger* panopticLogger, const char* objectTag));

#ifdef ATF_PANOPTIC_METRICS
	public:
		MOCK_METHOD(void, _reportPanopticMetrics, (IPanopticLogger& panopticLogger, const char* objectTag, const char* stationName));
#endif
	//============================================================================================================

	public:
		typedef TTraceLogoutMessage<AtfCommServerConnection> TraceUserLogout;
	};


#define ATFCOMMONSERVEROBJECT_WRAPPERS  \
	MOCK_METHOD(void, processMessage, (_CommMsg& msg), (override));  \
	MOCK_METHOD(void, processTimerMessage, (UINT32 handle, UINT32 msgId, CommMsgBody& body), (override));  \
	MOCK_METHOD(bool, deleteTimerMessage, (UINT32 handle));  \
	MOCK_METHOD(UINT32, postTimerMessage, (UINT32 msgId, CommMsgBody& body, int msec));  \
	MOCK_METHOD(void, exit, ());


	class AtfCommServerObject : public CommServerObject, public AtfCommObjectImpl
	{
	public:
		AtfCommServerObject(_CommInterface& i) : CommServerObject(i), AtfCommObjectImpl(i) {}
		ATFCOMMONSERVEROBJECT_WRAPPERS
	};


	class ServiceReplyWaitableOnReliableConnection : public WeakReferencable
	{
	public:
		ServiceReplyWaitableOnReliableConnection() {}
		~ServiceReplyWaitableOnReliableConnection() {}
	public:
		MOCK_METHOD(bool, processAtfServiceReplyMsg, (UINT32 msgId, const CommMsgBody& body));
		MOCK_METHOD(void, notifyServicesDisconnectEvent, ());
	public:
		MOCK_METHOD(void, registerServiceForWaitingReply, (UINT32 replyMsg, UINT32 disconNotifMsgId, Service* service));
		MOCK_METHOD(void, unregisterAllWaitingReplyMsgs, (Service* service));
	};


	class AtfCommClientConnection : public CommClientConnection, public ServiceReplyWaitableOnReliableConnection
	{
	protected:
		AtfCommObjectImpl* atfServerObj = nullptr;
	public:
		AtfCommClientConnection(AtfCommObjectImpl* obj, CommClientGuardFactory& guardFactory, const char *connTraceMarker = "") : CommClientConnection(guardFactory) {}

		MOCK_METHOD(bool, isActuallyConnected, (), (const));
		MOCK_METHOD(void, setTraceMarker, (const char *newTraceMarker));
		MOCK_METHOD(const char*, getTraceMarker, (), (const));
		MOCK_METHOD(void, post, (UINT32 msgId, CommMsgBody& body), (override));
		MOCK_METHOD(void, _clearAll, (), (override));
		virtual void connected() override {}
		virtual void postMsg(const MessageProtocol& msg, bool trace = true) {}
		virtual void traceOutgoing(UINT32 msgId) {}
		MOCK_METHOD(bool, isInAtfTraceLogContext, (), (const));
		MOCK_METHOD(void, setInAtfTraceLogContext, (bool b));
		virtual bool closedOrDisconnected(int errCode, const char* errMsg) override { return false; };
		virtual bool closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) override { return false; }
	public:
		MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
		virtual void _processMessage(UINT32 msgId, const CommMsgBody& body) {}
	protected:
		virtual void _traceConnected() {}
		virtual void _traceDisconnected(int errCode, const char* errMsg) {}

		MOCK_METHOD(void, _setActuallyConnected, (bool isConnected));
	public:
		typedef TTraceIncomingMessageFromClientConnection<AtfCommClientConnection> TraceIncomingMsg;
		typedef TTraceConnectedMessage<AtfCommClientConnection> TraceConnected;
		typedef TTraceDisconnectedMessage<AtfCommClientConnection> TraceDisconnected;
	};


	class AtfCommClientGConnection : public CommClientGConnection  
	{
	protected:
		AtfCommObjectImpl* atfServerObj = nullptr;
	public:
		AtfCommClientGConnection(AtfCommObjectImpl* obj, CommClientGuardFactory& guardFactory, const char *connTraceMarker = "") : CommClientGConnection(guardFactory) {}
		virtual ~AtfCommClientGConnection() {}

		MOCK_METHOD(UINT32, id, (), (const));
		MOCK_METHOD(UINT32, gConnObjId, (), (const));
		MOCK_METHOD(void, setTraceMarker, (const char *newTraceMarker));
		MOCK_METHOD(const char*, getTraceMarker, (), (const));
		MOCK_METHOD(UINT32, post_impl, (UINT32 msgId, CommMsgBody& body, AsyncCall* call));
		UINT32 post(UINT32 msgId, CommMsgBody& body, AsyncCall* call = 0) override
		{
			return post_impl(msgId, body, call);
		}
		virtual UINT32 postMsg(const MessageProtocol& msg, AsyncCall* call = 0, bool trace = true) { return 0; }
		virtual void traceOutgoing(UINT32 msgId, UINT32 reqId) {}
		MOCK_METHOD(bool, isInAtfTraceLogContext, (), (const));
		MOCK_METHOD(void, setInAtfTraceLogContext, (bool b));
		virtual void connected() override {}
		virtual bool closedOrDisconnected(int errCode, const char* errMsg) override { return false; }
		virtual bool closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) override { return false; }
		using CallbackFunc_t = std::function<void (UINT32 reqId, UINT32 replyMsgId, const CommMsgBody& replyMsgBody)>;
		MOCK_METHOD(UINT32, asyncSend_impl, (const MessageProtocol& msg, CallbackFunc_t callbackFunc, bool trace));
		UINT32 asyncSend(const MessageProtocol& msg, CallbackFunc_t callbackFunc, bool trace = true)
		{
			return asyncSend_impl(msg, callbackFunc, trace);
		}
	public:
		MOCK_METHOD(void, processGMessage, (UINT32 requestId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call), (override));
		virtual void _processGMessage(UINT32 requestId, UINT32 msgId, const CommMsgBody& body) {}
	protected:
		virtual void _traceConnected() {}
		virtual void _traceDisconnected(int errCode, const char* errMsg) {}
	public:
		class _AsyncCall : public CommClientGConnection::AsyncCall
		{
		public:
			_AsyncCall(std::function<void( UINT32 reqId, UINT32 replyMsgId, const CommMsgBody& replyMsgBody )> callback_ ) {}
		protected:
			~_AsyncCall() {}
		public:
			MOCK_METHOD(void, processReply, (UINT32 requestId, UINT32 msgId, const CommMsgBody& body), (override));
		};
	public:
		typedef TTraceIncomingMessageFromClientConnection<AtfCommClientGConnection> TraceIncomingMsg;
		typedef TTraceConnectedMessage<AtfCommClientGConnection> TraceConnected;
		typedef TTraceDisconnectedMessage<AtfCommClientGConnection> TraceDisconnected;
	};

	class AtfCommClientGConnectionEx : public CommClientGConnectionEx
	{
	protected:
		AtfCommObjectImpl * atfServerObj = nullptr;
	public:
		AtfCommClientGConnectionEx( AtfCommObjectImpl* obj, CommClientGuardFactory& guardFactory, const char *connTraceMarker = "", INT32 pollTimeMilliSecs = 0) : CommClientGConnectionEx(guardFactory) {}
		virtual ~AtfCommClientGConnectionEx() {}

		MOCK_METHOD(UINT32, id, (), (const));
		MOCK_METHOD(UINT32, gConnExObjId, (), (const));
		MOCK_METHOD(void, setTraceMarker, (const char *newTraceMarker));
		MOCK_METHOD(const char*, getTraceMarker, (), (const));
		MOCK_METHOD(UINT32, post_impl, (UINT32 msgId, CommMsgBody& body, AsyncCall* call));
		UINT32 post(UINT32 msgId, CommMsgBody& body, AsyncCall* call = 0) override
		{
			return post_impl(msgId, body, call);
		}
		virtual UINT32 postMsg(const MessageProtocol& msg, AsyncCall* call = 0, bool trace = true) { return 0; }
		virtual void traceOutgoing(UINT32 msgId, UINT32 reqId) {}
		MOCK_METHOD(bool, isInAtfTraceLogContext, (), (const));
		MOCK_METHOD(void, setInAtfTraceLogContext, (bool b));
		virtual void connected() override {}
		virtual bool closedOrDisconnected(int errCode, const char* errMsg) override { return false; }
		virtual bool closedOrDisconnected(int errCode, const char* errMsg, CommMsgBody* errMsgBody) override { return false; }
		using CallbackFunc_t = std::function<void(UINT32 reqId, UINT32 replyMsgId, const CommMsgBody& replyMsgBody)>;
		MOCK_METHOD(UINT32, asyncSend_impl, (const MessageProtocol& msg, CallbackFunc_t callbackFunc, bool trace));
		UINT32 asyncSend(const MessageProtocol& msg, CallbackFunc_t callbackFunc, bool trace = true)
		{
			return asyncSend(msg, callbackFunc, trace);
		}
	public:
		MOCK_METHOD(void, processGMessage, (UINT32 requestId, UINT32 msgId, const CommMsgBody& body, AsyncCall* call), (override));
		virtual void _processGMessage(UINT32 requestId, UINT32 msgId, const CommMsgBody& body) {}
	protected:
		virtual void _traceConnected() {}
		virtual void _traceDisconnected(int errCode, const char* errMsg) {}
	public:
		typedef TTraceIncomingMessageFromClientConnection<AtfCommClientGConnectionEx> TraceIncomingMsg;
		typedef TTraceConnectedMessage<AtfCommClientGConnectionEx> TraceConnected;
		typedef TTraceDisconnectedMessage<AtfCommClientGConnectionEx> TraceDisconnected;
	};

	typedef AtfCommClientGConnection AtfGConnWithoutUnsolicitedMsg;


	class AtfCommServerConnection : public CommServerConnection, public ServiceReplyWaitableOnReliableConnection
	{
	protected:
		AtfCommObjectImpl* atfServerObj = nullptr;
		bool _isPeerGConnection;
	public:
		AtfCommServerConnection(AtfCommObjectImpl* obj_, bool isPeerGConnection_, const char *connTraceMarker = "") {}
		virtual void postMsg(const MessageProtocol& msg, bool trace = true) {}
		virtual void postMsgWithId( UINT32 msgId, const MessageProtocol& msg, bool trace = true) {}
		virtual void postGMsg(UINT32 reqId, UINT32 msgId, CommMsgBody& body) {}
		virtual void postGMsg(UINT32 reqId, const MessageProtocol& msg, bool trace = true) {}
		virtual void traceOutgoing( UINT32 msgId, const CommMsgBody& body ) {}
		MOCK_METHOD(bool, isInAtfTraceLogContext, (), (const));
		MOCK_METHOD(void, setInAtfTraceLogContext, (bool b));
		virtual void connected() override {}
		virtual void closedOrDisconnected( int errCode, const char* errMsg ) override {}
	public:
		MOCK_METHOD(void, post, (UINT32 msgId, CommMsgBody& body), (override));
		MOCK_METHOD(void, setTraceMarker, (const char *newTraceMarker));
		MOCK_METHOD(const char*, getTraceMarker, (), (const));
		MOCK_METHOD(void, setUserIdForLogging, (const char *userId_));
		MOCK_METHOD(const char*, getUserIdForLogging, (), (const));
		MOCK_METHOD(bool, isPeerGConnection, (), (const));
	public:
		MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
		virtual void _processMessage(UINT32 msgId, const CommMsgBody& body) {}
	protected:
		virtual void _traceConnected() {}
		virtual void _traceDisconnected(int errCode, const char* errMsg) {}
	public:
		typedef TTraceIncomingMessageFromServerConnection<AtfCommServerConnection> TraceIncomingMsg;
		typedef TTraceConnectedMessage<AtfCommServerConnection> TraceConnected;
		typedef TTraceDisconnectedMessage<AtfCommServerConnection> TraceDisconnected;
		typedef TTraceGetUserAuthMessage<AtfCommServerConnection> TraceGetUserAuth;
		typedef TTraceLogoutMessage<AtfCommServerConnection> TraceUserLogout;
	};


	class AtfCommServerConnectionEx : public CommServerConnectionEx, public ServiceReplyWaitableOnReliableConnection
	{
	protected:
		AtfCommObjectImpl* atfServerObj;
		bool _isPeerGConnection;
	public:
		AtfCommServerConnectionEx(AtfCommObjectImpl* obj_, bool isPeerGConnection_, const char* connTraceMarker = "") {}
		virtual void postMsg( const MessageProtocol& msg, bool trace = true ) {}
		virtual void postMsgWithId( UINT32 msgId, const MessageProtocol& msg, bool trace = true ) {}
		virtual void postGMsg( UINT32 reqId, UINT32 msgId, CommMsgBody& body ) {}
		virtual void postGMsg( UINT32 reqId, const MessageProtocol& msg, bool trace = true ) {}
		virtual void traceOutgoing( UINT32 msgId, const CommMsgBody& body ) {}
		MOCK_METHOD(bool, isInAtfTraceLogContext, (), (const));
		MOCK_METHOD(void, setInAtfTraceLogContext, (bool b));
		virtual void connected() override {}
		virtual void closedOrDisconnected( int errCode, const char* errMsg ) override {}
	public:
		MOCK_METHOD(void, post, (UINT32 msgId, CommMsgBody& body), (override));
		MOCK_METHOD(void, setTraceMarker, (const char* newTraceMarker));
		MOCK_METHOD(const char*, getTraceMarker, (), (const));
		MOCK_METHOD(void, setUserIdForLogging, (const char* userId_));
		MOCK_METHOD(const char*, getUserIdForLogging, (), (const));
		MOCK_METHOD(bool, isPeerGConnection, (), (const));
	public:
		MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
		virtual void _processMessage(UINT32 msgId, const CommMsgBody& body) {}
	protected:
		virtual void _traceConnected() {}
		virtual void _traceDisconnected(int errCode, const char* errMsg) {}
	public:
		typedef TTraceIncomingMessageFromServerConnection<AtfCommServerConnectionEx> TraceIncomingMsg;
		typedef TTraceConnectedMessage<AtfCommServerConnectionEx> TraceConnected;
		typedef TTraceDisconnectedMessage<AtfCommServerConnectionEx> TraceDisconnected;
		typedef TTraceGetUserAuthMessage<AtfCommServerConnectionEx> TraceGetUserAuth;
		typedef TTraceLogoutMessage<AtfCommServerConnectionEx> TraceUserLogout;
	};


	class IgnoreReplyAsyncCall : public RefAsyncCall
	{
	public:
		IgnoreReplyAsyncCall(bool ignoreReplyContent_ = false) {}
		MOCK_METHOD(void, processReply, (UINT32 requestId, UINT32 msgId, const CommMsgBody& body), (override));
	};

};


// surprisingly, without "(body)._size()" below, PARSE_PROTO_MSG(protObj, parser) could also be compiled.
// so add (body)._size() to prevent PARSE_PROTO_MSG() from being called mistakenly with a parser object because the parser does not have _size() member function
#define PARSE_PROTO_MSG(protObj, body)   do { CommMsgParser _parser000(body); protObj.parseMsg(_parser000); PString _buff000; myPLog("<< %s%s", protObj.asTraceString(_buff000), (body)._size() ? "" :" (empty msgbody)"); } while(0)
#define PARSE_PROTO_STRUCT(structObj, parser)   do { structObj.parseMsg(parser); { PString _buff000; myPLog("<< %s", structObj.toTraceString(_buff000)); } } while(0)

// the following two macros are obsoleted, please do not use them in the new code
#define PARSE_PROTO_MSG_OBJ(protObj, body, serverObject)   do { protObj.parseMessage(body); serverObject->myPLogInBound(protObj); } while(0)   // retired! should use PARSE_PROTO_MSG
#define PARSE_PROTO_STRUCT_OBJ(structObj, parser, serverObject)   do { structObj.parseMsg(parser); { PString _buff000; serverObject->myPLog("<< %s", structObj.toTraceString(_buff000)); } } while(0)  // retired! should use PARSE_PROTO_STRUCT

// a plain json string is composed in body, this nacro is to parse this body to an atf object
#define PARSE_PROTO_MSG_FROM_MSGBODY_OF_JSON_STRING(protObj, body)   do { PString _jsonStr; CommMsgParser _parser000(body); _parser000.parseStringP(_jsonStr); protObj.loadFromJSONString(_jsonStr); myPLog("<< %s", _jsonStr.c_str()); } while(0)

#endif
