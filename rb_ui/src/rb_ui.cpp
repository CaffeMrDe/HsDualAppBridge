#include "include/rb_ui/MainWindow.h"
#include "logmanager.h"
#include "globalvar.h"
#include "messagehandler.h"
using namespace std;


int main(int args,char** argv){
    std::string nodeName = "robot_UI";
    ros::init(args, argv, nodeName);
    //创建节点
    log4cplus::Initializer initializer;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node;
    QApplication app(args, argv);
    MainWindow mainwindow;
    mainwindow.setupUi(&node);
    gloalMain = &mainwindow;

    qInstallMessageHandler(customMessageHandler);

    return app.exec();

}






