#include "GamePacketHandler.h"
#include "EventFuncs.h"

void GamePacketHandler::Init()
{
    // register game packet
    this->RegisterEvent(PACKET_STATE, event::gp_state);

    ::printf("%zu game packet handler%s registered\n", m_handlers.size(), m_handlers.size() >= 2 ? "s": "");
}

void GamePacketHandler::RegisterEvent(uint8_t type, EventHandler_t handler)
{
    if (handler == nullptr)
    {
        ::printf("Huh?! Somehow tried to register a GamePacketHandler with nullptr!\n");
        return;
    }

    m_handlers[type] = std::move(handler);
}

void GamePacketHandler::CallHandler(EventContext& ctx)
{
    if (m_handlers.empty())
    {
        ::printf("GamePacketHandler::CallHandler() Fatal error. Zero handlers in map!\n");
        return;
    }

    auto it = m_handlers.find(ctx.m_gamePacket->type);

    if (it != m_handlers.end())
    {
        it->second(ctx);
    }
}