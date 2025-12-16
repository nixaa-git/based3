#include "Tile.h"
#include "../CoreApp.h"

void Tile::Serialize(uint8_t* pData, int& offset, bool bWriteToMem, bool bClientPacket)
{
    MemorySerialize(m_fg, pData, offset, bWriteToMem);
    MemorySerialize(m_bg, pData, offset, bWriteToMem);
    MemorySerialize(m_parent, pData, offset, bWriteToMem);
    MemorySerialize(m_flags, pData, offset, bWriteToMem);

    if (m_flags & TILEFLAG_EXTRA)
    {
        this->SerializeExtra(pData, offset, bWriteToMem, bClientPacket);
    }
}

uint32_t Tile::GetEstimatedMem(bool bClientPacket)
{
    uint32_t res = 0;
    res += sizeof(short) * 4;

    if (m_flags & TILEFLAG_EXTRA)
    {
        res += sizeof(uint8_t); // extraType

        ItemInfo* pItem = g_pApp->GetItemInfoManager()->GetItemByIDSafe(m_fg);
        switch ((eItemType)pItem->m_type)
        {
            case ITEM_TYPE_USER_DOOR:
            case ITEM_TYPE_DOOR:
            case ITEM_TYPE_PORTAL:
            {
                DoorExtra* pData = dynamic_cast<DoorExtra*>(m_pExtra);
                if (!pData)
                {
                    break;
                }

                res += pData->GetEstimatedMem(bClientPacket);
                return res;
            } break;

            case ITEM_TYPE_SIGN:
            {
                SignExtra* pData = dynamic_cast<SignExtra*>(m_pExtra);
                if (!pData)
                {
                    break;
                }

                res += pData->GetEstimatedMem(bClientPacket);
                return res;
            } break;

            case ITEM_TYPE_LOCK:
            {
                LockExtra* pData = dynamic_cast<LockExtra*>(m_pExtra);
                if (!pData)
                {
                    break;
                }

                res += pData->GetEstimatedMem(bClientPacket);
                return res;
            } break;
        }
    }

    return res;
}

void Tile::SetFG(short fg, bool bSetTileExtra)
{
    ItemInfo* pItem = g_pApp->GetItemInfoManager()->GetItemByIDSafe(static_cast<int>(fg));

    if (!pItem)
    {
        return;
    }

    if (bSetTileExtra)
    {
        m_flags |= TILEFLAG_EXTRA;
    }

    if (m_pExtra && m_pExtra->m_extraType != (eItemType)pItem->m_type)
    {
        delete m_pExtra;
        m_pExtra = nullptr;

        if (m_flags & TILEFLAG_EXTRA)
        {
            m_flags &= ~TILEFLAG_EXTRA;
        }
    }

    m_fg = fg;

    if (!m_pExtra)
    {
        m_pExtra = GetExtraDataDefault(pItem);
    }
}

TileExtra* Tile::GetExtraDataDefault(ItemInfo* pItem)
{
    if (!pItem)
    {
        return nullptr;
    }

    TileExtra* pExtraData = nullptr;

    switch ((eItemType)pItem->m_type)
    {
        case ITEM_TYPE_USER_DOOR:
        case ITEM_TYPE_PORTAL:
        case ITEM_TYPE_DOOR:
        {
            pExtraData = new DoorExtra();
            DoorExtra* pData = dynamic_cast<DoorExtra*>(pExtraData);
            if (!pData)
            {
                break;
            }

            if (pItem->m_itemID == ITEM_ID_MAIN_DOOR)
            {
                pData->m_label = "EXIT";
            }

        } break;

        case ITEM_TYPE_SIGN:
        {
            pExtraData = new SignExtra();
            SignExtra* pData = dynamic_cast<SignExtra*>(pExtraData);
            if (!pData)
            {
                break;
            }

        } break;

        case ITEM_TYPE_LOCK:
        {
            pExtraData = new LockExtra();
            LockExtra* pData = dynamic_cast<LockExtra*>(pExtraData);
            if (!pData)
            {
                break;
            }

        } break;

        default:
        {
            pExtraData = new TileExtra();
        } break;
    }

    if (pExtraData)
    {
        pExtraData->m_extraType = (eItemType)pItem->m_type;
    }

    return pExtraData;
}

void Tile::SerializeExtra(uint8_t* pData, int& offset, bool bWriteToMem, bool bClientPacket)
{
    ItemInfo* pItem = g_pApp->GetItemInfoManager()->GetItemByIDSafe(m_fg);

    if (!pItem)
    {
        return;
    }

    switch ((eItemType)pItem->m_type)
    {
        case ITEM_TYPE_USER_DOOR:
        case ITEM_TYPE_DOOR:
        case ITEM_TYPE_PORTAL:
        {
            DoorExtra* pExtraData = dynamic_cast<DoorExtra*>(m_pExtra);
            if (!pExtraData)
            {
                return;
            }

            uint8_t extraType = TILE_EXTRA_DOOR;
            MemorySerialize(extraType, pData, offset, bWriteToMem);
            MemorySerialize(pExtraData->m_label, pData, offset, bWriteToMem);
            MemorySerialize(pExtraData->m_bIsLocked, pData, offset, bWriteToMem);
        } break;

        case ITEM_TYPE_SIGN:
        {
            SignExtra* pExtraData = dynamic_cast<SignExtra*>(m_pExtra);
            if (!pExtraData)
            {
                return;
            }

            uint8_t extraType = TILE_EXTRA_SIGN;
            MemorySerialize(extraType, pData, offset, bWriteToMem);
            MemorySerialize(pExtraData->m_label, pData, offset, bWriteToMem);
            MemorySerialize(pExtraData->m_flags, pData, offset, bWriteToMem);
        } break;

        case ITEM_TYPE_LOCK:
        {
            LockExtra* pExtraData = dynamic_cast<LockExtra*>(m_pExtra);
            if (!pExtraData)
            {
                return;
            }

            uint8_t extraType = TILE_EXTRA_LOCK;
            MemorySerialize(extraType, pData, offset, bWriteToMem);
            MemorySerialize(pExtraData->m_lockSettings, pData, offset, bWriteToMem);
            MemorySerialize(pExtraData->m_lockOwnerID, pData, offset, bWriteToMem);
            MemorySerialize(pExtraData->m_adminCount, pData, offset, bWriteToMem);

            if (bWriteToMem)
            {
                pExtraData->m_adminCount = pExtraData->m_admins.size();

                for (int i = 0; i < pExtraData->m_adminCount; i++)
                {
                    MemorySerialize(pExtraData->m_admins[i], pData, offset, bWriteToMem);
                }
            }
            else
            {
                for (int i = 0; i < pExtraData->m_adminCount; i++)
                {
                    int adminID = -1;
                    MemorySerialize(adminID, pData, offset, bWriteToMem);
                    pExtraData->m_admins.push_back(adminID);
                }
            }
        } break;
    }
}