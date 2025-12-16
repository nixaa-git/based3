#pragma once

#include <iostream>
#include "Network/ENetServer.h"
#include "Events/EventManager.h"
#include "Manager/ItemInfoManager.h"
#include "Manager/WorldManager.h"
#include "SQL/MySQLManager.h"
#include "SQL/AccountManager.h"
#include "SQL/WorldDBManager.h"

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
    void CreateDirsIfNeeded();

    // getters
    ENetServer* GetENetServer();
    MySQLManager* GetSQLManager();
    AccountManager* GetAccountManager();
    WorldDBManager* GetWorldDBManager();
    WorldManager* GetWorldManager();
    EventManager* GetEventManager();
    ItemInfoManager* GetItemInfoManager();
    uint8_t* GetItemInfoBuffer();
    uint32_t GetItemInfoBufferSize();
    uint32_t GetItemInfoHash();

private:
    ENetServer* m_pENetServer = NULL;
    MySQLManager* m_pSQLManager = NULL;
    AccountManager* m_pAccountManager = NULL;
    WorldDBManager* m_pWorldDBManager = NULL;
    EventManager* m_pEventManager = NULL;
    ItemInfoManager* m_pItemInfoManager = NULL;
    WorldManager* m_pWorldManager = NULL;
    uint8_t* m_pItemInfoBuffer = NULL;
    int32_t m_itemInfoBufferSize = NULL;
    uint32_t m_itemInfoHash = NULL;
};

extern CoreApp* g_pApp;