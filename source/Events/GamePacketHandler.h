#pragma once

#include "EventContext.h"

class GamePacketHandler
{
public:
    void Init();
    void RegisterEvent(uint8_t type, EventHandler_t handler);
    void CallHandler(EventContext& ctx);

private:
    std::unordered_map<uint8_t, EventHandler_t> m_handlers{};
};