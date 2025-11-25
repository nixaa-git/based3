#include "MySQLManager.h"
#include <proton/MiscUtils.h>

MySQLManager* g_pMySQLManager = new MySQLManager();

MySQLManager* GetSQLManager()
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

    if (!mysql_real_connect(m_pMYSQL, host, name, password, dbName, 3306, NULL, NULL))
    {
        ::printf("MySQLManager::Init() Fatal error, failed to connect to %s\n", host);
        Kill();
        return false;
    }

    return true;
}

int MySQLManager::ShowError(std::string optionalLabel)
{
	if (!m_pMYSQL) return 0;

	int error = mysql_errno(m_pMYSQL);

	if (optionalLabel.length() > 128)
	{
	   //TruncateString(optionalLabel, 128);
	}

	::printf("MySQLManager error: %s %s (%s)\n", toString(error).c_str(), mysql_error(m_pMYSQL), optionalLabel.c_str());
	return error;
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
            ShowError("");
            return false;
        }

        return false;
    }

    return true;
}

bool MySQLManager::DoesTableExist(std::string table, bool bShowErrors)
{
    if (!m_pMYSQL)
    {
        ::printf("Why you trying to DoesTableExist when SQL isn't initted?\n");
        return false;
    }

    assert(m_pMYSQL);
    MYSQL_RES* result = NULL;

    bool bSuccess = Query("SHOW TABLES LIKE '"+table+"'", bShowErrors);

	if (!bSuccess) return false;

	result = mysql_store_result(m_pMYSQL);
	
	int fields = mysql_num_fields(result);
	int rows = (int)mysql_num_rows(result);
	mysql_free_result(result);
	
	return rows > 0;
}

std::string MySQLManager::EscapeString(const std::string& input)
{
	char *pBuffer = new char[input.length()*2+1];

	mysql_real_escape_string(m_pMYSQL, pBuffer, input.c_str(), (unsigned long)input.size());

	std::string ret = pBuffer;
	if (pBuffer)
    {
        ::free(pBuffer);
        pBuffer = NULL;
    }

	return ret;
}

int MySQLManager::GetLastAutoIncrementInsertID()
{
	return (int)mysql_insert_id(m_pMYSQL);
}

MYSQL* MySQLManager::GetConnection()
{
    return m_pMYSQL;
}