#include "auxservercommon/MockAuxReefAccessor.h"

#include "auxservercommon/AuxReefAccessor.h"

MockAuxReefAccessor* mockAuxReefAccessor = new MockAuxReefAccessor();

void AuxReefAccessor::init() {
	// This fake implementation must at least init the config object. 
	// Production code might implement more intricate initialization logic.
	this->config = std::make_unique<AuxReefAccessConfig>();
	this->config->valid = true;
	mockAuxReefAccessor->init(this);
}

void AuxStateAccessor::updateState()
{ }

void AuxStateAccessor::clearState()
{ }

/* static */CommClientNullGuardFactory AuxReefAccessor::nullGuardFactoryC;
AuxReefAccessor::AuxReefAccessor(AuxServerCommonImpl* serverObj, const char* configSection, const char* connType)
	:AuxServlet(serverObj)
	, reefConn(serverObj->getAtfCommObjectImpl(), nullGuardFactoryC)
	, configSection(configSection)
	, connType(connType)
{
}

void AuxReefAccessor::preloadDynamicConfig(const PIniFile& ini, const AuxEslResolver* esl)
{
}

void AuxReefAccessor::applyDynamicConfig(bool rereadIni)
{
}

void AuxReefAccessor::stop()
{
}

void AuxReefAccessor::processSubscribeReply(const CommMsgBody& body)
{
}

void AuxReefAccessor::processFetchReply(const CommMsgBody& body)
{
}

void AuxReefAccessor::subscribe()
{
}

void AuxReefAccessor::subscribe(const std::vector<Filter>& filters, EventHandler callback)
{ }

void AuxReefAccessor::sendEvent(const reef::ProducerHeader& header, const Atf::BigSharedMsgBody& body)
{
}

void AuxReefAccessor::sendEvent(UINT32 eventType, const Atf::BigSharedMsgBody& body)
{
}

void AuxReefAccessor::sendEvent(const Atf::MessageProtocol& evt)
{
}