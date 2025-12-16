#pragma once

#include <proton/MiscUtils.h>
#include <proton/clanlib.h>

class WorldObject
{
public:
    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);
    uint32_t GetEstimatedMem(bool bClientPacket = true);

    uint16_t m_itemID = 0;
    CL_Vec2f m_pos{};
    uint8_t m_amount{};
    uint8_t m_flags{};
    uint32_t m_id{};
};