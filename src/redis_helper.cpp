//
// Created by cuizhou on 18-9-4.
//

#include "redis_helper.h"

using namespace std;

bool RedisHelper::Connect(const Ip &ip, const Port &port, const Password &password) {
    _conn = shared_ptr<redisContext>(redisConnect(ip._ip.c_str(), std::stoi(port._port)), redisFree);
//    _conn = redisConnect(ip._ip.c_str(), std::stoi(port._port));
    if (_conn == nullptr) {
        cerr << "connect failed: " << _conn->err << endl;
        return false;
    }

    // password to get authority
    redisReply *reply = (redisReply *) redisCommand(_conn.get(), "AUTH %s", password._password.c_str());
    if (reply == NULL) {
        cerr << "authority faied, password excute:" << _conn->err << endl;
        return false;
    } else if (reply->type == 6) {
        cerr << "authority faied, password excute:" << reply->str << endl;
        return false;
    }
    freeReplyObject(reply);
    cout << "connect successfully !" << endl;
    _ip = ip;
    _port = port;
    _password = password;
    return true;
}

bool RedisHelper::ExcuteCommand(const std::string &command) {
    if (_conn == nullptr) {
        cout << "warning: connection NULL, try to reconnect !" << endl;
    }

    redisReply *reply = (redisReply *) redisCommand(_conn.get(), command.c_str());
    switch (reply->type) {
        case 3:
            cout << reply->integer;
        case 6:
            cout << "excute get task length error:" << reply->str << endl;
            return false;
    }
}

    int RedisHelper::GetTaskLen(std::string listname) {
        if (_conn == NULL) {
            cout << "warning: connection NULL, try to reconnect !" << endl;
            if (Connect(_ip, _port, _password)) {
                cout << " reconnect success !" << endl;
            }
        }

        redisReply *reply = (redisReply *) redisCommand(_conn.get(), "llen %s", listname.c_str());
        switch (reply->type) {
            case 3:
                return reply->integer;
            case 6:
                cout << "excute get task length error:" << reply->str << endl;
                return -1;
        }
    }

    string RedisHelper::GetTaskVal(std::string listname) {
        if (_conn == NULL) {
            cout << "warning: connection NULL, try to reconnect !" << endl;
            if (Connect(_ip, _port, _password)) {
                cout << " reconnect success !" << endl;
            }
        }

        redisReply *reply = (redisReply *) redisCommand(_conn.get(), "lpop %s", listname.c_str());
        switch (reply->type) {
            case 1:
                return reply->str;
            case 6:
                cout << "excute get task length error:" << reply->str << endl;
                return "";
        }
    }