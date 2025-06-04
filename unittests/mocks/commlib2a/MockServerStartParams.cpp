#include "ServerStartParams.h"

#include "commlib2a/MockServerStartParams.h"

using namespace pokerstars::commlib;
void ServerStartParams::parseServerStartParams(CommMsgParser& parser, const char* iniFileName_)
{
	mockServerStartParams->parseServerStartParams(this, parser, iniFileName_);
}