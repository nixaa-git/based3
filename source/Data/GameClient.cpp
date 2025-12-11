#include "GameClient.h"
#include "../SQL/AccountManager.h"
#include <format>

ENetPeer* GameClient::GetENetPeer() const
{
    return m_pPeer;
}

std::string GameClient::GetName() const
{
    return m_name;
}

uint64_t GameClient::GetUserID() const
{
    return m_userID;
}

eClientAuthStatus GameClient::GetAuthStatus() const
{
    return m_authStatus;
}

PlayerSQLField GameClient::GetSQLDataCached() const
{
    return m_sqlData;
}

std::string GameClient::GetDisplayName(bool bRemovePrefixAndSuffix) const
{
    // todo: is current owner/admin of this world?
    // is nicked?
    //
    
    std::string namePrefix = "`w";
    std::string nameSuffix = "``";

    if (bRemovePrefixAndSuffix)
    {
        namePrefix = "";
        nameSuffix = "";
    }

    return std::format("{}{}{}", namePrefix, m_name, nameSuffix);
}

void GameClient::SetName(const std::string& newName)
{
    m_name = newName;
}

void GameClient::SetUserID(uint64_t userID)
{
    m_userID = userID;
}

void GameClient::SetAuthStatus(eClientAuthStatus status)
{
    m_authStatus = status;
}

void GameClient::SetSQLDataCached(PlayerSQLField psql)
{
    m_sqlData = psql;

    // set member data here?


    m_name = std::string(psql.LogonName).empty() ? psql.Name : psql.LogonName;

}

void GameClient::SendHelloPacket()
{
    static constexpr int type = 1;
    static constexpr int el_numero_cero = 0;

    ENetPacket* pNetPacket = enet_packet_create(NULL, sizeof(int) + sizeof(uint8_t), ENET_PACKET_FLAG_RELIABLE);
    ::memcpy(pNetPacket->data, &type, sizeof(int));
    ::memcpy(pNetPacket->data + sizeof(int), &el_numero_cero, 1);

    if (m_pPeer)
    {
        ::printf("Sent hello packet to peer\n");
        enet_peer_send(m_pPeer, NULL, pNetPacket);
    }
}
