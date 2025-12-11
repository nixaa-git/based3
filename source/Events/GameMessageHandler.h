#pragma once

#include "EventContext.h"

class GameMessageHandler
{
public:
    void Init();
    void RegisterEvent(const std::string& action, EventHandler_t handler);
    void CallHandler(const std::string& action, EventContext& ctx);

private:
    std::unordered_map<std::string, EventHandler_t> m_handlers{};
};