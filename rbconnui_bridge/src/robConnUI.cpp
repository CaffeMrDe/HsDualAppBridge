#include <iostream>
#include "ros/ros.h"
#include "rbconnui_bridge/util_robConnUI.h"
using namespace std;


int main(int args,char** avgs){
    ros::init(args,avgs,"RobConnUI");
    ros::NodeHandle node;
    RobConnUI rbcui(&node);
    ros::spin();
    return 0;
}



