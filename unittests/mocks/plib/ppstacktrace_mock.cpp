#include "../ExcludeNonMockHeaders.h"
#include "ppstacktrace_mock.h"

#if defined(COMM_CLIENT_ONLY)
	void StackTrace::getStackTrace(char* dst, int n, void* ctx)
	{
	}
	void StackTrace::decodeStackTrace(const char* file)
	{
	}
#elif defined(_WIN32) || defined(LINUX)
	void StackTrace::getStackTrace(char* dst, int n, CONTEXT* ctx)
	{
	}
	void StackTrace::decodeStackTrace(const char* file)
	{
	}
#endif