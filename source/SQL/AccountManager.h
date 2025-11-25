#pragma once

#include "MySQLManager.h"

class GameClient;

class AccountManager
{
public:
    AccountManager();

    bool Init();
    bool CreateTablesIfNeeded();
    bool UpdateDatabaseIfNeeded();

    int64_t GetUserIDByLogonName(const std::string& logonName);
    bool AddPlayer(GameClient* pClient, const std::string& name, const std::string& country);
    bool SetPasswordByID(int userID, const std::string& newPassword);
    bool CreateGrowID(int userID, const std::string& growID, const std::string& password, const std::string& email);
    bool IsPasswordCorrect(int userID, const std::string& password);

    MYSQL* GetConnection();

private:
    MySQLManager* m_pSQLManager = NULL;
};