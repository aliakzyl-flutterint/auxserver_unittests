#ifndef StatusCheckServerConn_mock_h_included
#define StatusCheckServerConn_mock_h_included

#include "../commlib2a/commsrv_mock.h"
#include "dbm.h"
#include "../../../atf/autopointer.h"
#include "../../../atf/PerformanceCounter.h"
#include <gmock/gmock.h>

#define INITDONE	"init_Done"	

#define CRITICAL_READY		"CRITICAL_READY"
#define CRITICAL_NOT_READY	"CRITICAL_NOT_READY"

////////////////////////////////////////////////////////////////////////////////

class CriticalBase
{
public:
	enum CRITICAL_COMPONENT_TYPE
	{
		CRITICAL_COMPONENT_TYPE_UNKNOWN = 0,
		CRITICAL_COMPONENT_TYPE_GCONNECTION = 1,
	};
public:
	CriticalBase(PString name_, CRITICAL_COMPONENT_TYPE type_ = CRITICAL_COMPONENT_TYPE_UNKNOWN):
		name(name_), 
		type(type_),
		status(CRITICAL_NOT_READY)
	{
	} 
	virtual ~CriticalBase() {} 
	virtual PString getStatus() { return status; }
	virtual size_t getQueueSize() { PASSERT(false);}
	MOCK_METHOD(void, setStatus, (PString status_));

public:
	const PString name;
	const CRITICAL_COMPONENT_TYPE type;
protected:
	PString status;
};

typedef Atf::SharedPointer<CriticalBase> CriticalPtr;

template<class T>
class CriticalConn : public CriticalBase
{
public:
	CriticalConn<T>(PString name_, T& conn_, CRITICAL_COMPONENT_TYPE type_ = CRITICAL_COMPONENT_TYPE_UNKNOWN):
		CriticalBase(name_, type_)
	{
	}
	MOCK_METHOD(PString, getStatus, (), (override));
	MOCK_METHOD(size_t, getQueueSize, (), (override));
};

class StatusServer;

class StatusServerPerformanceCounter : public Atf::PerformanceCounter
{
public:
	StatusServerPerformanceCounter();
	MOCK_METHOD(void, init, (StatusServer* statusServer_));
public:
	MOCK_METHOD(void, reset, (), (override));
	MOCK_METHOD(void, getPerformanceData, (std::vector<PNameValue>& data), (override));
};

class StatusServer
{
	friend class StatusServerPerformanceCounter;

	class StatusCheckServerConnection : public CommServerConnection
	{
	public:
		StatusCheckServerConnection(StatusServer* obj_) {}

		MOCK_METHOD(void, connected, (), (override));
		MOCK_METHOD(void, closedOrDisconnected, (int errCode, const char* errMsg), (override));
		MOCK_METHOD(void, processMessage, (UINT32 msgId, const CommMsgBody& body), (override));
	};

	class StatusCheckServerConnFactory : public CommServerConnectionFactory
	{
	public:
		StatusCheckServerConnFactory(CommServerGuardFactory& guardFactory_) 
			: CommServerConnectionFactory(guardFactory_)
		{
		}

		MOCK_METHOD(void, init, (StatusServer* obj_));
		MOCK_METHOD(CommServerConnection*, createConnection, (), (override));
	};

public:
	StatusServer() {}
	MOCK_METHOD(StatusServer&, init, (CommServerConnectionPool& srvpool));
	MOCK_METHOD(StatusServer&, addCriticalComponent, (const char* name));
	
	/*template<class T> StatusServer& addCriticalComponent(const char* name, T& conn)
	{
		bool isGConnection = (dynamic_cast<const CommClientGConnection*>(&conn) != nullptr);

		CriticalPtr cp = CriticalPtr(new CriticalConn<T>(name, conn, 
										isGConnection ? CriticalBase::CRITICAL_COMPONENT_TYPE_GCONNECTION : 
														CriticalBase::CRITICAL_COMPONENT_TYPE_UNKNOWN));

		return addCriticalComponent(cp);
	}*/
	MOCK_METHOD(StatusServer&, removeCriticalComponent, (const char* name));
	MOCK_METHOD(StatusServer&, setCriticalComponentStatus, (const char* name, const char* stauts));
};


#endif // StatusCheckServerConn_mock_h_included
