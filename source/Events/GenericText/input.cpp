#include "../EventManager.h"
#include "../../World/World.h"
#include <format>
#include <proton/TextScanner.h>
#include "../../CoreApp.h"

namespace event
{
    void input(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        std::string chatMsg = ctx.m_packetText.erase(0, 19);

        if (chatMsg.starts_with('/'))
        {
            // the client is invoking a command

            std::string cmd = StringTokenize(chatMsg.erase(0, 1), " ")[0];
            g_pApp->GetCommandHandler()->CallHandler(cmd, ctx);
            return;
        }

        World* pWorld = ctx.m_pClient->GetCurrentWorld();
        if (!pWorld)
        {
            return;
        }

        VariantList varConMsg{};
        varConMsg.Get(0).Set("OnConsoleMessage");
        varConMsg.Get(1).Set(std::format("`5<``{}`5>`` `w{}``", ctx.m_pClient->GetDisplayName(), chatMsg));

        VariantList varTalkBubble{};
        varTalkBubble.Get(0).Set("OnTalkBubble");
        varTalkBubble.Get(1).Set(ctx.m_pClient->GetNetID());
        varTalkBubble.Get(2).Set(chatMsg);
        varTalkBubble.Get(3).Set(0);
        varTalkBubble.Get(4).Set(0);

        pWorld->Broadcast([&](GameClient* pClient) {
            pClient->SendGlobalFunctionCall(varConMsg, 0, -1);
            pClient->SendGlobalFunctionCall(varTalkBubble, 0, -1);
        });
    }
}