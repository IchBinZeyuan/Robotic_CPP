#include "ros/ros.h"
#include "std_msgs/String.h"
#include <QApplication>
#include "SONG.h"
#include <iostream>
#include <cstdlib>
#include <nav_msgs/Odometry.h>
#include "robottest/signal_robot.h"
#include "robottest/signal_transfer.h"
enum State {
        Robot_init,     // initial state for Robot
        Robot_connect,  // the state that connected to Angelina
        Robot_wait_d,   // the state that Robot waits for detection start signal
        Robot_d,        // the state that Robot detectes a, b and team color
        Robot_wait_g,   // the state that Robot waits for game start signal
        Robot_g,        // the state that Robot start to play hocky.
        Robot_done,     // the state that Robot finished the game.
        Robot_stop      // the state that Robot has been stoped.
};

struct Robot_state
{
        State now;      //the latest state for Robot;
        State next;     //the next state for Robot
        State temp;
        };

using namespace std;int flag=0;
//void sub_signaltransferCallback(const robottest::signal_transfer::ConstPtr& msgr)
//{

//}
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
        ros::init(argc, argv, "testconnect");	//initialed the Ros_node
	ros::NodeHandle nh;
  //      ros::Publisher pub_signalrobot = nh.advertise<robottest::signal_robot>("signal_robottopic", 1);
    //    ros::Subscriber sub_signaltranfer = nh.subscribe("signal_transfertopic", 1, sub_signaltransferCallback);
      //  robottest::signal_robot msgt;
       // msgt.abratio = 0.5;   // float64  a/b_ratio;
       // msgt.detectcolor = 0; // int8     detectcolor;
        //msgt.detect_done = true;   // bool     detection done;
       // msgt.reportgoal = 1;       // int8     reportgoal = {0,1,2,3};
       // msgt.odometrie_1 = 1.0;          // float64  odometrie_1
       // msgt.odometrie_2 = 2.0;          // float64  odometrie_2
       // msgt.odometrie_3 = 3.0;           // float64  odometrie_3
        //pub_signalrobot.publish(msgt);

        double a=4.0;double b=2.25;int i=0;int j=0;
        //TeamColor tColour=blue;
        //TeamColor t_color=yellow;
        TeamColor t_color=yellow;
        //TeamColor false_color=blue;
        //TeamColor detected_color=yellow;
        //TeamColor wrong_color=blue;

        SONG angelina;  //defined the Class named "angelina" to communicate with Angelina;
        Robot_state robot;    //defined the State of Robot;
        //angelina.referee = new Referee((2));
        angelina.connected = false;
        angelina.disconnected = false;
        angelina.detection_Start = false;
        angelina.trueColorOfTeam = false;
        angelina.cd_wrong=false;
        angelina.ab_default = false;
        angelina.game_Start = false;
        angelina.pause_signal = false;
        angelina.game_Over = false;

        //angelina.Connect("127.0.0.1", 10000);
        robot.next = Robot_connect;

        //angelina.slotTruecolor(t_color);
        //angelina.detected_color=blue;
        //angelina.TelltoTeamColor(angelina.detected_color);
        //angelina.TellAbRatio(0);
        //angelina.slotReportDone();
        angelina.sendalive_timer();
        //angelina.sendposition_timer();
        //angelina.senddetect_timer();
        //testgia.slotTellEgoPos(10.0,10.0);

        ros::Rate rate(1);
while (ros::ok())
{
        app.processEvents();
        if (angelina.pause_signal)
        {
            robot.next = Robot_stop;
            angelina.pause_signal = false;
        }
        if (angelina.pause_signal)
        {
            robot.next = Robot_stop;
            angelina.pause_signal = false;
        }
        switch (robot.next)
        {
           //case Robot_INIT:
           //{
           //angelina.slotConnect();
           // }
            case Robot_connect:
           {
                 robot.now = Robot_connect;
                 // Check if the connection is established;
                 if (angelina.connected)
                {
                 ROS_INFO(" Angelina connected~");
                 //send ready signal to Angelina;
                 angelina.ReportReady();
                 ROS_INFO(" Angelina reportready~");
                 //save the state of Robot and go to next state;
                 robot.next = Robot_wait_d;
                }
                  else
                {
                 angelina.Connect("127.0.0.1", 10000);
                 angelina.connected=true;
                 ROS_INFO(" Angelina connected again~");
                 //send ready signal to Angelina;
                 angelina.ReportReady();
                 ROS_INFO(" Angelina reportready~");
                 //save the state of Robot and go to next state;
                 robot.next = Robot_wait_d;
                }
            break;
           }
            case Robot_wait_d:
           {
                 robot.now = Robot_wait_d;
                 ROS_INFO(" We are waiting for detect start~ ");
                // pub_signalrobot.publish(msgt);
                 //angelina.detection_Start = true;
                 //if (i==1)
                //{
                 //flag=angelina.senddetect_timer();
                 //flag = 1;
                 //if (flag==1)// {robot.next = Robot_wait_g;}
                //}
                 //if (flag==1)
                 //{i=0;flag=0;}
                 // Check if the detection_Start signal;
                 if (angelina.detection_Start)
                {
                 ROS_INFO(" detection started~ ");
                 // detect_run=true; if (detect_run){ detection();}if                                           //检测a,b,color;
                 //send detected a,b and team color;
                 //angelina.slotTellTeamColor( );
                 //angelina.slotTellAbRatio(5);
                 //save the state of Robot and go to next state;
                 i++;
                 angelina.detected_color=blue;
                 angelina.TelltoTeamColor(angelina.detected_color);
                // if (i==1)
             {
                 if (angelina.cd_wrong)
                {
                 ROS_INFO(" color wrong~ ");
                 angelina.detected_color = angelina.true_color;
                 angelina.cd_wrong = false;                                          //tell true color
                 ROS_INFO(" color corrected~ ");
                }
                 angelina.TellAbRatio(0.5);
                 if (angelina.ab_default)
                {
                 a = angelina.a_default;
                 b = angelina.a_default;
                 angelina.ab_default = false;                                                                   //tell true a,b
                 //angelina.ab_ready = false;
                 ROS_INFO(" ab received~ ");
                }
              }
                 robot.next = Robot_wait_g;
                 angelina.detection_Start = false;
                 ROS_INFO(" detection finished~ ");
                }
            break;
           }

            case Robot_wait_g:
           {
                 ROS_INFO(" we are waiting for gamestart! ");
                 robot.now = Robot_wait_g;

                 // Check if the true a,b and team color, which told by Angelina;
                 //angelina.game_Start = true;
                 // receive the game_Start signal;
                 if (angelina.game_Start)
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
                ROS_INFO(" playing Game~ ");
                j++;
                                //push the ball;if we finished,send reportdone;
                if(j==1)
               {
                angelina.sendposition_timer();
                //angelina.ReportGoal();
                ROS_INFO(" first ball finished ~ ");
                //angelina.ReportGoal();
                ROS_INFO(" second ball finished ~ ");
                //angelina.ReportGoal();
                ROS_INFO(" third ball finished ~ ");
               }
                robot.now = Robot_g;
                //robot.next = Robot_done;
            break;
           }

            case Robot_stop:
           {
                 // If Angelina calls stop, we call the currently working node to stop.
                 ROS_INFO(" stop move ~");
                 robot.temp = robot.now;
                {
                 // Once Angelina resumes the game, we call the lately working node to start his work again.
                 if (angelina.game_Start)
                {
                 robot.now = Robot_stop;
                 robot.next = robot.temp;
                }
                 else if (angelina.detection_Start)
                {
                 ROS_INFO(" Robot restart~ ");
                 robot.now = Robot_stop;
                 robot.next = robot.temp;
                }
           }
            break;
           }
            case Robot_done:
           {
                 ROS_INFO_STREAM(" game finished! ");
                 angelina.ReportDone();
            break;
           }
            default:
           {
            break;
           }
        }

        ros::spinOnce();
        rate.sleep();
}



        return app.exec();
}
