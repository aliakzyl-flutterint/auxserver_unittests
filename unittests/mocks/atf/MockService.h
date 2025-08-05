#pragma once

#include <gmock/gmock.h>
#include <string>

class MockService
{ 
public:
	MOCK_METHOD(void, serviceStarted, (const std::string& serviceName));
};

extern MockService* mockService;