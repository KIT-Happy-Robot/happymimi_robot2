#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include <string>

double vx =  0.0;
double vy =  0.0;
double vth = 0.0;
double odom_kv = 1.0;
double odom_kth = 1.0;

int receive_flag = 0;

void roverOdomCallback(const geometry_msgs::msg::Twist::ConstPtr& rover_odom){
  vx = odom_kv * rover_odom->linear.x;
  vth = odom_kth * rover_odom->angular.z;
  receive_flag = 1;
}

int main(int argc, char** argv){
  /* ros::init(argc, argv, "odometry_publisher"); */
  rclcpp::init(argc, argv);
  //std::shared_ptr<rclcpp::Node> node
  auto node = rclcpp::Node::make_shared("pub_odom2");
  auto odom_pub = node->create_publisher<nav_msgs::msg::Odometry>("odom",50);
  auto odom_sub = node->create_subscription<std_msgs::msg::String>("/rover_odo",roverOdomCallback);
  //tf2_ros::TransformBroadcaster odom_broadcaster;
  tf2_ros::TransformBroadcaster br(node); // !!!

  //get params !!!
  //rclcpp::param::param<double>("odom_kv", odom_kv, 1.0);
  //rclcpp::param::param<double>("odom_kth", odom_kth, 1.0);
  node->get_parameter("odom_kv", odom_kv, 1.0);
  node->get_parameter("odom_kth", odom_kth, 1.0)

  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  rclcpp::Time current_time, last_time;
  current_time = rclcpp::Time::now(); // !!!
  last_time = rclcpp::Time::now();

  rclcpp::Rate rate(20);
  while(rclcpp.ok()){

    rclcpp::spinOnce();               // check for incoming messages
    current_time = rclcpp::Time::now(); // !!!

    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::msg::Quaternion odom_quat = tf2_ros::createQuaternionMsgFromYaw(th);

    //check null quaternion
    if(odom_quat.x == 0.0 && odom_quat.y == 0.0 && odom_quat.z == 0.0 && odom_quat.w == 0.0){
      odom_quat.w = 1.0;
    }

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_footprint";
    /* odom_trans.child_frame_id = "base_link"; */

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_footprint";
    /* odom.child_frame_id = "base_link"; */
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub.publish(odom);


    last_time = current_time;
    rclcpp::spinOnce();
    r.sleep();

  }
}
