//
// Created by cuizhou on 18-9-4.
//

#ifndef INTERFACEREDISSQL_REDIS_HELPER_H
#define INTERFACEREDISSQL_REDIS_HELPER_H

//#======redis========
//redisip=116.62.174.64
//redisport=6379
//redispsw=redisPSW0328

//当命令被成功执行后redisCommand会有相应的返回值。
//如果有错误发生，返回值为NULL并且redisReply结构体中的err变量将会被设置成相应的值。
//一旦有错误发生context不能被重用并且需要建立一个新的连接。

//#define REDIS_REPLY_STRING 1
//#define REDIS_REPLY_ARRAY 2
//#define REDIS_REPLY_INTEGER 3
//#define REDIS_REPLY_NIL 4
//#define REDIS_REPLY_STATUS 5
//#define REDIS_REPLY_ERROR 6

#include "interface_database.h"
#include <hiredis/hiredis.h>
#include <boost/shared_ptr.hpp>

class RedisHelper : public InterfaceDataBase {
public:
    RedisHelper() : _conn(nullptr, redisFree), _ip(Ip("")), _port(Port("")), _password(Password("")) {};

    ~RedisHelper() {};

    bool Connect(const Ip &ip, const Port &port, const Password &password) override;

    bool Connect(const Ip &ip, const DbName &dbname, const Usr &usr, const Password &password) override {};

    bool Connect(const Ip &ip, const Port &port, const Usr &usr, const Password &password) override {};

    bool
    Connect(const Ip &ip, const Port &port, const DbName &dbname, const Usr &usr, const Password &password) override {};

    bool ExcuteCommand(const std::string &command) override;

public:
    int GetTaskLen(std::string listname);

    std::string GetTaskVal(std::string listname);

private:
    std::shared_ptr<redisContext> _conn;
    Ip _ip;
    Port _port;
    Password _password;
};


#endif //INTERFACEREDISSQL_REDIS_HELPER_H
