#include "ros/ros.h"
#include "std_msgs/String.h"
#include <QApplication>
#include "SONG.h"
#include <iostream>
#include <cstdlib>
#include "std_msgs/Int8.h"
#include "std_msgs/Int16.h"
#include "robottest/signal_transfer.h"
#include "robottest/signal_robot.h"
#include <geometry_msgs/Pose2D.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
enum State {
        Robot_init,     // initial state for Robot
        Robot_connect,  // the state that connected to Angelina
        Robot_wait_d,   // the state that Robot waits for detection start signal
        Robot_d,        // the state that Robot detectes a, b and team color
        Robot_wait_g,   // the state that Robot waits for game start signal
        Robot_g,        // the state that Robot starts to play hocky.
        Robot_done,     // the state that Robot finished the game.
        Robot_stop      // the state that Robot has been stoped.
};

struct Robot_state
{
        State now;      // the latest state for Robot;
        State next;     // the next state for Robot
        State temp;
        };

using namespace std;bool df=false;int gf=0;int t=0;int goal1;int goal2;int goal3;
float ab=0;int c;int goal=0;
geometry_msgs::Pose2D odom1;
geometry_msgs::Pose2D odom2;
geometry_msgs::Pose2D current_pose;

float robot_x,robot_y,result_x,result_y;


void sub_signalrobotCallback(const robottest::signal_robot::ConstPtr& msg)
{
      if (msg->abratio > 0.000001){ab = msg->abratio;}
      if (msg->detectcolor > 0){c = msg->detectcolor;}
      if (msg->detect_done){df = true;}
      //std::cout << " message= " << msg->data << std::endl;
      switch (msg->reportgoal)
      {
        case 0: { break; }
        case 1: {  goal = 1;break; }
        case 2: {  goal = 2;break; }
        case 3: {  goal = 3;break; }
        default:{break;}
        }
      { odom1 = msg->odometrie_1; odom2 = msg->odometrie_2; }

}

void odomCallback(const nav_msgs::OdometryConstPtr& msg)
{
 current_pose.x = msg->pose.pose.position.x;
 current_pose.y = msg->pose.pose.position.y;
 tf::Quaternion q(
     msg->pose.pose.orientation.x,
     msg->pose.pose.orientation.y,
     msg->pose.pose.orientation.z,
     msg->pose.pose.orientation.w);
 tf::Matrix3x3 m(q);
 double roll, pitch, yaw;
 m.getRPY(roll, pitch, yaw);
 current_pose.theta = yaw;
 //ROS_INFO("odom x,y,theta %f,%f,%f",current_pose.x,current_pose.y,current_pose.theta);
}

int  main(int argc, char *argv[])
{
	QApplication app(argc, argv);
  ros::init(argc, argv, "State_maschine_group3");	// initialed the Ros_node
	ros::NodeHandle n;
  ros::Publisher pub_signal_tranfer = n.advertise<robottest::signal_transfer>("signal_transfertopic", 10);
  ros::Subscriber sub_signalrobot = n.subscribe("signal_robottopic", 1, sub_signalrobotCallback);
  ros::Subscriber odom_sub = n.subscribe("odom",1,odomCallback);
  robottest::signal_transfer msgg;
        //msgg.detectionstart = false;       // bool detect_start signal
        //msgg.gamestart = false;            // bool game_start signal
        //msgg.stop = false;                 // bool stop_signal
        //msgg.true_a = float(0.0);          // float default_a
       // msgg.true_b = float(0.0);          // float default_b
        //msgg.T_color = 0;                  // int8 default_color 1 yellow, 2 blue

  double a=4.0;double b=2.25;int detect=0;int game=0;int gamedone=0;int stop=0;

        //TeamColor tColour=blue;
        //TeamColor t_color=yellow;
        //TeamColor t_color=yellow;
        //TeamColor false_color=blue;
        //TeamColor detected_color=yellow;
        //TeamColor wrong_color=blue;

  SONG angelina;         // defined the Class named "angelina" to communicate with Angelina;
  Robot_state robot;     // defined the State of Robot;
  angelina.posx = 1.0;angelina.posy = 2.0;
  angelina.connected = false;
  angelina.connect_again = false;
  angelina.disconnected = false;
  angelina.detection_Start = false;
  angelina.trueColorOfTeam = false;
  angelina.cd_wrong = false;
  angelina.ab_default = false;
  angelina.game_Start = false;
  angelina.pause_signal = false;
  angelina.game_Over = false;

  angelina.Connect("127.0.0.1", 10000);
  robot.now = Robot_init;//robot.next = Robot_init;
  robot.next = Robot_connect;

  //angelina.slotgetTruecolor(t_color);
  //angelina.detected_color=blue;
  //angelina.TelltoTeamColor(angelina.detected_color);
  //angelina.TellAbRatio(0);
  //angelina.slotReportDone();


  //angelina.senddetect_timer();
  ros::Rate rate(20);
  while ( ros::ok() )
  {
    app.processEvents();
    if ( angelina.pause_signal )
    {
      robot.next = Robot_stop;
      angelina.pause_signal = false;
    }
    if ( angelina.disconnected )
    {
      robot.next = Robot_done;
      angelina.disconnected = false;
    }
    if ( angelina.game_Over )
    {
      robot.next = Robot_done;
      ROS_INFO(" GAME OVER~ ");
      angelina.game_Over = false;
    }
    switch  ( robot.next )
    {
        case Robot_connect:
       {
             robot.now = Robot_connect;
             // check if the connection is established;
             if ( angelina.connected && !angelina.connect_again )
            {
             ROS_INFO(" Angelina connected~");
             // send ready signal to Angelina;
             angelina.ReportReady();
             ROS_INFO(" Angelina reportready~");
             // save the state of Robot and go to next state;
             robot.next = Robot_wait_d;
            }
             else if ( angelina.connect_again && !angelina.connected )
            {
             angelina.Connect("127.0.0.1", 10000);
             ROS_INFO(" Angelina connected again~");
            }
        break;
       }
        case Robot_wait_d:
       {
             robot.now = Robot_wait_d;
             ROS_INFO(" We are waiting for detect start~ ");
             // angelina.detection_Start = true;

             if (angelina.detection_Start )
            {
             ROS_INFO(" detection started~ ");
             robot.next = Robot_d;
            }

        break;
       }
        case Robot_d:
       {
             robot.now = Robot_d;detect++;

             if ( detect == 1 )
             {//df = angelina.Test();
           msgg.detectionstart = true;
            pub_signal_tranfer.publish(msgg);                              // detect start
             ROS_INFO(" we have a detect messeage published! ");

             }
             if (ab > 0.000001)
             {ROS_INFO(" we have a detect ab published! ");t++;
             if ( t == 1 )
             {angelina.TellAbRatio( ab );}                        // tell detected a,b
                if ( angelina.ab_default )
                {
               msgg.true_a  = float(angelina.a_default);
                msgg.true_b  = float(angelina.b_default);
                pub_signal_tranfer.publish(msgg);
               angelina.ab_default = false;
                ROS_INFO(" we have a default ab published! ");


                }

             if ( df == true )
             {
                ROS_INFO(" we have a detect-finished messeage subscribed! ");
                detect = 0;



                robot.next = Robot_wait_g;
                angelina.detection_Start = false;
                ROS_INFO(" detection finished~ ");
             }
             break;
       }

        case Robot_wait_g:
        {
           robot.now = Robot_wait_g;
           ROS_INFO(" we are waiting for gamestart! ");
           // Check if the true a,b and team color, which told by Angelina;
           //angelina.game_Start = true;
           // receive the game_Start signal;
           if ( angelina.game_Start )
           {
           //save the state of Robot and go to next state;
           robot.next = Robot_g;
           angelina.game_Start = false;
           //ROS_INFO(" game started~ ");
           }
        break;
       }

        case Robot_g:
        {
           robot.now = Robot_g;
           game++;
           ROS_INFO(" Gamestart~ ");
           //angelina.sendposition_timer();
           if ( game == 1)
           {angelina.sendalive_timer();
           angelina.sendposition_timer();
           msgg.gamestart = true;
           pub_signal_tranfer.publish(msgg);                              // game start
           ROS_INFO(" we have a gamestart messeage published! ");
           }
           if ( c )
           {

           if (c == 1) {angelina.TelltoTeamColor( blue );}
           if (c == 2) {angelina.TelltoTeamColor( yellow );}
           if (angelina.true_color == blue)
           {msgg.T_color = 1;}
           else{
             msgg.T_color = 0; }
           pub_signal_tranfer.publish(msgg);
             c = 0;    // get the real color
           ROS_INFO(" we have a default color published! ");
           }
           // get the goal_signal
           ros::spinOnce();
           switch ( goal )
           {
             case 0: { break ;}
             case 1: { goal1++;   if ( goal1 == 1 )
                     {angelina.ReportGoal();
                       ROS_INFO(" first ball finished ~ "); break;} }
             case 2: { goal2++;   if ( goal2 == 1 )
                     {angelina.ReportGoal();
                       ROS_INFO(" second ball finished ~ "); break;} }
             case 3: {  goal3++;   if ( goal3 == 1 )
          rate.sleep();
             {angelina.ReportGoal();
                       ROS_INFO("third ball finished ~ ");
                       angelina.ReportDone();} // if we finished,send reportdone
                       robot.next = Robot_done;break;}

                       default:break;
          }

        break;
       }

        case Robot_stop:
       {
         robot.temp = robot.now;
         robot.now = Robot_stop;stop++;
         if ( stop == 1 )
         {
           msgg.stop = true;
           pub_signal_tranfer.publish(msgg);
           ROS_INFO(" we have a stop messeage published! ");
         // If Angelina calls stop, we call the currently working node to stop.
         ROS_INFO(" stop move ~");
         }
            {
           // Once Angelina resumes the game, we call the lately working node to start his work again.
           if ( angelina.game_Start )
          {
           robot.now = Robot_stop;
           robot.next = robot.temp;
          }
           else if ( angelina.detection_Start )
          {
           ROS_INFO(" Robot restart~ ");
           robot.next = robot.temp;
          }
       }
        break;
       }

        case Robot_done:
       {     robot.now = Robot_done;gamedone++;
             if ( gamedone == 1 )
             {ROS_INFO_STREAM(" game finished! ");}

        break;
       }

        default:
       {
        break;
       }
    }
	ros::spinOnce();

	robot_y = -(-current_pose.y+odom2.y)*sin(odom2.theta) + (current_pose.x-odom2.x)*cos(odom2.theta);
  robot_x = (-current_pose.y+odom2.y)*cos(odom2.theta) + (current_pose.x-odom2.x)*sin(odom2.theta);

	result_y = -(robot_x)*sin(odom1.theta) + (robot_y)*cos(odom1.theta)+odom1.y;
  result_x = (robot_x)*cos(odom1.theta) + (robot_y)*sin(odom1.theta)+odom1.x;

  if (angelina.true_color == blue)
  {
    angelina.posx = result_y; angelina.posy= result_x;
  }
  else if(angelina.true_color == yellow)
  {
    angelina.posx = 3*angelina.a_default-result_y; angelina.posy= angelina.b_default - result_x;
  }

  // ros::spinOnce();
  rate.sleep();
}
}
return app.exec();
}
