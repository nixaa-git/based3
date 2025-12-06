#include "WorldTileMap.h"

WorldTileMap::WorldTileMap(CL_Vec2i size)
{
    // load data from map file if exist etc ?
}

void WorldTileMap::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    MemorySerialize(m_size.x, pData, offset, bWriteToMem);
    MemorySerialize(m_size.y, pData, offset, bWriteToMem);

    if (bWriteToMem)
    {
        m_tileCount = m_tiles.size();
    }
    
    MemorySerialize(m_tileCount, pData, offset, bWriteToMem);

    if (bWriteToMem)
    {
        for (auto& tile : m_tiles)
        {
            tile.Serialize(pData, offset, bWriteToMem);
        }
    }
    else 
    {
        for (int i = 0; i < m_tileCount; i++)
        {
            Tile tile{};
            tile.m_index = i;
            tile.Serialize(pData, offset, bWriteToMem);
        }
    }
}

void WorldTileMap::Generate()
{
    for (int xx = 0; xx < m_size.x; xx++)
    {
        for (int yy = 0; yy < m_size.y; yy++)
        {
            int index = 

            if 
        }
    }
}