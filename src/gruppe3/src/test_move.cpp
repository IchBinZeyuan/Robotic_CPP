#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc,char **argv)
{
ros::init(argc,argv,"move_turtle");
ros::NodeHandle node;
ros::Publisher pub = node.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",10); //"mobile_base/commands/velocity" "cmd_vel_mux/input/navi"
geometry_msgs::Twist msg;

const double pi = 0.5 * 3.1415926 ;
const double speed = 0.2 ;
const double dur = 2 ;
msg.linear.x = 0;
msg.angular.z = pi;
ROS_INFO("start");
//ros::Rate rate(10);
//int i = 0;
ros::Time beginTime1 = ros::Time::now();
ros::Rate rate(50);
while(ros::Time::now() - beginTime1 < ros::Duration(dur)){
pub.publish(msg);
ros::spinOnce();
rate.sleep();
//i++;
//ros::Duration(0.1).sleep();
}
return 0;
}
