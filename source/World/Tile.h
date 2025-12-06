#pragma once

#include <proton/MiscUtils.h>

class Tile
{
public:
    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);

private:
    uint16_t m_fg;
    uint16_t m_bg;
    uint16_t m_flags;
    uint16_t m_parent;
    // TileExtra ptr

    // extra members not needed in serialization
    int m_index;
};