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
    uint64_t GetUserID() const;

    // setters
    void SetName(const std::string& newName);
    void SetUserID(uint64_t userID);

    // methods
    void SendHelloPacket();

private:
    ENetPeer* m_pPeer = NULL;

    std::string m_name{};
    uint64_t m_userID = 0;
    int64_t m_gems = 0;
};