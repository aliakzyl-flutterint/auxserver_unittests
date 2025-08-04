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

class FakeConnection
{
    std::map<std::string, Atf::AtfCommServerConnection*> m_receivers;
public:
    friend Atf::AtfServerReverseGConnection;
    void connectServices(const std::string& senderTraceMarker, Atf::AtfCommServerConnection* receiver);
    MOCK_METHOD(void, postGMsg,(const std::string& traceMarker, UINT32 reqId, const Atf::MessageProtocol& msg));
    MOCK_METHOD(void, postMsg, (const std::string& msgIdStr, const Atf::MessageProtocol& msg));
};

extern FakeConnection* fakeConnection;