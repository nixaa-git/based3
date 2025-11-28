#include "World.h"

void World::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    MemorySerialize(m_version, pData, offset, bWriteToMem);
    MemorySerialize(m_flags, pData, offset, bWriteToMem);
    MemorySerialize(m_name, pData, offset, bWriteToMem);
    m_worldTileMap.Serialize(pData, offset, bWriteToMem);
    m_worldObjectMap.Serialize(pData, offset, bWriteMem);
    MemorySerialize(m_baseWeather, pData, offset, bWriteToMem);
    MemorySerialize(m_weather, pData, offset, bWriteToMem);
}