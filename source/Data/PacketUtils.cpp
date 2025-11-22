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

    return (const char*)&pNetPacket->data[4];
}

GameUpdatePacket* GetStructPointerFromPacket(ENetPacket* pNetPacket)
{
    if (!pNetPacket)
    {
        return nullptr;
    }

    return (GameUpdatePacket*)&pNetPacket[0];
}