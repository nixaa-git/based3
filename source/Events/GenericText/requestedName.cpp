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

        AccountManager* pAccMgr = g_pApp->GetAccountManager();
        if (!pAccMgr)
        {
            return;
        }

        // auth the client firstly

        // todo: handle for guest

        TextScanner scan(ctx.m_packetText.c_str());

        bool bIsGuest = ctx.m_packetText.find("tankIDName|") == std::string::npos;
        bool bValidAuth = false;

        if (bIsGuest == false)
        {
            std::string growID = scan.GetParmString("tankIDName", 1);
            std::string password = scan.GetParmString("tankIDPass", 1);

            // todo: check if the users account is already logged in
            // disconnect them and allow this user to join
            bValidAuth = pAccMgr->IsPasswordCorrect(pAccMgr->GetUserIDByLogonName(growID), password);
        }

        if (!bValidAuth)
        {
            ::printf("Client auth wasn't valid, sending logon fail and disconnecting them...\n");
            ctx.m_pClient->SendPacket(2, "action|logon_fail");
            enet_peer_disconnect_now(ctx.m_pClient->GetENetPeer(), 0);
        }
        else
        {
            ::printf("Client valid auth!\n");
            // todo: Load data from SQL to GameClients fields
        }

        // 2.88 OnSuperMainStartAcceptLogonFB211131ddf
        // 3.02 OnSuperMainStartAcceptLogonHrdxs47254722215a

        VariantList var1;
        var1.Get(0).Set("OnSuperMainStartAcceptLogonHrdxs47254722215a");
        var1.Get(1).Set(g_pApp->GetItemInfoHash());
        var1.Get(2).Set("growtopia2.com");
        var1.Get(3).Set("cache/");
        var1.Get(4).Set("cc.madcat.app wtf.lol.fp");
        var1.Get(5).Set("proto=93|choosemusic=audio/mp3/about_theme.mp3|active_holiday=0|server_tick=12419248|");
        ctx.m_pClient->SendGlobalFunctionCall(var1, 0, -1);

        //::printf("Items.dat hash is %u\n", g_pApp->GetItemInfoHash());

        //VariantList var2{ "OnRequestWorldSelectMenu", "default|based server v3\nadd_filter|\nset_max_rows|4\nadd_floater|wow|50|0.5|3529161471" };
        //ctx.m_pClient->SendGlobalFunctionCall(var2, 0, -1);
    }
}