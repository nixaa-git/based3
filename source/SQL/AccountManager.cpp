#include "AccountManager.h"
#include "MySQLManager.h"

AccountManager::AccountManager()
{
    m_pSQLManager = GetSQLManager();
}

void AccountManager::CreateTablesIfNeeded()
{
    if (DoesTableExist(m_pSQLManager))
    {
        return false;
    }

    std::string query = "CREATE TABLE players (ID INT NOT NULL AUTO_INCREMENT PRIMARY KEY, DateCreated DATE NOT NULL,"
        "NAME CHAR(10) NOT NULL,"
        "Score INT DEFAULT 0,"
        "IP CHAR(20) NOT NULL DEFAULT '0.0.0.0',"
        "Country CHAR(3) NOT NULL DEFAULT '00',"

    return true;
}