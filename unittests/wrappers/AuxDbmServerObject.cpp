
// Disable original headers when we have mocked:
#include "../mocks/ExcludeNonMockHeaders.h"
// AuxDbmServerObject is tested, so for this cpp we need original header:
#undef AuxDbmServerObject_h__

#include "../mocks/commlib2a/commsrv_mock.h"
#include "../mocks/commlib2a/commcli_mock.h"
#include "../mocks/commlib2a/commgrdnull_mock.h"
#include "../mocks/plib/ppstacktrace_mock.h"
#include "../mocks/protocols/counters_mock.h"
#include "../mocks/protocols/dbcommon_mock.h"
#include "../mocks/protocols/dbmgenerator_mock.h"
#include "../mocks/protocols/dbmserverobjectcommon_mock.h"
#include "../mocks/protocols/OlapCommon_mock.h"
#include "../mocks/auxcommon/auxdbcommon_mock.h"
#include "../mocks/auxiliary/auxdbm/MainDbmManager_mock.h"
#include "../mocks/atf/AtfCommServerObject_mock.h"
#include "../mocks/atf/TimerServer_mock.h"
#include "../mocks/auxservercommon/AuxCommServerObject_mock.h"
#include "../mocks/auxservercommon/auxdbmcommon_mock.h"
#include "../mocks/auxservercommon/auxsqlclidbmcommon_mock.h"
#include "../mocks/auxservercommon/StatusCheckServer_mock.h"

#include "../../auxiliary/auxdbm/AuxDbmServerObject.cpp"