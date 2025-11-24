#include "../EventManager.h"
#include "../../CoreApp.h"

namespace event
{
    void requestedName(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        ::printf("Holy carp requestName event handler has been callington'd!\n");

        // 2.88 OnSuperMainStartAcceptLogonFB211131ddf
        // 3.02 OnSuperMainStartAcceptLogonHrdxs47254722215a

        VariantList var1;
        var1.Get(0).Set("OnSuperMainStartAcceptLogonHrdxs47254722215a");
        var1.Get(1).Set(g_pApp->GetItemInfoHash());
        var1.Get(2).Set("growtopia2.com");
        var1.Get(3).Set("cache/");
        var1.Get(4).Set("cc.madcat.app wtf.lol.fp");
        var1.Get(5).Set("proto=93|choosemusic=audio/mp3/about_theme.mp3|active_holiday=0|server_tick=12419248|");
        //var1.Get(6).Set(uint32_t(694201291093));
        ctx.m_pClient->SendGlobalFunctionCall(var1, 0, -1);

        ::printf("Items.dat hash is %u\n", g_pApp->GetItemInfoHash());

        //VariantList var{ "OnConsoleMessage", "Welcome back homie" };
        //ctx.m_pClient->SendGlobalFunctionCall(var, 0, -1);

        //VariantList var2{ "OnRequestWorldSelectMenu", "default|based server v3\nadd_filter|\nset_max_rows|4\nadd_floater|wow|50|0.5|3529161471" };
        //ctx.m_pClient->SendGlobalFunctionCall(var2, 0, -1);
    }
}