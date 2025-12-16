#pragma once

#include "MySQLManager.h"

struct WorldSQLField
{
    int64_t ID = -1;
    int64_t DateCreated = 0;
    int64_t DateLastLogin = 0;
    char* Name = nullptr;
    char* Description = nullptr;
    int Version = 0;
    int Bits = 0;
};

class World;

class WorldDBManager
{
public:
    WorldDBManager();

    bool Init();
    bool CreateTablesIfNeeded();
    bool UpdateDatabaseIfNeeded();

    bool DoesWorldExist(const std::string& worldName);
    bool LoadDataIntoCache(World* pWorld);
    int AddByName(World* pWorld);

private:
    MySQLManager* m_pSQLManager = NULL;
};