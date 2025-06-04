#pragma once

#include <gmock/gmock.h>
#include "ppinifile.h"
#include <string>


class MockPpIncludeBase
{
public:
	MOCK_METHOD(void, PCurrentUTCTime, (struct tm* tm), ());	
};

extern MockPpIncludeBase* mockPpIncludeBase;