#include "WorldManager.h"
#include "../World/World.h"
#include "../CoreApp.h"
#include <filesystem>

WorldManager::~WorldManager()
{
    for (auto& world : m_worlds)
    {
        delete world;
    }
    m_worlds.clear();
}

void WorldManager::AddWorld(World* pWorld)
{
    if (!pWorld)
    {
        return;
    }

    pWorld->SetWorldID(g_pApp->GetWorldDBManager()->AddByName(pWorld));

    if (pWorld->GetWorldID() == -1)
    {
        bool bDidCache =g_pApp->GetWorldDBManager()->LoadDataIntoCache(pWorld);
        if (bDidCache)
        {
            printf("World exists so we are loading from disk...\n");
            pWorld->SetWorldID(pWorld->GetSQLDataCached().ID);
            pWorld->LoadFromDisk();
        }
        else
        {
            ::printf("World doesn't exist, generating new map...\n");
            pWorld->MakeDefault();
            //pWorld->MakeMars();
        }
    }
    else
    {
        pWorld->MakeDefault();
        //pWorld->MakeMars();
    }

    m_worlds.push_back(pWorld);
}

void WorldManager::RemoveWorld(World* pWorld)
{
    if (!pWorld)
    {
        return;
    }

    auto it = std::find(m_worlds.begin(), m_worlds.end(), pWorld);
    if (it != m_worlds.end())
    {
        m_worlds.erase(it);
    }
}

World* WorldManager::GetWorldByName(const std::string& worldName)
{
    for (auto& world : m_worlds)
    {
        if (world->GetName() == worldName)
        {
            return world;
        }
    }

    return nullptr;
}