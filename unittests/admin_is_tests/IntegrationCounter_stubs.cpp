#include "integrationcounters.h"

IntegrationCounter::IntegrationCounter()
{}

IntegrationCounter::~IntegrationCounter()
{}

void IntegrationCounter::init(AuxIntegrationServerObject* serverObject_)
{}

void IntegrationCounter::addErrorsBackoffice(int hostId, UINT32 callType)
{}

void IntegrationCounter::addProcessingMsec(INT32 processingTime)
{}

void IntegrationCounter::addProcessingMsec(INT32 hostId, UINT32 callType, INT32 processingTime)
{}

void IntegrationCounter::addActiveQueueSize(INT32 activeQueueSize)
{}

void IntegrationCounter::addBackofficeProcessingMsec(INT32 hostId, UINT32 callType, INT32 processingTime)
{}

void IntegrationCounter::setNumberOfSuspendedRequests(INT32 count)
{}

void IntegrationCounter::setNumberOfActiveRequests(INT32 count)
{}

void IntegrationCounter::addErrorsISDbm()
{}

void IntegrationCounter::increaseNumberOfProcessedRequests()
{}

void IntegrationCounter::setRequestRetryCountByHost(INT32 const retryCountsByHost_[])
{}

void IntegrationCounter::setRequestsPendingInJpChannel(INT32 count)
{}

void IntegrationCounter::setNewRequestsSuspended(INT32 count)
{}

void IntegrationCounter::setGamesWithoutDkAnnotations(INT32 count)
{}

void IntegrationCounter::reset()
{}

void IntegrationCounter::getPerformanceData(std::vector<PNameValue>& data)
{}