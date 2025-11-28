#pragma once

#include "WorldTileMap.h"
#include "WorldObjectMap.h"
#include <proton/MiscUtils.h>
#include <vector>

class World
{
public:
    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);

private:
    uint16_t m_version = 14;
    uint32_t m_flags = 0;
    std::string m_name = "EXIT";
    WorldTileMap m_worldTileMap;
    WorldObjectMap m_worldObjectMap;
    uint32_t m_baseWeather;
    uint32_t m_weather;
};