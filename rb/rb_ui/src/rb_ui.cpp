#include "src/utils/MainWindow.h"
using namespace std;


int main(int args,char** argv){
    std::string nodeName = "robot_UI";
    ros::init(args, argv, nodeName);
    //创建节点
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node;
    QApplication app(args, argv);
    MainWindow mainwindow;
    mainwindow.setupUi(&node);
    return app.exec();

}






