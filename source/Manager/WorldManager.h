#pragma once

#include <iostream>
#include <vector>
#include <proton/MiscUtils.h>
#include <memory>

class World;

class WorldManager
{
public:
    ~WorldManager();

    void AddWorld(World* pWorld);
    void LoadDataFromSQL();

    void RemoveWorld(World* pWorld);
    World* GetWorldByName(const std::string& worldName);


private:

    std::vector<World*> m_worlds;
};