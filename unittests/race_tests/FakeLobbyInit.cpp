#include <AuxLobbyServerObject.h>
using namespace Dbm;

void AuxLobbyServerObject::initCriticalComponents()
{
    AuxLobbyTableTypePtr tableType;
    tableType.assign(new AuxLobbyTableType());
    tableType->maxSeats = 8;
    tableType->gameTypeId = 10;
    tableType->variantType = 20;
    AuxLobbyTableDataPtr table;
    table.assign(new AuxLobbyTableData(this));
    table->tableId = 301;
    table->tableType = tableType;
    this->tables.insert(std::make_pair(table->tableId, table));

    auto addPlayer = [this, &table](
        const std::string& auxUserId_,
        UINT32 userIntId_,
        BYTE hostId_)
        {
            AuxLobbyPlayerPtr user_;
            user_.assign(new AuxLobbyPlayer(auxUserId_.c_str(), userIntId_, hostId_));
            user_->setPlayerOnTable(table->tableId, user_);
            this->players.insert(std::make_pair(user_->auxUserId, user_));
        };

    addPlayer("user1", 1,1);
    addPlayer("user2", 2,1);
    addPlayer("user3", 3,1);
    
    for (auto& p : this->players)
    {
        auto& player = p.second;
        LobbyLoginSessionPtr session(new LobbyLoginSession(player));
        session->appSessionId = 1001;
        session->loginSessionId = 2000 + player->userIntId;
        player->addLoginSession(session);
    }
}