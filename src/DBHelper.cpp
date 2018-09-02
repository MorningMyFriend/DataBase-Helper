//
// Created by wurui on 18-5-23.
//

#include <json/json.h>
#include "DBHelper.h"

namespace db_helper {

// static member
    const string RedisHelper::_listname = "ocr_task_list";

    RedisHelper::RedisHelper() {
        _ip = "116.62.174.64";
        _port = "6379";
        _password = "redisPSW0328";
        if (Connect()) {
            cout << "connect success!" << endl;
        }
    }

    RedisHelper::RedisHelper(string ip, string port, string password) :
            _ip(ip),
            _port(port),
            _password(password) {
        if (Connect()) {
            cout << "connect success!" << endl;
        }
    }

    bool RedisHelper::Connect() {
        _conn = redisConnect(_ip.c_str(), std::stoi(_port));
        if (_conn == NULL) {
            cerr << "connect failed: " << _conn->err << endl;
            return false;
        }
        redisReply *reply = (redisReply *) redisCommand(_conn, "AUTH %s", _password.c_str());
        if (reply == NULL) {
            cerr << "connect faied, password excute:" << _conn->err << endl;
            return false;
        } else if (reply->type == 6) {
            cerr << "connect faied, password excute:" << reply->str << endl;
            return false;
        }
        freeReplyObject(reply);
        return true;
    }

    int RedisHelper::GetTaskLen() {
        if (_conn == NULL) {
            cout << "warning: connection NULL, try to reconnect !" << endl;
            if (Connect()) {
                cout << " reconnect success !" << endl;
            }
        }

        redisReply *reply = (redisReply *) redisCommand(_conn, "llen %s", _listname.c_str());
        switch (reply->type) {
            case 3:
                return reply->integer;
            case 6:
                cout << "excute get task length error:" << reply->str << endl;
                return -1;
        }
    }

    string RedisHelper::GetTaskVal() {
        if (_conn == NULL) {
            cout << "warning: connection NULL, try to reconnect !" << endl;
            if (Connect()) {
                cout << " reconnect success !" << endl;
            }
        }

        redisReply *reply = (redisReply *) redisCommand(_conn, "lpop %s", _listname.c_str());
        switch (reply->type) {
            case 1:
                return reply->str;
            case 6:
                cout << "excute get task length error:" << reply->str << endl;
                return "";
        }
    }

    using namespace pqxx;

    PqSqlHelper::PqSqlHelper() : _dbname("cuizhou"),
                                 _user("postgres"),
                                 _password("postgresPSW0328"),
                                 _ip("116.62.174.64") {
        if (Connect()) cout << "connect success" << endl;
    }

    PqSqlHelper::PqSqlHelper(string dbname, string user, string password, string ip) : _dbname(dbname),
                                                                                       _user(user),
                                                                                       _password(password),
                                                                                       _ip(ip) {
        if (Connect()) cout << "connect success" << endl;
    }

    bool PqSqlHelper::Connect() {
        try {
            string sql = "dbname=" + _dbname + " user=" + _user + " password=" + _password + " hostaddr=" + _ip;
            _conn = new connection(sql);
            if (_conn->is_open()) {
                cout << "connect database successfully: " << _conn->dbname() << endl;
            } else {
                cout << "failed connect database" << endl;
                return true;
            }
            _conn->disconnect();
        } catch (const std::exception &e) {
            cerr << e.what() << std::endl;
            return false;
        }
    }

    bool PqSqlHelper::Update(string status, string json, string id) {
        try {
            if (status == "2") {
                json = "识别失败";
            }
            string sql = "UPDATE CZ_TASK SET tstate = " + status + ", rjson = '" + json + "' WHERE tid = '" + id + "'";
            work W(*_conn);
            W.exec(sql);
            W.commit();
            cout << "Records update successfully" << endl;
            return true;
        } catch (const std::exception &e) {
            cerr << e.what() << endl;
            return false;
        }
    }

    bool PqSqlHelper::Update(string sql) {
        try {
            work W(*_conn);
            W.exec(sql);
            W.commit();
            cout << "Records update successfully" << endl;
            return true;
        } catch (const std::exception &e) {
            cerr << e.what() << endl;
            return false;
        }
    }


    string GetJsonStr(vector<pair<string, string>> const &items){
        Json::Value jarray;
        for (int i = 0; i < items.size(); ++i) {
            Json::Value item;
            item[items[i].first] = items[i].second;
            jarray.append(item);
        }
//        Json::FastWriter jwriter;
//        string jstr = jwriter.write(jarray);
        return jarray.toStyledString();
    }
}