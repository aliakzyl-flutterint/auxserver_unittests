#include "auxservercommon/RaceScriptsParser.h"
#include "auxservercommon/AuxServerCommonDefs.h"

#include "race_tests/FakeRaceData.h"

#include "AtfCommServerObject.h"
//dbm simulation

namespace
{
	// raceId -> sessionId's
	std::map<int, std::vector<int>> m_races = {
	{11, {22, 23}},
	{12, {24}},
	{13, {25, 26, 27}}
	};
    int maxPlayers = 2;

	int beginTime = 100000000;
	int plannedEndTime = 100010000;

	// deltas
	int announceDelta = 4000;
	int openRegistrationDelta = 3000;
    int closeRegistrationDelta = 2000;
	int removeFromLobbyDelta = 1000;
}

void AuxServer::RacePrizeSpec::fromJSONString(const PString& _jsonString)
{
	this->maxPlayers = maxPlayers;
    this->prizes.clear();
}

void AuxServer::RaceEventTimingSpec::fromJSONString(const PString& _jsonString)
{
	this->announce = announceDelta;
    this->openRegistration = openRegistrationDelta;
    this->closeRegistration = closeRegistrationDelta;
	this->removeFromLobby = removeFromLobbyDelta;
}

void racePrizePositionsFromJSON(
	const PString& prizeSpecStr, std::vector<aux::RacePrizePosition>& prizePositions, INT64& totalPrize,
	std::vector<PrizePosition>& prizeStructure, vector<aux::CompactPayoutStructure>& compactPayoutStructure)
{
}

void checkAndSetExtraRaceStaticInfo(aux::ExtraRaceStaticInfo& extraraceInfo, const vector<aux::RaceTemplateProperties>& props)
{ }

void deserializeCountries(const PString countries, std::vector<PString>& vectCountries)
{ }

void deserializeCountries(const PString countries, std::set<PString, PStringCmp>& setCountries) {}

void FakeRaceData::init(int getRaceId)
{
	using namespace RaceDbm::RaceServer;
	using namespace aux;

	for (const auto& [raceId, sessionIds] : m_races) {
		if (raceId != getRaceId)
			continue;
		RaceDetail rd;
		rd.race.raceId = raceId;
		rd.race.status = RaceStatus::RACE_STATUS_STARTED;
		rd.race.beginTime = CommUtcTime(beginTime);
        rd.race.plannedEndTime = CommUtcTime(plannedEndTime);

		rd.race.raceTemplate.hosts = 1;
		rd.race.raceTemplate.sites = 1;
		rd.race.raceTemplate.clientPlatforms = 1;
		rd.race.raceTemplate.gameTemplate.gameType = 1;
		rd.race.raceTemplate.gameTemplate.variantType = 2;
		//rd.race.raceTemplate.raceTemplateId = 1;
		for (const auto& sessionId : sessionIds)
		{
			DbRaceSession race_session;
			race_session.raceId = raceId;
			race_session.raceSessionId = sessionId;
			dbmRaceSessions.raceSessions.push_back(race_session);
		}
		dbmRaces.races.push_back(rd);
	}
}

aux::Race FakeRaceData::createRace(int raceId)
{
	using namespace aux;
    Race raceObj;
    raceObj.raceId = raceId;
	raceObj.status = RaceStatus::RACE_STATUS_NONE;
	raceObj.beginTime = CommUtcTime(beginTime);
	raceObj.plannedEndTime = CommUtcTime(plannedEndTime);

	raceObj.raceTemplate.hosts = 1;
	raceObj.raceTemplate.sites = 1;
	raceObj.raceTemplate.clientPlatforms = 1;
	raceObj.raceTemplate.gameTemplate.gameType = 1;
	raceObj.raceTemplate.gameTemplate.variantType = 2;
    return raceObj;
}

Atf::Timer* Atf::AtfCommObjectImpl::getDefaultTimer()
{
	if (defTimer == nullptr)
	{
		defTimer = new TimerServer(this);  // support both second and millisecond timer
	}
	return defTimer;
}