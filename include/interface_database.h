//
// Created by cuizhou on 18-9-3.
//

#ifndef INTERFACEREDISSQL_INTERFACE_MYSQL_H
#define INTERFACEREDISSQL_INTERFACE_MYSQL_H

#include <iostream>
#include <string>
#include <vector>


struct Ip {
    explicit Ip(std::string ip) : _ip(ip) {}

    std::string _ip;
};


struct Port {
    explicit Port(std::string port) : _port(port) {}

    std::string _port;
};

struct DbName {
    explicit DbName(std::string dbname) : _dbname(dbname) {}

    std::string _dbname;
};

struct Usr {
    explicit Usr(std::string usr) : _usr(usr) {}

    std::string _usr;
};

struct Password {
    explicit Password(std::string password) : _password(password) {}

    std::string _password;
};

class InterfaceDataBase {
public:
    InterfaceDataBase() = default;

    virtual ~InterfaceDataBase() {};

public:
    virtual bool Connect(const Ip &ip, const Port &port, const Password &password) = 0;

    virtual bool Connect(const Ip &ip, const DbName &dbname, const Usr &usr, const Password &password) = 0;

    virtual bool Connect(const Ip &ip, const Port &port, const Usr &usr, const Password &password) = 0;

    virtual bool
    Connect(const Ip &ip, const Port &port, const DbName &dbname, const Usr &usr, const Password &password) = 0;

    virtual bool ExcuteCommand(const std::string &command) = 0;

};


#endif //INTERFACEREDISSQL_INTERFACE_MYSQL_H
