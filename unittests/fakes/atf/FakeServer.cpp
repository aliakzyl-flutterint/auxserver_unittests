#include "FakeServer.h"
#include "atf/MockService.h"

#include "Service.h"

namespace
{
	enum SIMPLE_SERVICE_STATES {
		ONREPLY = 2, ONREPLY2, ONREPLY3, ONREPLY4, ONREPLY5, ONREPLY6, ONREPLY7, ONREPLY8, ONREPLY9, ONREPLY10,
		ONREPLY11, ONREPLY12, ONREPLY13, ONREPLY14, ONREPLY15, ONREPLY16, ONREPLY17, ONREPLY18, ONREPLY19, ONREPLY20,
		SIMPLE_SERVICE_STATES_NAMES_SIZE /*must be the last one*/
	};
}

void FakeServer::addService(const std::string& serviceName, Atf::Service* service)
{
	if (!service) return;
	serviceMap[serviceName] = service;
	
}

void FakeServer::sendRequest(const std::string& serviceName)
{
	auto& service = serviceMap[serviceName];
	CommMsgBody emptyMsg;
    service->directGoToNewState(Atf::BASE_SERVICE_STATES::INIT_STATE);
	service->safeProcessMessage(0, emptyMsg);
}

void FakeServer::nextStep(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg)
{
	auto& service = serviceMap[serviceName];
	service->safeProcessMessage(msgId, msg);
}

void FakeServer::triggerOnReply(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg)
{
	auto& service = serviceMap[serviceName];
	service->directGoToNewState(SIMPLE_SERVICE_STATES::ONREPLY);
	service->safeProcessMessage(msgId, msg);
}

void FakeServer::triggerOnReply2(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg)
{
	auto& service = serviceMap[serviceName];
    service->directGoToNewState(SIMPLE_SERVICE_STATES::ONREPLY2);
	service->safeProcessMessage(msgId, msg);
}

void FakeServer::triggerOnReply3(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg)
{
	auto& service = serviceMap[serviceName];
    service->directGoToNewState(SIMPLE_SERVICE_STATES::ONREPLY3);
	service->safeProcessMessage(msgId, msg);
}

void FakeServer::triggerOnExit(const std::string& serviceName)
{
	auto& service = serviceMap[serviceName];
	service->exitService();
}

Atf::SimpleServiceClazz::SimpleServiceClazz(AtfCommObjectImpl* obj, const char* serviceName)
	: Service(obj, serviceName), _thisState(UNKNOWN_STATE), _nextStateUpdated(false), _currTrueCond(NULL), _serviceConditionWaited(false)
{
}

Atf::Service::Service(AtfCommObjectImpl* obj, const char* serviceName):
	serviceNameBase(serviceName)
{
}

Atf::Service::~Service()
{
}

Atf::SimpleServiceClazz::~SimpleServiceClazz()
{
}

void Atf::Service::directGoToNewState(int newState)
{
	this->_state = newState;
}

void Atf::Service::safeProcessMessage(UINT32 msgId, const CommMsgBody& msg)
{
	this->processMessage(msgId, msg);
}

void Atf::Service::startService()
{
	fakeServer->addService(this->serviceNameBase.c_str(), this);
	mockService->serviceStarted(this->serviceNameBase.c_str());
}

UINT32 Atf::Service::startTimerMSec(UINT32 msgId, INT32 timeOutInMSec)
{
	return 0;
}

void Atf::Service::exitService()
{
	this->cleanUpWhenServiceExit();
}

void Atf::SimpleServiceClazz::cleanUpWhenServiceExit()
{
	onExit();
}

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnection& conn, UINT32 msgId, CommMsgBody& body)
{
	return conn.post(msgId, body, nullptr);
}

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnectionEx& conn, UINT32 msgId, CommMsgBody& body)  // GConnection only
{
	return conn.post(msgId, body, nullptr);
}

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnection& conn, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
	CommMsgBody body;
	msg.composeMsg(body);

	return sendMsgToServer(conn, msg.getMsgId(), body);
}

UINT32 Atf::Service::sendMsgToServer(AtfCommClientGConnectionEx& conn, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
	CommMsgBody body;
	msg.composeMsg(body);

	return sendMsgToServer(conn, msg.getMsgId(), body);
}

void Atf::Service::postMsgToGClient(UINT32 connId, UINT32 reqId, const Atf::MessageProtocol& msg, bool trace /* = true */)
{
	CommMsgBody body;
	msg.composeMsg(body);
	std::string serviceName = this->serviceNameBase.c_str();
	mockService->postMsgToGClient(serviceName, reqId, body);
}