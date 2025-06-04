#pragma once

#include <gmock/gmock.h>

class pokerstars::commlib::ServerStartParams;

class MockServerStartParams
{
public:
	MOCK_METHOD(void, parseServerStartParams, (pokerstars::commlib::ServerStartParams* serverStartParams, CommMsgParser& parser, const char* iniFileName_));
};

extern MockServerStartParams* mockServerStartParams;