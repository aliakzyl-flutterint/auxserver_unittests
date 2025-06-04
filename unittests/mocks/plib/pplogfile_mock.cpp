#include "ppinclude.h"
#include "pplogfile.h"


static void _logNameByDate( PString& ret, const char* baseFileName, int version, const struct tm* tm )
{
}

static void _logNameByDateLimited( PString& ret, const char* baseFileName )
{
}

static void _bakFile1( const char* fileName, const PStringEncoding* fileNameEncoding_ )
{
}

static time_t secondsSinceMidnight()
{
	return 0;
}

#if defined( NOLOCK_LOG ) && defined( PWIN32 )

static LOGFILE_T _openLogFile( const char* fileName, const char* mode, const PStringEncoding* fileNameEncoding_ )
{
	return INVALID_HANDLE_VALUE;
}

static inline LOGFILE_T _invalidLogFile()
{
	return INVALID_HANDLE_VALUE;
}

#ifdef PROTOCOL_CLIENT_ONLY
void PLogFile::_writeLogFile( LOGFILE_T f, const void* buff, size_t n )
#else
static inline void _writeLogFile( LOGFILE_T f, const void* buff, size_t n )
#endif
{
}

static inline void _closeLogFile( LOGFILE_T f )
{
}

static inline void _flushLogFile( LOGFILE_T f )
{
}

#else

static LOGFILE_T _openLogFile( const char* fileName, const char* mode, const PStringEncoding* fileNameEncoding_ )
{
	return NULL;
}

static inline LOGFILE_T _invalidLogFile()
{
	return NULL;
}

#ifdef NOLOCK_LOG
#ifdef PROTOCOL_CLIENT_ONLY
void PLogFile::_writeLogFile( LOGFILE_T f, const void* buff, size_t n )
#else
static inline void _writeLogFile( LOGFILE_T f, const void* buff, size_t n )
#endif
{
}
#endif

static void _closeLogFile( LOGFILE_T f )
{
}

static void _flushLogFile( LOGFILE_T f )
{
}

#endif

static inline bool _isValidLogFile( LOGFILE_T f )
{
	return false;
}

namespace plib
{
	namespace logging
	{
		PLogFile::PLogFile( const char* fileName, UINT32 flags_, const PStringEncoding* fileNameEncoding_)
		{
		}
		
		PLogFile::~PLogFile()
		{
		}

		void PLogFile::reopenLogFile(const char* fileName)
		{
		}

		void PLogFile::addCallBack(Callback* _callback)
		{
		}

		void PLogFile::_callCallback()
		{
		}

		void PLogFile::flush()
		{
		}

		void PLogFile::updateFlags(UINT32 updateMask, UINT32 newFlags )
		{
		}

		void PLogFile::_print(_In_z_ _Printf_format_string_ const char* fmt, ... )
		{
		}

		void PLogFile::_vprint(_In_z_ const char* prefix, _In_z_ _Printf_format_string_ const char* fmt, va_list args )
		{
		}

		void PLogFile::flushBufferedLogger()
		{
		}

		bool PLogFile::checkRotationFrequency(const tm& t)
		{
			return false;
		}

		void PLogFile::initNextLogRotationTime()
		{
		}

		void PLogFile::updateBaseFileName()
		{
		}

		bool PLogFile::checkRotate(bool printTime)
		{
			return false;
		}

		void PLogFile::disableBufferedLogging()
		{
		}


		void PLogFile::vlog( _In_opt_z_ const char* prefix, _In_z_ _Printf_format_string_ const char* fmt, va_list args )
		{
		}

		void PLogFile::dump( _In_z_ const char* s )
		{
		}

		void PLogFile::tags(_In_z_ const char* prefix)
		{
		}


		bool PLogFile::reopen()
		{
			return false;
		}
	} // namespace logging
} // namespace plib

//****************************************************************************

static PLogFileBase* _logFile = 0;
thread_local PLogFileBase* _threadLogFile = 0;

inline PLogFileBase* getLogFile()
{
	return nullptr;
}

bool PLogIsInit() noexcept
{
	return false;
}

const char * PLogGetFileName() noexcept
{
	return "";
}
bool PLogReopen() noexcept
{
	return false;
}
void PLogCheckRotate() noexcept
{
}


#ifdef PWIN32//you can name it a win32 hack :-)
#ifndef NDEBUG

static int _ourReportingFunction( int reportType, char *userMessage, int *retVal )
{
	return 0;
}

#endif
#endif

/// @brief Represents an error callback which writes caught error message to a log file
class _PLogErrorCallback : public PError::Callback
{
public:
	void error( const char* msg ) override
	{
	}
};

#ifdef PWIN32
#ifndef PWIN64
extern "C" int __active_heap;
#endif
// Doesn't exist in VS2017 runtime and not needed anyway
//extern "C" HANDLE _crtheap;
#endif

#ifdef PWIN32
int Plib_handle_program_memory( size_t bytes )
{
	return 0;
}

#if !defined(COMM_CLIENT_ONLY) && !defined(PPYCL)
void initSigHandlers()
{
}
#endif
#endif

void PLogInit( PLogFileBase* logFile )
{
}

void PLogFree() noexcept
{
}

void PLogInitThreadLocal( PLogFileBase* logFile) noexcept
{
}

void PLogFreeThreadLocal() noexcept
{
}

void PLogUpdateFlags( UINT32 updateMask, UINT32 newFlags ) noexcept
{
}

void PLog_internal( _In_z_ _Printf_format_string_ const char* fmt, ... ) noexcept
{
}

void PLogWithLevel_internal(int level, _In_z_ _Printf_format_string_ const char* fmt, ... ) noexcept
{
}

void PLogError_internal( _In_z_ _Printf_format_string_ const char* fmt, ... ) noexcept
{
}

void PVLog( _In_z_ _Printf_format_string_ const char* fmt, va_list args ) noexcept
{
}

void PDump( _In_z_ const char* s ) noexcept
{
}

// print the current tag summary
void PLogTagSummary() noexcept
{
}

void PLogStackTrace() noexcept
{
}

void PLogSetLevelFilter(int plog_level) noexcept
{
}

void PLogSetBufferedLogFlushFrequency(UINT64 flushFreqMs) noexcept
{
}

void PLogDisableBufferedLogging() noexcept
{
}

void PVLogWithPrefix( _In_opt_z_ const char* prefix, _In_z_ _Printf_format_string_ const char* fmt, va_list args ) noexcept //thread-safe
{
}

void PLogSetCallback(PLogFile::Callback *_callBack) noexcept
{
}

// Default string representations of each log level.
static constexpr auto LEVEL_STR_CRITICAL = "critical";
static constexpr auto LEVEL_STR_ERROR = "error";
static constexpr auto LEVEL_STR_WARN = "warn";
static constexpr auto LEVEL_STR_INFO = "info";
static constexpr auto LEVEL_STR_DEBUG = "debug";
static constexpr auto LEVEL_STR_TRACE = "trace";

int PLogLevelFromString(const char *level, int default_value) noexcept
{
	if (!level)
	{
		return default_value;
	}
	if (PString::compareIgnoreCase(level, LEVEL_STR_CRITICAL) == 0 || PString::equals(level, "0"))
	{
		return PLOG_LEVEL_CRITICAL;
	}
	else if (PString::compareIgnoreCase(level, LEVEL_STR_ERROR) == 0 || PString::compareIgnoreCase(level, "err") == 0 || PString::equals(level, "1"))
	{
		return PLOG_LEVEL_ERROR;
	}
	else if (PString::compareIgnoreCase(level, LEVEL_STR_WARN) == 0 || PString::compareIgnoreCase(level, "warning") == 0 || PString::equals(level, "2"))
	{
		return PLOG_LEVEL_WARN;
	}
	else if (PString::compareIgnoreCase(level, LEVEL_STR_INFO) == 0 || PString::equals(level, "3"))
	{
		return PLOG_LEVEL_INFO;
	}
	else if (PString::compareIgnoreCase(level, LEVEL_STR_DEBUG) == 0 || PString::equals(level, "4"))
	{
		return PLOG_LEVEL_DEBUG;
	}
	else if (PString::compareIgnoreCase(level, LEVEL_STR_TRACE) == 0 || PString::equals(level, "5"))
	{
		return PLOG_LEVEL_TRACE;
	}
	return default_value;
}

const char * PLogLevelToString(int level) noexcept
{
	switch (level)
	{
		case PLOG_LEVEL_CRITICAL:
			return LEVEL_STR_CRITICAL;
		case PLOG_LEVEL_ERROR:
			return LEVEL_STR_ERROR;
		case PLOG_LEVEL_WARN:
			return LEVEL_STR_WARN;
		case PLOG_LEVEL_INFO:
			return LEVEL_STR_INFO;
		case PLOG_LEVEL_DEBUG:
			return LEVEL_STR_DEBUG;
		case PLOG_LEVEL_TRACE:
			return LEVEL_STR_TRACE;
		default:
			return "invalid";
	}
}
