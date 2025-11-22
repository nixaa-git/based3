#include "../EventManager.h"

namespace event
{
    void enter_game(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        // todo. check if client is validly authed
    }
}