#pragma once
#ifndef SOLVE_H
#define SOLVE_H

#include "cube_solve.h"
#include "svmdetect.h"
#include "correct.h"
#include <std_msgs/Int8MultiArray.h>

#include <ros/ros.h>
#include <iostream>

#include <cubeParse/SolveCube.h>
//#include <cubeParse/Correction.h>

#include <rb_msgAndSrv/rb_string.h>

using namespace std;
using namespace cv;
using namespace ros;

#define SOLVE_SERVER_NAME "solve_cube"
#define CORRECTION_SERVER_NAME "cube_correct"

class Solve
{
    public:
      /**
       * @brief   构造函数
       */
      Solve(NodeHandle n);
     
      /**
       * @brief   析构函数
       */
      ~Solve();

      /**
       * @brief  发布总服务和话题
       */
      void start();

      /**
       * @brief  识别加解算加发布，一步到位
       */
      vector<int> operation();

      /**
       * @brief  修改颜色序列+解算加发布，一步到位
       */
      vector<int> reoperation(string c);
    
    private:
       /**
        * @brief 解算魔方服务回调函数
        */
       bool solvecube_server_Callback(cubeParse::SolveCube::Request &req, cubeParse::SolveCube::Response &res);

       /**
        * @brief 解算魔方服务回调函数
        */
       bool correction_server_Callback(rb_msgAndSrv::rb_string::Request &req, rb_msgAndSrv::rb_string::Response &res);
      
       /**
        * @brief 各项服务的实例
        */
       ros::ServiceServer solvecubeServer;
       ros::ServiceServer correctionServer;

       /**
        * @brief 发布话题
        */
       ros::Publisher solution_pub;
       ros::Publisher solution_supervise_pub;

        /**
        * @brief mNodeHandle   ROS节点
        */
        ros::NodeHandle nh;

        /**
        * @brief 魔方解算状态反馈
        */
        std_msgs::Bool solve_judge;


};

#endif // SOLVE_H