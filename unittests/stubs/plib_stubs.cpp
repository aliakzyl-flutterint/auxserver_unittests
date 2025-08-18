#include "pperror.h"
#include "ppthread.h"
#include "ppjsonparser.h"
#include "pbase64.h"
#include "ppunistring.h"
#include "ppi18n_utf8.h"
#include "ppi18n_codepage.h"
#include "ppi18n_x.h"

/* static */ int PCriticalSection::tecsInited = 0;

PError::PError()
{
	msg = new PString();
}
PError::PError(const char* msg_, bool logError)
{
	msg = new PString(msg_);
}

PError::PError(PString&& msg_, bool logError)
{
    msg = new PString(std::move(msg_));
}

PError::PError(const PError& other)
{
	msg = new PString(other.why());
}

const char* PError::why() const
{
	return *msg;
}

PError::~PError()
{
	delete msg;
}

PParserError::PParserError(const char* msg)
{ }

PSystemError::PSystemError(const char* msg, int errCode) : m_errCode(errCode)
{
}

PSystemMemoryError::PSystemMemoryError(const char* msg, size_t numBytes)
{
}

void PUtf8String::_staticAppend(PString& s, const char* begin, const char* end)
{ }

/* static */ void PCriticalSection::_initTecs()
{
}

void Pbase64::decode(PBlock& ret, const char* s, size_t sz)
{ }

void Pbase64::encode(PString& ret, const BYTE* p, size_t sz, int lineLen, bool urlSafe)
{

}

bool PUtf8String::isValidString(const char* s, const char* end)
{
	return false;
}

void PUtf8String::staticAppend(PString& s, PUNICHAR_32 c)
{

}

PUNICHAR_RET PUtf8String::_nextChar(const char*& p, const char* endP)
{
	return 0;
}

int PUtf8String::charLength(const char* s)
{
	return 0;
}

int PStreamEncodingWin1252::_staticReadChars(PUNICHAR*& dst, PUNICHAR* dstEnd, const BYTE*& src, const BYTE* srcEnd)
{
	return 0;
}

int PStreamEncodingWin1252::_staticWriteChar(PUNICHAR_32 c)
{
	return 0;
}

int PStreamEncodingUtf8::_readChars(PUNICHAR*& dst, PUNICHAR* dstEnd, const BYTE*& src_, const BYTE* srcEnd_) const
{
	return 0;
}

int PStreamEncodingWin1252::_readChars(PUNICHAR*& dst, PUNICHAR* dstEnd, const BYTE*& src, const BYTE* srcEnd) const
{
	return 0;
}

void PStringEncodingPStringX::preparePMsg(PString& ret, const char* msg, int argc, const char* argv[]) const
{
}

void PStringEncodingPStringX::_append(PString& s, PUNICHAR_32 c) const
{ }

void PUniString::_append(PUNICHAR c)
{ }

PString& PDirectory::ensureTrailingSlash(PString& path)
{
	return path;
}