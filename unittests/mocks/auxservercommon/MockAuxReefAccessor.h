#pragma once

#include <gmock/gmock.h>

class AuxReefAccessor;

class MockAuxReefAccessor
{
public:
	MOCK_METHOD(void, init, (AuxReefAccessor*));
};

extern MockAuxReefAccessor* mockAuxReefAccessor;