#pragma once

#include "WorldTileMap.h"
#include "WorldObjectMap.h"
#include "../SQL/WorldDBManager.h"
#include "Terraformer.h"
#include <proton/MiscUtils.h>
#include <vector>
#include "../Manager/NetObjectManager.h"

class GameClient;

class World : public Terraformer
{
public:
    World(CL_Vec2i worldSize) : m_worldTileMap(worldSize)
    {
        SetWorld(this);
    }

    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem, bool bClientPacket = true);
    uint32_t GetEstimatedMem(bool bClientPacket = true);
    void SaveToDisk();
    bool LoadFromDisk();

    void SendMapData(GameClient* pClient);

    void SetName(const std::string& name);
    std::string GetName();
    void SetSQLDataCached(WorldSQLField wsql);
    WorldSQLField GetSQLDataCached() { return m_sqlData; }

    void SetWorldID(int worldID);
    int GetWorldID();

    WorldTileMap& GetWorldTileMap() { return m_worldTileMap; }
    WorldObjectMap& GetWorldObjectMap() { return m_worldObjectMap; }
    NetObjectManager& GetNetObjectManager() { return m_netObjManager; }

    uint32_t GetWeatherID() { return m_weather; }
    void SetWeatherID(uint32_t weatherID) { m_weather = weatherID; }

    // broadcast func
    template <typename Func>
    void Broadcast(Func&& func)
    {
        for (auto& netObj : m_netObjManager.GetObjects())
        {
            if (netObj.second)
            {
                func(netObj.second);
            }
        }
    }

private:
    uint16_t m_version = 15;
    uint32_t m_flags = 0;
    std::string m_name = "PERKELE";
    WorldTileMap m_worldTileMap;
    WorldObjectMap m_worldObjectMap;
    uint32_t m_baseWeather = 1;
    uint32_t m_weather = 14;

    WorldSQLField m_sqlData{};
    NetObjectManager m_netObjManager{};
};