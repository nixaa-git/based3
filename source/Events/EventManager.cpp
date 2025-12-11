#include "EventManager.h"
#include <proton/MiscUtils.h>
#include <proton/TextScanner.h>

void EventManager::Init()
{
    ::printf("EventManager initting...\n");

    m_gtxHandler.Init();
    m_gmHandler.Init();
    // GameMessageHandler::Init();
    // GameUpdateHandler::Init();
}

void EventManager::HandlePacket(EventContext& ctx)
{
    bool bIsDealingWithMessagePacket = !ctx.m_packetText.empty();

    ::printf("EventManager::HandlePacket() called! bIsDealingWithMessagePacket = %d\n", bIsDealingWithMessagePacket);

    if (bIsDealingWithMessagePacket && ctx.m_gamePacket.type == 0)
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



        /*
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

                switch (ctx.m_packetType)
                {
                    case 2:
                    {
                        m_gtxHandler.CallHandler(buildo[1], ctx);
                    } break;
                    case 3:
                    {
                        m_gmHandler.CallHandler(buildo[1], ctx);
                    } break;
                }
            }
        }*/
    }
    else
    {
        GameUpdatePacket pkt = ctx.m_gamePacket;

        // todo GameUpdateHandler.
    }
}