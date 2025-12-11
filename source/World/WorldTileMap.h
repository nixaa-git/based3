#pragma once

#include "Tile.h"
#include <vector>
#include <proton/clanlib.h>

class WorldTileMap
{
public:
    WorldTileMap(CL_Vec2i size) : m_size(size)
    {
        this->Generate();
    }

    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);
    uint32_t GetEstimatedMem();
    void Generate();

private:
    uint32_t m_tileCount{};
    CL_Vec2i m_size = {100, 60};

    std::vector<Tile> m_tiles;
};