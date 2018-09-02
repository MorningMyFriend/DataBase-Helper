//
// Created by wurui on 18-5-25.
//

#ifndef INTERFACEREDISSQL_MYSQLHELPER_H
#define INTERFACEREDISSQL_MYSQLHELPER_H

#include <iostream>
#include "mysql/mysql.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class MySqlHelper {
public:
    MySqlHelper()= delete;
    MySqlHelper(string user, string password, string ip="127.0.0.1", string port="3306");
    ~MySqlHelper();

    virtual bool Connect();
    virtual bool EnterDatabase(string dbname);
    virtual bool ExeSQL(string sql);
    virtual bool ExeSQLUpdate(string sql);
    virtual bool ExeSQLQuery(string sql);
    virtual void ThrowError(sql::SQLException &e);

    bool EnterTable();

protected:
    string _user;
    string _password;
    string _ip; // default localhost = "tcp://127.0.0.1:3306"
    string _port; // default = 3306

    sql::Driver *_driver;
    sql::Connection *_conn;

};


#endif //INTERFACEREDISSQL_MYSQLHELPER_H

// ----------- install -------------------//
// apt-get install mysql-server
// apt-get install mysql-client
// apt-get install libmysqlclient-dev
// apt-get install libmysqlcppconn-dev

// ----------- mysql commands ------------//
// connect$: mysql -u root -p
// create database$: CREATE DATABASE dbname;
// show database$: show databases;
// open database$: use dbname
// create table$: CREATE TABLE IF NOT EXISTS runoob_tbl (runoob_id INT UNSIGNED AUTO_INCREMENT,runoob_title VARCHAR(100) NOT NULL,count INT,PRIMARY KEY (runoob_id))ENGINE=InnoDB DEFAULT CHARSET=utf8;
// show table$: show tables; desc tabel_name;