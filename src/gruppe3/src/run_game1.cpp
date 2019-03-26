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
#include "trans_o_c.h"

using namespace Eigen;
const double PI = 3.14159265358979323846;
using namespace cv;
using namespace std;

geometry_msgs::Pose2D current_pose;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "TurnandGo");
  int i, j, trial,counter;
  Gnuplot gp0, gp1, gp2, gp3, gp4, gp5, gp6;
  vector<boost::tuple<double, double> > pts_0, pts_1, pts_2, pts_3, pts_4, pts_5, pts_6;
  MatrixXd coord_1, coord_2;
  double move_angle, move_distance, angle_main, dx, dy, a, b;
  move move_parameter;
  TurnandGo Move;

  playground world;
  VectorXd lidar_point, lidar_point1, lidar_point2;
  playground result;

  double dist2line_1, dist2line_2;
  double nearby = 0.5;
  double angle_c_o;

  MatrixXd court_coord1, court_coord2, court_coord;
  MatrixXd coord_1_standard(7,2);
  MatrixXd coord_2_standard(7,2);


  float x_odom1, y_odom1, theta_odom1, x_odom2, y_odom2, theta_odom2;



// turn around to find the pillars
  ros::Rate move_rate(50);

  while (Move.pillars_found == 0){
    // ros::Duration(1).sleep();
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

  Move.which_func = 3;
  i = 0;
  while(Move.pillars_found == 1 && i< 500){
    Move.specific_green_rgb();
    Move.green_pillars_depth();
    ros::spinOnce();
    move_rate.sleep();
    i++;
  }
  Move.which_func = 5;

  if (Move.pillars_found == 0){
      while (Move.pillars_found == 0){
        // ros::Duration(1).sleep();
        Move.specific_green_rgb();
        if(Move.pillars_found == 1 ){
          ROS_INFO("FOUND PILLARS!!");
          break;
        }
        else{
          ROS_INFO("DIDNT FIND PILLARS, KEEP TURNING!!");
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
        if (Move.depth_done == 1)
        {
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
  //
  // Move.setAngle(line1.angle);
  // Move.setLength(line1.distance-1);
  // Move.beginMove();
  // lidar_point1 = Move.ladarData();
  // court_coord1 = cal_coordinate(lidar_point1, 1);
  // for(i=0; i<court_coord1.rows(); i++){
  //   court_coord1(i,1) = court_coord1(i,1) - (line1.distance-1);
  // }
  //
  // Move.setAngle(3.1416);
  // Move.beginMove();
  // Move.setLength(line1.distance-1);
  // Move.beginMove();
  // lidar_point2 = Move.ladarData();
  // court_coord2 = cal_coordinate(lidar_point2, 1);
  //
  //
  // dist2line_1 = 3-1.15;
  // dist2line_2 = 1.15;



  Move.setAngle(line1.angle);
  Move.setLength(line1.distance-1.5);

  cout<<"angle = "<<line1.angle <<"distance = "<< line1.distance<<endl;
  ROS_INFO("move to the middle of the court===================");
  Move.beginMove();

  Move.which_func = 5;
  dist2line_1 = 1.65;
  dist2line_2 = 3-1.65;
  // if (Move.pillars_coord.cols() == 1){
  //   dist2line_2 = Move.pillars_coord(1,0)+0.15;
  // }
  // else{
  //   fitted_line line2 = line_fitting(Move.pillars_coord.transpose());
  //   dist2line_2 = line2.distance+0.15;
  // }



  // first lidar localization
  bool success = 0;
  while (success == 0){
      lidar_point = Move.ladarData();
      court_coord = cal_coordinate(lidar_point, 1);
      world = lidar_main(court_coord, 1, dist2line_1, dist2line_2);
      success = world.success;
  }
  coord_1 = world.coord_1;
  coord_2 = world.coord_2;
  cout<<"coord_1 = "<<endl<<coord_1<<endl;
  cout<<"coord_2 = "<<endl<<coord_2<<endl;


  a = world.a;
  b = world.b;
  coord_1_standard<< 0, 0, 0, 0.25*a, 0, a, 0, 1.5*a, 0, 2.0*a, 0, 2.75*a, 0, 3.0*a;
  coord_2_standard<< b, 0, b, 0.25*a, b, a, b, 1.5*a, b, 2.0*a, b, 2.75*a, b, 3.0*a;
  angle_main  = world.angle;
  dx          = world.dx;
  dy          = world.dy;
  coord_1     = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
  coord_2     = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);
  cout<<"new coord_1 = "<<endl<<coord_1<<endl;
  cout<<" new coord_2 = "<<endl<<coord_2<<endl;

  x_odom1 = current_pose.x;
  y_odom1 = current_pose.y;
  theta_odom1 = current_pose.theta;
  coord_struct test_coord1 = trans_c_o(1.5, 2.5, angle_main, dx, dy, theta_odom1, x_odom1, y_odom1);
  coord_struct test_coord2 = trans_o_c(test_coord1.x, test_coord1.y, angle_main, dx, dy, theta_odom1, x_odom1, y_odom1);
  cout<<"test_coord2" << test_coord2.x<<" / "<<test_coord2.y<<endl;


  MatrixXd lidar_world_0 = trans_coordinate(cal_coordinate(lidar_point, 1), angle_main, dx, dy, 0, 0);
  for (int i=0; i<lidar_world_0.rows(); i++) {
          pts_0.push_back(boost::make_tuple(
                  lidar_world_0(i, 0),
                  lidar_world_0(i, 1)));
  }
  gp0 << "plot '-' with points title 'world0'\n";
  gp0.send1d(pts_0);

  move_parameter = move_para(angle_main, dx, dy, b/2.0, a);
  move_angle     = move_parameter.angle - PI;
  while(move_angle > PI){
      move_angle -= 2*PI;
  }
  while(move_angle < -PI){
      move_angle += 2*PI;
  }
  move_distance  = -move_parameter.distance;
  Move.setAngle(move_angle);
  Move.setLength(move_distance);
  ROS_INFO("move to the center of the court===========================");
  Move.beginMove();

// Turn to the color block, and then move to the middle of the path
  lidar_point = Move.ladarData();
  cout<<"trans_coordinate"<<endl;
  MatrixXd raw_lidar_colorblock = cal_coordinate(lidar_point, 1);
  for (int i=0; i<raw_lidar_colorblock.rows(); i++) {
          pts_1.push_back(boost::make_tuple(
                  raw_lidar_colorblock(i, 0),
                  raw_lidar_colorblock(i, 1)));
  }
  gp1 << "plot '-' with points title 'raw_lidar_colorblock'\n";
  gp1.send1d(pts_1);


  world       = predict2(coord_1, coord_2, move_angle, 0, move_distance, nearby, cal_coordinate(lidar_point, 1), a, b);
  cout<<"trans_coordinate finished"<<endl;
  angle_main  = world.angle;
  dx          = world.dx;
  dy          = world.dy;
  coord_1     = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
  coord_2     = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);
  MatrixXd lidar_world_2 = trans_coordinate(cal_coordinate(lidar_point, 1), angle_main, dx, dy, 0, 0);
  for (int i=0; i<lidar_world_2.rows(); i++) {
          pts_2.push_back(boost::make_tuple(
                  lidar_world_2(i, 0),
                  lidar_world_2(i, 1)));
  }
  gp2 << "plot '-' with points title 'world2'\n";
  gp2.send1d(pts_2);


  // Turn to the color block
  move_parameter= move_para(angle_main, dx, dy, dx, 0);
  move_angle    = move_parameter.angle;
  move_distance = 0;
  Move.setAngle(move_angle);
  Move.setLength(move_distance);
  ROS_INFO("turn to the color block===================");
  Move.beginMove();

// Open Camera to identify our color//////////////////////////////////////////
  Move.which_func = 6;
  counter = 0;
  while(ros::ok() && counter < 50){
    Move.team_color();
    ros::spinOnce();
    move_rate.sleep();
    counter++;
  }
  if(Move.color_code){
    cout<<"our team coloris yellow"<<endl;
  }
  else{
    cout<<"our team color is blue"<<endl;
  }
  Move.which_func = 5;




// Turn to the middle of the path
  double middle = find_path(lidar_world_2, a, b, dy);
  move_parameter= move_para(angle_main, dx, dy, middle, a);
  move_angle    += move_parameter.angle;
  while(move_angle > PI){
      move_angle -= 2*PI;
  }
  while(move_angle < -PI){
      move_angle += 2*PI;
  }
  move_distance = move_parameter.distance;
  Move.setAngle(move_parameter.angle);
  Move.setLength(move_distance);
  ROS_INFO("move to the middle of the path===================");
  Move.beginMove();

// Turn to the other side of the court
  success = 0;
  while (success == 0) {
    lidar_point = Move.ladarData();
    world       = predict2(coord_1, coord_2, move_angle, 0, move_distance, nearby, cal_coordinate(lidar_point, 1), a, b);
    success     = world.success;
  }

  lidar_point = Move.ladarData();
  world       = predict2(coord_1, coord_2, move_angle, 0, move_distance, nearby, cal_coordinate(lidar_point, 1), a, b);
  angle_main  = world.angle;
  dx          = world.dx;
  dy          = world.dy;
  coord_1     = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
  coord_2     = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);
  // Turn
  move_parameter= move_para(angle_main, dx, dy, dx, 2*a);
  move_angle    = move_parameter.angle;
  move_distance = 0;
  Move.setAngle(move_angle);
  Move.setLength(move_distance);
  ROS_INFO("turn to the other side of the court===================");
  Move.beginMove();

  //Last lidar calculation===================================================================================


  x_odom1 = current_pose.x;
  y_odom1 = current_pose.y;
  theta_odom1 = current_pose.theta;

  lidar_point = Move.ladarData();
  world       = predict2(coord_1, coord_2, move_angle, 0, move_distance, nearby, cal_coordinate(lidar_point, 1), a, b);
  angle_main  = world.angle;
  dx          = world.dx;
  dy          = world.dy;
  coord_1     = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
  coord_2     = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);
  MatrixXd raw_lidar = cal_coordinate(lidar_point, 1);

  result.coord_1 = coord_1;
  result.coord_2 = coord_2;
  result.a = a;
  result.b = b;
  result.angle_turn = move_angle;



///////////////////////////////////////////////////////////////////////////////////////////////

MatrixXd ball_coord;
bool found_ball;
double move_distance_x, move_distance_y;
MatrixXd goal_coordinate(3,2);
bool start_from;

Move.setAngle(0);
Move.setLength(1.2*a);
ROS_INFO("move to the other side of the court===========================");
Move.beginMove();

x_odom2 = current_pose.x;
y_odom2 = current_pose.y;
theta_odom2 = current_pose.theta;

// find ball
for(int score = 0; score<3; score++){

    move_angle      = theta_odom2 - theta_odom1;
    move_distance_x = (x_odom1-x_odom2)*sin(theta_odom2) - (y_odom1-y_odom2)*cos(theta_odom2);
    move_distance_y = (x_odom1-x_odom2)*cos(theta_odom2) + (y_odom1-y_odom2)*sin(theta_odom2);
    lidar_point     = Move.ladarData();
    move_distance   = 1.2*a;
    world           = predict2(coord_1, coord_2, move_angle, -move_distance_x, -move_distance_y, nearby, cal_coordinate(lidar_point, 1), a, b);


    angle_main  = world.angle;
    dx          = world.dx;
    dy          = world.dy;
    angle_c_o   = angle_main + current_pose.theta;
    coord_1     = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
    coord_2     = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);

    if (score == 0){
        if (dx <0.5*b){
            goal_coordinate<<0.43*b,2.5*a,0.5*b, 2.5*a, 0.57*b, 2.5*a;
            start_from = 0;
        }
        else{
            goal_coordinate<<0.57*b, 2.5*a, 0.5*b, 2.5*a, 0.43*b,2.5*a;
            start_from = 1;
        }
        std::cout<<"goal_coordinate"<<std::endl<<goal_coordinate<<std::endl;
    }

  // loop begins=====================================================================================================
  // for(int score=0; score<3; score++)
  // {
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
        move_parameter= move_para(angle_main, dx, dy, ball_coord(trial,0), ball_coord(trial,1));
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
        Move.beginMove();

        //RGB================================================================================================================
        ros::Rate move_rate(100);
        ros::Rate speed_rate(1000);

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
              }
              else{
                  ROS_INFO("CAUGHT BALL!!!!!!!!! WOW~");
              }

            }
        }
        else{
            ROS_INFO("NOT OUR BALL...");
        }
        x_odom1     = x_odom2;
        y_odom1     = y_odom2;
        theta_odom1 = theta_odom2;
        x_odom2     = current_pose.x;
        y_odom2     = current_pose.y;
        theta_odom2 = current_pose.theta;

        trial++;
        // ============================================================================================================================

    }

    // Calculate the move since the last lidar localization


    coord_struct goal1 = trans_c_o(goal_coordinate(1,0), goal_coordinate(1,1), angle_main, dx, dy, theta_odom1, x_odom1, y_odom1);
    move_parameter= move_para(- current_pose.theta, -current_pose.y, current_pose.x, -goal1.y, goal1.x);
    move_angle    = move_parameter.angle;
    move_distance = move_parameter.distance;
    Move.setAngle(move_angle);
    Move.setLength(move_distance);
    ROS_INFO("move to the goal==========================");
    Move.beginMove();

    Move.setAngle(angle_c_o-current_pose.theta);
    Move.setLength(-0.3);
    ROS_INFO("move to the goal==========================");
    Move.beginMove();

    x_odom1     = x_odom2;
    y_odom1     = y_odom2;
    theta_odom1 = theta_odom2;
    x_odom2     = current_pose.x;
    y_odom2     = current_pose.y;
    theta_odom2 = current_pose.theta;


}


  // lidar_point = Move.ladarData();
  // world       = predict2(coord_1, coord_2, move_angle, 0, move_distance, nearby, cal_coordinate(lidar_point, 1), a, b);
  // angle_main  = world.angle;
  // dx          = world.dx;
  // dy          = world.dy;
  // coord_1     = trans_coordinate(coord_1_standard, -angle_main, 0, 0, -dx, -dy);
  // coord_2     = trans_coordinate(coord_2_standard, -angle_main, 0, 0, -dx, -dy);
  //
  // MatrixXd lidar_world_4 = trans_coordinate(cal_coordinate(lidar_point, 1), angle_main, dx, dy, 0, 0);
  //
  // for (i=0; i<lidar_world_4.rows(); i++) {
  //         pts_4.push_back(boost::make_tuple(
  //                 lidar_world_4(i, 0),
  //                 lidar_world_4(i, 1)));
  //     }
  // gp4 << "plot '-' with points title 'world3'\n";
  // gp4.send1d(pts_4);
  //
  // move_parameter= move_para(angle_main, dx, dy, dx, dy+0.3);
  // move_angle    = move_parameter.angle;
  // move_distance = -move_parameter.distance;
  // Move.setAngle(move_angle);
  // Move.setLength(move_distance);
  // ROS_INFO("goal==========================");
  // Move.beginMove();
  // std::cout<<"****origin_x   = "<<dx<<std::endl;
  // std::cout<<"****origin_y   = "<<dy<<std::endl;
  // std::cout<<"****move_angle = "<<move_angle/3.1416*180<<std::endl;
  // std::cout<<"****move_dist  = "<<move_distance<<std::endl;

// }
  // return result;

  return 0;
}
