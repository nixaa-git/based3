#include "PacketSender.h"
#include "PacketUtils.h"
#include <format>

void PacketSender::SendPacket(int type, const std::string& genericText)
{
    if (!m_pPeer)
    {
        return;
    } 

    ENetPacket* pNetPacket = enet_packet_create(NULL, 5 + genericText.length(), ENET_PACKET_FLAG_RELIABLE);
    *(int*)(pNetPacket->data) = type;
    ::memcpy(pNetPacket->data + sizeof(int), genericText.c_str(), genericText.size());

    enet_peer_send(m_pPeer, NULL, pNetPacket);
}

void PacketSender::SendPacketRaw(int type, void* pData, int32_t szData, void* pExtraData, enet_uint8 packetFlag)
{
    if (!m_pPeer || !pData)
    {
        return;
    }

    uint32_t msgType = type;
    ENetPacket* pNetPacket = NULL;

    if (msgType == 4 && ((GameUpdatePacket*)pData)->flags & NET_GAME_PACKET_FLAG_EXTENDED)
    {
        pNetPacket = enet_packet_create(NULL, szData + 5 + ((GameUpdatePacket*)pData)->extraDataSize, packetFlag);

        int offset = 0;
        MemorySerialize(msgType, pNetPacket->data, offset, true);
        MemorySerializeRaw((uint8_t*)pData, pNetPacket->data, szData, offset, true);
        MemorySerializeRaw((uint8_t*)pExtraData, pNetPacket->data, ((GameUpdatePacket*)pData)->extraDataSize, offset, true);
    }
    else
    {
        pNetPacket = enet_packet_create(NULL, szData + 5, packetFlag);

        int offset = 0;
        MemorySerialize(msgType, pNetPacket->data, offset, true);
        MemorySerializeRaw((uint8_t*)pData, pNetPacket->data, szData, offset, true);
    }

    if (enet_peer_send(m_pPeer, NULL, pNetPacket))
    {
        enet_packet_destroy(pNetPacket);
    }
}

void PacketSender::SendGlobalFunctionCall(VariantList varlist, int delay, int netID)
{
    GameUpdatePacket pkt;
    pkt.type = PACKET_CALL_FUNCTION;
    pkt.flags |= NET_GAME_PACKET_FLAG_EXTENDED;
    pkt.functionDelay = delay;
    pkt.netID = netID;

    uint8_t* pData = varlist.SerializeToMem(pkt.extraDataSize);

    SendPacketRaw(4, &pkt, sizeof(GameUpdatePacket), pData);

    ::free(pData);
}