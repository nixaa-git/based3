#include "EventManager.h"
#include <proton/MiscUtils.h>
#include <proton/TextScanner.h>

void EventManager::Init()
{
    ::printf("EventManager initting...\n");

    m_gtxHandler.Init();
    m_gmHandler.Init();
    m_gpHandler.Init();
    // GameMessageHandler::Init();
    // GameUpdateHandler::Init();
}

void EventManager::HandlePacket(EventContext& ctx)
{
    bool bIsDealingWithMessagePacket = !ctx.m_packetText.empty();

    if (bIsDealingWithMessagePacket && ctx.m_gamePacket == nullptr)
    {
        TextScanner scan;
        scan.SetupFromMemoryAddress(ctx.m_packetText.c_str());

        if (ctx.m_packetText.find("requestedName") != std::string::npos || ctx.m_packetText.find("tankIDName") != std::string::npos)
        {
            m_gtxHandler.CallHandler("requestedName", ctx);
            return;
        }

        switch (ctx.m_packetType)
        {
            case 2:
            {
                m_gtxHandler.CallHandler(scan.GetParmString("action", 1), ctx);
            } break;
            case 3:
            {
                m_gmHandler.CallHandler(scan.GetParmString("action", 1), ctx);
            } break;
        }
    }
    else
    {
        if (ctx.m_gamePacket == nullptr)
        {
            ::printf("tried to call game packet handler but the game packet was nullptr??\n");
            return;
        }

        m_gpHandler.CallHandler(ctx);
    }
}