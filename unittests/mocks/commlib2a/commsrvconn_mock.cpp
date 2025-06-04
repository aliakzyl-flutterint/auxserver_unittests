// This file added for getclientIP() in AtfUtility.cpp
#include "ppinclude.h"
#include "ppstring.h"
#include "pperror.h"
#include "pplogfile.h"
#include "commsrv.h"

int CommServerConnection::connPathLen() const
{
	return physAddresses.size();
}

const char* CommServerConnection::connPathPoint(int i) const
{
	PASSERT3(i >= 0 && i < physAddresses.size());
	return physAddresses[i];
}
