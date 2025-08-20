
#include "GenericServerObjectSuite.h"

#include "commmsgbody.h"
#include "ServerStartParams.h"

//#include <AuxLobbyServerObject.h>
#include "commlib2a/MockServerStartParams.h"
#include "plib/MockPIniFile.h"
#include "atf/MockAtfCommObjectImpl.h"
#include "auxservercommon/MockAuxReefAccessor.h"

#include "atf/FakeServer.h"
#include "atf/MockService.h"

FakeServer* fakeServer = nullptr;
MockService* mockService = nullptr;
MockPIniFile* mockPIniFile =nullptr;
MockAtfCommObjectImpl* mockAtfCommObjectImpl = nullptr;
MockServerStartParams* mockServerStartParams = nullptr;

using namespace testing;
using namespace pokerstars::commlib;

void GenericServerObjectSuite::SetUp()
{
	fakeServer = new FakeServer();
	mockService = new MockService();
	mockPIniFile = new MockPIniFile();
	mockAtfCommObjectImpl = new MockAtfCommObjectImpl();
	mockServerStartParams = new MockServerStartParams();
	mockAuxReefAccessor = new MockAuxReefAccessor();

		
	EXPECT_CALL(*mockServerStartParams,
		parseServerStartParams(_, _, _)).WillRepeatedly(
			Invoke([this](ServerStartParams* serverStartParams, CommMsgParser& parser, const char* iniFileName_)
				{
					serverStartParams->fullIniFileName = this->iniFileName.c_str();
				}));
	EXPECT_CALL(*mockPIniFile, _load(_, iniFileName)).Times(AtLeast(1));


	ExpectInit();

	EXPECT_CALL(*mockAuxReefAccessor, init(_)).Times(AtLeast(min_num_servlets));
}

void GenericServerObjectSuite::TearDown()
{
	if (fakeServer)
	{
		delete fakeServer;
		fakeServer = nullptr;
	}
	if (mockService)
	{
		delete mockService;
		mockService = nullptr;
	}
	if (mockPIniFile)
	{
		delete mockPIniFile;
		mockPIniFile = nullptr;
	}
	if (mockAtfCommObjectImpl)
	{
		delete mockAtfCommObjectImpl;
		mockAtfCommObjectImpl = nullptr;
	}
	if (mockServerStartParams)
	{
		delete mockServerStartParams;
		mockServerStartParams = nullptr;
	}

	if (mockAuxReefAccessor)
	{
		delete mockAuxReefAccessor;
		mockAuxReefAccessor = nullptr;
	}
}