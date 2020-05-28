cmake_minimum_required(VERSION 3.0.2)
project(rb_msgs)

find_package(catkin REQUIRED COMPONENTS
  std_msgs
  sensor_msgs
message_generation
)


## Generate messages in the 'msg' folder
 add_message_files(
   FILES
rbImageList.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   rb_ArrayAndBool.srv
rb_DoubleBool.srv
robotConn.srv
robotError.srv
SetEnableSrv.srv
 )

 generate_messages(
   DEPENDENCIES
   sensor_msgs
   std_msgs  # Or other packages containing msgs
 )


catkin_package(

CATKIN_DEPENDS message_runtime
)

#catkin_package(
#  CATKIN_DEPENDS  std_msgs
#)


