#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
//#include <nav_msgs/Odometry.h>
#include <math.h>
#include <Eigen/Dense>
//#include "laser_main.h"
#include "cal_coordinate.h"
#include <tf/tf.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64MultiArray.h>
#include <stdio.h>
#include "cal_coordinate.h"
#include<std_msgs/Int8.h>
#include "gruppe3/signal_robot.h"
#include "gruppe3/signal_transfer.h"

using namespace std;
using namespace Eigen;

//float world_x,world_y;
float datalaser[360];
geometry_msgs::Pose2D current_pose;

int count_obstacle;
bool start_game_flag;
bool start_loc_flag;
bool halten_flag;

void odomCallback(const nav_msgs::OdometryConstPtr& msg)
{
    // linear position
    current_pose.x = msg->pose.pose.position.x;
    current_pose.y = msg->pose.pose.position.y;

    // quaternion to RPY conversion
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);

    // angular position
    current_pose.theta = yaw;
    //pub_pose2d.publish(current_pose);
    // ROS_INFO("Received odom info:[%f,%f,%f]",current_pose.x,current_pose.y,current_pose.theta);
}

MatrixXd cal_coordinate(VectorXd ranges, double angle_min, double angle_max)
{
    MatrixXd coord = MatrixXd::Zero(5*360, 4);
    MatrixXd coord_o;
    int ii = 0;
    double angle_increment = (angle_max - angle_min)/360;
    for (int i=0; i<5*360; i++){
        if(ranges(i) != 0){
            coord(ii,0) = ranges(i) * sin(angle_min + (i%360)*angle_increment);
            coord(ii,1) = ranges(i) * cos(angle_min + (i%360)*angle_increment);
            ii++;
        }
    }
    coord_o = coord.topRows(ii);
    return coord_o;
}

void sub_signaltransferCallback(const gruppe3::signal_transfer::ConstPtr& msg)
{
  start_loc_flag = msg->detectionstart;
  start_game_flag = msg->gamestart;
  halten_flag = msg->stop;
}


void get_laser_callback(const sensor_msgs::LaserScan &laser)
{
  int i = 0 ;
  for(int i = 0 ;i < 360;i++)
	{
    datalaser[i] = laser.ranges[i] ;
	}
  Eigen::VectorXd ladar_ranges = Eigen::VectorXd::Zero(360*10);
  //ros::Rate loop_rate(100);
  for(int ii = 0;ii < 2;ii++)
  {
      //for (int jj = 0; jj< 30; jj++){
          //ros::spinOnce();
          //rate.sleep();
      //}
    for (int jj=0; jj<360; jj++)
    {
      ros::spinOnce();
      if (isfinite(datalaser[jj]))
      {
        ladar_ranges(ii*360+jj) = datalaser[jj];
      }
      else
      {
        ladar_ranges(ii*360+jj) = 0;
      }
    }
  }
    double angle_min = -3.12413907051;
    double angle_max = 3.14159274101;
    MatrixXd coord_ladar;
    MatrixXd coord_bump=MatrixXd::Zero(1, 2);
    coord_ladar = cal_coordinate(ladar_ranges, angle_min, angle_max);
    count_obstacle = 0;
    int r = coord_ladar.rows();
    float goal_coord; // Y coordinate(lidar frame) of goal ball
    //ROS_INFO("test 1");
    int flag_1 = 0,flag_2 = 0,flag_3 = 0;
    for (int i = 0; i < r; ++i)
    {
      if (coord_ladar(i,0) < 0.20 && coord_ladar(i,0) > -0.20 && coord_ladar(i,1) > -0.55 && coord_ladar(i,1) < 0)
      {
        flag_1 += 1; // have obstacle ahead
        continue;
      }

      if (coord_ladar(i,0) < -0.20 && coord_ladar(i,0) > -0.65 && coord_ladar(i,1) > -0.55 && coord_ladar(i,1) < 0)
      {
        flag_2 += 1; // have obstacle ahead left
        continue;
      }

      if (coord_ladar(i,0) < 0.65 && coord_ladar(i,0) > 0.20 && coord_ladar(i,1) > -0.55 && coord_ladar(i,1) < 0)
      {
        flag_3 += 1; // have obstacle ahead right
        continue;
      }
    }

    ROS_INFO("flag_1,flag_2,flag_3:%d,%d,%d",flag_1,flag_2,flag_3);
    if (flag_1!=0)
    {
      if(flag_2 > flag_3 && flag_2 > flag_1)
      {
        count_obstacle = 2;
        ROS_INFO("Have obstacle ahead left");
      }
      else if(flag_3 > flag_2 && flag_3 > flag_1)
      {
        count_obstacle = 3;
        ROS_INFO("Have obstacle ahead right");
      }
      else if(flag_1 > flag_2 && flag_1 > flag_3)
      {
        count_obstacle = 1;
        ROS_INFO("Have obstacle ahead");
      }
    }
    else
    {
      ROS_INFO("Clear!");
      count_obstacle = 0;
    }
}
////////// get message of compensated odometry information and flag ///////////
// void outmsg_callback(const geometry_msgs::Pose2D &msg)
// {
//   double x = current_pose.x;
//   double y = current_pose.y; // information get from /odom
//   //process the message to get six parameters
//   double x_r;
//   double y_r;
//   double theta_r;
//   double angle_out;
//   double dx;
//   double dy;
//
//   double result_x, result_y;
//   double x1 = (x-x_r)*cos(theta_r) + (y-y_r)*sin(theta_r);
//   double y1 = -(x-x_r)*sin(angle) + (y-y_r)*cos(theta_r);
//
//   result_x = x1*cos(angle) + y1*sin(angle)+ dx ;
//   result_y = -x1*sin(angle) + y1*cos(angle)+ dy;
//
//
//   return result_x, result_y;
//
// }


int main(int argc,char **argv)
{
  ros::init(argc,argv,"stop");
  ros::NodeHandle n;
  ros::Subscriber laser_sub = n.subscribe("/lidarscan",800,get_laser_callback);
  ros::Subscriber signaltransfer_sub = n.subscribe("signal_transfertopic",1,sub_signaltransferCallback);
  //ros::Subscriber coordinate = n.subscribe("/outmsg",10,outmsg_callback);
  //ros::Publisher stop_now=n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/safety_controller",1);
  ros::Publisher stop_flag=n.advertise<std_msgs::Int8>("/stop_flag",1);

  ros::Rate rate(50);
  //bool angelina_stop = flase;
  //bool loc_state = false; // if current is 90s' localization state
  //bool anti_crash_state = false; // if the robot haven't reached in our side, it's false
  while(ros::ok())
  {
    ros::spinOnce();

    if(start_loc_flag == true && start_game_flag == false)
    {
      while (halten_flag == true)
      {
        ros::spinOnce();
        std_msgs::Int8 s_flag;
        //ROS_INFO("stop!");
        s_flag.data = 4;
        stop_flag.publish(s_flag);
        rate.sleep();
      }
      while(halten_flag == false && start_game_flag == false)
      {
        ros::spinOnce();
        std_msgs::Int8 s_flag;
        //ROS_INFO("stop!");
        s_flag.data = 0;
        stop_flag.publish(s_flag);
        rate.sleep();
      }
      if (start_game_flag == true)
      {
        continue;
      }
    }
    if(start_game_flag == true)
    {
      while(halten_flag == false)
      {
        ros::spinOnce();
        std_msgs::Int8 s_flag;
        s_flag.data = count_obstacle;
        stop_flag.publish(s_flag);
        rate.sleep();
      }
      while (halten_flag == true)
      {
        ros::spinOnce();
        std_msgs::Int8 s_flag;
        s_flag.data = 4;
        stop_flag.publish(s_flag);
        rate.sleep();
      }
    }
    // if (halten_flag ==true && start_flag == false)
    // {
    //   std_msgs::Int8 s_flag;
    //   //ROS_INFO("stop!");
    //   s_flag.data = ;
    //   stop_flag.publish(s_flag);
    //   rate.sleep();
    // }
  //  float a,b; // width and height of the playground
  }
  return 0;
}
