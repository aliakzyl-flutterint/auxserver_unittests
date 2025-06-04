#include "commsrv.h"

CommServerObject::CommServerObject(_CommInterface& inter_)
{
}

CommServerObject::~CommServerObject()
{
}

ConnInfo& ConnInfo::operator=(ConnInfo&& other)
{
	return *this;
}