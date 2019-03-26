#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <Eigen/Dense>
#include "laser_main.h"

using namespace std;
geometry_msgs::Pose2D current_pose;
float datalaser[360] = {0} ;
const double PI = 3.14159265358979323846;

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

void get_laser_callback(const sensor_msgs::LaserScan &laser)
{
int i = 0 ;
for(int i = 0 ;i < 360;i++)
	{
	datalaser[i] = laser.ranges[i] ;
	}
}


int main (int argc, char **argv)
{
    ros::init(argc,argv,"synthesis");
    ros::NodeHandle n;
    ros::Subscriber laser_sub = n.subscribe("/lidarscan",1000,get_laser_callback);
    ros::Subscriber sub_odometry = n.subscribe("odom",1, odomCallback);
    ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",10);
    ros::Rate rate(10);

/////////////////////////////////////////////////////////////////////////////////////////////////////

    float angle_1 = 0; // Angle between robot direction and the horizontal line of the field
    float dis_1   = 0; // Distance between robot location and the middle of the horizontal line
    float dis_2   = 0; // Distance between robot location and the blue line

////////////////////////////////////////////////////////////////////////////////////////////////////

    Eigen::VectorXd ranges = Eigen::VectorXd::Zero(360*10);

    int ii = 0;
    ros::Rate loop_rate_l(100);
    while(ros::ok()&& ii < 10){
        ros::spinOnce();
        loop_rate_l.sleep();
        ii++;
    }
    ii = 0;
    while(ros::ok()&& ii < 10){
        for (int jj = 0; jj< 30; jj++){
            ros::spinOnce();
            loop_rate_l.sleep();
        }

        for (int jj=0; jj<360; jj++){
            if (isfinite(datalaser[jj])){
                ranges(ii*360+jj) = datalaser[jj];
            }
            else{
                ranges(ii*360+jj) = 0;
            }
        }
        ii++;
    }

    //////////////////////////// Give values to angle and distance////////////////////////////////////////////
    playground res1 = laser_main(ranges);
    angle_1 = res1.angle_turn1;
    dis_1 = res1.d1;
    dis_2 = res1.d2;

    ROS_INFO("angle_1:%f",angle_1);
    ROS_INFO("dis_1:%f",dis_1);
    ROS_INFO("dis_2:%f",dis_2);

    while(ros::ok()){
        ros::Rate loop_rate(500);

        /////////////////////////////////////////////////// Angle_1 ////////////////////////////////////////////////
        ROS_INFO("turn to the middle of the playground");
        float cur_1=current_pose.theta;
        float now_1 = cur_1 ;
        float goal = cur_1 + angle_1;
        while ( goal > 3.1416){
            goal -= 2*3.1416;
        }
        while(goal < -3.1416){
            goal += 2*3.1416;
        }
        ROS_INFO("Initial angle:%f", cur_1);
        ROS_INFO("Goal angle final:%f", goal);

        // turn command
        while(fabs(now_1-goal)>0.01){
            now_1 = current_pose.theta;
	          geometry_msgs::Twist move;
            if (angle_1>0){
                move.linear.x = 0; //speed value m/s
                move.angular.z = 0.4;
            }
            else{
                move.linear.x = 0; //speed value m/s
                move.angular.z = -0.4;
            }

            movement_pub.publish(move);
            ros::spinOnce();
            loop_rate.sleep();
        }
        ROS_INFO("finished turning");

        /////////////////////////////////////////////////// Dis_1 ////////////////////////////////////////////////
        float y_intl;
        float x_intl ;
        for(int countt = 0;countt<2;countt++){
            ros::spinOnce();
            ROS_INFO("current x:%f",current_pose.x);
	          ROS_INFO("current y:%f",current_pose.y);
	          y_intl = current_pose.y;
	          x_intl = current_pose.x;
	          ros::Duration(1).sleep();
        }
        ROS_INFO("move to the middle");

        while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < dis_1){
            geometry_msgs::Twist move;
            move.linear.x = 0.2;
            move.angular.z = 0;
            movement_pub.publish(move);

            ros::spinOnce();
            loop_rate.sleep();
        }

        //////////////////////////////////////////////turn right/////////////////////////////////////////////////
        ROS_INFO("turn backwards");
        ROS_INFO("current theta:%f",current_pose.theta);
        float cur_2 = current_pose.theta;
        float now_2 = cur_2;
        float goal2 = cur_2 + res1.angle_turn2;
        while ( goal2 > 3.1416){
            goal2 -= 2*3.1416;
        }
        while(goal2 < -3.1416){
            goal2 += 2*3.1416;
        }
        ROS_INFO("cur_2:%f",cur_2);
        ROS_INFO("angle difference:%f",res1.angle_turn2);
        ROS_INFO("goal2:%f",goal2);

        while(fabs(now_2-goal2)>0.01){
            now_2 = current_pose.theta;
            // ROS_INFO("now_2:%f",now_2);

            geometry_msgs::Twist move;
            if (res1.angle_turn2>0){
                move.linear.x = 0; //speed value m/s
                move.angular.z = 0.2;
            }
            else{
                move.linear.x = 0; //speed value m/s
                move.angular.z = -0.2;
            }

            movement_pub.publish(move);
            ros::spinOnce();
            loop_rate.sleep();
        }

        //////////////////////////////////////////////////Dis_2//////////////////////////////////////////
        for(int countx =0;countx<2;countx++){
	          ros::spinOnce();
	          ROS_INFO("current x:%f",current_pose.x);
	          x_intl = current_pose.x;
	          y_intl = current_pose.y;
	          ros::Duration(1).sleep();
        }
        ROS_INFO("Move backward");
        while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(dis_2)){
            geometry_msgs::Twist move;
            if( dis_2 < 0){
                move.linear.x = -0.2;
                move.angular.z = 0;
            }
            else{
                move.linear.x = 0.2;
                move.angular.z = 0;
            }
            movement_pub.publish(move);

            ros::spinOnce();
            loop_rate.sleep();
        }
        // just stop
        ROS_INFO("stop");
        while(ros::ok()) {
            geometry_msgs::Twist move;
            move.linear.x = 0;
            move.angular.z = 0;
            movement_pub.publish(move);
            ros::spinOnce();
            loop_rate.sleep();
        }
        ros::spinOnce();
	      rate.sleep();
    }
    return 0;
}
