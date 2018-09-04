#include <iostream>
#include "DBHelper.h"
#include "pqxx/pqxx"
#include "json/json.h"
#include "vs_mysql_helper.h"

using namespace std;
using namespace pqxx;
using namespace db_helper;


void redis(){
    RedisHelper redisHelper("116.62.174.64","6379","redisPSW0328");
    int tasklen = redisHelper.GetTaskLen();
    string taskVal = redisHelper.GetTaskVal();
    cout << tasklen << endl << taskVal << endl;
}

void pqsql(){
    PqSqlHelper *pqSqlHelper = new PqSqlHelper();
    pqSqlHelper->Update("1", "j", "0");
}

void json(){
    vector<pair<string, string>> items = {{"1","a"}, {"2","b"}, {"3","c"}};
    cout << db_helper::GetJsonStr(items) << endl;
}

void mysql(int id) {
    if (id == 0) {
        VsDatabaseHelper vsDatabaseHelper("root", "950123", "vs_data", "127.0.0.1", "3306");
        vsDatabaseHelper.CreateTable(0);

        Pedestrian *pedestrian = new Pedestrian();
        pedestrian->_age = "18";
        vector<float> v(128, 1);
        pedestrian->_face_descriptor = v;
        pedestrian->_face_rect = cv::Rect(1, 1, 2, 2);
        pedestrian->_gait = "3";
        pedestrian->_sexual = "1";
        pedestrian->_has_glass = "0";
        pedestrian->_has_mask = "3";
        pedestrian->_has_hat = "2";
        pedestrian->_jacket_color = "4";
        pedestrian->_jacket_type = "5";
        pedestrian->_pants_color = "6";
        pedestrian->_pants_type = "7";
        pedestrian->_has_face = true;

        vsDatabaseHelper.Insert(*pedestrian);
    } else if (id == 1){
        VsDatabaseHelper vsDatabaseHelper("root", "950123", "vs_data", "127.0.0.1", "3306");
//        vsDatabaseHelper.CreateTable(1);

        Motor *motor = new Motor();
        motor->_main_belting="3";
        motor->_main_calling="5";
        motor->_motor_skylight='6';
        motor->_motor_brand="1";
        motor->_motor_color="7";
        motor->_motor_type="9";
//        motor->_plate_num="8";
//        motor->_struct_type="2";
//        motor->_plate_color="0";

        vsDatabaseHelper.Insert(*motor);
    } else if (id == 2){
        VsDatabaseHelper vsDatabaseHelper("root", "950123", "vs_data", "127.0.0.1", "3306");
        vsDatabaseHelper.CreateTable(2);

        NonMotor *nonMotor = new NonMotor();
        nonMotor->_struct_type="d";
        nonMotor->_has_face= true;
        vector<float> vec(128,0.5);
        nonMotor->_driver_face_descriptor.assign(vec.begin(), vec.end());


        bool success = vsDatabaseHelper.Insert(*nonMotor);
    }

}

int main() {
//    redis();
//    pqsql();
//    json();
    mysql(2);
    return 0;
}


//#========postgresql=========================
//jdbcUrl=jdbc:postgresql://116.62.174.64/cuizhou
//user = postgres
//password =postgresPSW0328
//
// cur.execute("UPDATE CZ_TASK SET tstate = %s, bz = %s WHERE tid = %s", ('2', '识别失败',task_id))
