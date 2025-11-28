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