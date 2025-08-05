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

    template<typename T>
    std::unique_ptr<T> createConnection(const std::string& connName)
    {
        EXPECT_TRUE(connections.count(connName)) << "Connection factory for " << connName << " not found";
        auto factory = fakeConnection->connections[connName];
        auto conn = factory->createConnection();
        EXPECT_TRUE(conn != nullptr);
        auto* real_conn = dynamic_cast<T*>(conn);
        EXPECT_TRUE(real_conn != nullptr);
        return std::unique_ptr<T>(real_conn);
    }

    friend Atf::AtfServerReverseGConnection;
    MOCK_METHOD(void, reversePostGMsg,(const std::string& traceMarker, UINT32 reqId, const Atf::MessageProtocol& msg));
    MOCK_METHOD(void, clientPostMsg, (const std::string& msgIdStr, const Atf::MessageProtocol& msg));
    MOCK_METHOD(void, serverPostMsg, (const std::string& msgIdStr, UINT32 reqId, const Atf::MessageProtocol& msg));
};

extern FakeConnection* fakeConnection;