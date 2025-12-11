#include "../EventManager.h"
#include <format>
#include "../../World/World.h"

namespace event
{
    void join_request(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        if (ctx.m_pClient->GetAuthStatus() != eClientAuthStatus::AUTHENTICATED)
        {
            ::printf("This guy is send action|join_request whilst being unauthenticated?! Cheater!\n");
            return;
        }

        static World world({100, 60});

        ::printf("oh my god join request handler called!\n");

        VariantList varmsg{ 
            "OnConsoleMessage",
            std::format("`oWorld {} entered``", world.GetName())
        };
        ctx.m_pClient->SendGlobalFunctionCall(varmsg, 0, -1);

        world.SendMapData(ctx.m_pClient);
    }
}