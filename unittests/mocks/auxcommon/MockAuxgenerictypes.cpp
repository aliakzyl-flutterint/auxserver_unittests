#include "auxcommon/auxgenerictypes.h"

#include "auxcommon/MockAuxgenerictypes.h"

MockAuxgenerictypes* mockAuxgenerictypes = nullptr;

bool isGgnHost(UINT16 hostId)
{
	return mockAuxgenerictypes->isGgnHost(hostId);
}

PString getValueByName(std::vector<aux::P_PNameValue>& allSettings, const char* name, bool removeFoundItem, const char* defaultValue)
{
	return defaultValue;
}

static const std::vector<PString> auxsupportedCurrencies = { "GBP", "USD", "EUR", "CAD", "RON", "BGN", "DKK", "CZK", "SEK", "BRL", "NOK", "CHF" };

bool supportedCurrency(const PString& currency, UINT32 hosts /* = 0 */)
{
	return false;
}

const std::vector<PString>& supportedCurrencies(UINT32 hosts /* = 0 */)
{
	return auxsupportedCurrencies;
}

UINT16 getHostIdOfBoId(UINT16 boId)
{
	return aux::HOST_POKERSTAR;
}