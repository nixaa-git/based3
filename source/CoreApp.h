#pragma once

#include <iostream>
#include "Network/ENetServer.h"
#include "Events/EventManager.h"
#include "Manager/ItemInfoManager.h"
#include "SQL/MySQLManager.h"

class CoreApp
{
public:
    static CoreApp* Get()
    {
        static CoreApp app;
        return &app;
    }

    void Init();
    void Main();
    void InitItemData();

    // getters
    ENetServer* GetENetServer();
    MySQLManager* GetSQLManager();
    EventManager* GetEventManager();
    ItemInfoManager* GetItemInfoManager();
    uint8_t* GetItemInfoBuffer();
    uint32_t GetItemInfoBufferSize();

private:
    ENetServer* m_pENetServer = NULL;
    MySQLManager* m_pSQLManager = NULL;
    EventManager* m_pEventManager = NULL;
    ItemInfoManager* m_pItemInfoManager = NULL;
    uint8_t* m_pItemInfoBuffer = NULL;
    uint32_t m_itemInfoBufferSize = NULL;
};

extern CoreApp* g_pApp;