#include "full_coverage_path_planner/spiral_stc.h"
#include <tf2_ros/transform_listener.h>
#include <iostream>
#include <fstream>

// tf2_ros::Buffer& tf_fcpp_;
costmap_2d::Costmap2DROS* fcpp_costmap_ros_;
full_coverage_path_planner::SpiralSTC* fcpp_;
std::vector<geometry_msgs::PoseStamped> fcpp_plan;
std::ofstream path_file;


bool planSrv(nav_msgs::GetPlan::Request &plan_req, nav_msgs::GetPlan::Response &plan_res);


int main(int argc, char **argv)
{
    ros::init(argc, argv, "FCPP");
    ros::NodeHandle nh; // Private node handler

    tf2_ros::Buffer buffer(ros::Duration(10));
    tf2_ros::Buffer& tf_fcpp_(buffer);
    tf2_ros::TransformListener tf(buffer);

    fcpp_costmap_ros_ = new costmap_2d::Costmap2DROS("global_costmap", tf_fcpp_);
    fcpp_costmap_ros_->pause();
    fcpp_ = new full_coverage_path_planner::SpiralSTC();
    fcpp_->initialize("fcpp_planner", fcpp_costmap_ros_);

    ros::ServiceServer fcpp_srv_ = nh.advertiseService("fcpp_plan", planSrv);

    ros::spin(); 
}

bool planSrv(nav_msgs::GetPlan::Request &plan_req, nav_msgs::GetPlan::Response &plan_res) {
    if(!fcpp_->makePlan(plan_req.start, plan_req.goal, fcpp_plan))
        return false;
    
    path_file.open("fcpp_plan.csv"); // TODO: Make the directory configurable by .yaml
    for(geometry_msgs::PoseStamped point : fcpp_plan) {
        path_file << point.pose.position.x << "," << point.pose.position.y << "," << //
            point.pose.orientation.z << "," << point.pose.orientation.w << "\n" ;
    }
    path_file.close();
    
    return true; 
}
