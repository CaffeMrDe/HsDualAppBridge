#pragma once
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/UInt16MultiArray.h>
#include "communication_bridge/rb_ArrayAndBool.h"
#include "communication_bridge/rb_DoubleBool.h"
#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;
 

class RobConnUI
{
private:
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
public:
    bool checkNet(std::string);
    bool checkAllNect();
    bool stopCommand();
    RobConnUI(ros::NodeHandle* node);
    ~RobConnUI();

public:
    void callback_rbStop_subscriber(std_msgs::Bool msg);
    void rbConnStatus();
    void rbErrStatus();
    bool callback_rbConnCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response);
    bool callback_rbRunCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response);
    bool callback_magicGetDatapCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response);
    bool callback_magicSolveCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response);
    bool callback_magicRunSolverCommand(communication_bridge::rb_DoubleBoolRequest& request,communication_bridge::rb_DoubleBoolResponse& response);
    bool callback_rbGrepSetCommand(communication_bridge::rb_ArrayAndBoolRequest& request,communication_bridge::rb_ArrayAndBoolResponse& response);
};






