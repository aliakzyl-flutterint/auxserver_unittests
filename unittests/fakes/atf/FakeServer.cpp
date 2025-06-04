#include "FakeServer.h"
#include "atf/MockService.h"
#include "Service.h"

void FakeServer::addService(const std::string& serviceName, Atf::Service* service)
{
	if (!service) return;
	serviceMap[serviceName] = service;
	
}

void FakeServer::triggerOnReply(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg)
{
	auto& service = serviceMap[serviceName];
	service->directGoToNewState(2);
	service->safeProcessMessage(msgId, msg);
}

void FakeServer::triggerOnReply2(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg)
{
	auto& service = serviceMap[serviceName];
	service->directGoToNewState(3);
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
	//this->directGoToNewState(3);
	//CommMsgBody msg;
	//this->processMessage(0, msg);
	fakeServer->addService(this->serviceNameBase.c_str(), this);
	mockService->serviceStarted(this->serviceNameBase);
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