#pragma once

#include <iostream>
#include "PacketSender.h"
#include "../SQL/AccountManager.h"

//struct PlayerSQLField;

enum class eClientAuthStatus
{
    NOT_AUTHENTICATED = 0,
    AUTHENTICATED,
    SIZE
};

class GameClient : public PacketSender
{
public:
    GameClient(ENetPeer* pPeer) : m_pPeer(pPeer), PacketSender(pPeer) {}
    //~GameClient();
    
    // getters
    ENetPeer* GetENetPeer() const;
    std::string GetName() const;
    uint64_t GetUserID() const;
    eClientAuthStatus GetAuthStatus() const;
    PlayerSQLField GetSQLDataCached() const;
    std::string GetDisplayName(bool bRemovePrefixAndSuffix = false) const;

    // setters
    void SetName(const std::string& newName);
    void SetUserID(uint64_t userID);
    void SetAuthStatus(eClientAuthStatus status);
    void SetSQLDataCached(PlayerSQLField psql);


    // methods
    void SendHelloPacket();

private:
    ENetPeer* m_pPeer = NULL;
    eClientAuthStatus m_authStatus = eClientAuthStatus::NOT_AUTHENTICATED;
    PlayerSQLField m_sqlData{};

    std::string m_name{};
    uint64_t m_userID = 0;
    int64_t m_gems = 0;
};
