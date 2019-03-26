#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>

#include <math.h>

geometry_msgs::Pose2D current_pose;
ros::Publisher pub_pose2d;

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
   ROS_INFO("Received odom info:[%f,%f,%f,%f]",odom->twist.twist.linear.x,odom->pose.pose.position.x,odom->pose.pose.position.y);
 current_pose.x = odom->pose.pose.position.x;
     current_pose.y = odom->pose.pose.position.y;
     //current_pose.z = odom->pose.pose.position.z;
}

int main(int argc, char **argv)
{
    const double PI = 3.14159265358979323846;

    ROS_INFO("start");

    ros::init(argc, argv, "move_pub");
    ros::NodeHandle n;
    ros::Subscriber sub_odometry = n.subscribe("odom", 5, odomCallback);
    ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",5); //for sensors the value after , should be higher to get a more accurate result (queued)

    double x_epos = 1;
    ros::Rate rate(10); //the larger the value, the "smoother" , try value of 1 to see "jerk" movement

    //move forward
    //ROS_INFO("start location:%f",start_loc);
    ros::Time start = ros::Time::now();
    while(current_pose.x != x_epos && ros::ok())

    {
        geometry_msgs::Twist move;

	if (current_pose.x<x_epos)
	{
	move.linear.x = 0.1 ;
	move.angular.z = 0 ;
movement_pub.publish(move);
	}
	else
{move.linear.x = -0.1 ;
	move.angular.z = 0 ;
movement_pub.publish(move);}
        //velocity controls
       // movement_pub.publish(move);
	ros::spinOnce();
        rate.sleep();
	}
	return 0 ;
    }
