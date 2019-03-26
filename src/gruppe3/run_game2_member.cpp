#include "run_game2.h"
using namespace cv;
using namespace std;

struct color_id{
    Mat  c,d;  };

geometry_msgs::Pose2D current_pose;
float datalaser[360] = {0} ;
const double PI = 3.14159265358979323846;
uchar ball_catched;

int color_code = 1;                    // yellow -> 1;blue -> 0.
int ball_iden;                         // ball_iden == 0 -> not our ball; ball_iden == 1 -> is our ball
int which_side;                        // which_side == 1 -> left; which_side == 0 -> right
int which_func;                    // ball_iden -> 0; which_side -> 1; depth -> 2; suitable_green_pillars -> 3; all_green_pillars -> 4;
uchar color_value;
int width_final;
int bound_x1;
double center_point;
int ball_x;
int color_rows;
int bound_rows;
int thres_color;

bool ball_in_catch = 2;

cv::Mat rgb_image;
cv::Mat depth_image;
cv::Mat src;
cv::Mat transition;
cv::Mat color_depth;

int count_helper = 0;
int count_0 = 0;
int count_1 = 0;
int center_ball = 1000;

cv::Mat blue_filtered_d;
cv::Mat yellow_filtered_d;
cv::Mat green_filtered_d;

// Global matrices and vars.
Eigen::MatrixXi count_color;
Eigen::MatrixXi bound;
Eigen::MatrixXi width;
Eigen::MatrixXi green_pillars;
Eigen::MatrixXd pillars_coord;

int pillars_found;
int pillars_num;
int depth_admitted;
int depth_switch;


int max_blue,max_yellow;
int thres_blue,thres_yellow;

const float camera_cx = 319.5;
const float camera_cy = 239.5;
const float camera_fx = 570.342;
const float camera_fy = 570.342;


color_id bluecolor(vector<Mat> mv, Mat src)
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
  color_id e = {b,d};
  //imshow("b",b);
  //imwrite("/home/haoming/catkin_ws/c1.png",c);
  //namedWindow("blue_dsc",  WINDOW_AUTOSIZE);
  //waitKey(0);
  return e;
}
color_id yellowcolor(vector<Mat> mv,Mat src)
{
  Mat  d(src.size(),CV_8U,Scalar(0));
  Mat  tmpH1(src.size(),CV_8U,Scalar(0));
  Mat  tmpH2(src.size(),CV_8U,Scalar(0));
  Mat  tmpH3(src.size(),CV_8U,Scalar(0));
  inRange(mv[0],Scalar(20.0,0.0,0,0),Scalar(34,0.0,0,0),tmpH1);
  inRange(mv[1],Scalar(150.0,0.0,0,0),Scalar(255.0,0.0,0,0),tmpH2);
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
  color_id e = {y,d};
  //waitKey(0);
  return e;
}
color_id greencolor(std::vector<cv::Mat> mv,cv::Mat src)
{
  cv::Mat  d(src.size(),CV_8U,Scalar(0));
  cv::Mat  tmpH1(src.size(),CV_8U,Scalar(0));
  cv::Mat  tmpH2(src.size(),CV_8U,Scalar(0));
  cv::Mat  tmpH3(src.size(),CV_8U,Scalar(0));
  inRange(mv[0],Scalar(35.0,0.0,0,0),Scalar(77.0,0.0,0,0),tmpH1);
  inRange(mv[1],Scalar(43.0,0.0,0,0),Scalar(255.0,0.0,0,0),tmpH2);
  inRange(mv[2],Scalar(46.0,0.0,0,0),Scalar(255.0,0.0,0,0),tmpH3);
  bitwise_and(tmpH3,tmpH2,tmpH2);
  bitwise_and(tmpH1,tmpH2,tmpH1);
  blur(tmpH1,tmpH1,Size(3,3)); // 使用3*3内核来降噪
  cv::Mat dsc;
  dsc = tmpH1.clone();
  d=(tmpH1)*(0.8);//绿色对应值 51.0；

  cv::Mat  g=Mat::zeros(src.size(),CV_8UC3);
  MatIterator_<uchar> greenit,greenend;
  MatIterator_<Vec3b> greenit1,greenend1;
  for(greenit = dsc.begin<uchar>(),greenend=dsc.end<uchar>(),greenit1 = g.begin<Vec3b>(),greenend1 = g.end<Vec3b>(); greenit != greenend; ++greenit,++greenit1)
  {
  if (*greenit == 255)
  {   (*greenit1)[1]=255;}}
  color_id e={g,d};
  //waitKey(0);
  return e;
}


TurnandGo::TurnandGo() :it(n)
{
  moveRobot_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",1);
  laserRobot_sub = n.subscribe("/lidarscan",1000,&TurnandGo::get_laser_callback,this);
  odom_sub = n.subscribe("odom",1, &TurnandGo::odomCallback,this);
  info_sub = n.subscribe("rosinfo",1, &TurnandGo::infoCallback,this);
  depth_image_ptr = ros::topic::waitForMessage<sensor_msgs::Image>("/camera/depth_registered/image_raw", n);
  rgb_sub = n.subscribe("/camera/rgb/image_raw/compressed", 1 ,&TurnandGo::rgb_Callback,this);
  depth_sub = it.subscribe("/camera/depth_registered/image_raw", 1 , &TurnandGo::depth_Callback,this);
}

void TurnandGo::setAngle (float ang)
{
  angle = ang;
}

void TurnandGo::setLength (float len)
{
  length = len;
}

void TurnandGo::infoCallback(const std_msgs::Float64MultiArray::ConstPtr& info)
{
  float x_cur = current_pose.x;
  float y_cur = current_pose.y; // information get from /odom
  //process the message to get six parameters
  float x_r = info->data[0];
  float y_r = info->data[1];
  float theta_r = info->data[2];
  float angle_out = info->data[3];
  float dx = info->data[4];
  float dy = info->data[5];
  float flg = info->data[6];
  //float result_x, result_y;
  float x1 = (x_cur-x_r)*cos(theta_r) + (y_cur-y_r)*sin(theta_r);
  float y1 = -(x_cur-x_r)*sin(angle_out) + (y_cur-y_r)*cos(theta_r);

  x_coor = x1*cos(angle_out) + y1*sin(angle_out)+ dx ;
  y_coor = -x1*sin(angle_out) + y1*cos(angle_out)+ dy;
}


void TurnandGo::get_laser_callback(const sensor_msgs::LaserScan &laser)
{
  int i = 0 ;
  for(int i = 0 ;i < 360;i++)
	 {
	    datalaser[i] = laser.ranges[i] ;
	 }
}

void TurnandGo::rgb_Callback(const sensor_msgs::CompressedImageConstPtr& msg)
{
  // cv_bridge::CvImagePtr cv_ptr;
  try{
      rgb_image = cv::imdecode(cv::Mat(msg -> data),1);
  }
  catch(cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge error: %s", e.what());
      return;
  }
  cv::waitKey(10);
  src = rgb_image;
  cv::Mat  hsv(src.size(),CV_8U,Scalar(0));
  cv::blur(src,src,Size(3,3));//先使用3*3内核来降噪
  cv::cvtColor(src, hsv, CV_BGR2HSV );//RGB to HSV

  std::vector<cv::Mat> mv;
  split(hsv,mv);
  color_id blue,yellow,green;
  blue=bluecolor( mv,  src);
  yellow=yellowcolor( mv, src);
  green=greencolor( mv, src);

  blue_filtered_d = blue.d;
  yellow_filtered_d = yellow.d;
  green_filtered_d = green.d;

  if (which_func == 1)
  {
    count_color = Eigen::MatrixXi::Zero(2,640);
    bound = Eigen::MatrixXi::Zero(4,640);
    width = Eigen::MatrixXi::Zero(2,640);

    max_blue = 0;
    max_yellow = 0;
    // Identify the ball in specific color.
    for(int c = 0;c < blue.d.cols;c++){
      for(int d = 180;d < 240;d++){
        if (blue.d.at<uchar>(d,c) == 51.0){
          count_color(0,c)++;
        }
        if (yellow.d.at<uchar>(d,c) == 153.0)
        {
          count_color(1,c)++;
        }
      }
      if (count_color(0,c) > max_blue){
        max_blue = count_color(0,c);
      }
      if (count_color(1,c) > max_yellow)
      {
        max_yellow = count_color(1,c);
      }
    }
    thres_blue = max_blue*5/6;
    thres_yellow = max_yellow*5/6;

    if (color_code == 0)      // yellow
    {
      transition = blue.d;
      color_value = 51.0;
      color_rows = 0;
      bound_rows = 0;
      thres_color = thres_blue*5/6;
    }
    else if (color_code == 1)   // blue
    {
      transition = yellow.d;
      color_value = 153.0;
      color_rows = 1;
      bound_rows = 2;
      thres_color = thres_yellow*5/6;
    }

    int ii_transition = 0;
    int color_flag = 0;
    int bound_transition_x1;
    int max_width_transition = 0;
    for(int n = 0;n < transition.cols-6;n++){
      if(color_flag == 0 && count_color(color_rows,n) > thres_color&& count_color(color_rows,n+1) > thres_color && count_color(color_rows,n+2) > thres_color)
      {
        bound(bound_rows,ii_transition) = n;
        color_flag = 1;
      }
      else if(color_flag == 1 && count_color(color_rows,n) < thres_color && count_color(color_rows,n+1) < thres_color && count_color(color_rows,n+2) < thres_color)
      {
        bound(bound_rows+1,ii_transition) = n;
        color_flag = 0;
        ii_transition++;
      }
    }
    if (color_flag == 1){
      bound(bound_rows+1,ii_transition) = transition.cols;
      ii_transition++;
    }
    for (int l = 0;l < ii_transition; l++)
    {
      width(color_rows,l) = bound(bound_rows+1,l)-bound(bound_rows,l);
      if (width(color_rows,l) > max_width_transition)
      {
        max_width_transition = width(color_rows,l);
        bound_transition_x1 = bound(bound_rows,l);
      }
    }
    width_final = max_width_transition;
    bound_x1 = bound_transition_x1;
    ball_x = bound_x1 + width_final/2;
    center_point = -0.0000985 * pow(width_final,2) + 0.8326 * width_final + 308.0392;
    count_helper++;
    if (abs(ball_x-(int)center_point) < abs(center_ball -(int)center_point))
    {
      center_ball = ball_x;
    }
    // ROS_INFO("center_ball:%i",center_ball);
    if (ball_x < (int)center_point)
    {
      which_side = 1;
      count_1++;
    }
    else
    {
      which_side = 0;
      count_0++;
    }
  }
  else if (which_func == 3)
  {
    if (depth_switch == 1)
    {
      count_color = Eigen::MatrixXi::Zero(1,640);
      bound = Eigen::MatrixXi::Zero(2,640);
      green_pillars = Eigen::MatrixXi::Zero(1,10);
      int max_green = 0;
      for(int c = 0;c < green_filtered_d.cols;c++)
      {
        for(int d = 180;d < 240;d++)
        {
          if (green_filtered_d.at<uchar>(d,c) == 204.0)
          {
            count_color(0,c)++;
          }
        }
        if (count_color(0,c) > max_green)
        {
          max_green = count_color(0,c);
        }
      }
      int thres_green = max_green*3/4;

      pillars_num = 0;
      pillars_found = 0;
      // find the first pillars.
      int color_flag_green = 0;
      for(int n = 0;n < green_filtered_d.cols-6;n++)
      {
        if(color_flag_green == 0 && count_color(0,n) > thres_green && count_color(0,n+1) > thres_green && count_color(0,n+2) > thres_green)
        {
          bound(0,pillars_num) = n;
          color_flag_green = 1;
        }
        else if(color_flag_green == 1 && count_color(0,n) < thres_green && count_color(0,n+1) < thres_green && count_color(0,n+2) < thres_green)
        {
          bound(1,pillars_num) = n;
          color_flag_green = 0;
          pillars_num++;
        }
      }
      width = Eigen::MatrixXi::Zero(1,pillars_num);
      int pillars_x;
      int center_pillars = 0;
      int average;
      int pillars_helper = 0;
      if (pillars_num < 3)
      {
        pillars_found = 0;
      }
      else if (pillars_num == 3 || pillars_num == 4)
      {
        for (int count_pillars = 0;count_pillars < pillars_num; count_pillars++)
        {
          if (bound(0,count_pillars) < 100 || bound(0,count_pillars) > 500)
          {
            center_pillars++;
          }
          if (center_pillars == pillars_num)
          {
            pillars_found = 0;
            depth_switch = 1;
          }
          else
          {
            pillars_helper = 1;
          }
          if (pillars_helper == 1)
          {
            int width_sum = 0;
            for (int e = 0;e < pillars_num ;e++)
            {
              width(0,e) = bound(1,e) - bound(0,e);
              green_pillars(0,e) = bound(0,e) + width(0,e)/2;
              // ROS_INFO("green_pillars,bound1,width:%i,%i,%i",green_pillars(0,e),bound(0,e),width(0,e));
              width_sum += width(0,e);
            }
            average = (int)(width_sum/pillars_num);
            // ROS_INFO("average:%i",average);
            int deviation_counter = 0;
            for (int e = 0;e < pillars_num ;e++)
            {
              if (abs(width(0,e)-average) < 4)
              {
                deviation_counter++;
              }
            }
            if (deviation_counter == pillars_num)
            {
              pillars_found = 1;
              depth_switch = 0;
            }
            else
            {
              pillars_found = 0;
              depth_switch = 1;
            }
          }
        }
      }
      ROS_INFO("pillars_found: %i",pillars_found);
      cout << "==============================================" << endl;
      cout << "width = " << width << endl;
      depth_admitted = 0;
    }
  }
  else if (which_func == 4)
  {
    if (depth_switch == 1)
    {
      count_color = Eigen::MatrixXi::Zero(1,640);
      bound = Eigen::MatrixXi::Zero(2,640);
      int max_green = 0;
      for(int c = 0;c < green_filtered_d.cols;c++)
      {
        for(int d = 180;d < 240;d++)
        {
          if (green_filtered_d.at<uchar>(d,c) == 204.0)
          {
            count_color(0,c)++;
          }
        }
        if (count_color(0,c) > max_green)
        {
          max_green = count_color(0,c);
        }
      }
      int thres_green = max_green*3/4;

      pillars_num = 0;
      pillars_found = 0;
      // find the first pillars.
      int color_flag_green = 0;
      for(int n = 0;n < green_filtered_d.cols-6;n++)
      {
        if(color_flag_green == 0 && count_color(0,n) > thres_green && count_color(0,n+1) > thres_green && count_color(0,n+2) > thres_green)
        {
          bound(0,pillars_num) = n;
          color_flag_green = 1;
        }
        else if(color_flag_green == 1 && count_color(0,n) < thres_green && count_color(0,n+1) < thres_green && count_color(0,n+2) < thres_green)
        {
          bound(1,pillars_num) = n;
          color_flag_green = 0;
          pillars_num++;
        }
      }
      width = Eigen::MatrixXi::Zero(1,pillars_num);
      green_pillars = Eigen::MatrixXi::Zero(1,pillars_num);
      for (int e = 0;e < pillars_num ;e++)
      {
        width(0,e) = bound(1,e) - bound(0,e);
        green_pillars(0,e) = bound(0,e) + width(0,e)/2;
        // ROS_INFO("green_pillars,bound1,width:%i,%i,%i",green_pillars(0,e),bound(0,e),width(0,e));
        depth_switch = 0;
      }
      pillars_found = 1;
    }
  }
}

void TurnandGo::depth_Callback(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr cv_ptr;
  try{
      cv_ptr = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::TYPE_32FC1);
  }
  catch(cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge error: %s", e.what());
      return;
  }
  cv_ptr->image.copyTo(depth_image);
  // ROS_INFO("We have depth_image.");
  // read the depth of clustering
  cv::Mat yellow_dep = Mat::zeros(src.size(),CV_32FC1);
  cv::Mat blue_dep = Mat::zeros(src.size(),CV_32FC1);
  cv::Mat green_dep = Mat::zeros(src.size(),CV_32FC1);

  for(int i = 0;i<depth_image.rows;i++){
    for(int j = 0;j<depth_image.cols;j++){
      if(yellow_filtered_d.at<uchar>(i,j) == 153.0){
        yellow_dep.at<float>(i,j) = depth_image.at<float>(i,j);
      }
      else if(blue_filtered_d.at<uchar>(i,j) == 51.0){
        blue_dep.at<float>(i,j) = depth_image.at<float>(i,j);
      }
      else if (green_filtered_d.at<uchar>(i,j) == 204.0)
      {
        green_dep.at<float>(i,j) = depth_image.at<float>(i,j);
      }
    }
  }
  /*if (which_func == 2)
  {
    ROS_INFO("start assignment");
    if (color_code == 1)       // yellow
    {
      color_depth = yellow_dep;
    }
    else if (color_code == 0)   // blue
    {
      color_depth = blue_dep;
    }
    cv::imwrite("/home/ge69toc/pics/color_depth.png",color_depth);
    ROS_INFO("End assignment");

    float depth_th = 0.04;
    int count_th = 50;
    int sum_x,sum_y,coord_x,coord_y;
    float sum = 0;
    int counter = 0;
    float sort = 10000;

    Eigen::MatrixXi flag = Eigen::MatrixXi::Zero(480,640);
    cv::Mat nearest_cluster = Mat::zeros(src.size(),CV_8U);
    cv::Mat clusters = Mat::zeros(src.size(),CV_8U);
    int ff = 1;
    int nearest_label;
    for(int m = 0;m < depth_image.rows;m = m + 4){
      for(int n = 0;n < depth_image.cols;n = n + 4){
        if (flag(m,n) == 0 && color_depth.at<float>(m,n) != 0){
          flag(m,n) = ff;
          sum = color_depth.at<float>(m, n);
          sum_x = n;
          sum_y = m;
          counter = 1;
          //ROS_INFO("yellow sorting: %i times",loop);
          //loop++;
          for (int p = 0;p < depth_image.rows;p = p + 4){
            for(int q = 0;q < depth_image.cols;q = q + 4){
              if(flag(p,q) == 0 && color_depth.at<float>(p,q) != 0 && abs(color_depth.at<float>(p,q)-sum/counter)<depth_th){
                flag(p,q) = ff;
                sum_x += q;
                sum_y += p;
                sum += color_depth.at<float>(p,q);
                counter++;
              }
            }
          }
          cv::imwrite("/home/ge69toc/pics/clusters.png",clusters);

          if (counter > count_th && sum/counter < sort){
              sort = sum/counter;
              nearest_label = ff;
              coord_x = sum_x/counter;
              coord_y = sum_y/counter;
            }
          }
          ff++;
        }
    }
  /////draw pic/////////////////////7
    for (int k = 0; k < depth_image.rows; k++) {
      for (int l = 0; l < depth_image.cols; l++) {
        if (flag(k,l) == nearest_label) {
          nearest_cluster.at<uchar>(k,l) = color_value;
        }
      }
    }
    // CHOOSE the left one when classify 2 clusters
    int count_filter;
    cv::Mat filtered_nearest_cluster = Mat::zeros(src.size(),CV_8U);
    if (color_depth.at<float>(coord_y,coord_x) == 0){
      sum = 0;
      sum_x = 0;
      sum_y = 0;
      count_filter = 0;
      ROS_INFO("filtering");
      for (int k = 0; k < depth_image.rows; k++){
        for (int v = 0; v < coord_x; v++){
          if (nearest_cluster.at<uchar>(k,v) == color_value){
            sum_x += v;
            sum_y += k;
            sum += color_depth.at<float>(k,v);
            count_filter++;
            filtered_nearest_cluster.at<uchar>(k,v) = color_value;
          }
        }
      }
      sort = sum/count_filter;
      coord_x = sum_x/count_filter;
      coord_y = sum_y/count_filter;
    }
    cv::imwrite("/home/ge69toc/nearest_cluster.png",nearest_cluster);
    cv::imwrite("/home/ge69toc/filtered_nearest_cluster.png",filtered_nearest_cluster);

    ROS_INFO("depth = %f",sort);
    ROS_INFO("coordinates = %i,%i",coord_x,coord_y);
    float pcl_coordinate_z = sort;
    float pcl_coordinate_x = (coord_x-camera_cx)*pcl_coordinate_z/camera_fx;
    float pcl_coordinate_y = (coord_y-camera_cy)*pcl_coordinate_z/camera_fy;
    ROS_INFO("coordinate_x:%f,",pcl_coordinate_x);
    ROS_INFO("coordinate_y:%f,",pcl_coordinate_y);
    ROS_INFO("coordinate_z:%f,",pcl_coordinate_z);
  }*/
  if (which_func == 0)
  {
    for(int c = 0;c < blue_filtered_d.cols;c++){
      for(int d = 180;d < 240;d++){
        if (blue_filtered_d.at<uchar>(d,c) == 51.0){
          if (blue_dep.at<float>(d,c) > 1.0 && blue_dep.at<float>(d,c) < 4.5)
          {
            blue_filtered_d.at<uchar>(d,c) = 0.0;
          }
        }
        if (yellow_filtered_d.at<uchar>(d,c) == 153.0)
        {
          if (yellow_dep.at<float>(d,c) > 1.0 && yellow_dep.at<float>(d,c) < 4.5)
          {
            yellow_filtered_d.at<uchar>(d,c) = 0.0;
          }
        }
      }
    }

    count_color = Eigen::MatrixXi::Zero(2,640);
    bound = Eigen::MatrixXi::Zero(4,640);
    width = Eigen::MatrixXi::Zero(2,640);

    max_blue = 0;
    max_yellow = 0;
    for(int c = 0;c < blue_filtered_d.cols;c++){
      for(int d = 180;d < 240;d++){
        if (blue_filtered_d.at<uchar>(d,c) == 51.0){
          count_color(0,c)++;
        }
        if (yellow_filtered_d.at<uchar>(d,c) == 153.0)
        {
          count_color(1,c)++;
        }
      }
      if (count_color(0,c) > max_blue){
        max_blue = count_color(0,c);
      }
      if (count_color(1,c) > max_yellow)
      {
        max_yellow = count_color(1,c);
      }
    }

    thres_blue = max_blue*5/6;
    thres_yellow = max_yellow*5/6;

    int ii_blue = 0;
    int ii_yellow = 0;
    int max_width_blue = 0;
    int max_width_yellow = 0;
    bool color_flag_yellow,color_flag_blue;
    int bound_yellow_x1,bound_blue_x1;

    color_flag_blue = 0;
    for(int n = 0;n < blue_filtered_d.cols-6;n++){
      if(color_flag_blue == 0 && count_color(0,n) > thres_blue && count_color(0,n+1) > thres_blue && count_color(0,n+2) > thres_blue){
        bound(0,ii_blue) = n;
        color_flag_blue = 1;
      }

      else if(color_flag_blue == 1 && count_color(0,n) < thres_blue && count_color(0,n+1) < thres_blue && count_color(0,n+2) < thres_blue){
        bound(1,ii_blue) = n;
        color_flag_blue = 0;
        ii_blue++;
      }
    }
    if (color_flag_blue == 1){
      bound(1,ii_blue) = blue_filtered_d.cols;
      ii_blue++;
    }
    for (int l = 0;l < ii_blue; l++){
      width(0,l) = bound(1,l)-bound(0,l);
      if (width(0,l) > max_width_blue){
        max_width_blue = width(0,l);
      }
    }
    // ROS_INFO("blue_width: %i",max_width_blue);

    color_flag_yellow = 0;
    for(int n = 0;n < yellow_filtered_d.cols-6;n++){
      if(color_flag_yellow == 0 && count_color(1,n) > thres_yellow && count_color(1,n+1) > thres_yellow && count_color(1,n+2) > thres_yellow){
        bound(2,ii_yellow) = n;
        color_flag_yellow = 1;
      }

      else if(color_flag_yellow == 1 && count_color(1,n) < thres_yellow && count_color(1,n+1) < thres_yellow && count_color(1,n+2) < thres_yellow){
        bound(3,ii_yellow) = n;
        color_flag_yellow = 0;
        ii_yellow++;
      }
    }
    if (color_flag_yellow == 1){
      bound(3,ii_yellow) = yellow_filtered_d.cols;
      ii_yellow++;
    }
    for (int l = 0;l < ii_yellow; l++){
      width(1,l) = bound(3,l)-bound(2,l);
      if (width(1,l) > max_width_yellow){
        max_width_yellow = width(1,l);
      }
    }
    // ROS_INFO("yellow_width: %i",max_width_yellow);
    if ((max_width_blue > max_width_yellow && color_code == 0) || (max_width_blue < max_width_yellow && color_code == 1))
    {
      ball_iden = 1;
    }
    else
    {
      ball_iden = 0;
    }
    // ROS_INFO("ball_iden:%i",ball_iden);
  }
  else if (which_func == 3 && pillars_found == 1 && depth_admitted == 0)
  {
    pillars_coord = Eigen::MatrixXd::Zero(2,pillars_num);
    int pillar_coord_x;
    float pillar_X,pillar_Z;
    float depth_sum = 0;
    int depth_helper = 2;
    ros::Duration(1.0).sleep();
    for (int f = 0;f < pillars_num; f++)
    {
      // ROS_INFO("green_pillars = %i",green_pillars(0,f));
      pillar_coord_x = green_pillars(0,f);
      ROS_INFO("pillar_coord_x:%i",pillar_coord_x);
      pillar_Z = green_dep.at<float>(240,pillar_coord_x);
      ROS_INFO("pillar_Z:%f",pillar_Z);
      if (pillar_Z != pillar_Z || fabs(pillar_Z) < 1e-5)
      {
        depth_helper = 0;
        ROS_INFO("abc======");
        break;
      }
      depth_sum += pillar_Z;
      pillar_X = (1.0*pillar_coord_x-camera_cx)*pillar_Z/camera_fx;
      pillars_coord(0,f) = pillar_X;
      pillars_coord(1,f) = pillar_Z;
      // std::cout<<"pillars coordinates:"<<std::endl<<pillars_coord<<std::endl;
    }
      // if (fabs(pillar_Z) > 1e-5)
      // {
      //   ROS_INFO("get depth");
      //   break;
      // }
    std::cout<<"pillars coordinates:"<<std::endl<<pillars_coord<<std::endl;
    if (fabs(pillar_Z) > 1e-5)
    {
      depth_helper = 1;
      ROS_INFO("1");
      ROS_INFO("depth_admitted:%i",depth_admitted);
      ROS_INFO("depth_helper:%i",depth_helper);
    }
    if (depth_helper == 0)
    {
      depth_admitted = 0;
      depth_switch = 1;
      ROS_INFO("2");
      ROS_INFO("depth_admitted:%i",depth_admitted);
      ROS_INFO("depth_helper:%i",depth_helper);
    }
    else if (depth_helper == 1)
    {
      ROS_INFO("3");
      int depth_counter = 0;
      for (int f = 0;f < pillars_num; f++)
      {
        if (fabs(pillars_coord(1,f) - depth_sum/pillars_num) < 0.15)
        {
          depth_counter++;
        }
      }
      ROS_INFO("a");
      if (depth_counter == pillars_num)
      {
        depth_admitted = 1;
        cout << "==============================================" << endl;
        cout << "==============================================" << endl;
        ROS_INFO("depth_admitted:%i",depth_admitted);
        depth_switch = 0;
        cout << "==============================================" << endl;
        cout << "coordinates = " << pillars_coord << endl;
      }
      else
      {
        depth_admitted = 0;
        depth_switch = 1;
      }
    }
    // ROS_INFO("pillar_x: %f, z: %f",pillar_X,pillar_Z);
  }
  else if (which_func == 4 && pillars_found == 1)
  {
    pillars_coord = Eigen::MatrixXd::Zero(2,pillars_num);
    int pillar_coord_x;
    float pillar_X,pillar_Z;
    float depth_sum = 0;
    int depth_counter = 0;
    for (int f = 0;f < pillars_num; f++)
    {
      ROS_INFO("green_pillars = %i",green_pillars(0,f));
      pillar_coord_x = green_pillars(0,f);
      ROS_INFO("pillar_coord_x:%i",pillar_coord_x);
      pillar_Z = green_dep.at<float>(240,pillar_coord_x);
      if (pillar_Z != pillar_Z && pillar_Z == 0)
      {
        depth_admitted = 0;
        break;
      }
      ROS_INFO("pillar_Z:%f",pillar_Z);
      pillar_X = (1.0*pillar_coord_x-camera_cx)*pillar_Z/camera_fx;
      pillars_coord(0,f) = pillar_X;
      pillars_coord(1,f) = pillar_Z;
    }
    if (pillars_coord(0,pillars_num) != 0)
    {
      depth_admitted = 1;
      ROS_INFO("depth_admitted");
    }
    depth_switch = 1;
  }
}



void TurnandGo::catchball()
{
  boost::shared_ptr<sensor_msgs::CompressedImage const> center_ptr;
  sensor_msgs::CompressedImage rgb_pic;
  ros::Rate loop_rate(1000);
  center_ptr = ros::topic::waitForMessage<sensor_msgs::CompressedImage>("/camera/rgb/image_raw/compressed",n);
  if (center_ptr != NULL)
  {
    rgb_pic = *center_ptr;
  }
  int flag_msg;
  while(ros::ok() && which_func == 1){
    geometry_msgs::Twist move;
    if(center_ptr != NULL){
      flag_msg = 1;
    }
    int side_helper;
    float speed_helper;
    float angle_speed_helper;
    int spin_helper;
    if (count_helper > 15 && abs(count_1 - count_0) < 3)
    {
      spin_helper = count_helper;
      if (center_ball < (int)center_point)
      {
        side_helper = 1;
      }
      else if (center_ball > (int)center_point)
      {
        side_helper = 0;
      }
    }
    if (count_helper > spin_helper && count_helper < spin_helper + 20)
    {
      if (side_helper == 1)
      {
        which_side = 1;
        speed_helper = 0.08;
        angle_speed_helper = 0.15;
      }
      else if (side_helper == 0)
      {
        which_side = 0;
        speed_helper = 0.08;
        angle_speed_helper = 0.15;
      }
    }
    else
    {
      speed_helper = 0;
      angle_speed_helper = 0.3;
    }
    if (flag_msg = 1){
      if (abs((int)center_point - ball_x) > 5){ // ADD CONDITION: CENTER OF THE BALL IS NEARBY THE CENTER OF THE CAMERA
          if (which_side == 1){
              move.angular.z = + angle_speed_helper;
              move.linear.x = speed_helper;
              // ROS_INFO("left rotate.");
          }
          else if (which_side == 0)
          {
              move.angular.z = - angle_speed_helper;
              move.linear.x = speed_helper;
              // ROS_INFO("right rotate.");
          }
        }
        else if (abs((int)center_point - ball_x) < 5){
          break;
        }
        moveRobot_pub.publish(move);
        ros::spinOnce();
        loop_rate.sleep();
      }
    }
    int width_thres = 0;
    while(ros::ok() && which_func == 1)
    {
      geometry_msgs::Twist move;

      if (width_final > 150)
      {
        ROS_INFO("We catched the ball.");
        ball_in_catch = 1;
        break;
      }
      else if (count_helper > 80 && width_thres - width_final > 50)
      {
        ROS_INFO("We missed the ball.");
        break;
      }
      if (width_final > width_thres)
      {
        width_thres = width_final;
      }
      if (abs((int)center_point - ball_x) > 10) //&& ball_catched != 1 && center_bumper != 1)
      { // ADD CONDITION: CENTER OF THE BALL IS NEARBY THE CENTER OF THE CAMERA
        move.linear.x = 0.15;
        if (which_side == 1){
          move.angular.z = + 0.3;
          // ROS_INFO("left rotate.");
        }
        else if (which_side == 0)
        {
            move.angular.z = - 0.3;
            // ROS_INFO("right rotate.");
        }
       }
      else if (abs((int)center_point - ball_x) < 10) //&& ball_catched != 1 && center_bumper != 1)
      {
        if (width_final < 100)
        {
          move.linear.x = 0.15;
        }
        else
        {
          move.linear.x = 0.1;
        }
        // ROS_INFO("Adjust direction.");
      }
      moveRobot_pub.publish(move);
      ros::spinOnce();
      loop_rate.sleep();
    }
}


/////////////////////////// process and store ladar data ////////////////////
Eigen::VectorXd TurnandGo::ladarData()
{
  Eigen::VectorXd ranges = Eigen::VectorXd::Zero(360*10);
  int ii = 0;
  ros::Rate loop_rate_l(100);
  while(ros::ok()&& ii < 10)
  {
    ros::spinOnce();
    loop_rate_l.sleep();
    ii++;
  }
  ii = 0;
  while(ros::ok()&& ii < 10)
  {
    for (int jj = 0; jj< 30; jj++)
    {
      ros::spinOnce();
      loop_rate_l.sleep();
    }

      for (int jj=0; jj<360; jj++)
      {
        if (std::isfinite(datalaser[jj]))
        {
          ranges(ii*360+jj) = datalaser[jj];
        }
        else
        {
          ranges(ii*360+jj) = 0;
        }
      }
      ii++;
  }
  return ranges;
}

////////////////////// get current pose through /odom /////////////////////
void TurnandGo::odomCallback(const nav_msgs::OdometryConstPtr& msg)
{
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
}


////// first turn an angle, and then move straightforward for a length ////////
void TurnandGo::beginMove()
{
  //while (ros::ok())
  float cur;
  for(int count = 0;count<2;count++)
  {
    ros::spinOnce();
    cur = current_pose.theta;
    ros::Duration(1).sleep();
  }

  //float cur=current_pose.theta;
  float now = cur ;
  float goal = cur + angle;

  while ( goal > 3.1416){
    goal -= 2*3.1416;
  }
  while(goal < -3.1416){
    goal += 2*3.1416;
  }
  //ROS_INFO("Initial angle:%f", cur_1);
  //ROS_INFO("Goal angle final:%f", goal);
  ros::Rate rate_l(100);
  ROS_INFO("begin to turn an angle:%f",angle);

  while(fabs(now-goal)>0.01)
  {
    now = current_pose.theta;
    // ROS_INFO("goal angle:%f",goal);
    // ROS_INFO("current angle:%f",now);
    // ROS_INFO("current difference:%f", fabs(now-goal));
    geometry_msgs::Twist move;
    //ROS_INFO("begin to turn an angle:%f",angle);
    if (angle>0)
    {
      move.linear.x = 0; //speed value m/s
      move.angular.z = 0.4;
    }
    else
    {
      move.linear.x = 0; //speed value m/s
      move.angular.z = -0.4;
    }
    moveRobot_pub.publish(move);
    ros::spinOnce();
    rate_l.sleep();
  }

  float y_intl;
  float x_intl ;

  for(int count = 0;count<2;count++)
  {
    ros::spinOnce();
    y_intl = current_pose.y;
    x_intl = current_pose.x;
    ros::Duration(1).sleep();
  }
  ROS_INFO("current coordinate:[%f,%f]",current_pose.x,current_pose.y);
  ROS_INFO("move straightforward for %f",length);

  while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < length)
  {
    geometry_msgs::Twist move;
    move.linear.x = 0.2;
    move.angular.z = 0;
    moveRobot_pub.publish(move);
    ros::spinOnce();
    rate_l.sleep();
  }
}

void TurnandGo::foolTurn()
{
  ros::Rate rate_l(100);
    float cur;
    for(int count = 0;count<2;count++)
    {
      ros::spinOnce();
      cur = current_pose.theta;
      ros::Duration(1).sleep();
    }

    //float cur=current_pose.theta;
    float now = cur ;
    float goal = cur + angle;

    while ( goal > PI){
      goal -= 2*PI;
    }
    while(goal < -PI){
      goal += 2*PI;
    }
    //ROS_INFO("Initial angle:%f", cur_1);
    //ROS_INFO("Goal angle final:%f", goal);
    ROS_INFO("begin to turn an angle:%f",angle);

    while(fabs(now-goal)>0.03)
    {
      now = current_pose.theta;
      // ROS_INFO("goal angle:%f",goal);
      // ROS_INFO("current angle:%f",now);
      // ROS_INFO("current difference:%f", fabs(now-goal));
      geometry_msgs::Twist move;
      //ROS_INFO("begin to turn an angle:%f",angle);
      if (angle>0)
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = 0.5;
      }
      else
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = -0.5;
      }
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
    for(int i = 0;i<2;i++)
    {
      geometry_msgs::Twist move;
      move.linear.x = 0; //speed value m/s
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
}
// {
//   //while(ros::ok())
//   float y_intl;
//   float x_intl ;
//   ros::Rate rate_l(50);
//
//   for(int count = 0;count<2;count++)
//   {
//     ros::spinOnce();
//     y_intl = current_pose.y;
//     x_intl = current_pose.x;
//     ros::Duration(1).sleep();
//   }
//   ROS_INFO("start move backward 0.08 m");
//
//   while(sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < length)
//   {
//     geometry_msgs::Twist move;
//     move.linear.x = -0.2;
//     move.angular.z = 0;
//     moveRobot_pub.publish(move);
//     ros::spinOnce();
//     rate_l.sleep();
//   }
// }


// void TurnandGo::moveBack()
// {
//   //while(ros::ok())
//   float y_intl;
//   float x_intl ;
//   ros::Rate rate_l(50);
//
//   for(int count = 0;count<2;count++)
//   {
//     ros::spinOnce();
//     y_intl = current_pose.y;
//     x_intl = current_pose.x;
//     ros::Duration(1).sleep();
//   }
//   ROS_INFO("start move backward 0.08 m");
//
//   while(sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < length)
//   {
//     geometry_msgs::Twist move;
//     move.linear.x = -0.2;
//     move.angular.z = 0;
//     moveRobot_pub.publish(move);
//     ros::spinOnce();
//     rate_l.sleep();
//   }
// }
