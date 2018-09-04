//
// Created by cuizhou on 18-9-3.
//

#ifndef INTERFACEREDISSQL_IMPLEMENTATION_DATABASE_H
#define INTERFACEREDISSQL_IMPLEMENTATION_DATABASE_H


#include "interface_database.h"
#include <memory>

#include "mysql/mysql.h"
#include "mysql_connection.h"
#include "../backup/MySqlHelper.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MySqlHelper : public InterfaceDataBase {
public:
    MySqlHelper() : _ptrDirver(nullptr), _ptrConnection(nullptr) {};

    ~MySqlHelper() {
        delete _ptrConnection;
        _ptrConnection = nullptr;
    };

public:
    bool Connect(const Ip &ip, const Port &port, const Password &password) override {}

    bool Connect(const Ip &ip, const Port &port, const Usr &usr, const Password &password) override;

    bool
    Connect(const Ip &ip, const Port &port, const DbName &dbname, const Usr &usr, const Password &password) override;

    bool EnterDatabse(const DbName &dbName);

    bool ExcuteCommand(const std::string &command) override;

    bool ExeSQLUpdate(std::string sql);

    bool ExeSQLQuery(std::string sql);

private:
    sql::Driver *_ptrDirver;
    sql::Connection *_ptrConnection;

private:
    void ThrowError(sql::SQLException &e);
};


#endif //INTERFACEREDISSQL_IMPLEMENTATION_DATABASE_H

// SQL Commands:
// DROP TABLE IF EXISTS test
// CREATE TABLE test(id INT)
// default localhost = "tcp://127.0.0.1:3306"
// default = 3306