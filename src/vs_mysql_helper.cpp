//
// Created by wurui on 18-5-25.
//

#include "vs_mysql_helper.h"

// static members
const int VsDatabaseHelper::_VECTOR_CAPACITY=20;
const int VsDatabaseHelper::_FACE_FEATURE_SIZE=128;

VsDatabaseHelper::VsDatabaseHelper(string user, string password, string dbname, string ip="127.0.0.1", string port="3306"):
        MySqlHelper(user, password, ip ,port){
    EnterDatabase(dbname);
}

bool VsDatabaseHelper::CreateTable(int type) {
    string sql = "CREATE TABLE IF NOT EXISTS ";
    switch (type) {
        case 0:
            sql+="Pedestrian (id INT UNSIGNED AUTO_INCREMENT,";
            sql=sql+"_struct_rect VARCHAR(255),"+
                    "_jacket_type TINYINT UNSIGNED,"+
                    "_jacket_color TINYINT UNSIGNED,"+
                    "_pants_type TINYINT UNSIGNED,"+
                    "_pants_color TINYINT UNSIGNED,"+
                    "_age TINYINT UNSIGNED,"+
                    "_sexual TINYINT UNSIGNED,"+
                    "_gait TINYINT UNSIGNED,"+
                    "_has_glass TINYINT UNSIGNED,"+
                    "_has_hat TINYINT UNSIGNED,"+
                    "_has_mask TINYINT UNSIGNED,"+
                    "_has_face TINYINT UNSIGNED,"+
                    SqlCreateColumnFromVector("_face_rect",0,1)+","+
                    SqlCreateColumnFromVector("_face_descriptor",1,_FACE_FEATURE_SIZE)+",";
            break;
        case 1:
            sql+="Motor (id INT UNSIGNED AUTO_INCREMENT,";
            sql=sql+"_struct_rect VARCHAR(255),"+
                    "_motor_type TINYINT UNSIGNED,"+
                    "_motor_brand TINYINT UNSIGNED,"+
                    "_motor_color TINYINT UNSIGNED,"+
                    "_motor_skylight TINYINT UNSIGNED,"+
                    SqlCreateColumnFromVector("_main_dirver",0,1)+","+
                    "_main_belting TINYINT UNSIGNED,"+
                    "_main_calling TINYINT UNSIGNED,"+
                    SqlCreateColumnFromVector("_co_dirvers",0)+","+
                    SqlCreateColumnFromVector("_co_belting",2)+","+
                    SqlCreateColumnFromVector("_annual_mark",0)+","+
                    SqlCreateColumnFromVector("_central_pendant",0)+","+
                    SqlCreateColumnFromVector("_tissue_box",0)+","+
                    SqlCreateColumnFromVector("_sun_visor",0)+","+
                    SqlCreateColumnFromVector("_temp_plate",0)+","+
                    "_plate_num TINYINT UNSIGNED,"+
                    "_plate_color TINYINT UNSIGNED,"+
                    SqlCreateColumnFromVector("_plate_rect",0,1)+",";
            break;
        case 2:
            sql+="NonMotor (id INT UNSIGNED AUTO_INCREMENT,";
            sql=sql+"_struct_rect VARCHAR(255),"+
                "_nonmotor_type TINYINT UNSIGNED,"+
                "_driver_visible TINYINT UNSIGNED,"+
                SqlCreateColumnFromVector("_driver",0,1)+","+
                "_driver_jacket_type TINYINT UNSIGNED,"+
                "_driver_jacket_color TINYINT UNSIGNED,"+
                "_driver_pants_type TINYINT UNSIGNED,"+
                "_driver_pants_color TINYINT UNSIGNED,"+
                "_driver_age TINYINT UNSIGNED,"+
                "_driver_sexual TINYINT UNSIGNED,"+
                "_driver_has_glass TINYINT UNSIGNED,"+
                "_driver_has_hat TINYINT UNSIGNED,"+
                "_driver_has_mask TINYINT UNSIGNED,"+
                "_has_face TINYINT UNSIGNED,"+
                SqlCreateColumnFromVector("_driver_face_rect",0,1)+","+
                SqlCreateColumnFromVector("_driver_face_descriptor",1,_FACE_FEATURE_SIZE)+",";
            break;
    }
    sql+="PRIMARY KEY (id))ENGINE=InnoDB DEFAULT CHARSET=utf8;";
    cout<<sql<<endl;
    ExeSQL(sql.c_str());
}

string VsDatabaseHelper::SqlCreateColumnFromVector(string vectorName, int valueTpye, int capacity, bool notNull) {
    string sql="";
    string notnull=notNull?" NOT NULL":"";
    switch (valueTpye) {
        case 0:
            //"Rect":
            for (int i = 0; i < capacity; ++i) {
                sql=sql+vectorName+"_"+std::to_string(i)+"_x "+" INT"+notnull+","+
                    vectorName+"_"+std::to_string(i)+"_y "+" INT"+notnull+","+
                    vectorName+"_"+std::to_string(i)+"_w "+" INT"+notnull+","+
                    vectorName+"_"+std::to_string(i)+"_h "+" INT"+notnull;
                if(i<capacity-1){
                    sql+=",";
                }
            }
            break;
        case 1:
            //"float":
            for (int i = 0; i < capacity; ++i) {
                sql=sql+vectorName+"_"+std::to_string(i)+" FLOAT"+notnull;
                if(i<capacity-1){
                    sql+=",";
                }
            }
            break;
        case 2:
            //"int":
            for (int i = 0; i < capacity; ++i) {
                sql=sql+vectorName+"_"+std::to_string(i)+" INT"+notnull;
                if(i<capacity-1){
                    sql+=",";
                }
            }
            break;
        case 3:
            //"string":
            for (int i = 0; i < capacity; ++i) {
                sql=sql+vectorName+"_"+std::to_string(i)+" VARCHAR(255)"+notnull;
                if(i<capacity-1){
                    sql+=",";
                }
            }
            break;
    }
    return sql;
}

bool VsDatabaseHelper::Insert(Pedestrian &pedestrian, string table) {
    string sql="INSERT INTO "+table+" ";
    string key="(";
    string value="(";

    key=key+"_struct_rect"+","+
        "_jacket_type"+","+
        "_jacket_color"+","+
        "_pants_type"+","+
        "_pants_color"+","+
        "_age"+","+
        "_sexual"+","+
        "_gait"+","+
        "_has_glass"+","+
        "_has_hat"+","+
        "_has_mask"+","+
        "_has_face"+","+
        SqlInsertKeyFromVector("_face_rect",-1,1)+","+
        SqlInsertKeyFromVector("_face_descriptor",1,_FACE_FEATURE_SIZE)+
        ")";
    value=value+SqlInsertVal(pedestrian._struct_rect, true)+","+
            SqlInsertVal(pedestrian._jacket_type)+","+
            SqlInsertVal(pedestrian._jacket_color)+","+
            SqlInsertVal(pedestrian._pants_type)+","+
            SqlInsertVal(pedestrian._pants_color)+","+
            SqlInsertVal(pedestrian._age)+","+
            SqlInsertVal(pedestrian._sexual)+","+
            SqlInsertVal(pedestrian._gait)+","+
            SqlInsertVal(pedestrian._has_glass)+","+
            SqlInsertVal(pedestrian._has_hat)+","+
            SqlInsertVal(pedestrian._has_mask)+","+
            std::to_string(pedestrian._has_face)+","+
            SqlInsertVal(pedestrian._face_rect)+","+
            SqlInsertVal(pedestrian._face_descriptor,_FACE_FEATURE_SIZE)+
            ")";

    sql=sql+key+" values "+value+";";
    cout<<sql<<endl;
    ExeSQL(sql);
}

bool VsDatabaseHelper::Insert(Motor &motor, string table) {
    string sql="INSERT INTO "+table+" ";
    string key="(";
    string value="(";

    key=key+"_struct_rect"+","+
            "_motor_type,"+
            "_motor_brand,"+
            "_motor_color,"+
            "_motor_skylight,"+
            SqlInsertKeyFromVector("_main_dirver",0,1)+","+
            "_main_belting,"+
            "_main_calling,"+
            SqlInsertKeyFromVector("_co_dirvers",0)+","+
            SqlInsertKeyFromVector("_co_belting",2)+","+
            SqlInsertKeyFromVector("_annual_mark",0)+","+
            SqlInsertKeyFromVector("_central_pendant",0)+","+
            SqlInsertKeyFromVector("_tissue_box",0)+","+
            SqlInsertKeyFromVector("_sun_visor",0)+","+
            SqlInsertKeyFromVector("_temp_plate",0)+","+
            "_plate_num,"+
            "_plate_color,"+
            SqlInsertKeyFromVector("_plate_rect",0,1)+
            ")";
    value=value+SqlInsertVal(motor._struct_rect)+","+
            SqlInsertVal(motor._motor_type)+","+
            SqlInsertVal(motor._motor_brand)+","+
            SqlInsertVal(motor._motor_color)+","+
            SqlInsertVal(motor._motor_skylight)+","+
            SqlInsertVal(motor._main_dirver)+","+
            SqlInsertVal(motor._main_belting)+","+
            SqlInsertVal(motor._main_calling)+","+
            SqlInsertVal(motor._co_dirvers)+","+
            SqlInsertVal(motor._co_belting)+","+
            SqlInsertVal(motor._annual_mark)+","+
            SqlInsertVal(motor._central_pendant)+","+
            SqlInsertVal(motor._tissue_box)+","+
            SqlInsertVal(motor._sun_visor)+","+
            SqlInsertVal(motor._temp_plate)+","+
            SqlInsertVal(motor._plate_num)+","+
            SqlInsertVal(motor._plate_color)+","+
            SqlInsertVal(motor._plate_rect)+
            ")";

    sql=sql+key+" values "+value+";";
    cout << sql << endl;
    ExeSQL(sql);
}

bool VsDatabaseHelper::Insert(NonMotor &nonMotor, string table) {
    string sql="INSERT INTO "+table+" ";
    string key="(";
    string value="(";

    key=key+"_struct_rect"+","+
            "_nonmotor_type,"+
            "_driver_visible,"+
            SqlInsertKeyFromVector("_driver",0,1)+","+
            "_driver_jacket_type,"+
            "_driver_jacket_color,"+
            "_driver_pants_type,"+
            "_driver_pants_color,"+
            "_driver_age,"+
            "_driver_sexual,"+
            "_driver_has_glass,"+
            "_driver_has_hat,"+
            "_driver_has_mask,"+
            "_has_face,"+
            SqlInsertKeyFromVector("_driver_face_rect",0,1)+","+
            SqlInsertKeyFromVector("_driver_face_descriptor",1,_FACE_FEATURE_SIZE)+
            ")";
    value=value+SqlInsertVal(nonMotor._struct_rect)+","+
            SqlInsertVal(nonMotor._nonmotor_type)+","+
            std::to_string(nonMotor._driver_visible)+","+
            SqlInsertVal(nonMotor._driver)+","+
            SqlInsertVal(nonMotor._driver_jacket_type)+","+
            SqlInsertVal(nonMotor._driver_jacket_color)+","+
            SqlInsertVal(nonMotor._driver_pants_type)+","+
            SqlInsertVal(nonMotor._driver_pants_color)+","+
            SqlInsertVal(nonMotor._driver_age)+","+
            SqlInsertVal(nonMotor._driver_sexual)+","+
            SqlInsertVal(nonMotor._driver_has_glass)+","+
            SqlInsertVal(nonMotor._driver_has_hat)+","+
            SqlInsertVal(nonMotor._driver_has_mask)+","+
            std::to_string(nonMotor._has_face)+","+
            SqlInsertVal(nonMotor._driver_face_rect)+","+
            SqlInsertVal(nonMotor._driver_face_descriptor,_FACE_FEATURE_SIZE)+
            ")";

    sql=sql+key+" values "+value+";";
    cout << sql << endl;
    ExeSQL(sql);
}

string VsDatabaseHelper::SqlInsertKeyFromVector(string vectorName, int valueTpye, int capacity, bool notNull) {
    string sql="";
    if(valueTpye==0) {
        for (int i = 0; i < capacity; ++i) {
            sql = sql + vectorName + "_" + std::to_string(i) + "_x" + "," +
                  vectorName + "_" + std::to_string(i) + "_y" + "," +
                  vectorName + "_" + std::to_string(i) + "_w" + "," +
                  vectorName + "_" + std::to_string(i) + "_h";
            if (i < capacity - 1) {
                sql += ",";
            }
        }
    } else if(valueTpye == -1){
        // rect
        sql = sql + vectorName + "_0_x," +
        vectorName + "_0_y," +
        vectorName + "_0_w," +
        vectorName + "_0_h";
    } else {
        for (int i = 0; i < capacity; ++i) {
            sql=sql+vectorName+"_"+std::to_string(i);
            if(i<capacity-1){
                sql+=",";
            }
        }
    }
    return sql;
}

string VsDatabaseHelper::SqlInsertVal(string &str, bool isVARCHAR) {
    if(isVARCHAR){
        return str.size()>0? "'"+str+"'":"'null'";
    } else {
        return str.size()>0? str:"null";
    }
}

string VsDatabaseHelper::SqlInsertVal(cv::Rect &rect) {
    if(rect.empty()){
        return "null,null,null,null";
    }
    return std::to_string(rect.x)+","+std::to_string(rect.y)+","+std::to_string(rect.width)+","+std::to_string(rect.height);
}

string VsDatabaseHelper::SqlInsertVal(vector<float> &vec, int capacity) {
    string sql="";
    for (int i = 0; i < capacity; ++i) {
        sql = sql + std::to_string(vec[i]);
        if (i < capacity - 1) {
            sql += ",";
        }
    }
    return sql;
}

string VsDatabaseHelper::SqlInsertVal(vector<int> &vec, int capacity) {
    string sql="";
    for (int i = 0; i < capacity; ++i) {
        if(i>=vec.size()){
            sql+="null";
        } else {
            sql = sql + std::to_string(vec[i]);
        }
        if (i < capacity - 1) {
            sql += ",";
        }
    }
    return sql;
}

string VsDatabaseHelper::SqlInsertVal(vector<cv::Rect> &rects, int capacity) {
    string sql="";
    if(rects.size()<capacity){
        for (int i = 0; i < rects.size(); ++i) {
            if(rects[i].empty()){
                sql = sql + "null,null,null,null";
                continue;
            }
            sql = sql + std::to_string(rects[i].x)+"," +
                  std::to_string(rects[i].y)+"," +
                  std::to_string(rects[i].width)+"," +
                  std::to_string(rects[i].height);
            if (i < capacity - 1) {
                sql += ",";
            }
        }
        for (int i = rects.size(); i < capacity; ++i) {
            sql = sql + "null,null,null,null";
            if (i < capacity - 1) {
                sql += ",";
            }
        }
    } else {
        for (int i = 0; i < capacity; ++i) {
            if(rects[i].empty()){
                sql = sql + "null,null,null,null";
                continue;
            }
            sql = sql + std::to_string(rects[i].x)+"," +
                  std::to_string(rects[i].y)+"," +
                  std::to_string(rects[i].width)+"," +
                  std::to_string(rects[i].height);
            if (i < capacity - 1) {
                sql += ",";
            }
        }
    }

    return sql;
}