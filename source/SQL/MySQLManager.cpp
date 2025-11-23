#include "MySQLManager.h"

void MySQLManager::Init(const char* host, const char* name, const char* password, const char* dbName)
{
    /*
    m_pDriver = sql::mysql::get_driver_instance();
    m_pCon(m_pDriver->connect(host, name, password));

    m_pCon->setSchema(dbName);
    */
}

bool MySQLManager::DoesTableExist(std::string table)
{
    /*
    try
    {
        //std::auto_ptr<sql::Statement> stmt(m_pCon->createStatement());
        
        //std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SHOW TABLES LIKE '" + table + "'"));
    
        X
        while (res->next())
        {
            ::printf("MySQLManager::DoesTableExist() statement result was %s\n", res->getString(1));
        }

        return true;
    } 
    catch (sql::SQLException& e)
    {
        return false;
    }*/

    return false;
}