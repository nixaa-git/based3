#pragma once

#include <unordered_map>

class GameClient; // fwd decl

class NetObjectManager
{
public:
    ~NetObjectManager();

    std::unordered_map<int, GameClient*> GetObjects();
    void AddObject(int netID, GameClient* pClient);
    bool RemoveObject(int netID);
private:
    int m_lastNetIDAdded = 0;
    std::unordered_map<int, GameClient*> m_objects;
};