#pragma once

#include <gmock/gmock.h>
#include <string>

namespace Atf
{
	class AtfCommClientConnection;
	class AtfCommClientGConnection;
	class AtfCommClientGConnectionEx;
}

class CommClientConnection;


class MockAtfCommObjectImpl
{
public:
	MOCK_METHOD(void, connect, (const char* srvAddr, const char* srvInstance, const std::string& connType));
	MOCK_METHOD(void, reportPanopticMetrics, (const char* objectTag, const char* stationName));
	MOCK_METHOD(bool, postMessageToClientG, (unsigned connId, unsigned reqId));
};

extern MockAtfCommObjectImpl* mockAtfCommObjectImpl;
