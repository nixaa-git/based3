#pragma once

#include <iostream>
#include <functional>
#include "../Data/GameClient.h"
#include "../Data/PacketUtils.h"

struct EventContext
{
public:
    GameClient* m_pClient = nullptr;
    int m_packetType = 0;
    std::string m_packetText = "";
    GameUpdatePacket* m_gamePacket = nullptr;

    EventContext(GameClient* pClient, int packetType, std::string packetText, GameUpdatePacket* pkt)
    : m_pClient(pClient), m_packetType(packetType), m_packetText(packetText), m_gamePacket(pkt) {}
};

#define EVENT_HANDLER_ARGS EventContext& ctx

using EventHandler_t = std::function<void(EVENT_HANDLER_ARGS)>;