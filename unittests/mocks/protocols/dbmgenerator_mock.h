#ifndef dbmgenerator_mock_h_included
#define dbmgenerator_mock_h_included

#include "pplib.h"
#include "ppcontainer.h"
#include <gmock/gmock.h>

class	DatabaseManagerCommon;
class	SetNextIdStmt;
class	SelectAndSetNextIdStmt;
class	CallGetAndUpdateNextIdStmt; // PYR-48098
class	CallInsertIdStmt; // PYR-48098

// PYR-27418
class InsertIdRangeStmt;
class GetIdRangesStmt;
class GetCurrentIdRangesStmt;
class IdRangeClientConnection;
class CommMsgParser;

#define	OBJECT_NAME_LEN				31 ////moved from "dbm.h"

class DbmGenerator
{
public:
	struct Generator // PYR-27418
	{
		const char* objectName = nullptr;
		bool local = false;
	};
	
	class DbmGeneratorCallback // PYR-27418 - to be overriden in server object to do some tasks after generator is initialized (received all ranges)
	{
	protected:
		DbmGeneratorCallback() {}

	public:
		virtual ~DbmGeneratorCallback() {}
		virtual void process() = 0;
	};

	DbmGenerator() {}
	MOCK_METHOD(bool, init, (INT32 remainingIdsThreshold_, INT32 requiredIdsBuffer_, DbmGeneratorCallback* callback));
	MOCK_METHOD(void, setIdRangeConn, (IdRangeClientConnection* conn));
	MOCK_METHOD(void, addObjectName, (const char* objectName, bool local));
	MOCK_METHOD(bool, useSharedGenerators, (), (const));
	MOCK_METHOD(INT16, getIdRangeForSlave, (const char* objectName, INT32 rangeSize, UINT64& startId, UINT64& endId, PString& sqlErr));
	MOCK_METHOD(void, processReceiveRangesRequest, (CommMsgParser& parser, PStringSet& requestsSent, DbmGeneratorCallback* callback));
	MOCK_METHOD(void, addMonotonicObjectName, (const char* objectName));
	MOCK_METHOD(bool, isMonotonicByUserId, (const char* objectName), (const));

	MOCK_METHOD(void, setRangeIncrement, (UINT32 newIncrement));
	MOCK_METHOD(UINT32, getRangeIncrement, (), (const));
	MOCK_METHOD(void, prepareStatements, (DatabaseManagerCommon& dbmanager));
	MOCK_METHOD(void, deleteStatements, ());
	~DbmGenerator() {}
	MOCK_METHOD(UINT64, getNextId64, (const char* objectName));
	MOCK_METHOD(UINT64, getNextId64UnCached, (const char* objectName));
	MOCK_METHOD(void, getNext2Ids64, (const char* objectName, UINT64& id1, UINT64& id2));

	static const char* getHandCounterName(UINT32 siteId) {}

	MOCK_METHOD(UINT64, peekNextHandId64, (UINT32 siteId));
	MOCK_METHOD(UINT64, peekNextId64NoInsert_impl, (const char* objectName, bool unCached));
	UINT64 peekNextId64NoInsert(const char* objectName, bool unCached = false)
	{
		return peekNextId64NoInsert_impl(objectName, unCached);
	}
	MOCK_METHOD(void, saveNextId64, (const char* objectName, UINT64 id));
	MOCK_METHOD(UINT64, checkAndAdjustNextId, (const char* objectName, UINT64& currentId, INT32& increment));
	MOCK_METHOD(bool, usingSlaveGenerator, (const char* objectName), (const));
	MOCK_METHOD(void, setUseSelectWithUpdate, (const bool useSelectWithUpdate_));
	MOCK_METHOD(void, setUseAutonomousTransaction, (const bool useAutonomousTransaction_));

	MOCK_METHOD(void, commit, ());
	MOCK_METHOD(void, rollback, ());
	MOCK_METHOD(void, clearPrevMap, ());

private:
	DbmGenerator( const DbmGenerator& other ) = delete;
	const DbmGenerator& operator =( const DbmGenerator& other ) = delete;
};

#endif	//dbmgenerator_mock_h_included
