#ifndef mockcomminterface_h_included
#define mockcomminterface_h_included

#include "commqueue.h"
#include <gmock/gmock.h>

class MockCommInterface : public _CommInterface
{
public:
	virtual ~MockCommInterface() {}
	MOCK_METHOD(void, _post, (_CommMsg& msg));
	MOCK_METHOD(UINT32, _postClientTimer, (_CommMsg& msg, int msec));

public:
	MOCK_METHOD(UINT32, _addServerTimer, (UINT32 msgId, CommMsgBody& body, int msec));
	MOCK_METHOD(bool, _delServerTimer, (UINT32 handle));
	MOCK_METHOD(const char*, _getIdent, (), (const));
	//const char* _getIdent() const { return ""; }

public:
	MOCK_METHOD(int, _getInQueueSize, (), (const));
	MOCK_METHOD(INT64, _getInMemorySize, (), (const));
	MOCK_METHOD(UINT64, _getWaitInQueueTime, (UINT64 *readTime , UINT64 *writeTime));
	MOCK_METHOD(void, _internalPost, (_CommMsg& msg));
	MOCK_METHOD(int, _getOutQueueSize, (), (const));
	MOCK_METHOD(INT64, _getOutMemorySize, (), (const));

	MOCK_METHOD(const ConnInfo&, getConnInfo, (const CommClientConnectionPool* pool), (const));
	/*const ConnInfo& getConnInfo(const CommClientConnectionPool* pool) const
	{
		static const ConnInfo empty;
		return empty;
	}*/
	MOCK_METHOD(void, setConnInfo, (const CommServerObject& obj, ConnInfo&& connInfo));
	MOCK_METHOD(void, removeConnInfo, (const CommServerObject& obj));
};

#endif
