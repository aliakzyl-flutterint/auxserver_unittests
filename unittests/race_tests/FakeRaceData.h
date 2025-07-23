#pragma once

#include "auxprotocols/RaceDbmProtocols.h"
#include "auxprotocols/RaceServerProtocols.h"


struct FakeRaceData
{
    RaceDbm::RaceServer::Protocol_AUX_RACE_DBM_MSG_A_RACE_SERVER_NEED_DATA dbmRaces;
    RaceDbm::RaceServer::Protocol_AUX_RACE_DBM_MSG_A_GET_LIMITED_RACE_SESSIONS dbmRaceSessions;
    void init(int getRaceId);

    static aux::Race createRace(int raceId);
    static RaceServer::Lobby::Protocol_AUX_RACE_MSG_Q_RACE_OPTIN_4_PLAY createOptUser(int raceId, int userId);
};
