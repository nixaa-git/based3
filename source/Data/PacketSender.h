#pragma once

#include <iostream>
#include <enet/include/enet.h>
#include <proton/Variant.h>

class PacketSender
{
public:
    PacketSender(ENetPeer* pPeer) : m_pPeer(pPeer) {}

    void SendPacket(int type, const std::string& genericText);
    void SendPacketRaw(int type, void* pData, int32_t szData, void* pExtraData, enet_uint8 packetFlag = ENET_PACKET_FLAG_RELIABLE);
    void SendGlobalFunctionCall(VariantList varlist, int delay, int netID);

private:
    ENetPeer* m_pPeer = NULL;
};