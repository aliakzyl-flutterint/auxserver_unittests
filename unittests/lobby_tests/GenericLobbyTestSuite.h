#pragma once

#include "GenericServerObjectSuite.h"

class AuxLobbyServerObject;

namespace IS
{
	class GGNLiveLoginSessionInfo;
}

class GenericLobbyTestSuite : public GenericServerObjectSuite
{
protected:
	
	void SetUp() override;
	void TearDown() override;
	void ExpectInit() override;

	void expectConnects(AuxLobbyServerObject& tstObj);

	void addUser(unsigned hostId, unsigned userIntId);

	void submitUsersToServer();

protected:
	std::vector< IS::GGNLiveLoginSessionInfo > users;

};