#include "pperror.h"
#include <iostream>
#include <cstdarg>

#include "Service.h"

PAssert::PAssert(const char* cond, const char* file, int line)
{	
	std::cout << "Assertion failed: " << cond << "\n"
		<< "File: " << file << "\n"
		<< "Line: " << line << std::endl;
}

void PLog_internal( const char* fmt, ...) noexcept
{
	std::cout << "plog message: ";
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	printf("\n");
	va_end(args);
	std::cout << std::endl;
}

// note: never call this function directly, use 'PLogWithLevel' macro instead with the same parameters
void PLogWithLevel_internal(int level, const char* fmt, ...) noexcept
{
	if (level > 0) {
		std::cout << "log level: " << level << " ";
	}
	std::cout << "log message: ";
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	printf("\n");
	va_end(args);
	std::cout << std::endl;
}


// note: never call this function directly, use 'PLogError' macro instead with the same parameters
void PLogError_internal(const char* fmt, ...) noexcept //thread-safe
{
    std::cout << "internal error: ";
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	printf("\n");
	va_end(args);
	std::cout << std::endl;
}

void myPLog_internal(const char* format, ...)
{
	std::cout << "internal message: ";
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
	std::cout << std::endl;
}

void myPLogDebug_internal(const char* format, ...) 
{
	std::cout << "internal debug message: ";
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	printf("\n");
	va_end(args);
	std::cout << std::endl;
}

void Atf::Service::myPLogInBound(const Atf::MessageProtocol& prot) const
{
	PString buff;
	prot.asTraceString(buff);
	myPLog("<< %s", buff.c_str());
}

void Atf::Service::myPLogOutBound(const Atf::MessageProtocol& prot) const
{
	PString buff;
	prot.asTraceString(buff);
	myPLog(">> %s", buff.c_str());
}
