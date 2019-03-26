#include "run_game2.h"
using namespace cv;
using namespace std;

struct color_id{
    Mat  c,d;  };

geometry_msgs::Pose2D current_pose;
float datalaser[360] = {0} ;
const double PI = 3.14159265358979323846;

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
  inRange(mv[0],Scalar(100,0.0,0,0),Scalar(124.0,0.0,0,0),tmpH1);
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

color_id greencolor(std::vector<cv::Mat> mv,cv::Mat src)
{
  cv::Mat  d(src.size(),CV_8U,Scalar(0));
  cv::Mat  tmpH1(src.size(),CV_8U,Scalar(0));
  cv::Mat  tmpH2(src.size(),CV_8U,Scalar(0));
  cv::Mat  tmpH3(src.size(),CV_8U,Scalar(0));
  inRange(mv[0],Scalar(45.0,0.0,0,0),Scalar(77.0,0.0,0,0),tmpH1);
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

color_id yellowcolor(vector<Mat> mv,Mat src)
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
  color_id e = {y,d};
  //waitKey(0);
  return e;
}

TurnandGo::TurnandGo() :it(n)
{
  moveRobot_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi",1);
  pub_signalrobot = n.advertise<gruppe3::signal_robot>("signal_robottopic", 1);//new
  laserRobot_sub = n.subscribe("/lidarscan",1000,&TurnandGo::get_laser_callback,this);
  odom_sub = n.subscribe("odom",1, &TurnandGo::odomCallback,this);
  info_sub = n.subscribe("rosinfo",1, &TurnandGo::infoCallback,this);//new
  sub_signaltranfer = n.subscribe("signal_transfertopic", 1, &TurnandGo::sub_signaltransferCallback,this);
  depth_image_ptr = ros::topic::waitForMessage<sensor_msgs::Image>("/camera/depth_registered/image_raw", n);
  rgb_sub = n.subscribe("/camera/rgb/image_raw/compressed", 1 ,&TurnandGo::rgb_Callback,this);
  depth_sub = it.subscribe("/camera/depth_registered/image_raw", 1 , &TurnandGo::depth_Callback,this);
  stop_sub = n.subscribe("/stop_flag",1,&TurnandGo::stop_callback,this);
  pillars_found = 0;
  ball_in_catch = 2;
  count_helper = 0;
  count_0 = 0;
  count_1 = 0;
  center_ball = 1000;
  count_yellow = 0;
  count_blue = 0;
  depth_filter_done = 0;
  depth_done = 0;
  break_signal =0;
  flag_1 = false;
  flag_2 = false;
  //gruppe3::signal_robot msgt;
        //msgt.abratio = 0.5;   // float64  a/b_ratio;
        //msgt.detectcolor = 0; // int8     detectcolor;
       // msgt.detect_done = true;   // bool     detection done;
        //msgt.reportgoal = 1;       // int8     reportgoal = {0,1,2,3};
        //msgt.odometrie_1 = 1.0;          // float64  odometrie_1
        //msgt.odometrie_2 = 2.0;          // float64  odometrie_2
       // msgt.odometrie_3 = 3.0;           // float64  odometrie_3
       // pub_signalrobot.publish(msgt);

  // depth_admitted = 0;

}

void TurnandGo::setAngle (float ang)
{
  angle = ang;
}

void TurnandGo::setLength (float len)
{
  length = len;
}

void TurnandGo::sub_signaltransferCallback(const gruppe3::signal_transfer::ConstPtr& msg)  //new sub_callback
{

  flag_1 = msg->detectionstart;
  flag_2 = msg->gamestart;
  flag_3 = msg->stop;
  flag_a = msg->true_a;
  flag_b = msg->true_b;
  flag_color = msg->T_color;
}

void TurnandGo::stop_callback (const std_msgs::Int8 &msg)
{
    break_signal = msg.data;
  //break_signal = msg.data;
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
  cv_bridge::CvImagePtr cv_ptr;
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

  blue_depth_filtered = blue.d;
  yellow_depth_filtered = yellow.d;

  count_color = Eigen::MatrixXi::Zero(2,640);
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
  }
  thres_blue = ceil(count_color.row(0).maxCoeff()*2/3);
  thres_yellow = ceil(count_color.row(1).maxCoeff()*2/3);

  count_green = Eigen::MatrixXi::Zero(1,640);
  for(int c = 20;c < green_filtered_d.cols - 25;c++)
  {
    for(int d = 0;d < green_filtered_d.rows;d++)
    {
      if (green_filtered_d.at<uchar>(d,c) == 204.0)
      {
        count_green(0,c)++;
      }
    }
  }
  thres_green = ceil(count_green.maxCoeff()*2/3);
}

void TurnandGo::depth_Callback(const sensor_msgs::ImageConstPtr& msg)
{
  // ROS_INFO("Begin second stage");
  cv_bridge::CvImagePtr cv_ptr;
  try{
      cv_ptr = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::TYPE_32FC1);
  }
  catch(cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge error: %s", e.what());
      return;
  }
  cv_ptr->image.copyTo(depth_image);
  depth_transition = Mat::zeros(src.size(),CV_32FC1);
  if (which_func == 0 || which_func == 3 || which_func == 4)
  {
    for(int i = 0;i<depth_image.rows;i++)
    {
      for(int j = 0;j<depth_image.cols;j++)
      {
        depth_transition.at<float>(i,j) = depth_image.at<float>(i,j);
      }
    }
    depth_done = 1;
    // cv::imwrite("/home/ga27bux/depth123.png",depth_transition);
  }
}

void TurnandGo::team_color()
{
  count_yellow = 0;
  count_blue = 0;
  for(int c = 0;c < blue_filtered_d.cols;c++)
  {
    for(int d = 240;d < blue_filtered_d.rows;d++)
    {
      if (blue_filtered_d.at<uchar>(d,c) == 51.0)
      {
        count_blue++;
      }
      if (yellow_filtered_d.at<uchar>(d,c) == 153.0)
      {
        count_yellow++;
      }
    }
  }
  if (count_blue < count_yellow){
    ROS_INFO("The color of our team is yellow.");
    color_code = 1;
  }
  else {
    ROS_INFO("The color of our team is blue.");
    color_code = 0;
  }
}

void TurnandGo::identify_hockey()              //which_func = 0;
{
  // Get the number of color points in each col.
  ROS_INFO("color_code: %i",color_code);
  if (color_code == 0)      // yellow
  {
    transition = blue_depth_filtered;
    color_value = 51.0;
    color_rows = 0;
    bound_rows = 0;
    thres_color = thres_blue;
  }
  else if (color_code == 1)   // blue
  {
    transition = yellow_depth_filtered;
    color_value = 153.0;
    color_rows = 1;
    bound_rows = 2;
    thres_color = thres_yellow;
  }
  // cv::imwrite("/home/ge69toc/transition.png",transition);
  int ii_transition = 0;
  int color_flag = 0;
  int bound_transition_x1;
  int max_width_transition = 0;

  bound = Eigen::MatrixXi::Zero(4,640);
  width = Eigen::MatrixXi::Zero(2,640);

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
  ROS_INFO("max_width_transition:%i",max_width_transition);
  if (max_width_transition >= 12)
  {
    ball_iden = 1;
  }
  else
  {
    ball_iden = 0;
  }
  ROS_INFO("ball_iden:%i",ball_iden);
}

void TurnandGo::identify_hockey_depth()
{
  if (depth_done == 1)
  {
    for(int i = 0;i<depth_transition.rows;i++)
    {
      for(int j = 0;j<depth_transition.cols;j++)
      {
        if (depth_transition.at<float>(i,j) == depth_transition.at<float>(i,j) && depth_transition.at<float>(i,j) > 1.5)
        {
          blue_depth_filtered.at<uchar>(i,j) = 0.0;
          yellow_depth_filtered.at<uchar>(i,j) = 0.0;
        }
      }
    }
    depth_filter_done = 1;
  }
}

void TurnandGo::specific_green_rgb()         //which_func = 3
{
  // cv::imwrite("/home/ga27bux/green.png",green_filtered_d);
  pillars_num = 0;
  // ROS_INFO("specific_green_rgb.");
  bound_green = Eigen::MatrixXi::Zero(2,640);
  green_pillars = Eigen::MatrixXi::Zero(1,10);
  int color_flag_green = 0;
  for(int n = 0;n < green_filtered_d.cols-6;n++)
  {
    if(color_flag_green == 0 && count_green(0,n) > thres_green && count_green(0,n+1) > thres_green && count_green(0,n+2) > thres_green)
    {
      bound_green(0,pillars_num) = n;
      color_flag_green = 1;
    }
    else if(color_flag_green == 1 && count_green(0,n) < thres_green && count_green(0,n+1) < thres_green && count_green(0,n+2) < thres_green)
    {
      bound_green(1,pillars_num) = n;
      color_flag_green = 0;
      pillars_num++;
    }
  }
  if (pillars_num < 2)
  {
    pillars_found = 0;
    // ROS_INFO("111111111111111111111111111");
  }
  else if (pillars_num >= 2 && pillars_num <= 5)
  {
    // ROS_INFO("222222222222222222222222222222222");
    int center_pillars = 0;
    for (int i = 0; i < pillars_num; i++)
    {
      if (bound_green(0,i) > 100 && bound_green(0,i) < 500)
      {
        center_pillars++;
      }
    }
    if (center_pillars == 0)
    {
      pillars_found = 0;
    }
    else
    {
      // ROS_INFO("33333333333333333333333333333333");
      width_green = Eigen::MatrixXi::Zero(1,pillars_num);
      pillars_height = Eigen::MatrixXf::Zero(1,pillars_num);
      for (int e = 0; e< pillars_num; e++)
      {
        width_green(0,e) = bound_green(1,e) - bound_green(0,e);
        green_pillars(0,e) = bound_green(0,e) + width_green(0,e)/2;
        // pillars_height(0,e) = count_color(0, green_pillars(0,e));
      }
      cout << "green_pillars:  " << green_pillars << endl;
      cout << "width_green:  " << width_green << endl;
      for (int f = 0; f < pillars_num; f++)
      {
        int max_count = 0;
        for (int g=bound_green(0,f); g<bound_green(1,f); g++)
        {
          if (count_green(0,g) > max_count)
          {
            max_count = count_green(0,g);
          }
          pillars_height(0,f) = 1.0*max_count;
        }
      }
      pillars_height = pillars_height / pillars_height.maxCoeff() *100;
      cout << "pillars_height" << pillars_height << endl;
      int height_mean = pillars_height.mean();
      double height_variance = 0;
      for (int e = 0; e<pillars_num; e++)
      {
        height_variance += 1.0/ pillars_num * pow(pillars_height(0,e)-height_mean,2);
      }
      ROS_INFO("height_variance:%lf",height_variance);
      if ((int)height_variance < 60)
      {
        pillars_found = 1;
        ROS_INFO("FOUND PILLARS!!  pillars_found:%i",pillars_found);
      }
    }
  }
  else
  {
  pillars_found = 0;
  }
}

void TurnandGo::all_green_rgb()              // which_func = 4
{
  pillars_num = 0;
  bound_green = Eigen::MatrixXi::Zero(2,640);
  int color_flag_green = 0;
  for(int n = 0;n < green_filtered_d.cols-6;n++)
  {
    if(color_flag_green == 0 && count_green(0,n) > thres_green && count_green(0,n+1) > thres_green && count_green(0,n+2) > thres_green)
    {
      bound_green(0,pillars_num) = n;
      color_flag_green = 1;
    }
    else if(color_flag_green == 1 && count_green(0,n) < thres_green && count_green(0,n+1) < thres_green && count_green(0,n+2) < thres_green)
    {
      bound_green(1,pillars_num) = n;
      color_flag_green = 0;
      pillars_num++;
    }
  }
  width_green = Eigen::MatrixXi::Zero(1,pillars_num);
  green_pillars = Eigen::MatrixXi::Zero(1,pillars_num);
  for (int e = 0;e < pillars_num ;e++)
  {
    width_green(0,e) = bound_green(1,e) - bound_green(0,e);
    green_pillars(0,e) = bound_green(0,e) + width_green(0,e)/2;
  }
  cout << "green_pillars :"<< green_pillars << endl;
  pillars_found = 1;
}

void TurnandGo::green_pillars_depth()
{
  int pillar_coord_x;
  float pillars_depth_sum = 0.0;
  int pixel_counter = 0;
  int width_helper;
  float pillar_Z,pillar_X;
  pillars_coord = Eigen::MatrixXf::Zero(2,pillars_num);
  // ROS_INFO("111111111111111111111111111");
  for (int e = 0;e < pillars_num; e++)
  {
    // ROS_INFO("green_pillars = %i",green_pillars(0,e));
    pillar_coord_x = green_pillars(0,e);
    width_helper = floor(width_green(0,e)/4);
    // ROS_INFO("pillar_coord_x:%i",pillar_coord_x);
    for (int w = pillar_coord_x - width_helper;w < pillar_coord_x + width_helper; w++)
    {
      for (int y = 230; y < 250; y++)
      {
        if (depth_transition.at<float>(y,w) == depth_transition.at<float>(y,w) && green_filtered_d.at<uchar>(y,w) == 204.0)
        {
          // ROS_INFO("222222222222222222222222222222222");
          pillars_depth_sum += depth_transition.at<float>(y,w);
          pixel_counter++;
        }
      }
    }
    pillar_Z = 1.0*pillars_depth_sum/pixel_counter;
    pillar_X = (1.0*pillar_coord_x-camera_cx)*pillar_Z/camera_fx;
    pillars_coord(0,e) = pillar_X;
    pillars_coord(1,e) = pillar_Z;
  }
  cout << "==============================================" << endl;
  cout << "==============================================" << endl;
  cout << "==============================================" << endl;
  cout << "==============================================" << endl;
  cout << "coordinates = " << pillars_coord << endl;
  cout << "==============================================" << endl;
  cout << "==============================================" << endl;
  cout << "==============================================" << endl;
  cout << "==============================================" << endl;
  // cv::imwrite("/home/ga27bux/depth.png",depth_transition);
}

void TurnandGo::catch_the_hockey()           //which_func = 1;
{
  if (color_code == 0)      // yellow
  {
    transition = blue_filtered_d;
    color_value = 51.0;
    color_rows = 0;
    bound_rows = 0;
    thres_color = thres_blue;
  }
  else if (color_code == 1)   // blue
  {
    transition = yellow_filtered_d;
    color_value = 153.0;
    color_rows = 1;
    bound_rows = 2;
    thres_color = thres_yellow;
  }
  int ii_transition = 0;
  int color_flag = 0;
  int bound_transition_x1;
  int max_width_transition = 0;

  bound = Eigen::MatrixXi::Zero(4,640);
  width = Eigen::MatrixXi::Zero(2,640);

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
  // cout << "bound: " << bound <<endl;
  // cout << "width: " << width <<endl;
  width_final = max_width_transition;
  bound_x1 = bound_transition_x1;
  ball_x = bound_x1 + width_final/2;
  ROS_INFO("width_final: %i",width_final);
  ROS_INFO("ball_x: %i",ball_x);
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
  ROS_INFO("which_side:%i",which_side);
}


void TurnandGo::catchball()
{
  boost::shared_ptr<sensor_msgs::CompressedImage const> center_ptr;
  sensor_msgs::CompressedImage rgb_pic;
  ros::Rate loop_rate(1000);
  geometry_msgs::Twist move;
  center_ptr = ros::topic::waitForMessage<sensor_msgs::CompressedImage>("/camera/rgb/image_raw/compressed",n);
  if (center_ptr != NULL)
  {
    rgb_pic = *center_ptr;
  }
  int flag_msg;
  while(ros::ok() && which_func == 1)
  {
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
      catch_the_hockey();
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
    catch_the_hockey();
    if (width_final > 150)
    {
      ROS_INFO("We catched the ball.");
      ball_in_catch = 1;
      break;
    }
    else if (count_helper > 80 && width_thres - width_final > 80)
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
  if (width_final > 150){
    for (int ii=0; ii<10; ii++){
      move.linear.x = 0;
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      loop_rate.sleep();
      ROS_INFO("1111111111111111111111111111111111111111");
    }
  }
}

/////////////////////////// process and store ladar data ////////////////////
Eigen::VectorXd TurnandGo::ladarData()
{
  Eigen::VectorXd ranges = Eigen::VectorXd::Zero(360*10);
  int ii = 0;
  ros::Rate loop_rate_l(100);
  while(ros::ok()&& ii < 10){
    for (int jj = 0; jj< 20; jj++){
      ros::spinOnce();
      loop_rate_l.sleep();
    }

    for (int jj=0; jj<360; jj++){
      if (std::isfinite(datalaser[jj])){
        ranges(ii*360+jj) = datalaser[jj];
      }
      else{
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
  // ROS_INFO("odom x,y,theta %f,%f,%f",current_pose.x,current_pose.y,current_pose.theta);
}

////// first turn an angle, and then move straightforward for a length ////////
// void TurnandGo::beginMove()
// {
//   ros::Rate rate_l(100);
//   if (fabs(angle)>1e-5){
//     float cur;
//     int count_odom = 0;
//
//     while(count_odom < 20 && fabs(current_pose.theta) < 1e-4 && fabs(current_pose.x) < 1e-4 && fabs(current_pose.y) < 1e-4)
//     {
//       ros::Duration(0.1).sleep();
//       count_odom++;
//       ros::spinOnce();
//     }
//     cur = current_pose.theta;
//
//
//     float now = cur ;
//     float goal = cur + angle;
//
//     while ( goal > PI){
//       goal -= 2*PI;
//     }
//     while(goal < -PI){
//       goal += 2*PI;
//     }
//     //ROS_INFO("Initial angle:%f", cur_1);
//     //ROS_INFO("Goal angle final:%f", goal);
//     ROS_INFO("begin to turn an angle:%f",angle);
//
//     while(fabs(now-goal)>0.5236)
//     {
//       now = current_pose.theta;
//       // ROS_INFO("goal angle:%f",goal);
//       // ROS_INFO("current angle:%f",now);
//       // ROS_INFO("current difference:%f", fabs(now-goal));
//       geometry_msgs::Twist move;
//       //ROS_INFO("begin to turn an angle:%f",angle);
//       if (angle>0)
//       {
//         move.linear.x = 0; //speed value m/s
//         move.angular.z = 1.5;
//       }
//       else
//       {
//         move.linear.x = 0; //speed value m/s
//         move.angular.z = -1.5;
//       }
//       moveRobot_pub.publish(move);
//       ros::spinOnce();
//       rate_l.sleep();
//     }
//
//     while(fabs(now-goal)>0.05)
//     {
//       now = current_pose.theta;
//       float diff = goal - now;
//       float v_min = 0.2;
//       float v_smooth = max(v_min,3*sin(fabs(diff)));
//       //ROS_INFO("velocity is %f",v_smooth);
//       // ROS_INFO("goal angle:%f",goal);
//       // ROS_INFO("current angle:%f",now);
//       // ROS_INFO("current difference:%f", fabs(now-goal));
//       geometry_msgs::Twist move;
//       //ROS_INFO("begin to turn an angle:%f",angle);
//       if (angle>0)
//       {
//         move.linear.x = 0; //speed value m/s
//         move.angular.z = v_smooth;
//       }
//       else
//       {
//         move.linear.x = 0; //speed value m/s
//         move.angular.z = -v_smooth;
//       }
//       moveRobot_pub.publish(move);
//       ros::spinOnce();
//       rate_l.sleep();
//     }
//
//     while(fabs(now-goal)>0.02)
//     {
//       now = current_pose.theta;
//       float diff = goal - now;
//       if (diff>PI)
//       {
//         diff -=2*PI;
//       }
//       else if(diff<-PI)
//       {
//         diff += 2*PI;
//       }
//       geometry_msgs::Twist move;
//
//       if (diff>0)
//       {
//         move.linear.x = 0; //speed value m/s
//         move.angular.z = 0.2;
//       }
//       else
//       {
//         move.linear.x = 0; //speed value m/s
//         move.angular.z = -0.2;
//       }
//       moveRobot_pub.publish(move);
//       ros::spinOnce();
//       rate_l.sleep();
//     }
//
//
//     for(int i = 0;i<2;i++)
//     {
//       geometry_msgs::Twist move;
//       move.linear.x = 0; //speed value m/s
//       move.angular.z = 0;
//       moveRobot_pub.publish(move);
//       ros::spinOnce();
//       rate_l.sleep();
//     }
//   }
//
//   if (fabs(length)>1e-5)
//   {
//     float y_intl;
//     float x_intl ;
//     int count_odom_xy = 0;
//     while(count_odom_xy < 20 && fabs(current_pose.theta) < 1e-4 && fabs(current_pose.x) < 1e-4 && fabs(current_pose.y) < 1e-4)
//     {
//       ros::Duration(0.1).sleep();
//       count_odom_xy++;
//       ros::spinOnce();
//     }
//     y_intl = current_pose.y;
//     x_intl = current_pose.x;
//
//     ROS_INFO("current coordinate:[%f,%f]",current_pose.x,current_pose.y);
//     ROS_INFO("move straightforward for %f",length);
//
//     if(fabs(length)>1)
//       {
//         while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(0.8*length) )
//         {
//           geometry_msgs::Twist move;
//           float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
//           float v_smooth = min((0.2+1/fabs(length)*(d_current)),0.5);
//
//           //ROS_INFO("velocity 1 is %f",v_smooth);
//           if (length<0)
//           {
//             move.linear.x = -v_smooth;
//           }
//           else
//           {
//             move.linear.x = v_smooth;
//           }
//           move.angular.z = 0;
//           moveRobot_pub.publish(move);
//           ros::spinOnce();
//           rate_l.sleep();
//         }
//
//         while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(length) )
//         {
//           geometry_msgs::Twist move;
//           float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
//           float v_smooth = max(0.1,(0.5-2/fabs(length)*(d_current-0.8*fabs(length))));
//           //ROS_INFO("velocity 2 is %f",v_smooth);
//           if (length<0)
//           {
//             move.linear.x = -v_smooth;
//           }
//           else
//           {
//             move.linear.x = v_smooth;
//           }
//           move.angular.z = 0;
//           moveRobot_pub.publish(move);
//           ros::spinOnce();
//           rate_l.sleep();
//         }
//       }
//       else
//       {
//         while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(0.8*length) )
//         {
//           geometry_msgs::Twist move;
//           float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
//           float v_smooth = min((0.2+1.0/fabs(length)*(d_current)),0.5);
//           //ROS_INFO("velocity 1 is %f",v_smooth);
//           if (length<0)
//           {
//             move.linear.x = -v_smooth;
//           }
//           else
//           {
//             move.linear.x = v_smooth;
//           }
//           move.angular.z = 0;
//           moveRobot_pub.publish(move);
//           ros::spinOnce();
//           rate_l.sleep();
//         }
//
//         while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(length) )
//         {
//           geometry_msgs::Twist move;
//           float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
//           float v_smooth = max(0.1,(0.5-2/fabs(length)*(d_current-0.8*fabs(length))));
//           //ROS_INFO("velocity 2 is %f",v_smooth);
//           if (length<0)
//           {
//             move.linear.x = -v_smooth;
//           }
//           else
//           {
//             move.linear.x = v_smooth;
//           }
//           move.angular.z = 0;
//           moveRobot_pub.publish(move);
//           ros::spinOnce();
//           rate_l.sleep();
//         }
//       }
//
//       for(int i = 0;i<2;i++)
//       {
//         geometry_msgs::Twist move;
//         move.linear.x = 0; //speed value m/s
//         move.angular.z = 0;
//         moveRobot_pub.publish(move);
//         ros::spinOnce();
//         rate_l.sleep();
//       }
//     }
// }

void TurnandGo::beginMove()
{

  //while (ros::ok())
  ros::Rate rate_l(50);
  ROS_INFO("break_signal is %d",break_signal);

  if (fabs(angle)>1e-5)
  {
    float cur;
    int count_odom = 0;

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
    ROS_INFO("break signal :%d",break_signal);

    while(fabs(now-goal)>0.5236 && break_signal == 0)
    {
      now = current_pose.theta;
      geometry_msgs::Twist move;

      if (angle>0)
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = 1;
      }
      else
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = -1;
      }
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }

    while(fabs(now-goal)>0.1 && break_signal == 0)  // 0.1 means 5.73 degree
    {
      now = current_pose.theta;
      float diff = goal - now;
      float v_min = 0.2;
      float v_smooth = max(v_min,2*sin(fabs(diff)));
      geometry_msgs::Twist move;
      if (angle>0)
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = v_smooth;
      }
      else
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = -v_smooth;
      }
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }



    while(fabs(now-goal)>0.02 && break_signal == 0)
    {
      now = current_pose.theta;
      float diff = goal - now;
      if (diff>PI)
      {
        diff -=2*PI;
      }
      else if(diff<-PI)
      {
        diff += 2*PI;
      }
      geometry_msgs::Twist move;

      if (diff>0)
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = 0.2;
      }
      else
      {
        move.linear.x = 0; //speed value m/s
        move.angular.z = -0.2;
      }

      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }


    for(int i = 0;i<1;i++)
    {
      geometry_msgs::Twist move;
      move.linear.x = 0; //speed value m/s
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
  }
  if (fabs(length)>1e-5)
  {
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

    // while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(0.1*length))
    // {
    //   geometry_msgs::Twist move;
    //   if (length<0)
    //   {
    //     move.linear.x = -0.3;
    //   }
    //   else
    //   {
    //     move.linear.x = 0.3;
    //   }
    //   move.angular.z = 0;
    //   moveRobot_pub.publish(move);
    //   ros::spinOnce();
    //   rate_l.sleep();
    // }

    if(fabs(length)>1)
    {
      while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(0.8*length) && break_signal == 0)
      {
        geometry_msgs::Twist move;
        float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
        float v_smooth = min((0.2+1/fabs(length)*(d_current)),0.5);
        if (length<0)
        {
          move.linear.x = -v_smooth;
        }
        else
        {
          move.linear.x = v_smooth;
        }
        move.angular.z = 0;
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }

      while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(length) && break_signal == 0)
      {
        geometry_msgs::Twist move;
        float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
        float v_smooth = max(0.1,(0.5-2/fabs(length)*(d_current-0.8*fabs(length))));
        if (length<0)
        {
          move.linear.x = -v_smooth;
        }
        else
        {
          move.linear.x = v_smooth;
        }
        move.angular.z = 0;
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }
    }
    else
    {
      while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(0.8*length) && break_signal == 0)
      {
        geometry_msgs::Twist move;
        float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
        float v_smooth = min((0.2+1/fabs(length)*(d_current)),0.3);
        if (length<0)
        {
          move.linear.x = -v_smooth;
        }
        else
        {
          move.linear.x = v_smooth;
        }
        move.angular.z = 0;
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }

      while( sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl)) < fabs(length) && break_signal == 0)
      {
        geometry_msgs::Twist move;
        float d_current = sqrt((current_pose.y-y_intl)*(current_pose.y-y_intl)+(current_pose.x-x_intl)*(current_pose.x-x_intl));
        float v_smooth = max(0.1,(0.3-1.5/fabs(length)*(d_current-0.8*fabs(length))));
        if (length<0)
        {
          move.linear.x = -v_smooth;
        }
        else
        {
          move.linear.x = v_smooth;
        }
        move.angular.z = 0;
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }
    }

    for(int i = 0;i<2;i++)
    {
      geometry_msgs::Twist move;
      move.linear.x = 0;
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
  }


  while(break_signal !=0)
  {
    ROS_INFO("avoid begin random left!");
    while (break_signal ==1)
    {
      geometry_msgs::Twist move;
      move.linear.x = 0;
      move.angular.z = 0.8;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
    while (break_signal ==2)
    {
      ROS_INFO("turn right to avoid!!!");
      geometry_msgs::Twist move;
      move.linear.x = 0;
      move.angular.z = -0.8;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
    while (break_signal ==3)
    {
      ROS_INFO("turn left to avoid!!!");
      geometry_msgs::Twist move;
      move.linear.x = 0;
      move.angular.z = 0.6;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
    while (break_signal == 4)
    {
      ROS_INFO("stop to wait for angelina!!!");
      geometry_msgs::Twist move;
      move.linear.x = 0;
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
    if(break_signal == 0)
    {
      newPath();
      // save goal coordinate
    }
    rate_l.sleep();
  }
}


void TurnandGo::calculate()
{
  ros::spinOnce();
  float move_angle, move_distance;
  float init_angle = -current_pose.theta;
  float x1 = -current_pose.y;
  float y1 = current_pose.x;
  float x2 = -goal_y;
  float y2 = goal_x;

  float dir_y = y2 - y1;
  float dir_x = x2 - x1;

  if (fabs(dir_y)<1e-5)
  {
    if (dir_x>0)
    {
      move_angle = -3.1416/2;
    }
    else
    {
      move_angle = 3.1416/2;
    }
  }
  else
  {
    move_angle = atan(-dir_x / dir_y);
    if (dir_y < 0)
    {
      move_angle += 3.1416;
    }
  }
  move_angle = init_angle + move_angle;
  while (move_angle < -3.1416)
  {
    move_angle += 2*3.1416;
  }
  while (move_angle > 3.1416)
  {
    move_angle -= 2*3.1416;
  }
  move_distance = sqrt(pow(dir_x, 2) + pow(dir_y, 2));
  setAngle(move_angle);
  setLength(move_distance);
  beginMove();
}

void TurnandGo::newPath()
{
  // avoid move begin!
  ROS_INFO("new path begin");
  setAngle(0);
  setLength(0.5);
  beginMove();
  ///////////// get needed angle and distance from goal coorfinate ////////
  ROS_INFO("move to the previous goal: %f,%f",goal_x,goal_y);
  calculate();
  // set a flag to call the path function
}

void TurnandGo::pureRotate(bool vel_switch)
{
  ros::Rate rate_l(50);
  float cur;
  int count_odom = 0;

  while(count_odom < 20 && fabs(current_pose.theta) < 1e-4 && fabs(current_pose.x) < 1e-4 && fabs(current_pose.y) < 1e-4)
  {
    ros::Duration(0.1).sleep();
    count_odom++;
    ros::spinOnce();
  }
  cur = current_pose.theta;

  if (vel_switch == true)
  {
    if (fabs(angle)>1e-5)
    {
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
      ROS_INFO("break signal :%d",break_signal);
      while(fabs(now-goal)>0.5236)
      {
        now = current_pose.theta;
        geometry_msgs::Twist move;
        if (angle>0)
        {
          move.linear.x = 0;
          move.angular.z = 1;
        }
        else
        {
          move.linear.x = 0;
          move.angular.z = -1;
        }
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }

      while(fabs(now-goal)>0.05)
      {
        now = current_pose.theta;
        float diff = goal - now;
        float v_min = 0.2;
        float v_smooth = max(v_min,2*sin(fabs(diff)));

        geometry_msgs::Twist move;
        if (angle>0)
        {
          move.linear.x = 0;
          move.angular.z = v_smooth;
        }
        else
        {
          move.linear.x = 0;
          move.angular.z = -v_smooth;
        }
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }



      while(fabs(now-goal)>0.02)
      {
        now = current_pose.theta;
        float diff = goal - now;
        if (diff>PI)
        {
          diff -=2*PI;
        }
        else if(diff<-PI)
        {
          diff += 2*PI;
        }
        geometry_msgs::Twist move;

        if (diff>0)
        {
          move.linear.x = 0;
          move.angular.z = 0.2;
        }
        else
        {
          move.linear.x = 0;
          move.angular.z = -0.2;
        }
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }

      for(int i = 0;i<2;i++)
      {
        geometry_msgs::Twist move;
        move.linear.x = 0;
        move.angular.z = 0;
        moveRobot_pub.publish(move);
        ros::spinOnce();
        rate_l.sleep();
      }
    }
  }
  else
  {
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
    ROS_INFO("break signal :%d",break_signal);
    while(fabs(now-goal)>0.05)
    {
      now = current_pose.theta;
      geometry_msgs::Twist move;
      if (angle>0)
      {
        move.linear.x = 0;
        move.angular.z = 0.5;
      }
      else
      {
        move.linear.x = 0;
        move.angular.z = -0.5;
      }
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
    while(fabs(now-goal)>0.03)
    {
      now = current_pose.theta;
      float diff = goal - now;
      if (diff>PI)
      {
        diff -=2*PI;
      }
      else if(diff<-PI)
      {
        diff += 2*PI;
      }
      geometry_msgs::Twist move;

      if (diff>0)
      {
        move.linear.x = 0;
        move.angular.z = 0.3;
      }
      else
      {
        move.linear.x = 0;
        move.angular.z = -0.3;
      }
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }

    for(int i = 0;i<2;i++)
    {
      geometry_msgs::Twist move;
      move.linear.x = 0;
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
  }


}


void TurnandGo::foolTurn(bool direction)
{
  ROS_INFO("Turning foolishly");
  geometry_msgs::Twist move;
  ros::Rate rate_l(50);
  pillars_found = 0;
  for(int count = 0;count<6000;count++){
    if(pillars_found == 1){
      ROS_INFO("STOP TURNING!!!!!!!!!!!! pillars_found = %i" ,pillars_found);
      break;
    }
    move.linear.x = 0;
    if (direction){
      move.angular.z = 0.2;
    }
    else{
      move.angular.z = -0.1;
    }
    moveRobot_pub.publish(move);
    ros::spinOnce();
    rate_l.sleep();
  }
  if (pillars_found == 1){
    // for (int i; i<5; i++){
    //   move.linear.x = 0;
    //   move.angular.z = -0.2;
    //   moveRobot_pub.publish(move);
    //   ros::spinOnce();
    //   rate_l.sleep();
    // }
    for (int i; i<5; i++){
      move.linear.x = 0;
      move.angular.z = 0;
      moveRobot_pub.publish(move);
      ros::spinOnce();
      rate_l.sleep();
    }
  }

}
