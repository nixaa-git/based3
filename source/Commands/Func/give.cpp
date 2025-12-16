#include "../CommandHandler.h"
#include "../../CoreApp.h"
#include <format>

namespace cmd
{
    void give(CMD_ARGS)
    {
        if (!ctx.m_pClient)
        {
            return;
        }

        auto args = CommandHandler::FetchArguments(ctx.m_packetText);

        /*
        args:
        1. growID or userID
        2. amount
        3. itemName or itemID
        */
        if (args.size() <= 3)
        {
            // todo send correct usage msg
            ::printf("/give invalid arg amount!\n");
            return;
        }

        bool bUsingGrowID = !isdigit(args[1].c_str()[0]);

        std::string growID = args[1];
        int64_t userID = bUsingGrowID ? ::atoi(args[1].c_str()) : -1;

        uint8_t amount = ::atoi(args[2].c_str());
        
        bool bUsingItemName = !isdigit(args[3].c_str()[0]);
        std::string itemName = args[3];
        int itemID = ::atoi(itemName.c_str());

        ItemInfo* pItem = bUsingItemName ? g_pApp->GetItemInfoManager()->GetItemByNameSafe(itemName) : g_pApp->GetItemInfoManager()->GetItemByIDSafe(itemID);
        if (!pItem)
        {
            ctx.m_pClient->SendPacket(3, "action|log\nmsg|`o>> Couldn't find that item in itemDB.");
            return;
        }

        VariantList msg{
            "OnConsoleMessage",
            std::format("`oGave `w{}`` {}", amount, pItem->m_name)
        };

        ctx.m_pClient->SendGlobalFunctionCall(msg, 0, -1);

        auto& inv = ctx.m_pClient->GetInventory();

        inv.AddItem(pItem->m_itemID, amount);

        inv.SendData();
    }
}