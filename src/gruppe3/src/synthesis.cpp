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
#include <stdio.h>
#include <cv_bridge/cv_bridge.h>  // OpenCV
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "predict2.h"
#include "cal_coordinate.h"
#include "clear_average.h"
#include "find_poles.h"
#include "gnuplot-iostream.h"
#include "trans_coordinate.h"
#include "find_path.h"
#include <vector>
#include <utility>

using namespace cv;
using namespace std;
geometry_msgs::Pose2D current_pose;
double datalaser[360] = {0} ;
const double PI = 3.14159265358979323846;
struct color{
    Mat  c,d;  };

Mat rgb_image;

color bluecolor(vector<Mat> mv, Mat src)
{
  Mat  c = Mat::zeros(src.size(),CV_8UC3);
  Mat  d(src.size(),CV_8U,Scalar(0));
  Mat  tmpH1(src.size(),CV_8U,Scalar(0));
  Mat  tmpH2(src.size(),CV_8U,Scalar(0));
  Mat  tmpH3(src.size(),CV_8U,Scalar(0));
  inRange(mv[0],Scalar(100,0.0,0,0),Scalar(130.0,0.0,0,0),tmpH1);
  inRange(mv[1],Scalar(43.0,0.0,0,0),Scalar(255.0,0.0,0,0),tmpH2);
  inRange(mv[2],Scalar(46.0,0.0,0,0),Scalar(255.0,0.0,0,0),tmpH3);
  bitwise_and(tmpH3,tmpH2,tmpH2);
  bitwise_and(tmpH1,tmpH2,tmpH1);
  blur(tmpH1,tmpH1,Size(3,3)); // 使用3*3内核来降噪

  Mat dsc;
  dsc = tmpH1.clone(); //tmpH1=0.25*tmpH1;
  //imshow("blue_dsc", tmpH1);
  d = tmpH1*0.2;//蓝色对应值：51.0；
  Mat  b = Mat::zeros(src.size(),CV_8UC3);
  MatIterator_<uchar> blueit,blueend;
  MatIterator_<Vec3b> blueit1,blueend1;
  for(blueit = dsc.begin<uchar>(),blueend=dsc.end<uchar>(),blueit1 = b.begin<Vec3b>(),blueend1 = b.end<Vec3b>(); blueit != blueend; ++blueit,++blueit1)
  {
  if (*blueit == 255)
  {   (*blueit1)[0] = 255;}}
  color e = {b,d};
  //imshow("b",b);
  //imwrite("/home/haoming/catkin_ws/c1.png",c);
  //namedWindow("blue_dsc",  WINDOW_AUTOSIZE);
  //waitKey(0);
  return e;
}
color yellowcolor(vector<Mat> mv,Mat src)
{
  Mat  d(src.size(),CV_8U,Scalar(0));
  Mat  tmpH1(src.size(),CV_8U,Scalar(0));
  Mat  tmpH2(src.size(),CV_8U,Scalar(0));
  Mat  tmpH3(src.size(),CV_8U,Scalar(0));
  inRange(mv[0],Scalar(20.0,0.0,0,0),Scalar(34,0.0,0,0),tmpH1);
  inRange(mv[1],Scalar(43.0,0.0,0,0),Scalar(255.0,0.0,0,0),tmpH2);
  inRange(mv[2],Scalar(46.0,0.0,0,0),Scalar(255.0,0.0,0,0),tmpH3);
  bitwise_and(tmpH3,tmpH2,tmpH2);
  bitwise_and(tmpH1,tmpH2,tmpH1);
  blur(tmpH1,tmpH1,Size(3,3)); // 使用3*3内核来降噪
  Mat dsc;
  dsc = tmpH1.clone();
  d = (tmpH1)*(0.6);//黄色对应值：153.0

  Mat y = Mat::zeros(src.size(),CV_8UC3);
  MatIterator_<uchar> yellowit,yellowend;
  MatIterator_<Vec3b> yellowit1,yellowend1;
  for(yellowit = dsc.begin<uchar>(),yellowend=dsc.end<uchar>(),yellowit1 = y.begin<Vec3b>(),yellowend1 = y.end<Vec3b>(); yellowit != yellowend; ++yellowit,++yellowit1)
  {
  if (*yellowit == 255)
  {   (*yellowit1)[1] = 255;(*yellowit1)[2]=255;}}
  color e = {y,d};
  //waitKey(0);
  return e;
}

// rgb_Callback
void rgb_Callback(const sensor_msgs::ImageConstPtr& msg){
  cv_bridge::CvImagePtr cv_ptr;
  try{
      cv_ptr = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
  }
  catch(cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge error: %s", e.what());
      return;
  }
  cv_ptr->image.copyTo(rgb_image);

  // namedWindow
  namedWindow("RGB Image Window");
  imshow("RGB Image Window",rgb_image);
  imwrite("/home/ge69toc/rgb.png",rgb_image);
  waitKey(5);

  Mat src = rgb_image;
  Mat  hsv(src.size(),CV_8U,Scalar(0));
  blur(src,src,Size(3,3)); //先使用3*3内核来降噪
  cvtColor(src, hsv, CV_BGR2HSV );//RGB to HSV

  vector<Mat> mv;
  split(hsv,mv);
  color blue,yellow;
  blue = bluecolor( mv,  src);
  yellow = yellowcolor( mv, src);
  // imwrite("/home/ge69toc/bd.png",blue.d);
  // imwrite("/home/ge69toc/yd.png",yellow.d);
  // blue.c=blue.c+black.c+yellow.c+green.c;
  // blue.d=blue.d+black.d+yellow.d+green.d;

  imwrite("/home/ge69toc/blue_c.png",blue.c);
  imwrite("/home/ge69toc/blue_d.png",blue.d);
  imwrite("/home/ge69toc/c.png",yellow.c);
  imwrite("/home/ge69toc/d.png",yellow.d);

  Mat blue_iden = blue.d;
  Mat yellow_iden = yellow.d;
  //ROS_INFO("rows: %i",blue_iden.rows);
  //ROS_INFO("cols: %i",blue_iden.cols);

  int count_yellow = 0;
  int count_blue = 0;
  for (int i = 0; i < blue_iden.rows; i++) {
    for (int j = 0; j < blue_iden.cols; j++) {
      if (yellow_iden.at<uchar>(i,j) == 153.0){
        count_yellow++;
        //ROS_INFO("yellow counting");
      }
      else if(blue_iden.at<uchar>(i,j) == 51.0){
        count_blue++;
        //ROS_INFO("blue counting");
      }
    }
  }

  if (count_blue < count_yellow){
    ROS_INFO("The color of our team is yellow.");
  }
  else {
    ROS_INFO("The color of our team is blue.");
  }
}


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
    for(int i = 0 ;i < 360;i++){
	      datalaser[i] = laser.ranges[i] ;
	  }
}


int main (int argc, char **argv)
{
    int i, j, ii, jj;
    Gnuplot gp1, gp2, gp3;
    vector<boost::tuple<double, double> > pts_1, pts_2, pts_3;

    ros::init(argc,argv,"synthesis");
    ros::NodeHandle n;
    ros::Subscriber laser_sub = n.subscribe("/lidarscan",1000,get_laser_callback);
    ros::Subscriber sub_odometry = n.subscribe("odom",1, odomCallback);
    ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",10);
    ros::Rate rate(10);

    // Initialization-----------------------------------------------------------
    playground res1, res2, res3;
    double y_intl, x_intl ;
    bool success  = 0;
    double angular_speed = 0.2;
    double linear_speed  = 0.3;
    int times_of_lidar = 20;
    double init_angle, curr_angle, diff_angle, goal_angle;
    Eigen::VectorXd ranges;
    ros::Rate loop_rate_lidar(100);
    ros::Rate loop_rate(100);
    int trial = 0;

    // 1st Lidar Calculation----------------------------------------------------
    /*
    trial = 0;
    while (success == 0 && ros::ok()){
        ranges = Eigen::VectorXd::Zero(360*times_of_lidar);


        for (ii=0; ii<times_of_lidar; ii++){
            for (jj=0; jj< 30; jj++){
                loop_rate_lidar.sleep();
            }
            for (jj=0; jj<360; jj++){
                ros::spinOnce();
                if (isfinite(datalaser[jj])){
                    ranges(ii*360+jj) = datalaser[jj];
                }
                else{
                    ranges(ii*360+jj) = 0;
                }
            }
        }

        res1 = laser_main(ranges, 0);
        cout<<"======TRIAL======:"<<trial++<<endl;
        success = res1.success;
        return 0;
    }
    // if(success){
    // while(ros::ok()) {

    //1st TURN--------------------------------------------------------------
    ROS_INFO("1st TURN==== turn to the middle of the playground");
    init_angle = current_pose.theta;
    curr_angle = init_angle ;
    goal_angle = init_angle + res1.angle_turn;
    while (goal_angle > PI){
        goal_angle -= 2*PI;
    }
    while(goal_angle < -PI){
        goal_angle += 2*PI;
    }

    ROS_INFO("1st TURN==== Initial angle:%f", init_angle);
    ROS_INFO("1st TURN==== Goal angle final:%f", goal_angle);

    while(fabs(curr_angle-goal_angle) > 0.01 && ros::ok()){
        curr_angle = current_pose.theta;
        diff_angle = goal_angle - curr_angle;
        while (diff_angle > PI){
            diff_angle -= 2*PI;
        }
        while(diff_angle < -PI){
            diff_angle += 2*PI;
        }
        // ROS_INFO("1st TURN==== Difference angle:%f", diff_angle);

        geometry_msgs::Twist move;
        if (diff_angle > 0){
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

    ROS_INFO("1st TURN==== Finished Turning in Angle:%f", curr_angle);

    //1st MOVE--------------------------------------------------------------

    for(ii = 0; ii < 2; ii++){
        ros::spinOnce();
        ROS_INFO("current x:%f",current_pose.x);
        ROS_INFO("current y:%f",current_pose.y);
        y_intl = current_pose.y;
        x_intl = current_pose.x;
        ros::Duration(1).sleep();
    }
    ROS_INFO("move to the middle");

    while(ros::ok() && sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(res1.d1)){
        geometry_msgs::Twist move;
        move.linear.x = linear_speed;
        move.angular.z = 0;
        movement_pub.publish(move);

        ros::spinOnce();
        loop_rate.sleep();
    }

    // 2nd Lidar Calculation------------------------------------------------
    ii = 0;
    while(ros::ok() && ii<20) {
        geometry_msgs::Twist move;
        move.linear.x = 0;
        move.angular.z = 0;
        movement_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
        ii++;
    }
    trial = 0;
    success = 0;
    while (success == 0 && ros::ok()){
        ranges = Eigen::VectorXd::Zero(360*times_of_lidar);
        for (ii=0; ii<times_of_lidar; ii++){
            for (jj=0; jj< 30; jj++){
                ros::spinOnce();
                loop_rate.sleep();
            }

            for (jj=0; jj<360; jj++){
                if (isfinite(datalaser[jj])){
                    ranges(ii*360+jj) = datalaser[jj];
                }
                else{
                    ranges(ii*360+jj) = 0;
                }
            }
        }

        res2 = laser_main(ranges, 1);
        cout<<"======TRIAL======:"<<trial++<<endl;
        success = res2.success;
        cout<<"======SUCCESS======:"<<success<<endl;
    }
    // if(success){
    // 2nd TURN-------------------------------------------------------------
    ROS_INFO("2nd TURN==== turn to the color block of our side");
    init_angle = current_pose.theta;
    curr_angle = init_angle ;
    goal_angle = init_angle + res2.angle + PI;
    while (goal_angle > PI){
        goal_angle -= 2*PI;
    }
    while(goal_angle < -PI){
        goal_angle += 2*PI;
    }

    ROS_INFO("2nd TURN==== Initial angle:%f", init_angle);
    ROS_INFO("2nd TURN==== Goal angle final:%f", goal_angle);

    while(fabs(curr_angle-goal_angle) > 0.01 && ros::ok()){
        curr_angle = current_pose.theta;
        diff_angle = goal_angle - curr_angle;
        while (diff_angle > PI){
            diff_angle -= 2*PI;
        }
        while(diff_angle < -PI){
            diff_angle += 2*PI;
        }

        geometry_msgs::Twist move;
        if (diff_angle > 0){
            move.linear.x = 0; //speed value m/s
            move.angular.z = angular_speed;
        }
        else{
            move.linear.x = 0; //speed value m/s
            move.angular.z = -angular_speed;
        }
        movement_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
    }

    ROS_INFO("2nd TURN==== Finished Turning in Angle:%f", curr_angle);

    //2nd MOVE--------------------------------------------------------------
    for(ii = 0; ii < 2; ii++){
        ros::spinOnce();
        ROS_INFO("current x:%f",current_pose.x);
        x_intl = current_pose.x;
        y_intl = current_pose.y;
        ros::Duration(1).sleep();
    }
    ROS_INFO("Move backward");
    while(ros::ok() && sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(res2.d2)){
        geometry_msgs::Twist move;
        if( res2.d2 < 0){
            move.linear.x = -linear_speed;
            move.angular.z = 0;
        }
        else{
            move.linear.x = linear_speed;
            move.angular.z = 0;
        }
        movement_pub.publish(move);

        ros::spinOnce();
        loop_rate.sleep();
    }

    // just stop
    ROS_INFO("stop");
    ii = 0;
    while(ros::ok() && ii<5) {
        geometry_msgs::Twist move;
        move.linear.x = 0;
        move.angular.z = 0;
        movement_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
        ii++;
    }
    // ROS_INFO("start color");
    // ///////////////color detection
    // image_transport::ImageTransport it_(n);
    // image_transport::Subscriber rgb_sub_ = it_.subscribe("/camera/rgb/image_raw", 1 ,&rgb_Callback);
    // //ros::Rate loop_rate(10);
    // ROS_INFO("end color");

    ii = 0;
    while (ros::ok() && ii<500) {

       ros::spinOnce();
       loop_rate.sleep();
       ii++;
    }
*/

    // 3rd Lidar Calculation

    ii = 0;
    while(ros::ok() && ii<20) {
        geometry_msgs::Twist move;
        move.linear.x = 0;
        move.angular.z = 0;
        movement_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
        ii++;
    }
    trial = 0;
    success = 0;
    // while (success == 0 && ros::ok()){
        ranges = Eigen::VectorXd::Zero(360*times_of_lidar);
        for (ii=0; ii<times_of_lidar; ii++){
            for (jj=0; jj< 30; jj++){
                ros::spinOnce();
                loop_rate.sleep();
            }

            for (jj=0; jj<360; jj++){
                if (isfinite(datalaser[jj])){
                    ranges(ii*360+jj) = datalaser[jj];
                }
                else{
                    ranges(ii*360+jj) = 0;
                }
            }
        }

        res3 = laser_main(ranges, 1);
        cout<<"======TRIAL======:"<<trial++<<endl;
        success = res3.success;
        cout<<"======SUCCESS======:"<<success<<endl;
    // }
    if (success){
    // turn 30 degree
    ROS_INFO("2nd TURN==== turn to the color block of our side");
    init_angle = current_pose.theta;
    curr_angle = init_angle ;
    goal_angle = init_angle + res3.angle_turn;

    while (goal_angle > PI){
        goal_angle -= 2*PI;
    }
    while(goal_angle < -PI){
        goal_angle += 2*PI;
    }

    ROS_INFO("2nd TURN==== Initial angle:%f", init_angle/3.1416*180);
    ROS_INFO("2nd TURN==== Turn angle   :%f", res3.angle_turn/3.1416*180);
    ROS_INFO("2nd TURN==== Goal angle   :%f", goal_angle/3.1416*180);

    while(fabs(curr_angle-goal_angle) > 0.01 && ros::ok()){
        curr_angle = current_pose.theta;
        diff_angle = goal_angle - curr_angle;
        while (diff_angle > PI){
            diff_angle -= 2*PI;
        }
        while(diff_angle < -PI){
            diff_angle += 2*PI;
        }

        geometry_msgs::Twist move;
        move.linear.x = 0; //speed value m/s
        if (diff_angle > 0){
            move.angular.z = 0.2;
        }
        else{
            move.angular.z = -0.2;
        }

        movement_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
    }

    ROS_INFO("2nd TURN==== Finished Turning in Angle:%f", curr_angle/3.1416*180);

    //go forward
    for(ii = 0; ii < 2; ii++){
        ros::spinOnce();
        ROS_INFO("current x:%f",current_pose.x);
        x_intl = current_pose.x;
        y_intl = current_pose.y;
        ros::Duration(1).sleep();
    }
    ROS_INFO("Move forward");
    while(ros::ok() && sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < res3.d1){
        geometry_msgs::Twist move;
        move.linear.x = linear_speed;
        move.angular.z = 0;
        movement_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
    }
    //get lidar points
    ROS_INFO("Get Lidar Points");
    ii = 0;
    while(ros::ok() && ii<20) {
        geometry_msgs::Twist move;
        move.linear.x = 0;
        move.angular.z = 0;
        movement_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
        ii++;
    }
    trial = 0;
    success = 0;
    ranges = Eigen::VectorXd::Zero(360*20);
    for (ii=0; ii<20; ii++){
        for (jj=0; jj< 30; jj++){
            ros::spinOnce();
            loop_rate.sleep();
        }

        for (jj=0; jj<360; jj++){
            if (isfinite(datalaser[jj])){
                ranges(ii*360+jj) = datalaser[jj];
            }
            else{
                ranges(ii*360+jj) = 0;
            }
        }
    }


    ROS_INFO("Predict new lidar points");
    //predict
    double angle_min = -3.12413907051;
    double angle_max = 3.14159274101;
    Eigen::MatrixXd lidar_points_clear = cal_coordinate(ranges, 1);
    cout<< "cleared lidar points = "<<lidar_points_clear.rows()<<endl;
    playground prediction = predict2(res3.coord_1, res3.coord_2, res3.angle_turn, res3.d1, 0.5, lidar_points_clear, 1.2, 3);

    for (i=0; i<lidar_points_clear.rows(); i++) {
        pts_1.push_back(boost::make_tuple(
                lidar_points_clear(i, 0),
                lidar_points_clear(i, 1)));
    }
    gp1 << "plot '-' with points title 'raw lidar points'\n";
    gp1.send1d(pts_1);
    ROS_INFO("DRAW");

    for (i=0; i<prediction.coord_1.rows(); i++) {
            pts_2.push_back(boost::make_tuple(
                    prediction.coord_1(i, 0),
                    prediction.coord_1(i, 1)));
        }
        for (i=0; i<prediction.coord_2.rows(); i++) {
            pts_2.push_back(boost::make_tuple(
                    prediction.coord_2(i, 0),
                    prediction.coord_2(i, 1)));
        }

    gp2 << "plot '-' with points title 'predict points'\n";
    gp2.send1d(pts_2);

    cout<<"after transformation"<<endl;
    cout<<trans_coordinate(prediction.coord_1, prediction.angle, 0, prediction.dx, prediction.dy, 0, 0)<<endl;
    cout<<trans_coordinate(prediction.coord_2, prediction.angle, 0, prediction.dx, prediction.dy, 0, 0)<<endl;

    Eigen::MatrixXd lidar_court = trans_coordinate(lidar_points_clear, prediction.angle, 0, prediction.dx, prediction.dy, 0, 0 );
    double middle;
    middle = find_path(lidar_court, 1.2, 3.0, prediction.dx, prediction.dy);
    cout<<"middle = "<<middle<<endl;



    cout<<"find path"<<endl;
    for (i=0; i<lidar_court.rows(); i++) {
            pts_3.push_back(boost::make_tuple(
                    lidar_court(i, 0),
                    lidar_court(i, 1)));
        }
    gp3 << "plot '-' with points title 'court coordinate'\n";
    gp3.send1d(pts_3);
    // for (i=0; i<lidar_candidates.rows(); i++) {
    //     pts_3.push_back(boost::make_tuple(
    //             lidar_candidates(i, 0),
    //             lidar_candidates(i, 1)));
    // }
    // gp3 << "plot '-' with points title 'lidar_candidates'\n";
    // gp3.send1d(pts_3);
    // ROS_INFO("FINISHED DRAW");

//     playground predict = find_poles(lidar_candidates, 0.05, 0.25, 0.05, 0.08, 1.2, 3);
//     ROS_INFO("FINISHED PREDICTION");
//     cout<< "predict.coord_1"<<endl<<predict.coord_1<<endl;
//     cout<<"predict.coord_2"<<endl<<predict.coord_2<<endl;
//     for (i=0; i<predict.coord_1.rows(); i++) {
//         pts_2.push_back(boost::make_tuple(
//                 predict.coord_1(i, 0),
//                 predict.coord_1(i, 1)));
//     }
//     for (i=0; i<predict.coord_2.rows(); i++) {
//         pts_2.push_back(boost::make_tuple(
//                 predict.coord_2(i, 0),
//                 predict.coord_2(i, 1)));
//     }
//
//     gp2 << "plot '-' with points title 'predict points'\n";
//     gp2.send1d(pts_2);
// }



// ros::spinOnce();
// ROS_INFO("spinOnce");
// rate.sleep();
}
    return 0;
}
