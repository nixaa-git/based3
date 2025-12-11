#pragma once

#include "WorldTileMap.h"
#include "WorldObjectMap.h"
#include <proton/MiscUtils.h>
#include <vector>

class GameClient;

class World
{
public:
    World(CL_Vec2i worldSize) : m_worldTileMap(worldSize) {}

    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);
    uint32_t GetEstimatedMem();
    void SendMapData(GameClient* pClient);

    std::string GetName();

private:
    uint16_t m_version = 14;
    uint32_t m_flags = 0;
    std::string m_name = "EXIT";
    WorldTileMap m_worldTileMap;
    WorldObjectMap m_worldObjectMap;
    uint32_t m_baseWeather = 1;
    uint32_t m_weather = 4;
};