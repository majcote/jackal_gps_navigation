#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <robot_localization/navsat_conversions.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
ros::init(argc, argv, "gps_waypoint");

MoveBaseClient ac("move_base", true);
double latitude_goal, longitude_goal;

move_base_msgs::MoveBaseGoal goal;

//Get Longitude and Latitude goals from the parameter server
ros::param::get("latitude_goal", latitude_goal);
ros::param::get("longitude_goal", longitude_goal);
ROS_INFO("Received Latitude goal:%f", latitude_goal);
ROS_INFO("Received longitude goal:%f", longitude_goal);

double utm_x = 0;
double utm_y = 0;
std::string utm_zone;

//Convert Longituded / Latitude to UTM
RobotLocalization::NavsatConversions::LLtoUTM(latitude_goal, longitude_goal, utm_y, utm_x, utm_zone);
ROS_INFO("UTM Cord is %f, %f", utm_x, utm_y);

//TO DO - transform UTM to map
//tf::TransformListener listener;
//try{
//      listener.lookupTransform("/utm", "/map", ros::Time(0), transform);
//    }



goal.target_pose.header.frame_id = "map";
goal.target_pose.header.stamp = ros::Time::now();

//Send goal to move_base
goal.target_pose.pose.position.x = latitude_goal;
goal.target_pose.pose.position.y = longitude_goal;
goal.target_pose.pose.orientation.w = 1.0;
ROS_INFO("Sending goal");
ac.sendGoal(goal);

ac.waitForResult();

if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  ROS_INFO("Jackal has reached it's goal");
else
  ROS_INFO("Jackal was unable to reach it's goal");

return 0;
}
