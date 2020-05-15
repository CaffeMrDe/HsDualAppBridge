#pragma once
#ifndef SVMDETECT_H
#define SVMDETECT_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#include <cubeParse/TakePhoto.h>
#include <cubeParse/Detection.h>

using namespace std;
using namespace cv;
using namespace ml;
using namespace ros;


#define TAKE_PHOTO_SERVER_NAME "get_cube"
#define DETECTION_SERVER_NAME "cube_detect"

class svmDetect  
{
    public:
        /**
        * @brief   构造函数
        */
        svmDetect(NodeHandle n);

        /**
        * @brief   析构函数
        */
        ~svmDetect();

        /**
        * @brief  发布服务
        */
        void start();

        /**
        * @brief   得出魔方54个小方块的颜色信息序列，打印并发送
        */
        vector<char> getResult();
       
    private:
        /**
        * @brief   打印魔方54个小方块的颜色信息序列
        * @param   img:需要识别的图像, facelet_label:魔方基本面确定后的编码顺序
        */
        void printResult();

        /**
        * @brief   进行魔方一个面的颜色检测
        * @param   img:需要识别的图像, facelet_label:魔方基本面确定后的编码顺序
        */
        vector<char> detection(cv::Mat img,  vector<char> facelet_label); 

        /**
        * @brief   进行图片中魔方的截取
        * @param   img:需要截取的图像
        * @return   img:图像中的魔方部分
        */
        cv::Mat capture_cube(cv::Mat img);

        /**
        * @brief   找到魔方的中心位置
          * @param   Mat 需要识别的图像
          * @return  cv::Point:中心位置的坐标x,y
        */
        cv::Point find_central_point(cv::Mat img);

        /**
        * @brief   点击鼠标事件回调函数，仅调试用，在图像返回坐标x,y
        */
        void onMouse(int event, int x, int y, int flags, void* prarm);
        
        /**
        * @brief  进行颜色识别
        * @param   img 需要进行颜色识别的图像
        * @return  string:颜色，如red, yellow, blue, orange, green, white
        */
        std::string SVM_Color(cv::Mat img);
        
        /**
        * @brief  进行颜色编码
        * @param   color 需要识别的颜色,如red, yellow, blue, orange, green, white
        * @return  char:颜色所对应的基准面编码，分别为U，D，F，B，L，R
        */
        char color_code(std::string color,  vector<char> facelet_label);
        
        /**
        * @brief  进行魔方扭动基准面的确定
        * @return  vector<char>:魔方基本面确定后的编码顺序，例如（ 'F', 'B', 'L', 'R', 'U', 'D'）
        */
        vector<char> establish_benchmark();

        /**
        * @brief  拍照服务的回调函数,调用订阅相机彩色照片的回调函数
        * @return  拍照成功返回true, 拍照失败返回false
        */
        bool takephoto_server_Callback(cubeParse::TakePhoto::Request &req, cubeParse::TakePhoto::Response &res);

        /**
        * @brief  订阅相机彩色照片的回调函数
        * @return  保存图片到本地
        */
        bool detection_server_Callback(cubeParse::Detection::Request &req, cubeParse::Detection::Response &res);

        /**
        * @brief  订阅相机彩色照片的回调函数
        * @return  保存图片到本地
        */
        void ImageSubscribeCallback(const sensor_msgs::ImageConstPtr & msg);
        /**
        * @brief 魔方拍照的计算次数
        */
        unsigned int fileNum = 0;

        /**
        * @brief 各项服务的实例
        */
        ros::ServiceServer takephotoServer;
        ros::ServiceServer detectionServer;
        
        /**
        * @brief 图片订阅话题
        */
        image_transport::Subscriber Imgsub;
        
        /**
        * @brief mNodeHandle   ROS节点
        */
        ros::NodeHandle mNodeHandle;
        
        /**
        * @brief 订阅相机节点照片参数  
        */
        std::stringstream stream1;
		    std::stringstream stream2;
        std::string filename1;
        std::string filename2;

};



#endif // SVMDETECT_H
