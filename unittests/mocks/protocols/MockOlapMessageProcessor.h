#ifndef mockolapmessageprocessor_h_included
#define	mockolapmessageprocessor_h_included

#include "OlapCommon_mock.h"
#include <gmock/gmock.h>

class MockOlapMessageProcessor : public OlapMessageProcessor
{
public:
	MockOlapMessageProcessor(const UINT32 *arr, UINT32 sizeArr) : OlapMessageProcessor(arr, sizeArr) {}

	MOCK_METHOD(void, processOlapMessage, (UINT32 msgId, CommMsgParser &parser, DbmToOlapClientConn* conn, UINT32 reqId, OlapServer& olapServer), (const));

	MOCK_METHOD(bool, isAllowedMessage, (const UINT32 msgId), (const));
};

#endif //mockolapmessageprocessor_h_included
