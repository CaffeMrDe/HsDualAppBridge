//
// Created by wangneng on 5/13/20.
//

#ifndef RB_UI_LOGCLASS_H
#define RB_UI_LOGCLASS_H

#include <iostream>
#include <fstream>
using namespace std;


class logClass {
public:
    enum logLevel{normal,err};
    //日志功能模块
    static void WriteLog(logLevel level,std::string log);


};


#endif //RB_UI_LOGCLASS_H
