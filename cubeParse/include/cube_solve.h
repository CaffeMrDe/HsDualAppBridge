#pragma once
#ifndef CUBE_SOLVE_H
#define CUBE_SOLVE_H

#include <ros/ros.h>

#include <Python.h>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class cubeSolve
{
    public:
      /**
       * @brief   构造函数
       */
      cubeSolve();

      /**
       * @brief   析构函数
       */
      ~cubeSolve();

      /**
       * @brief   解魔方执行总函数
       * @param   魔方54个小面颜色序列
       * @return  机器人执行动作的对应编码
       */
      vector<int> settlement(std::string c);

    private:
      
      /**
       * @brief   解魔方函数
       * @param   魔方54个小面颜色序列
       * @return  解魔方的步骤
       */
      char* ko_solve(std::string color_code);

      /**
       * @brief   魔方动作编码函数
       * @param   解魔方的步骤
       * @return  机器人执行动作的对应编码
       */
      vector<int> move_code(std::string solution);

      
      
};



#endif // CUBE_SOLVE_H