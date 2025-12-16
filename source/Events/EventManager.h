#pragma once

#include <iostream>
#include <unordered_map>
#include "GenericTextHandler.h"
#include "GameMessageHandler.h"
#include "GamePacketHandler.h"
#include "EventContext.h"

class EventManager
{
public:
    EventManager() = default;

    void Init();
    void HandlePacket(EventContext& ctx);

    GenericTextHandler m_gtxHandler{};
    GameMessageHandler m_gmHandler{};
    GamePacketHandler m_gpHandler{};
};