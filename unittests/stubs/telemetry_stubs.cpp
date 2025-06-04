#include <telemetry/config.h>
#include <telemetry/gateway/client.h>

namespace pokerstars { namespace telemetry { namespace config {
	bool Config::reload(const PIniFile& appConfig, const char* const rootSection, const Config::EslResolve& eslResolve) {
		return false;
	}
}}}

namespace pokerstars {namespace telemetry {namespace gateway {
	bool Client::init()
	{
		return false;
	}

	void Client::cleanup()
	{ }
}}}