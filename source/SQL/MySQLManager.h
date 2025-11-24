#pragma once

#include <iostream>
#include <cassert>
#include <mysql.h>

class MySQLManager
{
public:
    MySQLManager();
    ~MySQLManager();

    void Kill();
    bool Init(const char* host, const char* name, const char* password, const char* dbName);

    bool Query(std::string query, bool bShowError);
    bool DoesTableExist(std::string table);

    MYSQL* GetConnection();

private:
    MYSQL* m_pMYSQL = NULL;
    int m_opsDone = 0;
};

extern MySQLManager* GetSQLManager();