#pragma once

#include <proton/MiscUtils.h>

class Tile
{
public:
    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);
    uint32_t GetEstimatedMem();

    short m_fg{};
    short m_bg{};
    short m_flags{};
    short m_parent{};
    // TileExtra ptr

    // extra members not needed in serialization
    int m_index;
};