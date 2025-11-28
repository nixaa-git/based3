#include "../EventManager.h"
#include <format>

namespace event
{
    void enter_game(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        if (ctx.m_pClient->GetAuthStatus() != eClientAuthStatus::AUTHENTICATED)
        {
            ::printf("This guy is send action|enter_game whilst being unauthenticated?! Cheater!\n");
            return;
        }

        VariantList varmsg{ 
            "OnConsoleMessage",
            std::format("`oWelcome back, `w{}``. No friends online.``", ctx.m_pClient->GetDisplayName())
        };

        ctx.m_pClient->SendGlobalFunctionCall(varmsg, 0, -1);

        VariantList var2{ "OnRequestWorldSelectMenu", "default|based server v3\nadd_filter|\nset_max_rows|4\nadd_floater|wow|50|0.5|3529161471" };
        ctx.m_pClient->SendGlobalFunctionCall(var2, 0, -1);
    }
}