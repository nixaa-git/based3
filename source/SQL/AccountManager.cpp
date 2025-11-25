#include "AccountManager.h"
#include "MySQLManager.h"
#include <proton/MiscUtils.h>

AccountManager::AccountManager()
{
    m_pSQLManager = GetSQLManager();
}

bool AccountManager::Init()
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

bool AccountManager::AddPlayer(/*GameClient* pClient*/ const std::string& name, const std::string& country)
{
    std::string query = m_pSQLManager->EscapeString("INSERT INTO players SET DateCreated = SYSDATE(),"
        "DailyLogon = SYSDATE(),"
        "DateLastLogin = NOW(),"
        "Name = '" + name 
        + "', Country = '" + country
        + "', Platform = 11"
    );

    //pClient->SetUserID(m_pSQLManager->GetLastAutoIncrementInsertID());

    if (m_pSQLManager->Query(query, false))
    {
        ::printf("Added player %s (ID: %d) to SQL!\n", name.c_str(), m_pSQLManager->GetLastAutoIncrementInsertID());
    }

    return true;
}

bool AccountManager::SetPasswordByID(int userID, const std::string& newPassword)
{
    std::string query = m_pSQLManager->EscapeString("UPDATE players SET PasswordHash=UNHEX(MD5(CONCAT(LOWER('" + newPassword
        + "'), ID+3, 'worg'))) WHERE id = " + toString(userID)
    );

    if (!m_pSQLManager->Query(query, true))
    {
        ::printf("Error can't update password\n");
        return false;
    }

    return true;
}

bool AccountManager::CreateGrowID(int userID, const std::string& growID, const std::string& password, const std::string& email)
{
    std::string query = m_pSQLManager->EscapeString("UPDATE players SET LogonName = " + growID 
        + ", Email = " + email
        + " WHERE ID = " + toString(userID)
    );

    if (m_pSQLManager->Query(query, true))
    {
        SetPasswordByID(userID, password);
    }
    else
    {
        ::printf("Error can't CreateTankID\n");
        return false;
    }

    return true;
}

bool AccountManager::IsPasswordCorrect(int userID, const std::string& password)
{
    std::string query = m_pSQLManager->EscapeString("SELECT ID FROM players WHERE ID = " + toString(userID)
        + " AND PasswordHash = UNHEX(md5(CONCAT(LOWER('" 
        + "'), ID+3, 'worg')))"
    );

    if (m_pSQLManager->Query(query, true))
    {
        MYSQL_RES* result;
        MYSQL_ROW row;

        result = mysql_store_result(m_pSQLManager->GetConnection());

        if (!result)
        {
            ::printf("AccountManager::IsPasswordCorrect() got invalid mysql result\n");
            return false;
        }

        int numFields = mysql_num_fields(result);

        while (row = mysql_fetch_row(result))
        {
            if ((int)row[0] != userID)
            {
                return false;
            }

            ::printf("row [0] = %d\n", row[0]);
        }

        mysql_free_result(result);
    }

    return true;
}

bool AccountManager::CreateTablesIfNeeded()
{
    if (m_pSQLManager->DoesTableExist("players", true))
    {
        return false;
    }

    ::printf("Players table doesn't exist, create it\n");

    std::string query = "CREATE TABLE players ("
        "ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
        "DateCreated DATE NOT NULL,"
        "Name CHAR(18) NOT NULL,"
        "Score INT DEFAULT 0,"
        "IP CHAR(20) NOT NULL DEFAULT '0.0.0.0',"
        "Country CHAR(3) NOT NULL DEFAULT '00',"
        "Platform INT DEFAULT 0,"
        "Hash INT DEFAULT 0,"
        "Settings INT DEFAULT 0,"
        "IAP INT DEFAULT 0,"
        "MoneySpent INT DEFAULT 0,"
        "IAPToday INT DEFAULT 0,"
        "IAPTransactions INT DEFAULT 0,"
        "Tapjoy INT DEFAULT 0,"
        "Coins INT DEFAULT 0,"
        "CoinsGivenToday INT DEFAULT 0,"
        "SecondHash INT DEFAULT 0,"
        "LogonName CHAR(20) DEFAULT '',"
        "ItemsA INT DEFAULT 0,"
        "Warnings INT DEFAULT 0,"
        "Mutes INT DEFAULT 0,"
        "Email CHAR(64) DEFAULT '',"
        "WorldID INT DEFAULT -1,"
        "PosX FLOAT DEFAULT 0,"
        "PosY FLOAT DEFAULT 0,"
        "Inventory VARBINARY(1),"
        "SkinColor INT DEFAULT 0,"
        "WorldCreatedToday INT DEFAULT 0,"
        "WorldCreated INT DEFAULT 0,"
        "TimesDied INT DEFAULT 0,"
        "TotalLogons INT DEFAULT 0,"
        "DoorsUsed INT DEFAULT 0)";

    // missing playmods varbinary and etc
    
    if (m_pSQLManager->Query(query, false))
    {
        ::printf("Player table created\n");
    }
    else 
    {
        ::printf("Error creating player table");
    }

    return true;
}

bool AccountManager::UpdateDatabaseIfNeeded()
{
    if (m_pSQLManager->Query("alter table players ADD PasswordHash BINARY(16) DEFAULT ''", true))
    {

    }

    return true;
}