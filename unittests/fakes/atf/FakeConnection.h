#pragma once
#include <string>
#include <gmock/gmock.h>

#include "UserDefStructs.h"

namespace Atf
{
    class AtfServerReverseGConnection;
    class AtfCommServerConnection;
    class AtfCommServerObject;
}

class CommServerConnectionFactory;

class FakeConnection
{
public:
    std::map<std::string, CommServerConnectionFactory*> connections;

    friend Atf::AtfServerReverseGConnection;
    MOCK_METHOD(void, reversePostGMsg,(const std::string& traceMarker, UINT32 reqId, const Atf::MessageProtocol& msg));
    MOCK_METHOD(void, clientPostMsg, (const std::string& msgIdStr, const Atf::MessageProtocol& msg));
    MOCK_METHOD(void, serverPostMsg, (const std::string& msgIdStr, UINT32 reqId, const Atf::MessageProtocol& msg));
};

extern FakeConnection* fakeConnection;