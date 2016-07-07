cmake_minimum_required(VERSION 2.8.3)
project(jackal_gps_nav)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  move_base_msgs
  roscpp
  diagnostic_msgs
  diagnostic_updater
  geographic_msgs
  geometry_msgs
  message_filters
  message_generation
  nav_msgs
  roslint
  sensor_msgs
  std_msgs
  tf
  tf2
  tf2_geometry_msgs
  tf2_ros
)

catkin_package(
)

add_executable(gps_waypoint src/gps_waypoint.cpp)
target_link_libraries(gps_waypoint ${catkin_LIBRARIES})
