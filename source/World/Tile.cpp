#include "Tile.h"

void Tile::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    MemorySerialize(m_fg, pData, offset, bWriteToMem);
    MemorySerialize(m_bg, pData, offset, bWriteToMem);
    MemorySerialize(m_flags, pData, offset, bWriteToMem);
    MemorySerialize(m_parent, pData, offset, bWriteToMem);

    if (m_flags & (1 << 3))
    {
        // TileExtra init and serialize etc
    }
}

uint32_t Tile::GetEstimatedMem()
{
    uint32_t res = 0;
    res += sizeof(short) * 4;

    if (m_flags & (1 << 3))
    {
        //todo
    }

    return res;
}