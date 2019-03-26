#include <iostream>
#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
using namespace std;
double data[360] = {0} ;
double angle_min, angle_max, angle_increment;

void get_laser_callback(const sensor_msgs::LaserScan &laser){
    int i = 0 ;
    angle_min = laser.angle_min;
    angle_max = laser.angle_max;
    angle_increment = laser.angle_increment;

    while ( i<360){
        data[i] = laser.ranges[i] ;
        i++;
    }

}

int load_lidar (int argc, char **argv)
{
    double datalaser[5][360]={0};
    ros::init(argc,argv,"laser");
    ros::NodeHandle n ;
    ros::Subscriber laser_sub = n.subscribe("/lidarscan",1000,get_laser_callback);
    ros::Rate rate[10];

    int i=0;
    while (i<5 && ros::ok()){
        ros::spinOnce();
        for(int j=0; j<360; j++){
            datalaser[i][j] = data[j];
        }
        rate.sleep();
        i++;


    }

    return 0;
}
