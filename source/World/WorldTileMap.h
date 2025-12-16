#pragma once

#include "Tile.h"
#include <vector>
#include <proton/clanlib.h>

class WorldTileMap
{
public:
    WorldTileMap(CL_Vec2i size) : m_size(size) {}

    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem, bool bClientPacket = true);
    uint32_t GetEstimatedMem(bool bClientPacket = true);

    // get
    std::vector<Tile>& GetTiles() { return m_tiles; }
    CL_Vec2i GetSize() { return m_size; }
    Tile* GetTileAtPos(int x, int y);
    CL_Vec2i GetMainDoorPos() { return m_mainDoorPos; }

    // set
    void SetMainDoorPos(CL_Vec2i mainDoorPos) { m_mainDoorPos = mainDoorPos; }

    // terraforming
    void FillRect(CL_Vec2i topLeft, CL_Vec2i bottomRight, short fg, short bg = 0, short flags = 0);
    void FillRectRandom(const CL_Vec2i& topLeft, const CL_Vec2i& bottomRight, int amount, short fg, short bg = 0);

private:
    // server side info
    CL_Vec2i m_mainDoorPos{};

    // client side info
    CL_Vec2i m_size = {100, 60};
    uint32_t m_tileCount{};

    std::vector<Tile> m_tiles;
};