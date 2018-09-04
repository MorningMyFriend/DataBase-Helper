//
// Created by cuizhou on 18-9-4.
//

#include "pqsql_helper.h"

using namespace std;

bool PqsqlHelper::Connect(const Ip &ip, const DbName &dbname, const Usr &usr, const Password &password) {
    try {
        string sql =
                "dbname=" + dbname._dbname + " user=" + usr._usr + " password=" + password._password + " hostaddr=" +
                ip._ip;
        _conn = shared_ptr<pqxx::connection>(new pqxx::connection(sql));
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

bool PqsqlHelper::ExcuteCommand(const std::string &command) {
    try {
        pqxx::work W(*_conn);
        W.exec(command);
        W.commit();
        cout << "Records update successfully" << endl;
        return true;
    } catch (const std::exception &e) {
        cerr << e.what() << endl;
        return false;
    }
}

//    bool PqSqlHelper::Update(string status, string json, string id) {
//        try {
//            if (status == "2") {
//                json = "识别失败";
//            }
//            string sql = "UPDATE CZ_TASK SET tstate = " + status + ", rjson = '" + json + "' WHERE tid = '" + id + "'";
//            work W(*_conn);
//            W.exec(sql);
//            W.commit();
//            cout << "Records update successfully" << endl;
//            return true;
//        } catch (const std::exception &e) {
//            cerr << e.what() << endl;
//            return false;
//        }
//    }