#include "ppincludebase.h"
#include "MockPpIncludeBase.h"

void PCurrentUTCTime(struct tm* tm)
{
	if (mockPpIncludeBase)
	{
		mockPpIncludeBase->PCurrentUTCTime(tm);
	}
}