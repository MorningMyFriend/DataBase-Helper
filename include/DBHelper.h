////
//// Created by wurui on 18-5-23.
////
//
//#ifndef INTERFACEREDISSQL_REDISHELPER_H
//#define INTERFACEREDISSQL_REDISHELPER_H
//
//#include <iostream>
//#include <hiredis/hiredis.h>
//#include "pqxx/pqxx"
//
//namespace db_helper {
//
//    using namespace std;
//
//    class RedisHelper {
//    public:
//        RedisHelper();
//
//        ~RedisHelper() {redisFree(_conn);}
//
//        RedisHelper(string ip, string port, string password);
//
//        bool Connect();
//
//        int GetTaskLen();
//
//        string GetTaskVal();
//
//    private:
//        static const string _listname;
//        string _ip;
//        string _port;
//        string _password;
//        redisContext *_conn;
//    };
//
//    using namespace pqxx;
//
//    class PqSqlHelper {
//    public:
//        PqSqlHelper();
//
//        ~PqSqlHelper() {
//            if (_conn->is_open()) _conn->disconnect();
//            delete _conn;
//        }
//
//        PqSqlHelper(string dbname, string user, string password, string ip);
//
//        bool Connect();
//
//        bool Update(string status, string json, string id);
//
//        bool Update(string sql);
//
//    private:
//        connection *_conn;
//        string _dbname;
//        string _user;
//        string _password;
//        string _ip;
//
//    };
//
//    string GetJsonStr(vector<pair<string, string>> const &items);
//}
//
//#endif //INTERFACEREDISSQL_REDISHELPER_H
//
////#======redis========
////redisip=116.62.174.64
////redisport=6379
////redispsw=redisPSW0328
//
////当命令被成功执行后redisCommand会有相应的返回值。
////如果有错误发生，返回值为NULL并且redisReply结构体中的err变量将会被设置成相应的值。
////一旦有错误发生context不能被重用并且需要建立一个新的连接。
//
////#define REDIS_REPLY_STRING 1
////#define REDIS_REPLY_ARRAY 2
////#define REDIS_REPLY_INTEGER 3
////#define REDIS_REPLY_NIL 4
////#define REDIS_REPLY_STATUS 5
////#define REDIS_REPLY_ERROR 6