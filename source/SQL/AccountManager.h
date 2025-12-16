#pragma once

#include "MySQLManager.h"

class GameClient;

struct PlayerSQLField
{
public:
    int64_t ID;
    int64_t DateCreated;
    char* Name;
    int Score;
    char* IP;
    char* Country;
    int Platform;
    int Hash;
    int Settings;
    int IAP;
    int MoneySpent;
    int IAPToday;
    int IAPTransactions;
    int Tapjoy;
    int Coins;
    int CoinsGiven;
    int SecondHash;
    char* LogonName;
    int ItemsA;
    int Warnings;
    int Mutes;
    char* Email;
    int WorldID;
    float PosX;
    float PosY;
    char* Inventory;
    int SkinColor;
    int WorldCreatedToday;
    int WorldCreated;
    int TimesDied;
    int TotalLogons;
    int DoorsUsed;
    char* PasswordHash;
};

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
    void LoadDataFromSQL(GameClient* pClient, int userID);
    void SaveProfile(GameClient* pClient);

    MYSQL* GetConnection();

private:
    MySQLManager* m_pSQLManager = NULL;
};