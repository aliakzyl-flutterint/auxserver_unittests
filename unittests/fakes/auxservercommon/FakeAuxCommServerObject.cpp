#include "commsrv.h"

bool CommServerObject::_safeInit(CommMsgBody& body)
{
	//setConnInfoFromIniImpl(*this, body);
	init(body);
	return true;
}