#include "ros/ros.h"
#include <iostream>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <std_msgs/UInt16MultiArray.h>
#include <std_msgs/Bool.h>
#include "rb_ui/rb_DoubleBool.h"
#include "rb_ui/rb_ArrayAndBool.h"
#include "std_msgs/UInt8MultiArray.h"
using namespace std;
QT_BEGIN_NAMESPACE

class MainWindow:public QObject
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    ros::NodeHandle* Node;
    ros::ServiceServer server_rbConnCommand;
    ros::ServiceServer server_rbRunCommand ;
    ros::ServiceServer server_magicGetDatapCommand ;
    ros::ServiceServer server_magicSolveCommand ;
    ros::ServiceServer server_magicRunSolverCommand;
    ros::ServiceServer server_rbGrepSetCommand;
    ros::Publisher publisher_rbConnStatus;
    ros::Publisher publisher_rbErrStatus;
    ros::Subscriber subscriber_rbStop;
    void setupUi(QMainWindow *MainWindow,ros::NodeHandle* node )
    {
        Node=node;
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(892, 574);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
//        pushButton->setObjectName(QString::fromUtf8("pushButton"));
//        pushButton->setGeometry(QRect(20, 20, 311, 51));
//        pushButton_2 = new QPushButton(centralWidget);
//        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
//        pushButton_2->setGeometry(QRect(20, 110, 311, 51));
//        pushButton_3 = new QPushButton(centralWidget);
//        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
//        pushButton_3->setGeometry(QRect(20, 190, 311, 51));
//        pushButton_4 = new QPushButton(centralWidget);
//        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
//        pushButton_4->setGeometry(QRect(20, 260, 311, 51));
//        pushButton_5 = new QPushButton(centralWidget);
//        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
//        pushButton_5->setGeometry(QRect(20, 340, 311, 51));
//        pushButton_6 = new QPushButton(centralWidget);
//        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
//        pushButton_6->setGeometry(QRect(30, 410, 311, 51));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(460, 90, 311, 51));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(460, 170, 311, 51));
//        pushButton_9 = new QPushButton(centralWidget);
//        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
//        pushButton_9->setGeometry(QRect(460, 270, 311, 51));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 892, 31));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        MainWindow->show();

        QMetaObject::connectSlotsByName(MainWindow);
        run();
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
//        pushButton->setText(QApplication::translate("MainWindow", "server_rbConnCommand", nullptr));
//        pushButton_2->setText(QApplication::translate("MainWindow", "server_rbRunCommand", nullptr));
//        pushButton_3->setText(QApplication::translate("MainWindow", "server_magicGetDatapCommand", nullptr));
//        pushButton_4->setText(QApplication::translate("MainWindow", "server_magicSolveCommand", nullptr));
//        pushButton_5->setText(QApplication::translate("MainWindow", "server_magicRunSolverCommand", nullptr));
//        pushButton_6->setText(QApplication::translate("MainWindow", "server_rbGrepSetCommand", nullptr));
        pushButton_7->setText(QApplication::translate("MainWindow", "publisher_rbConnStatus", nullptr));
        pushButton_8->setText(QApplication::translate("MainWindow", "publisher_rbErrStatus", nullptr));
//        pushButton_9->setText(QApplication::translate("MainWindow", "subscriber_rbStop", nullptr));
    } // retranslateUi

    void run(){
        server_rbConnCommand = Node->advertiseService("/Rb_connCommand", &MainWindow::callback_rbConnCommand,this);
        server_rbRunCommand = Node->advertiseService("/Rb_runCommand", &MainWindow::callback_rbRunCommand,this);
        server_magicGetDatapCommand = Node->advertiseService("/MagicGetDataCommand", &MainWindow::callback_magicGetDatapCommand,this);
        server_magicSolveCommand = Node->advertiseService("/MagicSolveCommand", &MainWindow::callback_magicSolveCommand,this);
        server_magicRunSolverCommand = Node->advertiseService("/MagicRunSolveCommand", &MainWindow::callback_magicRunSolverCommand,this);
        server_rbGrepSetCommand = Node->advertiseService("/Rb_grepSetCommand", &MainWindow::callback_rbGrepSetCommand,this);
        publisher_rbConnStatus=Node->advertise<std_msgs::UInt8MultiArray>("/Rb_connStatus", 1);
        QObject::connect(pushButton_7,&QPushButton::clicked,this,&MainWindow::rbConnStatus);
        publisher_rbErrStatus=Node->advertise<std_msgs::UInt16MultiArray>("/Rb_errStatus", 1);
        QObject::connect(pushButton_8,&QPushButton::clicked,this,&MainWindow::rbErrStatus);
        subscriber_rbStop=Node->subscribe<std_msgs::Bool>("/Rb_stopCommand", 1,&MainWindow::callback_rbStop_subscriber,this);

    }

    void callback_rbStop_subscriber(std_msgs::Bool msg){
        if(msg.data){
            cout<<"接收到机器人停止命令"<<endl;
        } else{
            cout<<"没有接收到机器人停止命令"<<endl;
        }
    }

    void rbConnStatus(){
        cout<<"点击了连按钮"<<endl;
        std_msgs::UInt8MultiArray msg;
        msg.data.resize(2);
        msg.data[0]=1;
        msg.data[1]=1;
        publisher_rbConnStatus.publish(msg);
}
    void rbErrStatus(){
        cout<<"点击了故障按钮"<<endl;
        std_msgs::UInt16MultiArray msg;
        msg.data.resize(2);
        msg.data[0]=1;
        msg.data[1]=1;
        publisher_rbErrStatus.publish(msg);
    }
    bool callback_rbConnCommand(rb_ui::rb_DoubleBoolRequest& request,rb_ui::rb_DoubleBoolResponse& response){
        for (int i = 0; i < 99999; ++i) {
        if(request.request){
            cout<<"--"<<i<<"收到请求"<<endl;
        }
        }
        response.respond= true;
        cout<<"发出完成信号"<<endl;
    }

    bool callback_rbRunCommand(rb_ui::rb_DoubleBoolRequest& request,rb_ui::rb_DoubleBoolResponse& response){
        for (int i = 0; i < 99999; ++i) {
            if(request.request){
                cout<<"--"<<i<<"收到请求"<<endl;
            }
        }
        response.respond= true;
        cout<<"发出完成信号"<<endl;
    }

    bool callback_magicGetDatapCommand(rb_ui::rb_DoubleBoolRequest& request,rb_ui::rb_DoubleBoolResponse& response){
        for (int i = 0; i < 99999; ++i) {
            if(request.request){
                cout<<"--"<<i<<"收到请求"<<endl;
            }
        }
        response.respond= true;
        cout<<"发出完成信号"<<endl;
    }

    bool callback_magicSolveCommand(rb_ui::rb_DoubleBoolRequest& request,rb_ui::rb_DoubleBoolResponse& response){
        for (int i = 0; i < 99999; ++i) {
            if(request.request){
                cout<<"--"<<i<<"收到请求"<<endl;
            }
        }
        response.respond= true;
        cout<<"发出完成信号"<<endl;
    }

    bool callback_magicRunSolverCommand(rb_ui::rb_DoubleBoolRequest& request,rb_ui::rb_DoubleBoolResponse& response){
        for (int i = 0; i < 99999; ++i) {
            if(request.request){
                cout<<"--"<<i<<"收到请求"<<endl;
            }
        }
        response.respond= true;
        cout<<"发出完成信号"<<endl;
    }

    bool callback_rbGrepSetCommand(rb_ui::rb_ArrayAndBoolRequest& request,rb_ui::rb_ArrayAndBoolResponse& response){
        for (int i = 0; i < 99999; ++i) {
                cout<<"--"<<i<<"收到请求"<<endl;
        }
        request.data.resize(3);
        cout<<"收到请求数据"<<request.data[0]<<request.data[1]<<request.data[2]<<endl;
        response.respond= true;
        cout<<"发出完成信号"<<endl;
    }





};


int main(int args,char** argv){
    std::string nodeName = "test";
    ros::init(args, argv, nodeName);
    //创建节点
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node;
    QApplication app(args, argv);
    MainWindow window;
    QMainWindow w;
    window.setupUi(&w,&node);
    return app.exec();

}






