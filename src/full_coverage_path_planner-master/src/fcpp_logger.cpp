#include <tf2_ros/transform_listener.h>
#include <nav_msgs/GetPlan.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <iostream>
#include <fstream>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "fcpp_logger");
    ros::NodeHandle nh;

    tf2_ros::Buffer buffer(ros::Duration(10));
    tf2_ros::Buffer& tf_buff_(buffer);
    tf2_ros::TransformListener tf(buffer);
    ros::Duration(0.2).sleep();

    ros::ServiceClient plan_client = nh.serviceClient<nav_msgs::GetPlan>("fcpp_plan");

    geometry_msgs::TransformStamped start_trans = tf_buff_.lookupTransform("map", "base_link", ros::Time::now(), ros::Duration(3.0));
    geometry_msgs::PoseStamped start_pose;
    geometry_msgs::PoseStamped goal_pose;
    nav_msgs::GetPlan plan_;
    start_pose.header.frame_id = "map";
    start_pose.pose.position.x = start_trans.transform.translation.x;
    start_pose.pose.position.y = start_trans.transform.translation.y;
    start_pose.pose.position.z = start_trans.transform.translation.z;
    start_pose.pose.orientation.x = start_trans.transform.rotation.x;
    start_pose.pose.orientation.y = start_trans.transform.rotation.y;
    start_pose.pose.orientation.z = start_trans.transform.rotation.z;
    start_pose.pose.orientation.w = start_trans.transform.rotation.w;

    goal_pose.header.frame_id = "map";
    goal_pose.pose.position.x = 0.95702;
    goal_pose.pose.position.y = -0.5;
    goal_pose.pose.orientation.z = -0.0500582073002107;
    goal_pose.pose.orientation.w = 0.9987463020616842;
    // TODO: Make the goal configurable by .yaml

    plan_.request.start = start_pose;
    plan_.request.goal = goal_pose;
    plan_.request.tolerance = 1;

    plan_client.call(plan_);
}