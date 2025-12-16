#include "WorldTileMap.h"
#include "../Manager/ItemDB.h"

/*
WorldTileMap::WorldTileMap(CL_Vec2i size)
{
    // load data from map file if exist etc ?
}*/

void WorldTileMap::Serialize(uint8_t* pData, int& offset, bool bWriteToMem, bool bClientPacket)
{
    MemorySerialize(m_size.x, pData, offset, bWriteToMem);
    MemorySerialize(m_size.y, pData, offset, bWriteToMem);

    if (!bClientPacket)
    {
        MemorySerialize(m_mainDoorPos.x, pData, offset, bWriteToMem);
        MemorySerialize(m_mainDoorPos.y, pData, offset, bWriteToMem);
    }

    uint32_t tileCount = m_tiles.size();
    MemorySerialize(tileCount, pData, offset, bWriteToMem);

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
        for (int i = 0; i < tileCount; i++)
        {
            Tile tile{};
            tile.m_index = i;
            tile.Serialize(pData, offset, bWriteToMem);
            m_tiles.push_back(tile);
        }
    }

    ::printf("%d tiles in vec\n", m_tiles.size());
}

uint32_t WorldTileMap::GetEstimatedMem(bool bClientPacket)
{
    uint32_t res = 0;
    res += sizeof(CL_Vec2i);
    res += sizeof(uint32_t);

    if (bClientPacket)
    {
        res += sizeof(CL_Vec2i); // main door server side info
    }

    for (auto& tile : m_tiles)
    {
        res += tile.GetEstimatedMem(bClientPacket);
    }

    return res;
}

Tile* WorldTileMap::GetTileAtPos(int x, int y)
{
    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
        return nullptr;

    return &m_tiles[y * m_size.x + x];
}

void WorldTileMap::FillRect(CL_Vec2i topLeft, CL_Vec2i bottomRight, short fg, short bg, short flags)
{
    for (int y = topLeft.y; y <= bottomRight.y; y++)
    {
        for (int x = topLeft.x; x <= bottomRight.x; x++)
        {
            if (x < 0 || x >= m_size.x || y < 0 || y >= m_size.y)
            {
                continue;
            }

            int index = y * m_size.x + x;
            if (index < 0 || index >= static_cast<int>(m_tiles.size()))
            {
                continue;
            }

            m_tiles[index].m_fg = fg;
            m_tiles[index].m_bg = bg;
            m_tiles[index].m_flags = flags;
        }
    }
}

void WorldTileMap::FillRectRandom(const CL_Vec2i& topLeft, const CL_Vec2i& bottomRight, int amount, short fg, short bg)
{
    if (amount <= 0)
        return;

    for (int i = 0; i < amount; i++)
    {
        int x = RandomRange(topLeft.x, bottomRight.x);
        int y = RandomRange(topLeft.y, bottomRight.y);

        if (x < 0 || x >= m_size.x || y < 0 || y >= m_size.y)
            continue;

        int index = y * m_size.x + x;
        if (index < 0 || index >= static_cast<int>(m_tiles.size()))
            continue;

        if (fg != -1)
            m_tiles[index].m_fg = fg;

        if (bg != -1)
            m_tiles[index].m_bg = bg;
    }
}