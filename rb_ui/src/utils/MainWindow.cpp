#include <rb_ui/rb_DoubleBool.h>
#include "MainWindow.h"
#include "logmanager.h"


MainWindow::MainWindow(ros::NodeHandle *node, QWidget *parent):QMainWindow(parent),Node(node){



    flag_rbConnStatus= false;
    //创建发布者/订阅者
    rbStopCommand_publisher= Node->advertise<std_msgs::Bool>("/Rb_stopCommand", 1000);
    SafetyStop_publisher=Node->advertise<std_msgs::Bool>("/Safety_stop", 1000);
    rbConnStatus_subscriber=Node->subscribe<std_msgs::UInt8MultiArray>("/Rb_connStatus", 1,&MainWindow::callback_rbConnStatus_subscriber,this);
    rbErrStatus_subscriber=Node->subscribe<std_msgs::UInt16MultiArray>("/Rb_errStatus", 1000,&MainWindow::callback_rbErrStatus_subscriber,this);
//  camera_subscriber=Node->subscribe<std_msgs::String>("", 1000,&MainWindow::callback_camera_subscriber, this));
    rbGrepSetCommand_client = Node->serviceClient<rb_ui::rb_ArrayAndBool>("/Rb_grepSetCommand");
    rbConnCommand_client = Node->serviceClient<rb_ui::rb_DoubleBool>("/Rb_connCommand");
    rbRunCommand_client = Node->serviceClient<rb_ui::rb_DoubleBool>("/Rb_runCommand");
    MagicGetDataCommand_client = Node->serviceClient<rb_ui::rb_DoubleBool>("/MagicGetDataCommand");
    MagicSolveCommand_client= Node->serviceClient<rb_ui::rb_DoubleBool>("/MagicSolveCommand");
    MagicRunSolveCommand_client = Node->serviceClient<rb_ui::rb_DoubleBool>("/MagicRunSolveCommand");
    initUi(this);
    retranslateUi(this);
    signalAndSlot();
}





void MainWindow::initUi(QMainWindow *MainWindow) {
//    if (MainWindow->objectName().isEmpty())
//        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
//    MainWindow->resize(967, 645);
//    QImage _image;
//    _image.load("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/a.jpg");
//    setAutoFillBackground(true);   // 这个属性一定要设置
//    QPalette pal(palette());
////    pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio)));
//    pal.setBrush(QPalette::Window, QBrush(_image.scaled(size(), Qt::IgnoreAspectRatio,
//                                                        Qt::SmoothTransformation)));
//    setPalette(pal);
//    设置背景颜色:
//    this->setStyleSheet("background-color:rgb(255,34,198)");
    MainWindow->resize(967, 824);
//    QLabel* qlabel = new QLabel(this);
//    qlabel->setGeometry(0, 0, this->width(), this->height());
//    QPixmap bgImage("a.jpg");
//    qlabel->setStyleSheet("background-color:black");
//    qlabel->setAlignment(Qt::AlignCenter);
//    qlabel->setPixmap(bgImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    verticalLayout_2 = new QVBoxLayout(centralWidget);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label_3 = new QLabel(centralWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/logo.png")));

    horizontalLayout->addWidget(label_3);

    label = new QLabel(centralWidget);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(false);
    font.setWeight(75);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    horizontalLayout->addWidget(label);

    horizontalLayout->setStretch(0, 1);
    horizontalLayout->setStretch(1, 6);

    verticalLayout->addLayout(horizontalLayout);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    tabWidget = new QTabWidget(centralWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    horizontalLayout_4 = new QHBoxLayout(tab);
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    verticalLayout_4 = new QVBoxLayout();
    verticalLayout_4->setSpacing(30);
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
//    verticalLayout_4->setStretch(0,1);
//    verticalLayout_4->setStretch(1,1);
    verticalLayout_4->setContentsMargins(-1, -1, -1, 100);
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalLayout_2->setContentsMargins(-1, -1, 0, 50);
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    label_5 = new QLabel(tab);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    gridLayout->addWidget(label_5, 0, 0, 1, 1);
    label_rb1CoonStatus = new QLabel(tab);
    label_rb1CoonStatus->setObjectName(QString::fromUtf8("label_rb1CoonStatus"));
    label_rb1CoonStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_red.png")));
    label_rb1CoonStatus->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    gridLayout->addWidget(label_rb1CoonStatus, 0, 1, 1, 1);

    label_6 = new QLabel(tab);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    gridLayout->addWidget(label_6, 0, 2, 1, 1);
    label_rb2CoonStatus = new QLabel(tab);
    label_rb2CoonStatus->setObjectName(QString::fromUtf8("label_rb2CoonStatus"));
    label_rb2CoonStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_red.png")));
    label_rb2CoonStatus->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    gridLayout->addWidget(label_rb2CoonStatus, 0, 3, 1, 1);

    label_7 = new QLabel(tab);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    gridLayout->addWidget(label_7, 0, 4, 1, 1);
    label_rb1ErrStatus = new QLabel(tab);
    label_rb1ErrStatus->setObjectName(QString::fromUtf8("label_rb1ErrStatus"));
    label_rb1ErrStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_red.png")));
    label_rb1ErrStatus->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    gridLayout->addWidget(label_rb1ErrStatus, 0, 5, 1, 1);

    label_8 = new QLabel(tab);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    gridLayout->addWidget(label_8, 0, 6, 1, 1);
    label_rb2ErrStatus = new QLabel(tab);
    label_rb2ErrStatus->setObjectName(QString::fromUtf8("label_rb2ErrStatus"));
    label_rb2ErrStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_red.png")));
    label_rb2ErrStatus->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    gridLayout->addWidget(label_rb2ErrStatus, 0, 7, 1, 1);

    horizontalLayout_2->addLayout(gridLayout);
    verticalLayout_4->addLayout(horizontalLayout_2);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setSpacing(6);
    horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
    btn_rbConn = new QPushButton(tab);
    btn_rbConn->setObjectName(QString::fromUtf8("btn_rbConn"));

    horizontalLayout_5->addWidget(btn_rbConn);

    btn_rvizRun = new QPushButton(tab);
    btn_rvizRun->setObjectName(QString::fromUtf8("btn_rvizRun"));

    horizontalLayout_5->addWidget(btn_rvizRun);

    btn_beginRun = new QPushButton(tab);
    btn_beginRun->setObjectName(QString::fromUtf8("btn_beginRun"));

    horizontalLayout_5->addWidget(btn_beginRun);

    btn_normalStop = new QPushButton(tab);
    btn_normalStop->setObjectName(QString::fromUtf8("btn_normalStop"));

    horizontalLayout_5->addWidget(btn_normalStop);


    verticalLayout_4->addLayout(horizontalLayout_5);

    verticalLayout_4->setStretch(0, 1);
    verticalLayout_4->setStretch(1, 1);

    horizontalLayout_4->addLayout(verticalLayout_4);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    tabWidget->addTab(tab_2, QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    horizontalLayout_8 = new QHBoxLayout(tab_3);
    horizontalLayout_8->setSpacing(6);
    horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
    horizontalLayout_7 = new QHBoxLayout();
    horizontalLayout_7->setSpacing(6);
    horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
    verticalLayout_6 = new QVBoxLayout();
    verticalLayout_6->setSpacing(6);
    verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
    tableView = new QTableView(tab_3);
    tableView->setObjectName(QString::fromUtf8("tableView"));

    verticalLayout_6->addWidget(tableView);


    horizontalLayout_7->addLayout(verticalLayout_6);

    verticalLayout_8 = new QVBoxLayout();
    verticalLayout_8->setSpacing(6);
    verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
    btn_magicGetdata = new QPushButton(tab_3);
    btn_magicGetdata->setObjectName(QString::fromUtf8("btn_magicGetdata"));

    verticalLayout_8->addWidget(btn_magicGetdata);

    btn_magicSolve = new QPushButton(tab_3);
    btn_magicSolve->setObjectName(QString::fromUtf8("btn_magicSolve"));

    verticalLayout_8->addWidget(btn_magicSolve);

    btn_magicRunSolve = new QPushButton(tab_3);
    btn_magicRunSolve->setObjectName(QString::fromUtf8("btn_magicRunSolve"));

    verticalLayout_8->addWidget(btn_magicRunSolve);

    btn_magicAutoSolve = new QPushButton(tab_3);
    btn_magicAutoSolve->setObjectName(QString::fromUtf8("btn_magicAutoSolve"));

    verticalLayout_8->addWidget(btn_magicAutoSolve);


    horizontalLayout_7->addLayout(verticalLayout_8);


    horizontalLayout_8->addLayout(horizontalLayout_7);

    tabWidget->addTab(tab_3, QString());
    tab_4 = new QWidget();
    tab_4->setObjectName(QString::fromUtf8("tab_4"));
    horizontalLayout_10 = new QHBoxLayout(tab_4);
    horizontalLayout_10->setSpacing(6);
    horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
    horizontalLayout_9 = new QHBoxLayout();
    horizontalLayout_9->setSpacing(6);
    horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
    verticalLayout_11 = new QVBoxLayout();
    verticalLayout_11->setSpacing(6);
    verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
    label_2 = new QLabel(tab_4);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setAlignment(Qt::AlignCenter);

    verticalLayout_11->addWidget(label_2);


    horizontalLayout_9->addLayout(verticalLayout_11);

    verticalLayout_9 = new QVBoxLayout();
    verticalLayout_9->setSpacing(6);
    verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));

    groupBox_setMod = new QGroupBox(tab_4);
    groupBox_setMod->setObjectName(QString::fromUtf8("groupBox_setMod"));
    horizontalLayout_11 = new QHBoxLayout(groupBox_setMod);
    horizontalLayout_11->setSpacing(6);
    horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
    comboBox = new QComboBox(groupBox_setMod);
    comboBox->addItem(QString());
    comboBox->addItem(QString());
    comboBox->setObjectName(QString::fromUtf8("comboBox"));

    horizontalLayout_11->addWidget(comboBox);


    verticalLayout_9->addWidget(groupBox_setMod);

    groupBox_selectObject = new QGroupBox(tab_4);
    groupBox_selectObject->setObjectName(QString::fromUtf8("groupBox_selectObject"));
    horizontalLayout_12 = new QHBoxLayout(groupBox_selectObject);
    horizontalLayout_12->setSpacing(6);
    horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
    comboBox_2 = new QComboBox(groupBox_selectObject);
    comboBox_2->addItem(QString());
    comboBox_2->addItem(QString());
    comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

    horizontalLayout_12->addWidget(comboBox_2);


    verticalLayout_9->addWidget(groupBox_selectObject);

    groupBox_selectRobot = new QGroupBox(tab_4);
    groupBox_selectRobot->setObjectName(QString::fromUtf8("groupBox_selectRobot"));
    horizontalLayout_13 = new QHBoxLayout(groupBox_selectRobot);
    horizontalLayout_13->setSpacing(6);
    horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
    comboBox_3 = new QComboBox(groupBox_selectRobot);
    comboBox_3->addItem(QString());
    comboBox_3->addItem(QString());
    comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

    horizontalLayout_13->addWidget(comboBox_3);


    verticalLayout_9->addWidget(groupBox_selectRobot);

    btn_rbGrep = new QPushButton(tab_4);
    btn_rbGrep->setObjectName(QString::fromUtf8("btn_rbGrep"));

    verticalLayout_9->addWidget(btn_rbGrep);


    horizontalLayout_9->addLayout(verticalLayout_9);
    horizontalLayout_9->setStretch(0,3);
    horizontalLayout_9->setStretch(1,1);

    horizontalLayout_10->addLayout(horizontalLayout_9);

    tabWidget->addTab(tab_4, QString());
    tab_5 = new QWidget();
    tab_5->setObjectName(QString::fromUtf8("tab_5"));
    horizontalLayout_15 = new QHBoxLayout(tab_5);
    horizontalLayout_15->setSpacing(6);
    horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
    horizontalLayout_16 = new QHBoxLayout();
    horizontalLayout_16->setSpacing(6);
    horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
    verticalLayout_13 = new QVBoxLayout();
    verticalLayout_13->setSpacing(6);
    verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
    plainTextEdit = new QPlainTextEdit(tab_5);
    plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

    verticalLayout_13->addWidget(plainTextEdit);


    horizontalLayout_16->addLayout(verticalLayout_13);

    verticalLayout_12 = new QVBoxLayout();
    verticalLayout_12->setSpacing(6);
    verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
    btn_oputRecord = new QPushButton(tab_5);
    btn_oputRecord->setObjectName(QString::fromUtf8("btn_oputRecord"));

    btn_clearRecord = new QPushButton(tab_5);
    btn_clearRecord->setObjectName(QString::fromUtf8("btn_clearRecord"));
    verticalLayout_12->addWidget(btn_oputRecord);
    verticalLayout_12->addWidget(btn_clearRecord);


    horizontalLayout_16->addLayout(verticalLayout_12);


    horizontalLayout_15->addLayout(horizontalLayout_16);

    tabWidget->addTab(tab_5, QString());
    tab_6 = new QWidget();
    tab_6->setObjectName(QString::fromUtf8("tab_6"));
    horizontalLayout_18 = new QHBoxLayout(tab_6);
    horizontalLayout_18->setSpacing(6);
    horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
    horizontalLayout_17 = new QHBoxLayout();
    horizontalLayout_17->setSpacing(6);
    horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
    btn_SatetyStop = new QPushButton(tab_6);
    btn_SatetyStop->setObjectName(QString::fromUtf8("btn_SatetyStop"));

    horizontalLayout_17->addWidget(btn_SatetyStop);

    btn_SatetyRb1Stop = new QPushButton(tab_6);
    btn_SatetyRb1Stop->setObjectName(QString::fromUtf8("btn_SatetyRb1Stop"));

    horizontalLayout_17->addWidget(btn_SatetyRb1Stop);

    btn_SatetyRb2Stop = new QPushButton(tab_6);
    btn_SatetyRb2Stop->setObjectName(QString::fromUtf8("btn_SatetyRb2Stop"));

    horizontalLayout_17->addWidget(btn_SatetyRb2Stop);


    horizontalLayout_18->addLayout(horizontalLayout_17);

    tabWidget->addTab(tab_6, QString());

    horizontalLayout_3->addWidget(tabWidget);


    verticalLayout->addLayout(horizontalLayout_3);

    verticalLayout->setStretch(0, 1);
    verticalLayout->setStretch(1, 9);

    verticalLayout_2->addLayout(verticalLayout);

    MainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 967, 31));
    MainWindow->setMenuBar(menuBar);
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    MainWindow->setStatusBar(statusBar);

//    retranslateUi(this);

    tabWidget->setCurrentIndex(0);
//    QMetaObject::connectSlotsByName(this);
}


void MainWindow::retranslateUi(QMainWindow *MainWindow) {
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\345\217\214\346\234\272\345\231\250\344\272\272\344\272\222\345\212\250\344\270\216\345\215\217\344\275\234\345\271\263\345\217\260", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "机器人1连接状态", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "机器人2连接状态", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "机器人1报警状态", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "机器人2报警状态", nullptr));

        label_rb1CoonStatus->setText(QString());
        btn_rbConn->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\236\346\216\245", nullptr));
        btn_rvizRun->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250rviz", nullptr));
        btn_beginRun->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\277\220\350\241\214", nullptr));
        btn_normalStop->setText(QApplication::translate("MainWindow", "\345\215\225\346\254\241\345\201\234\346\255\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\344\273\277\347\234\237\347\225\214\351\235\242", nullptr));
        btn_magicGetdata->setText(QApplication::translate("MainWindow", "\351\207\207\351\233\206\351\255\224\346\226\271\346\225\260\346\215\256", nullptr));
        btn_magicSolve->setText(QApplication::translate("MainWindow", "\350\247\243\347\256\227", nullptr));
        btn_magicRunSolve->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214\350\247\243\347\256\227", nullptr));
        btn_magicAutoSolve->setText(QApplication::translate("MainWindow", "\344\270\200\351\224\256\350\247\243\347\256\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\351\255\224\346\226\271\347\225\214\351\235\242", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\346\230\276\347\244\272", nullptr));
        groupBox_setMod->setTitle(QApplication::translate("MainWindow", "\346\250\241\345\274\217\350\256\276\347\275\256", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "\344\273\216\346\241\214\345\255\220\346\212\223,\346\224\276\350\264\247\346\236\266\344\270\212", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "\344\273\216\350\264\247\346\236\266\346\212\223.\346\224\276\346\241\214\345\255\220\344\270\212", nullptr));

        groupBox_selectObject->setTitle(QApplication::translate("MainWindow", "\346\212\223\345\217\226\345\257\271\350\261\241", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "\345\217\257\344\271\220\347\275\220", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "\347\211\233\345\245\266\347\233\222", nullptr));

        groupBox_selectRobot->setTitle(QApplication::translate("MainWindow", "\346\234\254\344\275\223\351\200\211\346\213\251", nullptr));
        comboBox_3->setItemText(0, QApplication::translate("MainWindow", "\345\267\246\346\234\272\345\231\250\344\272\272\346\212\223", nullptr));
        comboBox_3->setItemText(1, QApplication::translate("MainWindow", "\345\217\263\346\234\272\345\231\250\344\272\272\346\212\223", nullptr));

        btn_rbGrep->setText(QApplication::translate("MainWindow", "\346\211\247\350\241\214\346\212\223\345\217\226", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\346\212\223\345\217\226\347\225\214\351\235\242", nullptr));
        btn_oputRecord->setText(QApplication::translate("MainWindow", "\346\227\245\345\277\227\345\257\274\345\207\272", nullptr));
        btn_clearRecord->setText(QApplication::translate("MainWindow", "日志清除", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "\346\227\245\345\277\227\347\225\214\351\235\242", nullptr));
        btn_SatetyStop->setText(QApplication::translate("MainWindow", "\347\263\273\347\273\237\346\200\245\345\201\234", nullptr));
        btn_SatetyRb1Stop->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\2721\345\201\234\346\255\242", nullptr));
        btn_SatetyRb2Stop->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\2722\345\201\234\346\255\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "\345\256\211\345\205\250\347\225\214\351\235\242", nullptr));
    } // retranslateUi
}


void MainWindow::signalAndSlot() {

    //设备连接
    connect(btn_rbConn,&QPushButton::clicked,this,&MainWindow::dev_connect);
    //rviz启动
    connect(btn_rvizRun,&QPushButton::clicked,this,&MainWindow::rviz_statup);
    //运行启动
    connect(btn_beginRun,&QPushButton::clicked,this,&MainWindow::run_statup);
    //运行停止
    connect(btn_normalStop,&QPushButton::clicked,this,&MainWindow::run_stop);
    //采集魔方数据
    connect(btn_magicGetdata,&QPushButton::clicked,this,&MainWindow::magicCube_get);
    //解算魔方数据
    connect(btn_magicSolve,&QPushButton::clicked,this,&MainWindow::magicCube_solve);
    //执行解算魔方数据
    connect(btn_magicRunSolve,&QPushButton::clicked,this,&MainWindow::magicCube_execute);
    //机器人抓取
    connect(btn_rbGrep,&QPushButton::clicked,this,&MainWindow::robot_grab);
    //导出日志
    connect(btn_oputRecord,&QPushButton::clicked,this,&MainWindow::oputRecord);
    //清除日志
    connect(btn_clearRecord,&QPushButton::clicked,this,&MainWindow::clearRecord);
    //系统停止
    connect(btn_SatetyStop,&QPushButton::clicked,this,&MainWindow::safety_sysStop);
    //机器人1停止
    connect(btn_SatetyRb1Stop,&QPushButton::clicked,this,&MainWindow::safety_rob1Stop);
    //机器人2停止
    connect(btn_SatetyRb2Stop,&QPushButton::clicked,this,&MainWindow::safety_rob2Stop);

    connect(this, &MainWindow::emitTextControl,this, &MainWindow::displayTextControl);

    //给设备连接按钮事件开辟子线程
    thread_forRbConn = new qthreadForRos();
    thread_forRbConn->setParm(this,&MainWindow::thread_rbConnCommand);
    //开始运行子线程
    thread_forBeginRun= new qthreadForRos();
    thread_forBeginRun->setParm(this,&MainWindow::thread_BeginRun);
    //采集魔方数据子线程
    thread_forGagicGetData= new qthreadForRos();
    thread_forGagicGetData->setParm(this,&MainWindow::thread_GagicGetData);
    //解算魔方子线程
    thread_forGagicSolve= new qthreadForRos();
    thread_forGagicSolve->setParm(this,&MainWindow::thread_GagicSolve);
    //运行解算子线程
    thread_forGagicRunSolve= new qthreadForRos();
    thread_forGagicRunSolve->setParm(this,&MainWindow::thread_GagicRunSolve);
    //机器人抓取子线程
    thread_forRbGrepSet= new qthreadForRos();
    thread_forRbGrepSet->setParm(this,&MainWindow::thread_RbGrepSet);
}

void MainWindow::dev_connect() {
    cout<<"点击了设备连接按钮"<<endl;
    //    if(!flag_rbConnStatus){
    thread_forRbConn->start();//把耗时操作放在子线程中避免堵塞主线程,多次调用start,若子线程未执行完,则自动拦截之后的请求,随便多次按.
    //    }
}

void MainWindow::rviz_statup() {
    QProcess *proc = new QProcess;
    proc->start("rosrun rviz rviz");
    cout<<"点击了qviz启动按钮"<<endl;
}

void MainWindow::run_statup() {
    cout<<"点击了运行启动按钮"<<endl;
    thread_forBeginRun->start();
}

void MainWindow::run_stop() {
    cout<<"点击了运行停止按钮"<<endl;
    std_msgs::Bool data_msg;
    data_msg.data= true;
    rbStopCommand_publisher.publish(data_msg);
}

void MainWindow::magicCube_get() {
    cout<<"点击了采集魔方数据按钮"<<endl;
    thread_forGagicGetData->start();
}

void MainWindow::magicCube_solve() {
    cout<<"点击了解算魔方数据按钮"<<endl;
    thread_forGagicSolve->start();
}

void MainWindow::magicCube_execute() {
    cout<<"点击了执行解算魔方数据按钮"<<endl;
    thread_forGagicRunSolve->start();
}

void MainWindow::robot_grab() {
    cout<<"点击了机器人抓取按钮"<<endl;
    thread_forRbGrepSet->start();

}

void MainWindow::safety_sysStop() {
    cout<<"点击了系统停止按钮"<<endl;
}

void MainWindow::safety_rob1Stop() {
    cout<<"点击了机器人1停止按钮"<<endl;
}

void MainWindow::safety_rob2Stop() {
    cout<<"点击了机器人2停止按钮"<<endl;
}

void MainWindow::callback_rbConnStatus_subscriber(std_msgs::UInt8MultiArray data_msg) {
//    if(data_msg.data[0]==1){
//        checkBox_rb1CoonStatus->setChecked(true);
//    } else{
//        checkBox_rb1CoonStatus->setChecked(false);
//    }
//
//    if(data_msg.data[1]==1){
//        checkBox_rb2CoonStatus->setChecked(true);
//    } else{
//        checkBox_rb2CoonStatus->setChecked(false);
//    }
    //两台机器人均连上了才表示连接标志成功
    if(data_msg.data[0]==1&&data_msg.data[1]==1){
        flag_rbConnStatus= true;
        cout<<"接收到连接成功数据"<<endl;
    } else{
        flag_rbConnStatus= false;
    }
}

void MainWindow::callback_rbErrStatus_subscriber(std_msgs::UInt16MultiArray data_msg) {
    if(data_msg.data[0]==1){
        label_rb1ErrStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_red.png")));
        LOG("Robot")->logErrorMessage("机器人1故障");
    }
    if(data_msg.data[1]==1){
        label_rb2ErrStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_red.png")));
        LOG("Robot")->logErrorMessage("机器人2故障");
    }
}

void MainWindow::callback_camera_subscriber() {

}

void MainWindow::oputRecord() {
    QString displayString;
    QFile file("./robotLog.log");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
//        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        displayString.append(str);
    }
    file.close();
    plainTextEdit->clear();
    plainTextEdit->setPlainText(displayString);
}

void MainWindow::clearRecord() {
    plainTextEdit->clear();
}

void MainWindow::displayTextControl(QString text) {
    plainTextEdit->appendPlainText(text);
}

void MainWindow::thread_rbConnCommand() {
    rb_ui::rb_DoubleBool data_srvs;
    data_srvs.request.request=true;
    if(rbConnCommand_client.call(data_srvs)){
        if(data_srvs.response.respond){
            label_rb1CoonStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_green.png")));
            label_rb2CoonStatus->setPixmap(QPixmap(QString::fromUtf8("/home/wangneng/catkin_ws/src/HsDualAppBridge/rb_ui/photo/light_green.png")));
        }
    } else{
        LOG("Warning")->logErrorMessage("rbConnCommand_client接收消息失败!");
    }
}

void MainWindow::thread_BeginRun() {
    rb_ui::rb_DoubleBool data_srvs;
    data_srvs.request.request=true;
    if(rbRunCommand_client.call(data_srvs)){
        if(data_srvs.response.respond){
            cout<<"开始运行成功"<<endl;
        }
    } else{
        LOG("Warning")->logErrorMessage("rbRunCommand_client接收消息失败!");
    }
}

void MainWindow::thread_GagicGetData() {
    rb_ui::rb_DoubleBool data_srvs;
    data_srvs.request.request=true;
    if(MagicGetDataCommand_client.call(data_srvs)){
        if(data_srvs.response.respond){
            cout<<"获取魔方数据成功"<<endl;
        }
    } else{
        LOG("Warning")->logErrorMessage("MagicGetDataCommand_client接收消息失败!");
    }

}

void MainWindow::thread_GagicSolve() {
    rb_ui::rb_DoubleBool data_srvs;
    data_srvs.request.request=true;
    if(MagicSolveCommand_client.call(data_srvs)){
        if(data_srvs.response.respond){
            cout<<"解算魔方数据成功"<<endl;
        }
    } else{
        LOG("")->logWarnMessage("MagicSolveCommand_client接收消息失败!");
    }
}

void MainWindow::thread_GagicRunSolve() {
    rb_ui::rb_DoubleBool data_srvs;
    data_srvs.request.request=true;
    if(MagicRunSolveCommand_client.call(data_srvs)){
        if(data_srvs.response.respond){
            cout<<"运行魔方解算数据成功"<<endl;
        }
    } else{
        LOG("Warning")->logErrorMessage("rbGrepSetCommand_client接收消息失败!");

    }
}

void MainWindow::thread_RbGrepSet() {
    int index1=comboBox->currentIndex();
    int index2=comboBox_2->currentIndex();
    int index3=comboBox_3->currentIndex();
    rb_ui::rb_ArrayAndBool data_msg;
    data_msg.request.data.reserve(3);
    data_msg.request.data[0]=index1;
    data_msg.request.data[1]=index2;
    data_msg.request.data[2]=index3;
    if(rbGrepSetCommand_client.call(data_msg)){
    if(data_msg.response.respond){
        cout<<"抓取成功"<<endl;
    }
    } else{
        LOG("Warning")->logErrorMessage("rbGrepSetCommand_client接收消息失败!");
    }
}

MainWindow::~MainWindow() {
    if(!thread_forRbGrepSet){
        delete thread_forRbGrepSet;
        thread_forRbGrepSet= nullptr;
        cout<<"thread_forRbGrepSet空间销毁"<<endl;
    }
    if(!thread_forGagicSolve){
        delete thread_forGagicSolve;
        thread_forGagicSolve= nullptr;
    }
    if(!thread_forGagicGetData){
        delete thread_forGagicGetData;
        thread_forGagicGetData= nullptr;
    }
    if(!thread_forBeginRun){
        delete thread_forBeginRun;
        thread_forBeginRun= nullptr;
    }
    if(!thread_forGagicRunSolve){
        delete thread_forGagicRunSolve;
        thread_forGagicRunSolve= nullptr;
    }
    if(!thread_forRbConn){
        delete thread_forRbConn;
        thread_forRbConn= nullptr;
    }
}








