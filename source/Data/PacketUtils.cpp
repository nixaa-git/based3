#include "PacketUtils.h"
 
int GetMessageTypeFromPacket(ENetPacket* pNetPacket)
{
    if (!pNetPacket)
    {
        return -1;
    }

    return *(int*)&pNetPacket->data[0];
}

const char* GetTextPointerFromPacket(ENetPacket* pNetPacket)
{
    if (!pNetPacket)
    {
        return nullptr;
    }

    pNetPacket->data[pNetPacket->dataLength - 1] = 0;

    return (const char*)&pNetPacket->data[4];
}

GameUpdatePacket* GetStructPointerFromPacket(ENetPacket* pNetPacket)
{
    if (!pNetPacket)
    {
        return nullptr;
    }

    return (GameUpdatePacket*)(pNetPacket->data + 4);
}