cmake_minimum_required(VERSION 2.8.3)
project(move_base)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  rospy
  roscpp
  std_msgs
  roslaunch
)

roslaunch_add_file_check(launch)


catkin_package(
CATKIN_DEPENDS rospy geometry_msgs std_msgs
)

add_executable(move_base src/move_base.cpp)
target_link_libraries(move_base  ${catkin_LIBRARIES})


include_directories(
  ${catkin_INCLUDE_DIRS}
)
