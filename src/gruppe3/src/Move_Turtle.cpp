#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc,char **argv)
{
ros::init(argc,argv,"move_turtle");
ros::NodeHandle node;
ros::Publisher pub = node.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",10); //"mobile_base/commands/velocity" "cmd_vel_mux/input/navi"
geometry_msgs::Twist msg;

const double pi = 3.1415926 ;
double dur = 2.0 ;
const double speed = 0.2 ;

ROS_INFO("start");
ros::Rate rate(10) ;
ros::Time beginTime1 = ros::Time::now();
while(ros::Time::now() - beginTime1 < ros::Duration(dur)){
msg.linear.x = 0;
msg.angular.z = 0.333 * pi;
pub.publish(msg);
ros::spinOnce();
rate.sleep();
//ros::Duration(0.1).sleep();
}

ros::Time beginTime2 = ros::Time::now();
while(ros::Time::now() - beginTime2 < ros::Duration(dur)){
msg.linear.x = speed;
msg.angular.z = 0;
pub.publish(msg);
ros::spinOnce();
rate.sleep();
}

ros::Time beginTime3 = ros::Time::now();
while(ros::Time::now() - beginTime3 < ros::Duration(dur)){
msg.linear.x = 0;
msg.angular.z = -0.5*pi;
pub.publish(msg);
ros::spinOnce();
rate.sleep();
}

ros::Time beginTime4 = ros::Time::now();
while(ros::Time::now() - beginTime4 < ros::Duration(dur)){
msg.linear.x = speed;
msg.angular.z = 0;
pub.publish(msg);
ros::spinOnce();
rate.sleep();
}
//ros::Duration(0.1).sleep();
return 0;
}
