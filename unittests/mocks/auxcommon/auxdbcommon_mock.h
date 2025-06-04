#ifndef _auxdbcommon_mock_h_included_
#define	_auxdbcommon_mock_h_included_

#include "../protocols/dbcommon_mock.h"
#include "dbmpropman.h"
#include <gmock/gmock.h>

#define AUX_DEFAULT_RANGE_INCREMENT_SIZE 10240
class AuxDatabaseManagerCommon : public DatabaseManagerCommon, public DbManagerTransControlInterface
{
public:
	AuxDatabaseManagerCommon() {}

	virtual INT16 execDirectStatement(const char* statement, PString& sqlErr, bool sendToOlap) { return 0; }

	MOCK_METHOD(void, setDbmId, (int dbmId_));
	MOCK_METHOD(void, setDbmIdAsProxyInstance, (int baseDbmId_, int instanceId_));

	MOCK_METHOD(bool, isProxyMode, ());

	MOCK_METHOD(UINT32, getDbmId, (), (const, override));
	MOCK_METHOD(int, getInstanceId, ());

	std::function<bool()> connectDataStorage;

	MOCK_METHOD(bool, getUtcTimeForOlap, (CommUtcTime& utcTime), (const, override));
};

class AuxDatabaseManagerHelper
{
public:
	static int loadAndForceCheckDbmId(const PIniFile& iniFile) {}
};

#endif