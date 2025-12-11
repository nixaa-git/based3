#include "WorldTileMap.h"

/*
WorldTileMap::WorldTileMap(CL_Vec2i size)
{
    // load data from map file if exist etc ?
}*/

void WorldTileMap::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    MemorySerialize(m_size.x, pData, offset, bWriteToMem);
    MemorySerialize(m_size.y, pData, offset, bWriteToMem);

    if (bWriteToMem)
    {
        m_tileCount = m_tiles.size();
    }
    
    MemorySerialize(m_tileCount, pData, offset, bWriteToMem);

    //offset += 5;

    if (bWriteToMem)
    {
        for (auto& tile : m_tiles)
        {
            tile.Serialize(pData, offset, bWriteToMem);
        }
    }
    else 
    {
        m_tiles.reserve(m_size.x * m_size.y);
        for (int i = 0; i < m_tileCount; i++)
        {
            Tile tile{};
            tile.m_index = i;
            tile.Serialize(pData, offset, bWriteToMem);
            m_tiles.push_back(tile);
        }
    }

    //offset += 12;
}

uint32_t WorldTileMap::GetEstimatedMem()
{
    uint32_t res = 0;
    for (auto& tile : m_tiles)
    {
        res += tile.GetEstimatedMem();
    }

    return res;
}

void WorldTileMap::Generate()
{
    m_tiles.reserve(m_size.x * m_size.y);
    for (int i = 0; i < (m_size.x * m_size.y); i++)
    {
        Tile tile;
        tile.m_fg = 2;
        tile.m_index = i;
        m_tiles.push_back(tile);
    }

    /*
    for (int xx = 0; xx < m_size.x; xx++)
    {
        for (int yy = 0; yy < m_size.y; yy++)
        {
            //int index = 
        }
    }*/
}