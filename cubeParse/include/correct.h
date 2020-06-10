#pragma once
#ifndef CORRECT_H
#define CORRECT_H

#include <ros/ros.h>

#include <iostream>
#include <vector>

using namespace std;

class correct
{
    public:
      /**
       * @brief   构造函数
       */
      correct();

      /**
       * @brief   析构函数
       */
      ~correct();

      /**
       * @brief   获取更改后的颜色序列
       */
      vector<char> getResult(string c);

    private:
      /**
       * @brief   确立基准面信息
       */
      vector<char> benchmark(vector<char> c);
      
      /**
       * @brief   进行颜色编码
       */
      char color_code(char color,  vector<char> facelet_label);

};

#endif // SCORRECT_H