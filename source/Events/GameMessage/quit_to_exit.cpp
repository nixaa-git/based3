#include "../EventManager.h"
#include "../../World/World.h"

namespace event
{
    void quit_to_exit(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        int clientNetID = ctx.m_pClient->GetNetID();
        ctx.m_pClient->GetCurrentWorld()->GetNetObjectManager().RemoveObject(clientNetID);
        ctx.m_pClient->SetCurrentWorld(nullptr);

        VariantList varmsg{
            "OnConsoleMessage",
            "`oWhere would you like to go? (`w1`` online)``"
        };

        ctx.m_pClient->SendGlobalFunctionCall(varmsg, 0, -1);

        // todo
        // send OnRequestWorldSelect 

        VariantList var2{ "OnRequestWorldSelectMenu", "default|START\nadd_filter|\nset_max_rows|4\nadd_floater|wow|50|0.5|3529161471" };
        ctx.m_pClient->SendGlobalFunctionCall(var2, 0, -1);
    }
}