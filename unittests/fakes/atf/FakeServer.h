#pragma once
#include <map>
#include <memory>
#include <string>

namespace Atf
{
	class Service;
}

class CommMsgBody;

class FakeServer
{
	using ServiceMap = std::map<std::string, Atf::Service*>;
public:
	void addService(const std::string& serviceName, Atf::Service* service);
	void sendRequest(const std::string& serviceName);
	void triggerOnReply(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg);
	void triggerOnReply2(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg);
	void triggerOnReply3(const std::string& serviceName, unsigned int msgId, const CommMsgBody& msg);
	void triggerOnExit(const std::string& serviceName);

	ServiceMap serviceMap;
};

extern FakeServer* fakeServer;