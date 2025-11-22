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

        auto hashwtf = ReliableHash((void*)g_pApp->GetItemInfoBuffer(), g_pApp->GetItemInfoBufferSize());

        VariantList var1;
        var1.Get(0).Set("OnSuperMainStartAcceptLogonHrdxs47254722215a");
        var1.Get(1).Set(hashwtf);
        var1.Get(2).Set("growtopia2.com");
        var1.Get(3).Set("cache/");
        var1.Get(4).Set("cc.madcat.app wtf.lol.fp");
        var1.Get(5).Set("use_beta_files=0|proto=93|choosemusic=audio/mp3/about_theme.mp3|active_holiday=0|server_tick=12419248|clash_active=0|drop_lavacheck_faster=1|isPayingUser=0|usingStoreNavigation=1|bigBackpack=1|");
        var1.Get(6).Set(uint32_t(694201291093));
        ctx.m_pClient->SendGlobalFunctionCall(var1, 0, -1);

        //VariantList var{ "OnConsoleMessage", "Welcome back homie" };
        //ctx.m_pClient->SendGlobalFunctionCall(var, 0, -1);

        //VariantList var2{ "OnRequestWorldSelectMenu", "default|based server v3\nadd_filter|\nset_max_rows|4\nadd_floater|wow|50|0.5|3529161471" };
        //ctx.m_pClient->SendGlobalFunctionCall(var2, 0, -1);
    }
}