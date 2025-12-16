#pragma once

#include <iostream>
#include <unordered_map>
#include <enet/include/enet.h>

class GameClient;

class PlayerInventory
{
public:
    void SetGameClient(GameClient* pClient);
    void Serialize(uint8_t* pData, int& offset, bool bWriteToMem);
    uint32_t GetEstimatedMem();
    void SendData();

    // funcs
    void AddItem(uint16_t itemID, uint8_t amount = 1);
    void RemoveItem(uint16_t itemID, uint8_t amount = 1);
    bool HasItem(uint16_t itemID, uint8_t amount = 1);
    void Reset();

private:
    uint8_t m_version = 0;
    uint32_t m_size = 16;
    uint8_t m_count = 0;

    std::unordered_map<uint16_t, uint8_t> m_items{};
    GameClient* m_pClient = nullptr;
};