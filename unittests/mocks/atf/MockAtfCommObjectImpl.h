#pragma once

#include <gmock/gmock.h>

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
	MOCK_METHOD(void, connect, (const char* srvAddr, const char* srvInstance, const char* connType));
	MOCK_METHOD(void, reportPanopticMetrics, (const char* objectTag, const char* stationName));
};

extern MockAtfCommObjectImpl* mockAtfCommObjectImpl;
