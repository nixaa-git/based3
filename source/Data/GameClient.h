#pragma once

#include <iostream>
#include "PacketSender.h"

class GameClient : public PacketSender
{
public:
    GameClient(ENetPeer* pPeer) : m_pPeer(pPeer), PacketSender(pPeer) {}
    //~GameClient();
    
    // getters
    std::string GetName() const;

    // setters
    void SetName(const std::string& newName);

    // methods
    void SendHelloPacket();

private:
    ENetPeer* m_pPeer = NULL;

    std::string m_name{};
    int64_t m_gems = 0;
};