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

#include "rb_msgAndSrv/rbImageList.h"


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
         * @brief   进行图片中魔方的截取
         * @param   img:需要截取的图像, x1,y1,x2,y2为捕获坐标
         * @return   img:图像中的魔方部分
         */
        cv::Mat capture_cube(cv::Mat img, int x1, int y1, int x2, int y2);

        /**
         * @brief  生成捕获魔方矩阵
         * @return  矩阵
         */
        vector<vector<int>> makeMatrix();

        /**
         * @brief  旋转图像
         * @para img:图像 ; angle:旋转的角度
         * @return  旋转后的图像
         */
        cv::Mat imgRotate(cv::Mat img, double angle);

        /**
         * @brief 对照片进行白平衡处理
         * @param img:要进行处理的图片
         * @return  白平衡处理后的图片
         */
        cv::Mat WhiteBalance(cv::Mat img);

        /**
         * @brief 对保存在来的原图进行魔方区域截取并保存
         */
        void ProcessImage();

        /**
          * @brief 给魔方方块填充颜色
         * @param img:要进行填充的图片, color:要填充的颜色, p:填充的位置
         * @return  填充颜色后的图片
         */
        void filling_color(cv::Mat img, std::string color, cv::Point p);

        /**
         * @brief 给魔方方块输入文本
         * @param img:要进行文本框输入的图片, color:文本框要输入的颜色, p:文本框的位置
         * @return  输入编辑过后的图像
         */
        void WriteText(cv::Mat img, std::string color, cv::Point p);

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
        // image_transport::Publisher Imgpub;
        ros::Publisher imglistPub;
        
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

        /**
        * @brief 魔方照片文件路徑参数  
        */
        std::string pathCurrent = "/home/de/catkin_ws/src/HsDualAppBridge/cubeParse/photo/Original/cube_";
        std::string pathSave = "/home/de/catkin_ws/src/HsDualAppBridge/cubeParse/photo/Processed/cube_";
        std::string pahtloadSvm = "/home/de/catkin_ws/src/HsDualAppBridge/cubeParse/svm_color.xml";
        std::string pathShow = "/home/de/catkin_ws/src/HsDualAppBridge/cubeParse/photo/Show/cube";

        /**
        * @brief 魔方照片矩阵参数  
        */

        //魔方前面参数
        int Front_x1 = 207;
        int Front_y1 = 121;
        int Front_x2 = 448;
        int Front_y2 = 359;

        //魔方背面参数
        int Back_x1 = 169;
        int Back_y1 = 105;
        int Back_x2 = 448;
        int Back_y2 = 381;

        //魔方左面参数
        int Left_x1 = 223;
        int Left_y1 = 164;
        int Left_x2 = 445;
        int Left_y2 = 382;

        //魔方右面参数
        int Right_x1 = 275;
        int Right_y1 = 229;
        int Right_x2 = 496;
        int Right_y2 = 442;

        //魔方顶面参数
        int Up_x1 = 218;
        int Up_y1 = 96;
        int Up_x2 = 458;
        int Up_y2 = 334;

        //魔方底面参数
        int Down_x1 = 215;
        int Down_y1 = 86;
        int Down_x2 = 510;
        int Down_y2 = 374;

};



#endif // SVMDETECT_H
