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

    ros::spin();
    return(0);
}