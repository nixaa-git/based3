#pragma once

#include "MySQLManager.h"

class AccountManager
{
public:
    AccountManager();

    void CreateTablesIfNeeded();

    MySQL* GetConnection();

private:
    MySQLManager* m_pSQLManager = NULL;
};