#include "Inventory.h"
#include "GameClient.h"
#include "PacketUtils.h"
#include "../Manager/ItemDB.h"
#include <proton/MiscUtils.h>

void PlayerInventory::SetGameClient(GameClient* pClient)
{
    m_pClient = pClient;

    Reset();
}

void PlayerInventory::Serialize(uint8_t* pData, int& offset, bool bWriteToMem)
{
    MemorySerialize(m_version, pData, offset, bWriteToMem);
    MemorySerialize(m_size, pData, offset, bWriteToMem);
    if (bWriteToMem)
    {
        m_count = static_cast<uint8_t>(m_items.size());
    }

    MemorySerialize(m_count, pData, offset, bWriteToMem);
    if (bWriteToMem)
    {
        for (const auto& pair : m_items)
        {
            uint16_t id = pair.first;
            uint8_t count = pair.second;
            uint8_t flag = 0;

            MemorySerialize(id, pData, offset, bWriteToMem);
            MemorySerialize(count, pData, offset, bWriteToMem);
            MemorySerialize(flag, pData, offset, bWriteToMem);   
        }
    }
    else
    {
        for (int i = 0; i < m_count; i++)
        {
            uint16_t itemID{};
            uint8_t itemCount{};
            uint8_t flag = 0;

            MemorySerialize(itemID, pData, offset, bWriteToMem);
            MemorySerialize(itemCount, pData, offset, bWriteToMem);
            MemorySerialize(flag, pData, offset, bWriteToMem);

            m_items.insert_or_assign(itemID, itemCount);
        }
    }
}

uint32_t PlayerInventory::GetEstimatedMem()
{
    uint32_t res = 0;
    res += sizeof(uint8_t);
    res += sizeof(uint32_t);
    res += sizeof(uint8_t);
    for (int i = 0; i < m_items.size(); i++)
    {
        res += sizeof(uint16_t);
        res += sizeof(uint8_t);
        res += sizeof(uint8_t);
    }

    return res;
}

void PlayerInventory::SendData()
{
    GameUpdatePacket pkt;
    pkt.type = PACKET_SEND_INVENTORY_STATE;
    pkt.flags = NET_GAME_PACKET_FLAG_EXTENDED;
    pkt.netID = 1;
    pkt.extraDataSize = this->GetEstimatedMem();
    
    uint8_t* pData = (uint8_t*)::malloc(pkt.extraDataSize);

    int offset = 0;
    this->Serialize(pData, offset, true);

    m_pClient->SendPacketRaw(4, &pkt, sizeof(GameUpdatePacket), pData);

    ::free(pData);
}

void PlayerInventory::AddItem(uint16_t itemID, uint8_t count)
{
    if (count > 200)
    {
        ::printf("PlayerInventory::AddItem() Error, called trying to give more than 200 of item ID %d\n", itemID);
        return;
    }

    m_items.insert_or_assign(itemID, count);
}

void PlayerInventory::RemoveItem(uint16_t itemID, uint8_t count)
{
    m_items[itemID] -= count;
}

bool PlayerInventory::HasItem(uint16_t itemID, uint8_t count)
{
    auto it = m_items.find(itemID);

    if (it != m_items.end())
    {
        if (it->second < count)
        {
            return false;
        }
        return true;
    }

    return false;
}

void PlayerInventory::Reset()
{
    m_items.clear();

    m_size = 16;
    AddItem(ITEM_ID_FIST, 1);
    AddItem(ITEM_ID_WRENCH, 1);
}