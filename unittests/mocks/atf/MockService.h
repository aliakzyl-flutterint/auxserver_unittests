#pragma once

#include <gmock/gmock.h>

class MockService
{ 
public:
	MOCK_METHOD(void, serviceStarted, (const char* serviceName));
};

extern MockService* mockService;