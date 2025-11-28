#pragma once

#include "Tile.h"
#include <vector>
#include <proton/clanlib.h>

class WorldTileMap
{
public:
    WorldTileMap(CL_Vec2i size) : m_size(size);

    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);

private:
    uint32_t m_tileCount;
    CL_Vec2i m_size = {100, 60};

    std::vector<Tile> m_tiles;
};