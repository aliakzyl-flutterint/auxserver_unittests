#pragma once

class AuxLobbyServerObject;

namespace expects
{
    void ExpectAuxRaceInits();
    void ExpectLobbyInits();
    void ExpectLobbyConnects(AuxLobbyServerObject& tstObj);
} // namespace expects

