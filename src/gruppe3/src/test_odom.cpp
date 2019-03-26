#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>

#include <math.h>

geometry_msgs::Pose2D current_pose;
//ros::Publisher pub_pose2d;

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

    current_pose.theta = yaw;
    //ROS_INFO("odom:[%f,%f]",current_pose.x,current_pose.y);
}

int main(int argc, char **argv)
{
    const double PI = 3.14159265358979323846;

    ROS_INFO("start");

    ros::init(argc, argv, "move_pub");
    ros::NodeHandle n;
    ros::Subscriber sub_odometry = n.subscribe("/odom",1, odomCallback);
    ros::Publisher moveRobot_pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",1); //for sensors the value after , should be higher to get a more accurate result (queued) //cmd_vel_mux/input/navi  mobile_base/commands/velocity /cmd_vel_mux/input/teleop
    //pub_pose2d = n.advertise<geometry_msgs::Pose2D>("pose", 1);
    ros::Rate rate(50); //the larger the value, the "smoother" , try value of 1 to see "jerk" movement
    //move forward
    ros::Time start = ros::Time::now();

    float cur;
    int count_odom = 0;

    float angle = PI/2;
    float length = 1.2;


    ros::Time beginTime = ros::Time::now();
    int count = 0;
    while(count<25)
    {
      geometry_msgs::Twist move;
      move.linear.x = 0; //speed value m/s
      move.angular.z = PI;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate.sleep();
      count++;
    }
    int ccount = 0;
    while(ccount<25)
    {
      // geometry_msgs::Twist move;
      // move.linear.x = 0; //speed value m/s
      // move.angular.z = 0;
      // moveRobot_pub.publish(move);
      ros::spinOnce();
      rate.sleep();
      ccount++;
    }
    int cccount = 0;
    while(cccount<5)
    {
      geometry_msgs::Twist move;
      move.linear.x = 0; //speed value m/s
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate.sleep();
      cccount++;
    }



    // ros::Time beginTime2 = ros::Time::now();
    // while(ros::Time::now() - beginTime2 < ros::Duration(2))
    // {
    //   geometry_msgs::Twist move;
    //   move.linear.x = 0.6; //speed value m/s
    //   move.angular.z = 0;
    //   moveRobot_pub.publish(move);
    //   ros::spinOnce();
    //   rate.sleep();
    // }

    // while(ros::ok())
    // {
    //   //ROS_INFO("current coordinate:[%f,%f]",current_pose.x,current_pose.y);
    //   ros::spinOnce();
    //   rate.sleep();
    // }





    while(count_odom < 20 && fabs(current_pose.theta) < 1e-4 && fabs(current_pose.x) < 1e-4 && fabs(current_pose.y) < 1e-4)
    {
      ros::Duration(0.1).sleep();
      count_odom++;
      ros::spinOnce();
    }
    cur = current_pose.theta;



    float now = cur ;
    float goal = cur + angle;

    while ( goal > PI){
      goal -= 2*PI;
    }
    while(goal < -PI){
      goal += 2*PI;
    }

    while (angle > PI)
    {
      angle -= 2*PI;
    }
    while(angle < -PI)
    {
      angle += 2*PI;
    }

    ROS_INFO("begin to turn an angle:%f",angle);


    float a_current;
    float diff_a_old;
    float diff_a = 0;
    const float k_a = 1.5;
    const float d_a = 0.3;

    while(fabs(now-goal)>0.05)
    {
      now = current_pose.theta;
      geometry_msgs::Twist move;

      a_current = now;
      diff_a_old = diff_a;
      diff_a = goal-a_current;
//////////////// Zweipunktregler ///////////////////
      float a_zwei = 0.8;
///////////////////////////////////////////////////



/////////////// P-Regler //////////////////////////
      float a_p = k_a*(diff_a);
///////////////////////////////////////////////////


/////////////// PD-Regler /////////////////////////////////////
      float a_pd = k_a*(diff_a) + d_a*(diff_a - diff_a_old)*10;
///////////////////////////////////////////////////////////////

      ROS_INFO("velocity kkkkkkkkk_a:%f",k_a*(diff_a));
      ROS_INFO("velocity ddddddddd_a:%f",d_a*(diff_a - diff_a_old)*10);
      ROS_INFO("velocity a_p:%f",a_p);

      if (angle>0)
      {
        move.linear.x = 0;
        move.angular.z = a_pd;
      }
      else
      {
        move.linear.x = 0;
        move.angular.z = -a_pd;
      }
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate.sleep();
    }

    float y_intl;
    float x_intl ;
    int count_odom_xy = 0;
    while(count_odom_xy < 20 && fabs(current_pose.theta) < 1e-4 && fabs(current_pose.x) < 1e-4 && fabs(current_pose.y) < 1e-4)
    {
      ros::Duration(0.1).sleep();
      count_odom_xy++;
      ros::spinOnce();
    }

    y_intl = current_pose.y;
    x_intl = current_pose.x;
    ROS_INFO("current coordinate:[%f,%f]",current_pose.x,current_pose.y);
    ROS_INFO("move straightforward for %f",length);

    float d_current;
    float diff_d_old;
    float diff_d = 0;
    const float k = 1.25;
    const float d = 0.2;

    while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < 0.95*fabs(length))
    {
      geometry_msgs::Twist move;

      d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
      diff_d_old = diff_d;
      diff_d = fabs(length)-fabs(d_current);

//////////////////// Zweipunktregler ////////////////
      float v_zwei = 0.5;
/////////////////////////////////////////////////////

/////////////////// P-Regler ////////////////////////
      float v_p = k*(diff_d);
/////////////////////////////////////////////////////

////////////////// PD-Regler ///////////////////////////////////////////////////
      float v_pd = k*(fabs(length)-fabs(d_current)) + d*(diff_d - diff_d_old)*10;
////////////////////////////////////////////////////////////////////////////////
      ROS_INFO("velocity kkkkkkkkk:%f",k*(fabs(length)-fabs(d_current)));
      ROS_INFO("velocity ddddddddd:%f",d*(diff_d - diff_d_old)*10);
      move.linear.x = v_pd;
      move.angular.z = 0;
      ROS_INFO("velocity:%f",v_pd);
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate.sleep();
    }
    return 0;
}
