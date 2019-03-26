#include "run_game2.h"
#include "lidar_main.h"
#include "cal_coordinate.h"
#include "find_path.h"
#include "gnuplot-iostream.h"
#include "trans_coordinate.h"
#include "line_fitting.h"
#include "move_para.h"
#include "predict2.h"
#include "find_ball.h"
#include "trans_x_y.h"
#include "trans_c_o.h"

using namespace Eigen;
const double PI = 3.14159265358979323846;
using namespace cv;
using namespace std;

geometry_msgs::Pose2D current_pose;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "TurnandGo");
  int i, j, trial, counter;
  Gnuplot gp1, gp2, gp3,gp4, gp5;
  vector<boost::tuple<double, double> > pts_1, pts_2, pts_3, pts_4, pts_5;
  MatrixXd coord_1, coord_2;
  double move_angle, move_distance, angle_main, angle_c_o, dx, dy, a, b;
  double x_robot, y_robot, theta_robot, x_robot_old, y_robot_old, theta_robot_old;
  move move_parameter;

  TurnandGo Move;

  playground world;
  VectorXd lidar_point;
  playground result;

  double dist2line_1, dist2line_2;
  double nearby = 0.4;
  double goal_x, goal_y;
  MatrixXd coord_1_standard(7,2);
  MatrixXd coord_2_standard(7,2);

  gruppe3::signal_robot msgt;
  geometry_msgs::Pose2D odom_msg1;
  geometry_msgs::Pose2D odom_msg2;
  msgt.abratio = 0.0;   // float64  a/b_ratio;
  msgt.detectcolor = 0; // int8     detectcolor;
  msgt.detect_done = false;   // bool     detection done;
  msgt.reportgoal = 0;       // int8     reportgoal = {0,1,2,3};
  //msgt.odometrie_1 = 0.0;          // float64  odometrie_1
 // msgt.odometrie_2 = 0.0;          // float64  odometrie_2
  //msgt.odometrie_3 = 0.0;           // float64  odometrie_3
  //msgt.odometrie_4 = 0.0;          // float64  odometrie_4
  //msgt.odometrie_5 = 0.0;          // float64  odometrie_5
  //msgt.odometrie_6 = 0.0;         // float64  odometrie_6

  ros::Rate move_rate(50);


  /////////////////////// Wait for angelina "start signal"/////////////////////

  while(Move.flag_1 == false)
  {
    ROS_INFO("wait for loc_begin signal!!");
    ros::spinOnce();
    move_rate.sleep();
  }

////////////////////////////////////////////////////////////////////////////////

  Move.which_func = 3;

  Move.depth_done = 0;
  while (Move.pillars_found == 0){
      ros::Duration(2).sleep();
      Move.specific_green_rgb();
      if(Move.pillars_found == 1 ){
          ROS_INFO("FOUND PILLARS!!");
          break;
      }
      else{
          ROS_INFO("DIDNT FIND PILLARS, KEEP TURNING!!");
          Move.setAngle(0.2);
          Move.setLength(0);
          Move.pureRotate(false);
          ros::spinOnce();
      }
  }

  i = 0;
  while(Move.pillars_found == 1 && i< 500){
    Move.specific_green_rgb();
    if (Move.depth_done == 1)
    {
      Move.green_pillars_depth();
    }
    ros::spinOnce();
    move_rate.sleep();
    i++;
  }
  Move.which_func = 5;
  Move.depth_done = 0;

  if (Move.pillars_found == 0){
      while (Move.pillars_found == 0){
        ros::Duration(2).sleep();
        Move.specific_green_rgb();
        if(Move.pillars_found == 1 ){
          ROS_INFO("FOUND PILLARS!!");
          break;
        }
        else{
          ROS_INFO("DIDNT FIND PILLARS, KEEP TURNING!!");
          ros::Duration(2).sleep();
          Move.setAngle(-0.2);
          Move.setLength(0);
          Move.pureRotate(false);
          ros::spinOnce();
        }
      }
      Move.which_func = 3;
      i = 0;
      while(Move.pillars_found == 1 && i< 500){
        Move.specific_green_rgb();
        if(Move.depth_done){
          Move.green_pillars_depth();
        }
        ros::spinOnce();
        move_rate.sleep();
        i++;
      }
      Move.which_func = 5;
  }


  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  cout<<i<<"   FIRST pillars coord ="<<endl<<Move.pillars_coord<<endl;
  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;

  Move.depth_done = 0;
  //Predict value of a
  VectorXd pole_dist = VectorXd::Zero(Move.pillars_coord.cols()-1);
  VectorXi pole_dist_ratio(6);
  VectorXd pole_ident = VectorXd::Zero(Move.pillars_coord.cols()-1);
  double   pole_var = 0;
  double   pole_var_min = 10000;
  double   a_predict = 0;

  pole_dist_ratio << 1, 3, 2, 2, 3, 1;
  for (i=0; i<Move.pillars_coord.cols()-1; i++){
    pole_dist(i) = sqrt(pow(Move.pillars_coord(0,i)-Move.pillars_coord(0,i+1),2) + pow(Move.pillars_coord(1,i)-Move.pillars_coord(1,i+1),2));
  }
  for (i=0; i<8-Move.pillars_coord.cols(); i++){
    pole_var = 0;
    for (j=0; j<Move.pillars_coord.cols()-1; j++){
      pole_ident(j) = pole_dist(j)/pole_dist_ratio(i+j);

    }
    for (j=0; j<Move.pillars_coord.cols()-1; j++){
      pole_var += pow(pole_ident(j)-pole_ident.mean(), 2);

    }
    if(pole_var_min > pole_var){
      pole_var_min = pole_var;
      a_predict = 4*pole_ident.mean();
    }
  }
  cout<<"prediction of a = "<<a_predict<<endl;



  Move.which_func = 5;
  Move.pillars_found = 0;
  // turn to the pillars
  fitted_line line1 = line_fitting(Move.pillars_coord.transpose());
  Move.setAngle(line1.angle);
  Move.setLength(line1.distance-1.5);

  cout<<"angle = "<<line1.angle <<"distance = "<< line1.distance<<endl;
  ROS_INFO("move to the middle of the court===================");


  //
  Move.beginMove();

  while(Move.flag_3 == true)
  {
    ros::spinOnce;
    move_rate.sleep();
  }

// first lidar localization
  Move.which_func  = 5;
  dist2line_1 = 3-1.65;
  dist2line_2 = 1.65;
  bool success = 0;
  while (success == 0){
      lidar_point = Move.ladarData();
      world = lidar_main(cal_coordinate(lidar_point, 1), 1, dist2line_1, dist2line_2);
      success = world.success;
  }

  ROS_INFO("test111111===================");

  a           = world.a;
  b           = world.b;
  angle_main  = world.angle;
  dx          = world.dx;
  dy          = world.dy;
  angle_c_o   = angle_main + current_pose.theta;
  ROS_INFO("test222222222===================");


/////////////////////////// Give angelina a/b ratia! ///////////////////////////

  msgt.abratio = a/b;
  Move.pub_signalrobot.publish(msgt);

////////////////////////////////////////////////////////////////////////////////



  /////////////////////////// Angelina give a,b back!!/////////////////////////

  ROS_INFO("test a b signal%f,%f",Move.flag_a,Move.flag_b);

  if(Move.flag_a>1e-3)
  {
    a = Move.flag_a;
  }

  if(Move.flag_b>1e-3)
  {
    b = Move.flag_b;
  }

  /////////////////////////////////////////////////////////////////////////////
  coord_1_standard<< 0, 0, 0, 0.25*a, 0, a, 0, 1.5*a, 0, 2.0*a, 0, 2.75*a, 0, 3.0*a;
  coord_2_standard<< b, 0, b, 0.25*a, b, a, b, 1.5*a, b, 2.0*a, b, 2.75*a, b, 3.0*a;

  coord_1     = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
  coord_2     = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);
  x_robot     = current_pose.x;
  y_robot     = current_pose.y;
  theta_robot = current_pose.theta;

  MatrixXd lidar_world_0 = trans_coordinate(cal_coordinate(lidar_point, 1), angle_main, dx, dy, 0, 0);
  for (i=0; i<lidar_world_0.rows(); i++) {
      pts_2.push_back(boost::make_tuple(
          lidar_world_0(i, 0),
          lidar_world_0(i, 1)));
      }
  gp2 << "plot '-' with points title 'world0'\n";
  gp2.send1d(pts_2);

  move_parameter = move_para(angle_main, dx, dy, b/2.0, a);
  move_angle     = move_parameter.angle - PI;
  move_distance  = - move_parameter.distance;
  Move.setAngle(move_angle);
  Move.setLength(move_distance);
  ROS_INFO("move to the center of the court===========================");

  // court: x:b/2 y:a
  Move.goal_x = b/2;
  Move.goal_y = a;
  Move.calculate();
  //Move.beginMove();

  // Turn to the color block
  Move.setAngle(angle_c_o + PI - current_pose.theta);
  Move.setLength(0);
  ROS_INFO("turn to the color block===================");
  Move.beginMove();

  while(Move.flag_3 == true)
  {
    ros::spinOnce;
    move_rate.sleep();
  }

  // Identify team color
  Move.which_func = 6;
  counter = 0;
  while(ros::ok() && counter < 50){
    Move.team_color();
    ros::spinOnce();
    move_rate.sleep();
    counter++;
  }
  if(Move.color_code){
    cout<<"our team color is yellow"<<endl;
  }
  else{
    cout<<"our team color is blue"<<endl;
  }



/////////////////////////  Give angelina color !!!! //////////////////////////

  msgt.detectcolor = Move.color_code + 1;
  Move.pub_signalrobot.publish(msgt);

//////////////////////////////////////////////////////////////////////////////


  ros::spinOnce();
  ROS_INFO("test color:%d",Move.flag_color-1);




  // Move to the middle of the path
  double middle = find_path(lidar_world_0, a, b, a); // court
  cout<<"middle = "<<middle<<" a = "<<a<<" b = "<< b<<endl;


  odom_msg1.theta = angle_main;
  odom_msg2.theta = theta_robot;

  odom_msg1.x = dx;
  odom_msg2.x = x_robot;

  odom_msg1.y = dy;
  odom_msg2.y = y_robot;

  msgt.odometrie_1  = odom_msg1;
  msgt.odometrie_2  = odom_msg2;
  Move.pub_signalrobot.publish(msgt);


  coord_struct goal_path = trans_c_o(middle, a, angle_main, dx, dy, theta_robot, x_robot, y_robot);
  move_parameter = move_para(-current_pose.theta, -current_pose.y, current_pose.x, -goal_path.y, goal_path.x);
  Move.setAngle(move_parameter.angle);
  Move.setLength(move_parameter.distance);
  ROS_INFO("move to the middle of the path===================");

  // court: x:middle y:a
  Move.goal_x = middle;
  Move.goal_y = a;
  Move.calculate();
  //Move.beginMove();

  // Turn to the other side of the court
  Move.setAngle(angle_c_o - current_pose.theta);
  Move.setLength(0);
  ROS_INFO("turn to the other side of the court===================");
  Move.beginMove();

  while(Move.flag_3 == true)
  {
    ros::spinOnce;
    move_rate.sleep();
  }

/////////////////////// Give angelina detect_done signal!! ////////////////////////////

  msgt.detect_done = true;
  Move.pub_signalrobot.publish(msgt);

/////////////////////////////////////////////////////////////////////////////////////



  ///////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////
  //GAME BEGINS!!



/////////////////////// Wait for angelina game start signal!! ////////////////////

  while(Move.flag_2 == false)
  {
    ROS_INFO("wait for game_begin signal!!");
    msgt.detect_done = true;
    Move.pub_signalrobot.publish(msgt);
    ros::spinOnce();
    move_rate.sleep();
  }

  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////Angelina gives color back! ///////////////////////
  if (Move.flag_color-1 >= 0)
  {
      Move.color_code = Move.flag_color-1;
  }

  Move.which_func = 5;

/////////////////////////////////////////////////////////////////////////////

  MatrixXd ball_coord;
  bool found_ball;
  double move_distance_x, move_distance_y;
  MatrixXd goal_coordinate(3,2);
  bool start_from; //0:start to search the ball from x=0, 1:start from x=b;

  Move.setAngle(0);
  Move.setLength(1.2*a);
  ROS_INFO("move to the other side of the court===========================");

  // court: x:midle y:2.2a
  Move.goal_x = middle;
  Move.goal_y = 2.2*a;
  Move.calculate();
  //Move.beginMove();

  // first lidar localization
  for(int score=0; score<3; score++){
      x_robot_old     = x_robot;
      y_robot_old     = y_robot;
      theta_robot_old = theta_robot;
      x_robot         = current_pose.x;
      y_robot         = current_pose.y;
      theta_robot     = current_pose.theta;

      move_angle      = theta_robot - theta_robot_old;
      move_distance_x = (x_robot_old-x_robot)*sin(theta_robot) - (y_robot_old-y_robot)*cos(theta_robot);
      move_distance_y = (x_robot_old-x_robot)*cos(theta_robot) + (y_robot_old-y_robot)*sin(theta_robot);

      lidar_point     = Move.ladarData();
      world           = predict2(coord_1, coord_2, move_angle, -move_distance_x, -move_distance_y, nearby, cal_coordinate(lidar_point, 1), a, b);
      angle_main      = world.angle;
      dx              = world.dx;
      dy              = world.dy;
      angle_c_o       = angle_main + current_pose.theta;
      coord_1         = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
      coord_2         = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);

      if (score == 0){
          if (dx <0.5*b){
              goal_coordinate<<0.43*b, 2.5*a-0.1, 0.5*b, 2.5*a-0.1, 0.57*b, 2.5*a-0.1;
              start_from = 0;
          }
          else{
              goal_coordinate<<0.57*b, 2.5*a-0.1, 0.5*b, 2.5*a-0.1, 0.43*b, 2.5*a-0.1;
              start_from = 1;
          }
          std::cout<<"goal_coordinate"<<std::endl<<goal_coordinate<<std::endl;
      }

      // find the nearst ball===========================================================================================
      found_ball = 0;
      trial = 0;
      while (found_ball == 0){
          if(trial == 0){
              MatrixXd lidar_world_1 = trans_coordinate(cal_coordinate(lidar_point, 1), angle_main, dx, dy, 0, 0);
              ball_coord  = find_ball(lidar_world_1, a, b, start_from);
              std::cout<<"ball_coord"<<std::endl<<ball_coord<<std::endl;

              for (i=0; i<lidar_world_1.rows(); i++) {
                  pts_1.push_back(boost::make_tuple(
                      lidar_world_1(i, 0),
                      lidar_world_1(i, 1)));
                  }
              gp1 << "plot '-' with points title 'world1'\n";
              gp1.send1d(pts_1);
          }

          std::cout<<"Trial "<<trial<<std::endl;
          std::cout<<"move to ball, coordinate = "<<ball_coord.row(trial)<<std::endl;

          coord_struct goal_ball = trans_c_o(ball_coord(trial,0), ball_coord(trial,1), angle_main, dx, dy, theta_robot, x_robot, y_robot);
          move_parameter = move_para(-current_pose.theta, -current_pose.y, current_pose.x, -goal_ball.y, goal_ball.x);
          move_angle    = move_parameter.angle;
          if (move_parameter.distance>0.8){
              move_distance = move_parameter.distance - 0.8;
          }
          else{
              move_distance = 0;
          }
          Move.setAngle(move_angle);
          Move.setLength(move_distance);
          ROS_INFO("turn to the  ball==========================");

          // odom: goal_ball

          Move.beginMove();
          while(Move.flag_3 == true)
          {
            ros::spinOnce;
            move_rate.sleep();
          }


          //RGB================================================================================================================
          ros::Rate move_rate(50);

          Move.which_func = 0;
          Move.ball_iden = 2;
          while(Move.depth_filter_done == 0)
          {
            Move.identify_hockey_depth();
            ros::spinOnce();
            move_rate.sleep();
          }
          if (Move.depth_filter_done == 1)
          {
            Move.identify_hockey();
            ros::spinOnce();
            move_rate.sleep();
          }
          Move.depth_done = 0;
          Move.depth_filter_done = 0;
          Move.which_func = 5;

          if (Move.ball_iden == 1){
              ROS_INFO("FOUND BALL!!!!!!!!!");
              found_ball = 1;
              Move.which_func = 1;
              Move.ball_in_catch = 0;
              while (Move.ball_in_catch == 0){
                // cout << "width_hockey: " << Move.width << endl;
                Move.catchball();
                // ros::spinOnce();
                // move_rate.sleep();
                if (Move.ball_in_catch == 0){
                    ROS_INFO("MISSED BALL, Try again");
                    Move.setLength(-0.3);
                    Move.beginMove();
                    while(Move.flag_3 == true)
                    {
                      ros::spinOnce;
                      move_rate.sleep();
                    }
                }
                else{
                    ROS_INFO("CAUGHT BALL!!!!!!!!! WOW~");
                }

              }
          }
          else{
              ROS_INFO("NOT OUR BALL...");
          }

          trial++;
          // ============================================================================================================================

      }

      //Move to the goal
      coord_struct goal_door = trans_c_o(goal_coordinate(score,0), goal_coordinate(score,1), angle_main, dx, dy, theta_robot, x_robot, y_robot);
      move_parameter = move_para(-current_pose.theta, -current_pose.y, current_pose.x, -goal_door.y, goal_door.x);
      Move.setAngle(move_parameter.angle);
      Move.setLength(move_parameter.distance);
      ROS_INFO("move to the goal==========================");

      // odom goal_door

      Move.goal_x = goal_door.x;
      Move.goal_y = goal_door.y;
      Move.calculate();

      //Move.beginMove();

      Move.setAngle(angle_c_o-current_pose.theta);
      Move.setLength(0);
      Move.beginMove();

      while(Move.flag_3 == true)
      {
        ros::spinOnce;
        move_rate.sleep();
      }

      Move.setAngle(0);
      Move.setLength(-0.3);
      ROS_INFO("go back==========================");
      Move.beginMove();

      while(Move.flag_3 == true)
      {
        ros::spinOnce;
        move_rate.sleep();
      }

      ROS_INFO("score %d",score+1);

    ///////////////////////// Give angelina score !! ///////////////////////////

      msgt.reportgoal = score+1;
      Move.pub_signalrobot.publish(msgt);

/////////////////////////////////////////////////////////////////////////////////

  }

  return 0;
}
