#include "../../ExcludeNonMockHeaders.h"

#include "../../commlib2a/commcli_mock.h"
#include "../../commlib2a/commgrdnull_mock.h"
#include "../../protocols/dbcommon_mock.h"
#include "../../protocols/dbmserverobjectcommon_mock.h"
#include "../../protocols/OlapCommon_mock.h"
#include "../../auxservercommon/auxdbmcommon_mock.h"
#include "../../auxservercommon/auxsqlclidbmcommon_mock.h"
#include "MainDbmManager_mock.h"

#include "../../../../auxiliary/auxdbm/AuxDbmServerObject.h"

AuxDbmServerConnDbd::AuxDbmServerConnDbd(AuxDbmServerObject* obj_) : AuxCommServerConnection(obj_, true, "DBD")
{
}
void AuxDbmServerConnDbd::processMessage(UINT32 msgId, const CommMsgBody& body)
{
}