#pragma once

#include <iostream>
#include <cassert>

extern "C" 
{
    #include <mysql.h>
}

class MySQLManager
{
public:
    MySQLManager();
    ~MySQLManager();

    void Kill();
    bool Init(const char* host, const char* name, const char* password, const char* dbName);
    int ShowError(std::string optionalLabel);
    bool Query(std::string query, bool bShowError);
    bool DoesTableExist(std::string table, bool bShowError);
    std::string EscapeString(const std::string& input);
    int GetLastAutoIncrementInsertID();

    MYSQL* GetConnection();

private:
    MYSQL* m_pMYSQL = NULL;
    int m_opsDone = 0;
};

extern MySQLManager* GetSQLManager();