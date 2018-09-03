//
// Created by cuizhou on 18-9-3.
//

#include <iostream>
#include <implementation_database.h>

using namespace std;

class item {
public:
    item(string n){
        name = new string(n);
    };
    string* get(){
        return name;
    }
    string *name;
};


void test_mysql(){
    ImplementationMySql implementationMySql = ImplementationMySql();
    implementationMySql.Connect(Ip("127.0.0.1"), Port("3306"), Usr("root"), Password("cuizhou"));

    implementationMySql.ExcuteCommand("CREATE DATABASE test;");
    implementationMySql.EnterDatabse(DbName("test"));
}

int main(){
//    item it1("aaa");
//    string *n = it1.get();
//    shared_ptr<string> sn;
//    sn = shared_ptr<string>(it1.get());
//    cout << *sn << endl;

    test_mysql();
}


