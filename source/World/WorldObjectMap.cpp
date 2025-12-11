#include "WorldObjectMap.h"

void WorldObjectMap::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    m_objectCount = m_objects.size();

    MemorySerialize(m_objectCount, pData, offset, bWriteToMem);
    MemorySerialize(m_lastObjectID, pData, offset, bWriteToMem);
    
    if (bWriteToMem)
    {
        for (auto& object : m_objects)
        {
            object.Serialize(pData, offset, bWriteToMem);
        }
    }
    else
    {
        WorldObject object{};
        object.Serialize(pData, offset, bWriteToMem);
    }
}

uint32_t WorldObjectMap::GetEstimatedMem()
{
    uint32_t res = 0;
    res += sizeof(uint32_t);
    res += sizeof(uint32_t);

    for (auto& obj : m_objects)
    {
        res += obj.GetEstimatedMem();
    }

    return res;
}