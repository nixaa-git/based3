#include "MySQLManager.h"

MySQLManager* g_pMySQLManager() = new MySQLManager();

MySQLManager* GetMySQLManager()
{
    return g_pMySQLManager;
}

MySQLManager::MySQLManager()
{
    m_pMYSQL = NULL;
}

MySQLManager::~MySQLManager()
{
    Kill();
}

void MySQLManager::Kill()
{
    if (m_pMYSQL)
    {
        mysql_close(m_pMYSQL);
        m_pMYSQL = NULL;
    }
}

bool MySQLManager::Init(const char* host, const char* name, const char* password, const char* dbName)
{
    ::printf("MySQL client version: %s\n", mysql_get_client_info());

    m_pMYSQL = mysql_init(NULL);

    if (!mysql_real_connect(m_pMYSQL, host, name, password, dbName, NULL, NULL, NULL))
    {
        ::printf("MySQLManager::Init() Fatal error, failed to connect to %s\n", host);
        Kill();
        return false;
    }

    return true;
}

bool MySQLManager::Query(std::string query, bool bShowError)
{
    if (!m_pMYSQL)
    {
        ::printf("Why you trying to Query when SQL isn't initted?\n");
        return false;
    }

    assert(m_pMYSQL);

    m_opsDone++;

    if (mysql_query(m_pMYSQL, query.c_str()))
    {
        if (bShowError)
        {
            //
            ::printf("Got some error sql query manager !\n");
            return false;
        }

        return false;
    }

    return true;
}

bool MySQLManager::DoesTableExist(std::string table)
{
    if (!m_pMYSQL)
    {
        ::printf("Why you trying to DoesTableExist when SQL isn't initted?\n");
        return false;
    }

    assert(m_pMYSQL);

    std::string query = "SHOW TABLES LIKE '" + table + "'";

    MYSQL_RES* res = NULL;

    if (mysql_query(m_pMYSQL, query.c_str()))
    {
        res = mysql_store_result(m_pMYSQL);
    }

    int fields = mysql_num_fields(res);
    int rows = (int)mysql_num_rows(res);
    mysql_free_result(res);

    return rows > 0;
}

MYSQL* MySQLManager::GetConnection()
{
    return m_pMYSQL;
}