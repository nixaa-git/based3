#include "World.h"
#include "../Data/GameClient.h"
#include "../Data/PacketUtils.h"
#include <format>

void World::Serialize(uint8_t* pData, int& offset, bool bWriteToMem, bool bClientPacket)
{
    MemorySerialize(m_version, pData, offset, bWriteToMem);
    MemorySerialize(m_flags, pData, offset, bWriteToMem);
    MemorySerialize(m_name, pData, offset, bWriteToMem);
    m_worldTileMap.Serialize(pData, offset, bWriteToMem, bClientPacket);

    int zero = 0;
    int zero2 = 0;
    MemorySerialize(zero, pData, offset, bWriteToMem);
    MemorySerialize(zero2, pData, offset, bWriteToMem);
    /*
    m_worldObjectMap.Serialize(pData, offset, bWriteToMem);
    */
    MemorySerialize(m_baseWeather, pData, offset, bWriteToMem);
    MemorySerialize(m_weather, pData, offset, bWriteToMem);
}

uint32_t World::GetEstimatedMem(bool bClientPacket)
{
    uint32_t res = 0;
    res += sizeof(uint16_t);
    res += sizeof(uint32_t);
    res += sizeof(short) + m_name.length();
    res += m_worldTileMap.GetEstimatedMem(bClientPacket);

    res += sizeof(int) * 2;
    //res += m_worldObjectMap.GetEstimatedMem();
    res += sizeof(uint32_t);
    res += sizeof(uint32_t);

    return res;
}

void World::SaveToDisk()
{
    uint32_t dataSize = GetEstimatedMem();
    uint8_t* pData = (uint8_t*)::malloc(dataSize);

    int offset = 0;
    this->Serialize(pData, offset, true, false);

    SaveFileFromMemoryBasic(std::format("maps/{}.map", m_sqlData.ID), pData, dataSize, false, false);

    ::free(pData);
}

bool World::LoadFromDisk()
{
    std::string mapfile = std::format("maps/{}.map", m_sqlData.ID);
    ::printf("Loading map file %s\n", mapfile.c_str());

    unsigned int fileSize = 0;
    uint8_t* pData = LoadFileIntoMemoryBasic(mapfile, &fileSize, false, false);
    if (!pData)
    {
        return false;
    }

    ::printf("Loaded map from disk, size %u bytes\n", fileSize);

    int offset = 0;
    this->Serialize(pData, offset, false, false);

    ::printf("Real offset after loading from disk: %d\n", offset);

    ::free(pData);
    return true;
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

    ::printf("map size is %u\n", pkt.extraDataSize);
    uint8_t* pData = (uint8_t*)::malloc(pkt.extraDataSize);

    int offset = 0;
    this->Serialize(pData, offset, true);
    ::printf("real offset after serialize: %d\n", offset);

    pClient->SendPacketRaw(4, &pkt, sizeof(GameUpdatePacket), pData);
}

void World::SetName(const std::string& name)
{
    m_name = ToUppercase(name);
}

std::string World::GetName()
{
    return m_name;
}

void World::SetWorldID(int worldID)
{
    m_sqlData.ID = worldID;
}

int World::GetWorldID()
{
    return static_cast<int>(m_sqlData.ID);
}

void World::SetSQLDataCached(WorldSQLField wsql)
{
    m_sqlData = wsql;

    m_name = ToUppercase(std::string(wsql.Name));
    
}