#include "GenericTextHandler.h"
#include "EventFuncs.h"

void GenericTextHandler::Init()
{
    // register actions

    //::printf("ptr for requestedName event func is %llX\n", event::requestedName);
    this->RegisterEvent("requestedName", event::requestedName);

    // item data refresh disabled for now bcs of crash issues ! 
    this->RegisterEvent("refresh_item_data", event::refresh_item_data);
    //this->RegisterEvent("enter_game", nullptr);

    ::printf("%zu generic text handler%s registered\n", m_handlers.size(), m_handlers.size() >= 2 ? "s": "");
}

void GenericTextHandler::RegisterEvent(const std::string& action, EventHandler_t handler)
{
    if (handler == nullptr)
    {
        ::printf("Huh?! Somehow tried to register a GenericTextHandler with nullptr!\n");
        return;
    }

    //::printf("Registering event %s\n", action.c_str());

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
        //::printf("Found handler for %s at %llX\n", action.c_str(), &it->second);
        it->second(ctx);
    }
}