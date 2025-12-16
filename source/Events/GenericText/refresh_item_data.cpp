#include "../EventManager.h"
#include "../../CoreApp.h"
#include <enet/include/enet.h>
#include <proton/MiscUtils.h>

namespace event
{
    void refresh_item_data(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        // todo check is client authed, if not then dc them right here.

        ::printf("Client requested item data!\n");

        VariantList msg{ "OnConsoleMessage", "`oOne moment, updating items...``" };
        ctx.m_pClient->SendGlobalFunctionCall(msg, 0, -1);

        GameUpdatePacket pkt;
        pkt.type = PACKET_SEND_ITEM_DATABASE_DATA;
        pkt.netID = -1;
        pkt.flags |= NET_GAME_PACKET_FLAG_EXTENDED;

        // testing sending one from based2
        // future note: if your client is fresh install you NEED to use the modern items data otherwise it will crash!
        // after the client has finished downloading necessary textures the game will no longer crash with old items data.

        uint8* pItemDataBuffer = LoadFileIntoMemoryBasic("items.dat", &pkt.extraDataSize);
        ctx.m_pClient->SendPacketRaw(4, &pkt, sizeof(GameUpdatePacket), pItemDataBuffer);
        

        ctx.m_pClient->m_bDidSendItemData = true;

        // normal 
        /*
        pkt.extraDataSize = g_pApp->GetItemInfoBufferSize();

        ctx.m_pClient->SendPacketRaw(4, &pkt, sizeof(GameUpdatePacket), g_pApp->GetItemInfoBuffer());
        */
    }
}