#pragma once

#include <iostream>
#include "PacketSender.h"
#include "Inventory.h"
#include "../SQL/AccountManager.h"

enum class eClientAuthStatus
{
    NOT_AUTHENTICATED = 0,
    AUTHENTICATED,
    SIZE
};

class World;

class GameClient : public PacketSender
{
public:
    GameClient(ENetPeer* pPeer) : m_pPeer(pPeer), PacketSender(pPeer) 
    {
        m_inventory.SetGameClient(this);
    }
    
    // getters
    ENetPeer* GetENetPeer() const;
    std::string GetName() const;
    uint64_t GetUserID() const;
    eClientAuthStatus GetAuthStatus() const;
    PlayerSQLField GetSQLDataCached() const;
    PlayerInventory& GetInventory();
    std::string GetDisplayName(bool bRemovePrefixAndSuffix = false) const;
    World* GetCurrentWorld() const;
    int GetNetID();
    int64_t GetSkinColour() const;

    // setters
    void SetName(const std::string& newName);
    void SetUserID(uint64_t userID);
    void SetAuthStatus(eClientAuthStatus status);
    void SetSQLDataCached(PlayerSQLField psql);
    void SetCurrentWorld(World* pWorld);
    void SetNetID(int netID);
    void SetSkinColour(int64_t skinCol);

    // methods
    void SendHelloPacket();

    bool m_bDidSendItemData = false;

private:
    ENetPeer* m_pPeer = NULL;
    eClientAuthStatus m_authStatus = eClientAuthStatus::NOT_AUTHENTICATED;
    PlayerSQLField m_sqlData{};

    std::string m_name{};
    uint64_t m_userID = 0;
    int64_t m_gems = 0;
    int64_t m_skinColour = 2190853119;
    PlayerInventory m_inventory;
    World* m_pCurrentWorld = nullptr;
    int m_netID = 0;
};
