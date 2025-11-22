#include "../EventManager.h"
#include "../../CoreApp.h"
#include <enet/include/enet.h>

namespace event
{
    void refresh_item_data(EVENT_HANDLER_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        ::printf("Client requested item data!\n");

        GameUpdatePacket pkt;
        pkt.type = PACKET_SEND_ITEM_DATABASE_DATA;
        pkt.netID = -1;
        pkt.flags |= NET_GAME_PACKET_FLAG_EXTENDED;
        pkt.extraDataSize = g_pApp->GetItemInfoBufferSize();

        ctx.m_pClient->SendPacketRaw(4, &pkt, sizeof(GameUpdatePacket), g_pApp->GetItemInfoBuffer());
    }
}