//
// Created by cuizhou on 18-9-3.
//

#include <iostream>
#include "mysql_helper.h"
#include "redis_helper.h"
#include "pqsql_helper.h"

using namespace std;

class item {
public:
    item(string n){
        name = new string(n);
    };
    void release(){
        cout << "release" << endl;
    }
    string* get(){
        return name;
    }
    string *name;
};

void clear(item *it){
    cout << "clear:" <<*(it->get()) << endl;
}


void test_mysql(){
    MySqlHelper mySqlHelper = MySqlHelper();
    mySqlHelper.Connect(Ip("127.0.0.1"), Port("3306"), Usr("root"), Password("cuizhou"));

    mySqlHelper.ExcuteCommand("CREATE DATABASE test;");
    mySqlHelper.EnterDatabse(DbName("test"));
}

void test_redis(){
    RedisHelper redisHelper = RedisHelper();
    redisHelper.Connect(Ip("116.62.174.64"),Port("6379"),Password("redisPSW0328"));
}

void test_pqsql(){
    PqsqlHelper pqsqlHelper = PqsqlHelper();
    pqsqlHelper.Connect(Ip("116.62.174.64"),DbName("cuizhou"),Usr("postgres"),Password("postgresPSW0328"));
}

void test_interface(){
    shared_ptr<InterfaceDataBase> interface = make_shared<MySqlHelper>(MySqlHelper());
    // mysql
    cout << "mysql >> ";
    interface->Connect(Ip("127.0.0.1"), Port("3306"), Usr("root"), Password("cuizhou"));
    // redis
    cout << "redis >> ";
    interface = make_shared<RedisHelper>(RedisHelper());
    interface->Connect(Ip("116.62.174.64"),Port("6379"),Password("redisPSW0328"));
    // pqsql
    cout << "pqsql >> ";
    interface = make_shared<PqsqlHelper>(PqsqlHelper());
    interface->Connect(Ip("116.62.174.64"),DbName("cuizhou"),Usr("postgres"),Password("postgresPSW0328"));
}

void test_shared_ptr(){
    item *it = new item("aaa");
    shared_ptr<item> pt0(it);
    shared_ptr<item> pt00(it);
    cout << "pt0" << pt0.use_count() << endl;
//    delete it;
    cout << "pt0" << pt0.use_count() << endl;

//    shared_ptr<item> pt1 = make_shared<item>(item("abc"), clear);
    shared_ptr<item> pt1(new item("abc"), clear);
    cout << "pt1" << pt1.use_count() << endl;
    shared_ptr<item> pt2(pt1);
    cout << "pt1" << pt1.use_count() << endl;
    shared_ptr<item> pt3(pt2);
    cout << "pt1" << pt1.use_count() << endl;
    pt3.reset(it);
    cout << "pt0" << pt0.use_count() << endl;
    cout << "pt1" << pt1.use_count() << endl;

}

int main(){
//    test_shared_ptr();
//    test_mysql();
//    test_redis();
//    test_pqsql();
    test_interface();
}



