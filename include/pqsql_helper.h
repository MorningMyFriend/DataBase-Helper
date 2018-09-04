//
// Created by cuizhou on 18-9-4.
//

#ifndef INTERFACEREDISSQL_PQSQL_HELPER_H
#define INTERFACEREDISSQL_PQSQL_HELPER_H

#include <memory>
#include "pqxx/pqxx"
#include "interface_database.h"

class PqsqlHelper: public InterfaceDataBase {
public:
    PqsqlHelper():_conn(nullptr){}
    ~PqsqlHelper(){}

public:
    bool Connect(const Ip &ip, const Port &port, const Password &password) override {};

    bool Connect(const Ip &ip, const DbName &dbname, const Usr &usr, const Password &password) override;

    bool Connect(const Ip &ip, const Port &port, const Usr &usr, const Password &password) override {};

    bool
    Connect(const Ip &ip, const Port &port, const DbName &dbname, const Usr &usr, const Password &password) override {};

    bool ExcuteCommand(const std::string &command) override;

private:
    std::shared_ptr<pqxx::connection> _conn;

};


#endif //INTERFACEREDISSQL_PQSQL_HELPER_H
