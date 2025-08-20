#pragma once

class AuxLobbyServerObject;

namespace expects
{
    void ExpectAuxRaceInits();
    void ExpectLobbyInits();
    void ExpectISInits();
    void ExpectAdminInits();
    void ExpectLobbyConnects(AuxLobbyServerObject& tstObj);
} // namespace expects

