#ifndef ppstacktrace_mock_h_included
#define ppstacktrace_mock_h_included

#if defined(COMM_CLIENT_ONLY)

class StackTrace
{
public:
	static void getStackTrace(char* dst, int n, void* ctx = nullptr);
	static void decodeStackTrace(const char* file);
	static bool isSupported() { return false; }
};

#elif defined(_WIN32) || defined(LINUX)

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

class StackTrace
{
#if defined(LINUX)
	using CONTEXT = struct sigcontext;
#endif
public:
	static void getStackTrace(char* dst, int n, CONTEXT* ctx = nullptr);
	static void decodeStackTrace(const char* file);
	static bool isSupported() { return false; }
};

#endif // defined(COMM_CLIENT_ONLY)

#endif // ppstacktrace_mock_h_included
