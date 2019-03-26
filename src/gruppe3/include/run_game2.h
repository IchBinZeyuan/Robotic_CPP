#ifndef FIND_PFOSTEN_EIGEN_TEST_H
#define FIND_PFOSTEN_EIGEN_TEST_H

#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/LaserScan.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <Eigen/Dense>
#include <std_msgs/Float64MultiArray.h>
#include <stdio.h>
#include <cv_bridge/cv_bridge.h>  // OpenCV
#include <sensor_msgs/Image.h>
//#include <kobuki_msgs/BumperEvent.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <utility>
#include "lidar_main.h"
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include "gruppe3/signal_robot.h"
#include "gruppe3/signal_transfer.h"
#include <std_msgs/Int8.h>
class TurnandGo
{
public:
  float angle;
  float length;
  float x_coor;
  float y_coor;
  float goal_x;
  float goal_y;
  int color_code;
  int ball_iden;
  int ball_x;
  int which_side,which_func;
  int color_rows,bound_rows;
  int thres_color,thres_blue,thres_yellow,thres_green;
  int width_final,bound_x1;
  int pillars_found;
  int pillars_num;
  int ball_in_catch;
  int count_helper,count_0,count_1,center_ball,count_yellow,count_blue;
  int break_signal;
  uchar ball_catched,color_value;
  double center_point;
  bool depth_done;
  bool depth_filter_done;
  bool goal_color;
  bool goal_found;

  bool flag_1; //detectionstart from angelina
  bool flag_2; // gamestart from angelina
  bool flag_3; // stop from angelina
  float flag_a;
  float flag_b;
  int flag_color;

  cv::Mat rgb_image;
  cv::Mat depth_image;
  cv::Mat src;
  cv::Mat transition;
  cv::Mat color_depth;
  cv::Mat blue_dep;
  cv::Mat yellow_dep;
  cv::Mat depth_transition;
  cv::Mat blue_filtered_d;
  cv::Mat yellow_filtered_d;
  cv::Mat green_filtered_d;
  cv::Mat blue_depth_filtered;
  cv::Mat yellow_depth_filtered;

  Eigen::MatrixXi count_color;
  Eigen::MatrixXi bound;
  Eigen::MatrixXi width;
  Eigen::MatrixXi count_green;
  Eigen::MatrixXi bound_green;
  Eigen::MatrixXi width_green;
  Eigen::MatrixXi count_goal;
  Eigen::MatrixXi green_pillars;
  Eigen::MatrixXf pillars_height;
  Eigen::MatrixXf pillars_coord;

  void team_color();
  void identify_hockey();
  void catch_the_hockey();
  void specific_green_rgb();
  void all_green_rgb();
  void green_pillars_depth();
  void setAngle(float ang);
  void setLength(float len);
  void beginMove();
  void foolTurn(bool direction);
  void catchball();
  void hockey_goal();
  void identify_hockey_depth();
  void pureRotate(bool vel_switch);
  void calculate();
  void newPath();
  Eigen::VectorXd ladarData();
  TurnandGo();
  ros::NodeHandle n;
  ros::Publisher moveRobot_pub;
  ros::Publisher pub_signalrobot; //new pub
  ros::Subscriber sub_signaltranfer;// new sub
  ros::Subscriber laserRobot_sub;
  ros::Subscriber odom_sub;
  ros::Subscriber info_sub;
  ros::Subscriber rgb_sub;
  ros::Subscriber stop_sub;
private:

  boost::shared_ptr<sensor_msgs::Image const> depth_image_ptr;
  image_transport::ImageTransport it;
  image_transport::Subscriber depth_sub;
  void odomCallback(const nav_msgs::OdometryConstPtr& msg);
  void get_laser_callback(const sensor_msgs::LaserScan &laser);
  void infoCallback(const std_msgs::Float64MultiArray::ConstPtr& info);
  void rgb_Callback(const sensor_msgs::CompressedImageConstPtr& msg);
  void depth_Callback(const sensor_msgs::ImageConstPtr& msg);
  void sub_signaltransferCallback(const gruppe3::signal_transfer::ConstPtr& msg);//new subcallback
  void stop_callback(const std_msgs::Int8& msg);
};

int run_game2(playground pg1);

#endif
