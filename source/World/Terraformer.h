#pragma once

#include <proton/MiscUtils.h>

class World;

// world derives it? strange.
class Terraformer
{
public:
    Terraformer() {}
    void SetWorld(World* pWorld)
    {
        m_pWorld = pWorld;
    }

    void Clear();

    void MakeDefault();
    void MakeBeach();
    void MakeDesert();
    void MakeHarvest();
    void MakeMars();
    void MakeEmpty();
    void MakeUndersea();
    void MakeJungle();
    void MakePyramid();
    void MakeCave();
    
    void MoveDoor();
    void MoveLock();

private:
    World* m_pWorld = nullptr;
};