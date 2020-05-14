
#ifndef RB_UI_MAINWINDOW_H
#define RB_UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QTimer>
#include <iostream>
#include <ctime>
#include <fstream>
//#include <direct.h>
//#include <unistd.h>
#include "QDebug"
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/UInt16MultiArray.h"
#include "roscpp_tutorials/TwoInts.h"
#include "rb_srvs/rb_DoubleBool.h"
#include "rb_srvs/rb_ArrayAndBool.h"
#include "logClass.h"
using namespace std;

class MainWindow: public QObject {
public:
    //ros节点
    ros::NodeHandle* Node;
    ros::Publisher rbStopCommand_publisher;//机器人停止命令
    ros::Publisher SafetyStop_publisher;//机器人紧急停止
    ros::Subscriber rbConnStatus_subscriber;//机器人连接状态
    ros::Subscriber rbErrStatus_subscriber;//机器人故障状态
    ros::Subscriber camera_subscriber;//相机数据采集
    ros::ServiceClient rbGrepSetCommand_client;
    ros::ServiceClient rbConnCommand_client ;
    ros::ServiceClient rbRunCommand_client ;
    ros::ServiceClient MagicGetDataCommand_client;
    ros::ServiceClient MagicSolveCommand_client;
    ros::ServiceClient MagicRunSolveCommand_client;

    //qt控件
    QMainWindow* w;
    QTimer* updateTimer;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_rb1CoonStatus;
    QCheckBox *checkBox_rb2CoonStatus;
    QCheckBox *checkBox_rb1ErrStatus;
    QCheckBox *checkBox_rb2ErrStatus;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btn_rbConn;
    QPushButton *btn_rvizRun;
    QPushButton *btn_beginRun;
    QPushButton *btn_normalStop;
    QWidget *tab_2;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_8;
    QPushButton *btn_magicGetdata;
    QPushButton *btn_magicSolve;
    QPushButton *btn_magicRunSolve;
    QPushButton *btn_magicAutoSolve;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_setMod;
    QHBoxLayout *horizontalLayout_11;
    QComboBox *comboBox;
    QGroupBox *groupBox_selectObject;
    QHBoxLayout *horizontalLayout_12;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_selectRobot;
    QHBoxLayout *horizontalLayout_13;
    QComboBox *comboBox_3;
    QPushButton *btn_rbGrep;
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout_15;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout_13;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout_12;
    QPushButton *btn_oputRecord;
    QPushButton *btn_clearRecord;
    QWidget *tab_6;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *btn_SatetyStop;
    QPushButton *btn_SatetyRb1Stop;
    QPushButton *btn_SatetyRb2Stop;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    //UI流程
    void setupUi(ros::NodeHandle* node);
    void initUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
    //处理所有信号和槽函数
    void signalAndSlot();
    //槽函数
    void onUpdate();//定时刷新
    void dev_connect();//按钮槽函数_设备连接槽函数
    void rviz_statup();//按钮槽函数_rviz启动
    void run_statup();//按钮槽函数_运行启动
    void run_stop();//按钮槽函数_运行停止
    void magicCube_get();//按钮槽函数_采集魔方数据
    void magicCube_solve();//按钮槽函数_解算魔方数据
    void magicCube_execute();//按钮槽函数_执行解算魔方数据
    void robot_grab();//按钮槽函数_机器人抓取
    void safety_sysStop();//按钮槽函数_系统停止
    void safety_rob1Stop();//按钮槽函数_机器人1停止
    void safety_rob2Stop();//按钮槽函数_机器人2停止
    void oputRecord();
    void clearRecord();

    //ros节点回调函数
    void callback_rbConnStatus_subscriber(std_msgs::UInt8MultiArray data_msg);
    void callback_rbErrStatus_subscriber(std_msgs::UInt16MultiArray data_msg);
    void callback_camera_subscriber();

};


#endif //RB_UI_MAINWINDOW_H