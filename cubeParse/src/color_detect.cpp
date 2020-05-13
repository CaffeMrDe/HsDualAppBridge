#include "svmdetect.h"
#include "cube_solve.h"
#include "solve.h"
#include <Python.h>

#include <ros/ros.h>

using namespace std;



int main(int argc, char *argv[])
{
   
    ros::init(argc, argv, "cubeParse_bridge");
	ros::NodeHandle n;

	ros::AsyncSpinner spinner(2);
	spinner.start();
	
	svmDetect svm(n);
	Solve s(n);

    svm.start();
	s.start();
	
	ros::waitForShutdown();
    return 0;

}