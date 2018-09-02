//
// Created by wurui on 18-5-25.
//

#include "MySqlHelper.h"

MySqlHelper::~MySqlHelper() {
    delete _conn;
};

MySqlHelper::MySqlHelper(string user, string password, string ip, string port):
        _user(user),
        _password(password),
        _ip(ip),
        _port(port) {
    if(Connect()) cout << "connect successfully!" << endl;
}

bool MySqlHelper::Connect() {
    try{
        _driver = get_driver_instance();
        string ip = "tcp://"+_ip+":"+_port;
        _conn = _driver->connect(ip.c_str(), _user.c_str(), _password.c_str());
        return true;

    } catch(sql::SQLException &e){
        cout << "connect error: " << endl;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::EnterDatabase(string dbname) {
    try{
        _conn->setSchema(dbname.c_str());
        cout << "Entered Databse: "<< dbname << endl;
        return true;
    } catch(sql::SQLException &e){
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::ExeSQL(string sql) {
    try{
        sql::Statement *stmt = _conn->createStatement();
        stmt->execute(sql.c_str());
        // example:
        // stmt->execute("DROP TABLE IF EXISTS test");
        // stmt->execute("CREATE TABLE test(id INT)");
        delete stmt;
        return true;
    } catch(sql::SQLException &e){
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::ExeSQLUpdate(string sql) {
    try{
        // example:
        sql::PreparedStatement *pstmt;
        pstmt = _conn->prepareStatement("INSERT INTO test(id) VALUES (?)");
        for (int i = 1; i <= 10; i++) {
            pstmt->setInt(1, i);
            pstmt->executeUpdate();
        }
        delete pstmt;
        return true;
    } catch(sql::SQLException &e){
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::ExeSQLQuery(string sql) {
    /* Select in ascending order */
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    pstmt = _conn->prepareStatement("SELECT id FROM test ORDER BY id ASC");
    res = pstmt->executeQuery();

    /* Fetch in reverse = descending order! */
    res->afterLast();
    while (res->previous())
        cout << "\t... MySQL counts: " << res->getInt("id") << endl;
    delete res;
    delete pstmt;
}

void MySqlHelper::ThrowError(sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}