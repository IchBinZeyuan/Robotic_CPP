#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/LaserScan.h>
using namespace std;
double datalaser[360] = {0} ;
//void AutoExp::processLaserScan(const sensor_msgs::LaserScan::ConstPtr& scan){
//ROS_INFO("laser messages:",scan->ranges[]);
//}

//int main(int argc,char** argv)
//{
//ros::init(argc,argv,"ladar");
//ros::NodeHandle nh;
//ros::Subscriber sub = nh.subscribe<sensor_msgs/LaserScan>("/scan",10,&AutoExp::processLaserScan,this);
//ros::spin();
//return 0;
//}

void get_laser_callback(const sensor_msgs::LaserScan &laser){
	//count << "ROS Ladar Data"<<endl;
	//count << "Front:"<<laser.ranges[719] << endl;
	//count << "----------------------"<< endl;
//double datalaser[360] = {0} ;
int i = 0 ;
while ( i<360){
datalaser[i] = laser.ranges[i] ;
i++;
}
	//ROS_INFO_STREAM("Front:"<<datalaser[2]);
}

int main (int argc, char **argv)
{
ros::init(argc,argv,"laser");
ros::NodeHandle n ;
ros::Subscriber laser_sub = n.subscribe("/lidarscan",1000,get_laser_callback);
	//ROS_INFO_STREAM("Front:"<<datalaser[2]);
ros::Rate rate(10);
int i = 0;
while(ros::ok()){
ROS_INFO_STREAM("Front:"<<datalaser[200]);

	ros::spinOnce();
rate.sleep();
i++;
}

return 0;
}
