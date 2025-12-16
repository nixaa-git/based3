#include "NetObjectManager.h"
#include "../Data/GameClient.h"

NetObjectManager::~NetObjectManager()
{
    m_objects.clear();
}

std::unordered_map<int, GameClient*> NetObjectManager::GetObjects()
{
    return m_objects;
}

void NetObjectManager::AddObject(int netID, GameClient* pClient)
{
    auto it = m_objects.find(netID);

    if (it != m_objects.end())
    {
        return;
    }

    m_objects.insert_or_assign(netID, std::move(pClient));
    m_lastNetIDAdded++;

    pClient->SetNetID(m_lastNetIDAdded);
}

bool NetObjectManager::RemoveObject(int netID)
{
    auto it = m_objects.find(netID);

    if (it != m_objects.end())
    {
        m_objects.erase(it);
        return true;
    }

    return false;
}