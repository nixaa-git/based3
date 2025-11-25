#include "GameClient.h"

std::string GameClient::GetName() const
{
    return m_name;
}

uint64_t GameClient::GetUserID() const
{
    return m_userID;
}

void GameClient::SetName(const std::string& newName)
{
    m_name = newName;
}

void GameClient::SetUserID(uint64_t userID)
{
    m_userID = userID;
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