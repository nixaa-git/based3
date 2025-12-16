#pragma once

#include "WorldObject.h"
#include <vector>

class WorldObjectMap
{
public:
    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem, bool bClientPacket = true);
    uint32_t GetEstimatedMem(bool bClientPacket = true);

private:
    uint32_t m_objectCount;
    uint32_t m_lastObjectID; // last object ID that was added to the vector.

    std::vector<WorldObject> m_objects;
};