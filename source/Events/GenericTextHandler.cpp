#include "GenericTextHandler.h"
#include "EventFuncs.h"

void GenericTextHandler::Init()
{
    // register actions
    this->RegisterEvent("requestedName", event::requestedName);
    this->RegisterEvent("refresh_item_data", event::refresh_item_data);
    this->RegisterEvent("enter_game", event::enter_game);
    this->RegisterEvent("input", event::input);

    ::printf("%zu generic text handler%s registered\n", m_handlers.size(), m_handlers.size() >= 2 ? "s": "");
}

void GenericTextHandler::RegisterEvent(const std::string& action, EventHandler_t handler)
{
    if (handler == nullptr)
    {
        ::printf("Huh?! Somehow tried to register a GenericTextHandler with nullptr!\n");
        return;
    }

    m_handlers[action] = std::move(handler);
}

void GenericTextHandler::CallHandler(const std::string& action, EventContext& ctx)
{
    if (m_handlers.empty())
    {
        ::printf("GenericTextHandler::CallHandler() Fatal error. Zero handlers in map!\n");
        return;
    }

    auto it = m_handlers.find(action);

    if (it != m_handlers.end())
    {
        it->second(ctx);
    }
}