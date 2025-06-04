#pragma once

#include <gmock/gmock.h>

class MockAuxgenerictypes
{
public:
	MOCK_METHOD(bool, isGgnHost, (unsigned int hostId));
};

extern MockAuxgenerictypes* mockAuxgenerictypes;