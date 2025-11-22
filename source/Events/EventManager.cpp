#include "EventManager.h"
#include <proton/MiscUtils.h>

void EventManager::Init()
{
    ::printf("EventManager initting...\n");

    m_gtxHandler.Init();
    // GameMessageHandler::Init();
    // GameUpdateHandler::Init();
}

void EventManager::HandlePacket(EventContext& ctx)
{
    bool bIsDealingWithMessagePacket = !ctx.m_packetText.empty();

    ::printf("EventManager::HandlePacket() called! bIsDealingWithMessagePacket = %d\n", bIsDealingWithMessagePacket);

    if (bIsDealingWithMessagePacket && ctx.m_gamePacket.type == 0)
    {
        std::vector<std::string> buildo = StringTokenize(ctx.m_packetText, "|");
        if (buildo.size() >= 2)
        {
            if (buildo[0] == "requestedName" || buildo[0] == "tankIDName")
            {
                m_gtxHandler.CallHandler("requestedName", ctx);
                return;
            }
            else if (buildo[0] == "action")
            {
                buildo[1].pop_back(); 
                m_gtxHandler.CallHandler(buildo[1], ctx);
            }
        }
    }
    else
    {
        GameUpdatePacket pkt = ctx.m_gamePacket;

        // todo GameUpdateHandler.
    }
}