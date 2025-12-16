#include "../EventManager.h"

namespace event
{
    void gp_state(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        if (ctx.m_pClient->GetAuthStatus() != eClientAuthStatus::AUTHENTICATED)
        {
            ::printf("This guy is sending state packet whilst being unauthenticated?! Cheater!\n");
            return;
        }

        ::printf("gp_state event handler has been called\n");

        GameUpdatePacket* pkt = ctx.m_gamePacket;
        if (!pkt)
        {
            return;
        }

        pkt->netID = ctx.m_pClient->GetNetID();
        CL_Vec2f pos = {pkt->posX, pkt->posY};

        std::printf("%s (NetID: %d) moved to %f, %f\n", ctx.m_pClient->GetName().c_str(), pkt->netID, pos.x, pos.y);
    }
}