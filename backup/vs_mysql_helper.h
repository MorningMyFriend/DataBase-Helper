//
// Created by wurui on 18-5-25.
//

#ifndef INTERFACEREDISSQL_VS_MYSQL_HELPER_H
#define INTERFACEREDISSQL_VS_MYSQL_HELPER_H

#include "MySqlHelper.h"
#include "structure.h"

using namespace std;

class VsDatabaseHelper: public MySqlHelper{
public:
    VsDatabaseHelper()= delete;
    VsDatabaseHelper(string user, string password, string dbname, string ip, string port);

    bool CreateTable(int type);
    string SqlCreateColumnFromVector(string vectorName, int valueTpye, int capacity=_VECTOR_CAPACITY, bool notNull=false);

    bool Insert(Pedestrian &pedestrian, string table="Pedestrian");
    bool Insert(Motor &motor, string table="Motor");
    bool Insert(NonMotor &nonMotor, string table="NonMotor");
    string SqlInsertKeyFromVector(string vectorName, int valueTpye, int capacity=_VECTOR_CAPACITY, bool notNull=false);
    string SqlInsertVal(string &str, bool isVARCHAR=false);
    string SqlInsertVal(cv::Rect &rect);
    string SqlInsertVal(vector<float> &vec, int capacity=_VECTOR_CAPACITY);
    string SqlInsertVal(vector<int> &vec, int capacity=_VECTOR_CAPACITY);
    string SqlInsertVal(vector<cv::Rect> &rects, int capacity=_VECTOR_CAPACITY);

private:
    static const int _VECTOR_CAPACITY;
    static const int _FACE_FEATURE_SIZE;

    string _dbname;

};


#endif //INTERFACEREDISSQL_VS_MYSQL_HELPER_H
