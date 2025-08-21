#pragma once

#include <gmock/gmock.h>
#include <string>

class CommMsgBody;

class MockService
{ 
public:
	MOCK_METHOD(void, serviceStarted, (const std::string& serviceName));
	MOCK_METHOD(void, postMsgToGClient, (const std::string& serviceName, unsigned reqId, CommMsgBody& msg));
};

extern MockService* mockService;