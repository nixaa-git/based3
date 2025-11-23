#pragma once

#include <iostream>

//#include <mysql/jdbc.h>

class MySQLManager
{
public:
    MySQLManager() {}

    void Init(const char* host, const char* name, const char* password, const char* dbName);

    bool DoesTableExist(std::string table);

private:
/*
    sql::Driver* m_pDriver = NULL;
    std::auto_ptr<sql::Connection> m_pCon = NULL*/
};