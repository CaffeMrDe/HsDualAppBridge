#pragma once
#ifndef SOLVE_H
#define SOLVE_H

#include "cube_solve.h"
#include "svmdetect.h"
#include <std_msgs/Int8MultiArray.h>

#include <ros/ros.h>
#include <iostream>


#include <cubeParse/SolveCube.h>

using namespace std;
using namespace cv;
using namespace ros;

#define SOLVE_SERVER_NAME "solve_cube"

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
    
    private:
       /**
        * @brief 解算魔方服务回调函数
        */
       bool solvecube_server_Callback(cubeParse::SolveCube::Request &req, cubeParse::SolveCube::Response &res);
      
       /**
        * @brief 各项服务的实例
        */
       ros::ServiceServer solvecubeServer;

       /**
        * @brief 发布话题
        */
       ros::Publisher solution_pub;

        /**
        * @brief mNodeHandle   ROS节点
        */
        ros::NodeHandle nh;
       

};

#endif // SOLVE_H