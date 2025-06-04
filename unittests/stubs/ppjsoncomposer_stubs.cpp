#include "ppjsoncomposer.h"
#include "pbase64.h"
#include "ppi18n_x.h"

PJSONStringComposer::PJSONStringComposer() : jsonstr(bufferInternal), empty(true), isObject(true)
{
	jsonstr.append("{}");
}

PJSONStringComposer::PJSONStringComposer(PString& buffer, bool isObject_) : jsonstr(buffer), empty(true), isObject(isObject_)
{
	if (isObject)
	{
		jsonstr.append("{}");
	}
}

void PJSONStringComposer::prepareAppend()
{
}

void PJSONStringComposer::appendName(const char *name)
{
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const char* value)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const bool value)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const char ch)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const INT32 i)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const UINT32 i)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const INT64 i)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const UINT64 i)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const PBlock& block)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const PSrvTime& value)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const PSrvDate& value)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const PUtcTime& value)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::compose(const char* name, const PUtcDate& value)
{
	return *this;
}

PJSONStringComposer & PJSONStringComposer::compose(const char* name, const PJSONStringComposer& other)
{
	return *this;
}

PJSONStringComposer & PJSONStringComposer::compose(const char* name, const vector<PJSONStringComposer>& value)
{
	return *this;
}

PJSONStringComposer& PJSONStringComposer::composeNull(const char* name)
{
	return *this;
}

/*static*/ const char * PJSONStringComposer::escapeString(const char *s, PString& out)
{

	out.append('\"');
	out.append('\"');

	return out.c_str();
}
