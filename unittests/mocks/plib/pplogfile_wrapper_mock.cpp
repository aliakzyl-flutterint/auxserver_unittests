#if !defined(PKS_PLOG_WRAPPER_DISABLED)

#ifndef PTRACELVL
	#define PTRACELVL 5
#endif
#include "pplogfile_wrapper.h"
#include "logging/logger.h"

namespace plib
{
	namespace logging
	{
		PLogFileWrapper::PLogFileWrapper(const char* fileName, UINT32 flags_, const PStringEncoding*)
		{
		}

		PLogFileWrapper::~PLogFileWrapper() = default;

		void PLogFileWrapper::updateFlags(UINT32 updateMask, UINT32 newFlags)
		{
		}

		void PLogFileWrapper::vlog(const char* prefix, const char* fmt, va_list args)
		{
		}

		void PLogFileWrapper::vlog_with_level(int plog_level,
											  _In_opt_z_ const char* prefix,
											  _In_z_ _Printf_format_string_ const char* fmt,
											  va_list args)
		{
		}

		void PLogFileWrapper::dump(const char* source)
		{
		}

		void PLogFileWrapper::tags(const char* prefix)
		{
		}

		bool PLogFileWrapper::reopen()
		{
			return false;
		}

		void PLogFileWrapper::addCallBack(PLogFileBase::Callback* _callback)
		{
		}

		void PLogFileWrapper::setLevelFilter(int plog_level)
		{
		}
	} // namespace logging
}  // namespace plib

#endif // !defined(PKS_PLOG_WRAPPER_DISABLED)
