#include "World.h"
#include "../Data/GameClient.h"
#include "../Data/PacketUtils.h"

void World::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    MemorySerialize(m_version, pData, offset, bWriteToMem);
    MemorySerialize(m_flags, pData, offset, bWriteToMem);
    MemorySerialize(m_name, pData, offset, bWriteToMem);
    m_worldTileMap.Serialize(pData, offset, bWriteToMem);
    m_worldObjectMap.Serialize(pData, offset, bWriteToMem);
    MemorySerialize(m_baseWeather, pData, offset, bWriteToMem);
    MemorySerialize(m_weather, pData, offset, bWriteToMem);
}

uint32_t World::GetEstimatedMem()
{
    uint32_t res = 0;
    res += sizeof(uint16_t);
    res += sizeof(uint32_t);
    res += sizeof(short) + m_name.length();
    res += m_worldTileMap.GetEstimatedMem();
    res += m_worldObjectMap.GetEstimatedMem();
    res += sizeof(uint32_t);
    res += sizeof(uint32_t);

    return res;
}

void World::SendMapData(GameClient* pClient)
{
    if (!pClient)
    {
        return;
    }

    GameUpdatePacket pkt;
    pkt.type = PACKET_SEND_MAP_DATA;
    pkt.flags = (1 << 3);
    pkt.extraDataSize = GetEstimatedMem();

    ::printf("map size is %zu\n", pkt.extraDataSize);
    uint8_t* pData = (uint8_t*)::malloc(pkt.extraDataSize);

    int offset = 0;
    this->Serialize(pData, offset, true);

    pClient->SendPacketRaw(4, &pkt, sizeof(GameUpdatePacket), pData);
}

std::string World::GetName()
{
    return m_name;
}