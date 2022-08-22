#include "full_coverage_path_planner/spiral_stc.h"
#include <tf2_ros/transform_listener.h>

// tf2_ros::Buffer& tf_fcpp_;
costmap_2d::Costmap2DROS* fcpp_costmap_ros_;
full_coverage_path_planner::SpiralSTC* fcpp_;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "FCPP");

    tf2_ros::Buffer buffer(ros::Duration(10));
    tf2_ros::Buffer& tf_fcpp_(buffer);
    tf2_ros::TransformListener tf(buffer);
    fcpp_costmap_ros_ = new costmap_2d::Costmap2DROS("global_costmap", tf_fcpp_);
    fcpp_costmap_ros_->pause();
    fcpp_ = new full_coverage_path_planner::SpiralSTC();
    fcpp_->initialize("fcpp_planner", fcpp_costmap_ros_);

    // TODO: add service client and master 

    // 23/08/2022
    ros::Rate fcpp_rate(1.0);

    std::vector<geometry_msgs::PoseStamped> fcpp_plan;
    
    while (ros::ok()) {
        ros::spinOnce();

        geometry_msgs::TransformStamped start_trans = tf_fcpp_.lookupTransform("base_link", "map", ros::Time(0));
        geometry_msgs::PoseStamped start_pose;
        geometry_msgs::PoseStamped goal_pose;
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
        goal_pose.pose.position.y = -2.1984;
        goal_pose.pose.orientation.z = -0.0500582073002107;
        goal_pose.pose.orientation.w = 0.9987463020616842;

        fcpp_->makePlan(start_pose, goal_pose, fcpp_plan);

        fcpp_rate.sleep();
    }

    // ros::spin(); 
    // 23/08/2022
}