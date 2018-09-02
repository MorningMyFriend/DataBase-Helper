/**
* @Copyright (c) 2018 by JpHu
* @Date 2018-5-24
* @Company CuiZhou
* @Email hujp@cuizhouai.com
* @Function
*/

#ifndef VIDEO_STRUCTURE_ANALYSIS_STRUCTURE_H
#define VIDEO_STRUCTURE_ANALYSIS_STRUCTURE_H

#include <opencv2/core.hpp>
#include <string>

using namespace std;
    class Sturcture {
    public:
        Sturcture()= default;
    };

    class Pedestrian : public Sturcture{
    public:
        Pedestrian();

        std::string _struct_type;
        string _struct_rect; //图片路径
        std::string _jacket_type;
        std::string _jacket_color;
        std::string _pants_type;
        std::string _pants_color;
        std::string _age;
        std::string _sexual;
        std::string _gait; //步态
        std::string _has_glass;
        std::string _has_hat;
        std::string _has_mask;
        bool _has_face;
        cv::Rect _face_rect;
        std::vector<float> _face_descriptor;//128维
    };

    class Motor : public Sturcture{
    public:
        Motor();
        std::string _struct_type;

        string _struct_rect;//图片路径
        std::string _motor_type;
        std::string _motor_brand;
        std::string _motor_color;
        std::string _motor_skylight;
        cv::Rect _main_dirver;
        std::string _main_belting;
        std::string _main_calling;
        std::vector<cv::Rect> _co_dirvers;
        std::vector<int> _co_belting;
        std::vector<cv::Rect> _annual_mark;
        std::vector<cv::Rect> _central_pendant;
        std::vector<cv::Rect> _tissue_box;
        std::vector<cv::Rect> _sun_visor;
        std::vector<cv::Rect> _temp_plate;
        std::string _plate_num;
        std::string _plate_color;
        cv::Rect _plate_rect;
    };

    class NonMotor : public Sturcture {
    public:
        NonMotor();
        std::string _struct_type;

        string _struct_rect;//图片路径
        std::string _nonmotor_type;
        bool _driver_visible;
        cv::Rect _driver;
        std::string _driver_jacket_type;
        std::string _driver_jacket_color;
        std::string _driver_pants_type;
        std::string _driver_pants_color;
        std::string _driver_age;
        std::string _driver_sexual;
        std::string _driver_has_glass;
        std::string _driver_has_hat;
        std::string _driver_has_mask;
        bool _has_face;
        cv::Rect _driver_face_rect;
        std::vector<float> _driver_face_descriptor;
    };

#endif //VIDEO_STRUCTURE_ANALYSIS_STRUCTURE_H
