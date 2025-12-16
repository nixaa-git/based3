#include "../EventManager.h"
#include <format>
#include "../../World/World.h"
#include <proton/TextScanner.h>
#include "../../CoreApp.h"

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

        TextScanner scan{ ctx.m_packetText.c_str() };
        std::string worldName = scan.GetParmString("name", 1);

        if (worldName.empty())
        {
            ::printf("Client sent empty world name in join_request\n");
            return;
        }

        World* pWorld = g_pApp->GetWorldManager()->GetWorldByName(worldName);
        if (!pWorld)
        {
            pWorld = new World({100, 60});
            pWorld->SetName(worldName);
            g_pApp->GetWorldManager()->AddWorld(pWorld);
        }

        ctx.m_pClient->SetCurrentWorld(pWorld);
        pWorld->GetNetObjectManager().AddObject(ctx.m_pClient->GetNetID(), ctx.m_pClient);

        pWorld->SaveToDisk();

        VariantList varmsg{ 
            "OnConsoleMessage",
            std::format("`oWorld `w{}`` entered.  There are `w{}`` other people here, `w1`` online.", pWorld->GetName(), pWorld->GetNetObjectManager().GetObjects().size() - 1)
        };
        ctx.m_pClient->SendGlobalFunctionCall(varmsg, 0, -1);

        CL_Vec2i mainDoorPos = pWorld->GetWorldTileMap().GetMainDoorPos();

        pWorld->SendMapData(ctx.m_pClient);
        const char* spawn = "";
        TextScanner onspawntxt;
        onspawntxt.SetupFromMemoryAddress(spawn);

        onspawntxt.AddParmString("spawn", "avatar");
        onspawntxt.AddParmString("netID", toString(ctx.m_pClient->GetNetID()));
        onspawntxt.AddParmString("userID", toString(ctx.m_pClient->GetUserID()));
        onspawntxt.AddParmString("colrect", "0|0|20|30");
        onspawntxt.AddParmString("posXY", std::format("{}|{}", mainDoorPos.x * 32, mainDoorPos.y * 32));
        onspawntxt.AddParmString("name", ctx.m_pClient->GetDisplayName());
        onspawntxt.AddParmString("country", "us");
        onspawntxt.AddParmString("invis", "0");
        onspawntxt.AddParmString("mstate", "1");
        onspawntxt.AddParmString("smstate", "1");
        onspawntxt.AddParmString("onlineID", "");
        onspawntxt.AddParmString("type", "local");

        VariantList spawnvar{};
        spawnvar.Get(0).Set("OnSpawn");
        spawnvar.Get(1).Set(onspawntxt.GetAllRaw());

        ctx.m_pClient->SendGlobalFunctionCall(spawnvar, -1, -1);

        VariantList clothingvar{};
        clothingvar.Get(0).Set("OnSetClothing");
        clothingvar.Get(1).Set(CL_Vec3f(0.f, 0.f, 0.f));
        clothingvar.Get(2).Set(CL_Vec3f(0.f, 0.f, 0.f));
        clothingvar.Get(3).Set(CL_Vec3f(1674.f, 0.f, 0.f));
        clothingvar.Get(4).Set((int)ctx.m_pClient->GetSkinColour());
        clothingvar.Get(5).Set(CL_Vec3f(0.f, 0.f, 0.f));
        ctx.m_pClient->SendGlobalFunctionCall(clothingvar, -1, ctx.m_pClient->GetNetID());

        // add essential items
        ctx.m_pClient->GetInventory().AddItem(ITEM_ID_FIST, 1);
        ctx.m_pClient->GetInventory().AddItem(ITEM_ID_WRENCH, 1);
        ctx.m_pClient->GetInventory().AddItem(ITEM_ID_DIRT, 50);

        ctx.m_pClient->GetInventory().SendData();
    }
}