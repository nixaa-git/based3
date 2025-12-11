#include "WorldObject.h"

void WorldObject::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    MemorySerialize(m_itemID, pData, offset, bWriteToMem);
    MemorySerialize(m_pos.x, pData, offset, bWriteToMem);
    MemorySerialize(m_pos.y, pData, offset, bWriteToMem);
    MemorySerialize(m_amount, pData, offset, bWriteToMem);
    MemorySerialize(m_flags, pData, offset, bWriteToMem);
    MemorySerialize(m_id, pData, offset, bWriteToMem);
}

uint32_t WorldObject::GetEstimatedMem()
{
    uint32_t res = 0;
    res += sizeof(uint16_t);
    res += sizeof(CL_Vec2f);
    res += sizeof(uint8_t);
    res += sizeof(uint8_t);
    res += sizeof(uint32_t);

    return res;
}