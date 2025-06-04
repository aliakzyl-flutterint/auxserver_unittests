#include "commmonitorlogger.h"

CommMonitorLoggerObject::CommMonitorLoggerObject(TelemetryClient client)
	: telemetryClient(client)
{}

CommMonitorLoggerObject::CommMonitorLoggerObject()
{ }

CommMonitorLoggerObject::~CommMonitorLoggerObject()
{ }

void CommMonitorLoggerObject::init(CommClientConnectionPool& cliPool, const char* strServerAddress, const char* strStationName, const UINT32 flags)
{ }

void CommMonitorLoggerObject::posted()
{}

void CommMonitorLoggerObject::processMyMessage(const UINT32 msgId, const CommMsgBody& msg)
{ }

void CommMonitorLoggerObject::connected()
{ }

void CommMonitorLoggerObject::createHeConnection()
{ }

void CommMonitorLoggerObject::compose(CommMsgBody& msg, const char* strParameterName, const char* strValue, const TelemetryTags& tags) const
{ }

void CommMonitorLoggerObject::post(CommMsgBody& msg)
{ }