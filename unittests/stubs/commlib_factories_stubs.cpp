#include "CommGrdNullWithInfo.h"
#include "auxcommon/CommGrdHostAuth.h"
#include "auxcommon/CommGrdAuxToken.h"
#include "commgrdnull.h"

CommServerGuard* CommServerNullWithInfoGuardFactory::createGuard(const vector< const char* >& guardNames)
{
	return nullptr;
}

CommServerGuard* CommServerHostAuthGuardFactory::createGuard(const vector< const char* >& guardNames)
{
	return nullptr;
}

CommServerGuard* CommServerAuxTokenGuardFactory::createGuard(const vector< const char* >& guardNames)
{
	return nullptr;
}

CommServerGuard* CommServerNullGuardFactory::createGuard(const vector< const char* >& guardNames)
{
	return nullptr;
}

CommServerConnectionFactory::CommServerConnectionFactory(CommServerGuardFactory& guardFactory_)
{
}

void CommServerConnectionFactory::addGuardFactory(CommServerGuardFactory& guardFactory_)
{
}

CommServerGuard* CommServerConnectionFactory::createGuard(const vector< const char* >& guardNames)
{
	return nullptr;
}

CommClientGuardAuth* CommClientNullGuardFactory::auth()
{
	return nullptr;
}

void CommClientNullGuardFactory::composeGuardNameList(CommMsgBody& msgBody) const
{
}

CommClientGuard* CommClientNullGuardFactory::createGuard(const char* guardName, CommClientGuardAuth* auth_)
{
	return nullptr;
}