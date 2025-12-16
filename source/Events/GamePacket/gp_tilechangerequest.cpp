#include "../EventManager.h"
#include "../../World/World.h"

namespace event
{
    void gp_tilechangerequest(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        if (ctx.m_pClient->GetAuthStatus() != eClientAuthStatus::AUTHENTICATED)
        {
            ::printf("This guy is sending tile change req packet whilst being unauthenticated?! Cheater!\n");
            return;
        }

        GameUpdatePacket* pkt = ctx.m_gamePacket;
        if (!pkt)
        {
            return;
        }

        World* pWorld = ctx.m_pClient->GetCurrentWorld();
        if (!pWorld)
        {
            return;
        }

        CL_Vec2i posPlace = {pkt->posX, pkt->posY};

        
    }
}