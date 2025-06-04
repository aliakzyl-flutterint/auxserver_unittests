#include "../../../ExcludeNonMockHeaders.h"

#include "../../commgrdnull_mock.h"
#include "telemetry/gateway/client.h"
#include "commmsgbody.h"
#include "../../commcli_mock.h"
#include <exception>
#include <memory>

namespace pokerstars {
namespace telemetry {
namespace gateway {

enum class NameCorrectness
{
    Ok,
    FirstDigit,
    UnallowedSymbols
};


static NameCorrectness checkNameCurrectness( const std::string& name )
{
    auto firstIt = name.begin();
    if( firstIt != name.end() && ::isdigit(*firstIt) ) {
        return NameCorrectness::FirstDigit;
    }
    for( const char& c : name ) {
        if( !::isalpha(c) && !::isdigit(c) && c != '_' ) {
            return NameCorrectness::UnallowedSymbols;
        }
    }
    return NameCorrectness::Ok;
}


static void checkNameCurrectness( const common::Tags& tags )
{
}

class ClientToGatewayConnection : public CommClientConnection
{
public:
    ClientToGatewayConnection( CommClientGuardFactory& guardFactory, Client& obj )
    : CommClientConnection( guardFactory)
    , m_obj( obj )
    , m_isConnected( false )
    {}

    void connected() override
    {
    }

    bool closedOrDisconnected( int errCode, const char* errMsg ) override
    {
        return false;
    }

    void processMessage( UINT32 msgId, const CommMsgBody& body ) override
    {
    }

    bool isConnected() const { return false; }

private:
    Client& m_obj;
    bool m_isConnected;
};

CommClientNullGuardFactory Client::guardFactory_;

static bool isConvertableToDouble( const char* str )
{
    if( str == nullptr ) {
        return false;
    }
    char* endptr;
    errno = 0;
    double val = std::strtod( str, &endptr );

    // Check for conversion errors
    if( errno == ERANGE || std::isnan( val ) || std::isinf( val ) ) {
        // The number is out of range for a double, or it's NAN or INFINITY
        return false;
    }
    // Check if the whole string was parsed
    if( *endptr != '\0' ) {
        // Not all of the string could be converted to a double
        return false;
    }
    return true;
}

Client::Client( const Config& config, CommClientConnectionPool& cliPool )
: config_( config )
, cliPool_( cliPool )
{}

Client::~Client()
{
}

bool Client::init()
{
	return false;
}

void Client::cleanup()
{
}

bool Client::isEnabled() const
{
    return isEnabled_ && config_.isEnabled();
}

bool Client::addMetric(const char* const name, const char* const value, const bool defaultMatch)
{
    return false;
}

bool Client::addMetric( const char* const name, const char* const value, const common::Tags& tags, const bool defaultMatch )
{
    return false;
}

void Client::post()
{
}

bool Client::addMetric(const char* const name, const char* const value, const bool defaultMatch, const common::Tags* tags)
{
    return false;
}

} // namespace gateway
} // namespace telemetry
} // namespace pokerstars
