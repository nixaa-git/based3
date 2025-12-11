#include "GameMessageHandler.h"
#include "EventFuncs.h"

void GameMessageHandler::Init()
{
    // register actions
    this->RegisterEvent("join_request", event::join_request);

    ::printf("%zu game message handler%s registered\n", m_handlers.size(), m_handlers.size() >= 2 ? "s": "");
}

void GameMessageHandler::RegisterEvent(const std::string& action, EventHandler_t handler)
{
    if (handler == nullptr)
    {
        ::printf("Huh?! Somehow tried to register a GameMessageHandler with nullptr!\n");
        return;
    }

    //::printf("Registering event %s\n", action.c_str());

    m_handlers[action] = std::move(handler);
}

void GameMessageHandler::CallHandler(const std::string& action, EventContext& ctx)
{
    ::printf("calling handler for %s\n", action.c_str());

    if (m_handlers.empty())
    {
        ::printf("GameMessageHandler::CallHandler() Fatal error. Zero handlers in map!\n");
        return;
    }

    auto it = m_handlers.find(action);

    if (it != m_handlers.end())
    {
        //::printf("Found handler for %s at %llX\n", action.c_str(), &it->second);
        it->second(ctx);
    }
}