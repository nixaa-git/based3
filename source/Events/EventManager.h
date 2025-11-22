#pragma once

#include <iostream>
#include <unordered_map>
#include "GenericTextHandler.h"
#include "EventContext.h"

class EventManager
{
public:
    EventManager() = default;

    void Init();
    void HandlePacket(EventContext& ctx);

    GenericTextHandler m_gtxHandler{};
};