#include "WorldDBManager.h"
#include "../World/World.h"
#include <proton/MiscUtils.h>

WorldDBManager::WorldDBManager()
{
    m_pSQLManager = GetSQLManager();
}

bool WorldDBManager::Init()
{
    if (m_pSQLManager->Init("localhost", "root", "password", "grow1_buildonet"))
    {
        if (m_pSQLManager->Query("create database grow1_buildonet", true))
        {
            ::printf("Main database created\n");
        }
        else 
        {
            ::printf("Unable to create main database, it probably already exists\n");
        }

        // why does seth call it twice? we shall never know..

        if (CreateTablesIfNeeded())
        {
            if (!UpdateDatabaseIfNeeded())
            {
                ::printf("Unable to update player database\n");
                return false;
            }

            return true;
        }
    }
    else
    {
        ::printf("Error initializing mySQL manager\n");
        return false;
    }

    return false;
}

bool WorldDBManager::CreateTablesIfNeeded()
{
    if (m_pSQLManager->DoesTableExist("worlds", true))
    {
        return false;
    }

    ::printf("Worlds table doesn't exist, create it\n");

    std::string query = "CREATE TABLE worlds ("
        "ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
        "DateCreated DATE DEFAULT NULL,"
        "DateLastLogin DATETIME DEFAULT NULL,"
        "Name CHAR(24) NOT NULL,"
        "Description CHAR(128) NOT NULL,"
        "Version INT DEFAULT 0,"
        "Bits INT DEFAULT 0)";

    if (m_pSQLManager->Query(query, false))
    {
        ::printf("Worlds table created\n");
    }
    else 
    {
        ::printf("Error creating worlds table");
    }

    return true;
}

bool WorldDBManager::UpdateDatabaseIfNeeded()
{
    // no updates yet
    return true;
}

bool WorldDBManager::DoesWorldExist(const std::string& worldName)
{
    std::string query = "SELECT ID FROM worlds WHERE Name = '" + m_pSQLManager->EscapeString(ToLowercase(worldName))
        + "'";
        
    if (m_pSQLManager->Query(query, false))
    {
        MYSQL_RES* result;
        MYSQL_ROW row;

        result = mysql_store_result(m_pSQLManager->GetConnection());

        int numRows = mysql_num_rows(result);

        if (numRows > 0)
        {
            return true;
        }
    }

    return false;
}

bool WorldDBManager::LoadDataIntoCache(World* pWorld)
{
    if (!pWorld)
    {
        return false;
    }

    const std::string& worldName = pWorld->GetName();

    std::string query = "SELECT * FROM worlds WHERE Name = '" + m_pSQLManager->EscapeString(ToLowercase(worldName))
        + "'";
        
    if (m_pSQLManager->Query(query, false))
    {
        MYSQL_RES* result;
        MYSQL_ROW row;

        result = mysql_store_result(m_pSQLManager->GetConnection());

        int numRows = mysql_num_rows(result);

        if (numRows > 0)
        {
            row = mysql_fetch_row(result);

            WorldSQLField field;
            field.ID = ::atoi(row[0]);
            field.DateCreated = ::atoi(row[1]);
            field.DateLastLogin = ::atoi(row[2]);
            field.Name = row[3];
            field.Description = row[4];
            field.Version = ::atoi(row[5]);
            field.Bits = ::atoi(row[6]);
            pWorld->SetSQLDataCached(field);

            mysql_free_result(result);
            return true;
        }
    }

    return false;
}

int WorldDBManager::AddByName(World* pWorld)
{
    if (!pWorld)
    {
        return -1;
    }

    const std::string& worldName = pWorld->GetName();

    if (DoesWorldExist(worldName))
    {
        ::printf("World %s already exists, not adding\n", worldName.c_str());
        return -1;
    }

    std::string query = "INSERT INTO worlds SET DateCreated = SYSDATE(),"
        "DateLastLogin = NOW(),"
        "Description = '',"
        "Version = 15,"
        "Name = '" + m_pSQLManager->EscapeString(ToLowercase(worldName)) + "'";

    if (m_pSQLManager->Query(query, false))
    {
        ::printf("Added world %s to SQL!\n", worldName.c_str());
        return m_pSQLManager->GetLastAutoIncrementInsertID();
    }

    return -1;
}