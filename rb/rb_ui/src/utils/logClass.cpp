
#include "logClass.h"

void logClass::WriteLog(logClass::logLevel level, std::string log) {
    try
    {
//        char* pathname; //获取路径名
//        pathname = get_current_dir_name();
//        cout<<"path="<<pathname<<endl;
        std::ofstream ofs;
        time_t t = time(0);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "[%Y-%m-%d %X]", localtime(&t));
        ofs.open("./robotLog.log", std::ofstream::app);
        ofs << tmp << " - ";
        switch (level){
            case normal:ofs << "normal" << " - ";ofs.write(log.c_str(), log.size()) ;break;
            case err:ofs << "err" << " - ";ofs.write(log.c_str(), log.size());break;
            default:ofs.write(log.c_str(), log.size());
        }
        ofs << std::endl;
        ofs.close();
    }
    catch(...)
    {
    }

}
