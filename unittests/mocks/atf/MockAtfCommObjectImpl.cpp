#include "atf/MockAtfCommObjectImpl.h"
#include "AtfCommServerObject.h"

void Atf::AtfCommObjectImpl::connect(AtfCommClientGConnection& conn, const char* srvAddr, const char* srvInstance, const char* connType)
{
	mockAtfCommObjectImpl->connect(srvAddr, srvInstance, connType);
}

void Atf::AtfCommObjectImpl::connect(AtfCommClientGConnectionEx& conn, const char* srvAddr, const char* srvInstance, const char* connType)
{
	mockAtfCommObjectImpl->connect(srvAddr, srvInstance, connType);
}

void Atf::AtfCommObjectImpl::connect(AtfCommClientConnection& conn, const char* srvAddr, const char* srvInstance, const char* connType)
{
	mockAtfCommObjectImpl->connect(srvAddr, srvInstance, connType);
}

void Atf::AtfCommObjectImpl::connect(const char* srvAddr, const char* srvInstance, const char* connType, CommClientConnection& conn, const char* logMarker)
{
	mockAtfCommObjectImpl->connect(srvAddr, srvInstance, connType);
}

void Atf::AtfCommObjectImpl::_reportPanopticMetrics(IPanopticLogger& panopticLogger, const char* objectTag, const char* stationName)
{
	mockAtfCommObjectImpl->reportPanopticMetrics(objectTag, stationName);
}