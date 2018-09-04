//
// Created by cuizhou on 18-9-3.
//

#include "mysql_helper.h"

using namespace std;

bool MySqlHelper::Connect(const Ip &ip, const Port &port, const Usr &usr, const Password &password) {
    // connect to database server
    if (_ptrConnection != nullptr) {
        delete _ptrConnection;
        _ptrConnection = nullptr;
    }

    try {
        _ptrDirver = get_driver_instance();

        string ip_total = "tcp://" + ip._ip + ":" + port._port;
        _ptrConnection = _ptrDirver->connect(ip._ip.c_str(), usr._usr.c_str(), password._password.c_str());
        cout << "Connect Successfully !" << endl;
        return true;

    } catch (sql::SQLException &e) {
        cout << "connect error: " << endl;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::Connect(const Ip &ip, const Port &port, const DbName &dbname, const Usr &usr,
                                  const Password &password) {

    this->Connect(ip, port, usr, password);

    // enter database
    this->EnterDatabse(dbname);
}

bool MySqlHelper::EnterDatabse(const DbName &dbName) {
    if (_ptrConnection == nullptr) {
        cout << "connection null" << endl;
        return false; }
    try {
        _ptrConnection->setSchema(dbName._dbname.c_str());
        cout << "Entered Databse: " << dbName._dbname << endl;
        return true;
    } catch (sql::SQLException &e) {
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::ExcuteCommand(const std::string &command) {
    if (_ptrConnection == nullptr) {
        cout << "connection null" << endl;
        return false; }
    try {
        sql::Statement *stmt = _ptrConnection->createStatement();
        stmt->execute(command.c_str());
        // example:
        // stmt->execute("DROP TABLE IF EXISTS test");
        // stmt->execute("CREATE TABLE test(id INT)");
        delete stmt;
        return true;
    } catch (sql::SQLException &e) {
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::ExeSQLUpdate(string sql) {
    try {
        // example:
        sql::PreparedStatement *pstmt;
        pstmt = _ptrConnection->prepareStatement("INSERT INTO test(id) VALUES (?)");
        for (int i = 1; i <= 10; i++) {
            pstmt->setInt(1, i);
            pstmt->executeUpdate();
        }
        delete pstmt;
        return true;
    } catch (sql::SQLException &e) {
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        ThrowError(e);
        return false;
    }
}

bool MySqlHelper::ExeSQLQuery(string sql) {
    /* Select in ascending order */
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    pstmt = _ptrConnection->prepareStatement("SELECT id FROM test ORDER BY id ASC");
    res = pstmt->executeQuery();

    /* Fetch in reverse = descending order! */
    res->afterLast();
    while (res->previous()){
        cout << "\t... MySQL counts: " << res->getInt("id") << endl;
    }
    delete res;
    delete pstmt;
}

void MySqlHelper::ThrowError(sql::SQLException &e) {
    cout << "# ERR: SQLException in " << __FILE__ << endl;
    cout << "# ERR: " << e.what() << endl;
    cout << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << endl;
}