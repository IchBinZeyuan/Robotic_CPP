#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include  <QObject>
#include "referee.h"
#include "SONG.h"
#include "ros/ros.h"

     SONG::SONG(QObject *parent) :QObject(parent),referee(0)
{
     referee = new Referee((3));
     bool connected = false;
     bool connect_again = false;
     bool disconnected = false;
     bool detection_Start = false;
     bool trueColorOfTeam = false;
     bool ab_default = false;
     bool cd_wrong=false;
     bool game_Start = false;
     bool pause_signal = false;
     bool game_Over = false;

     QObject::connect(referee, SIGNAL(disconnected()), this, SLOT(slotdisconnected()));
     QObject::connect(referee, SIGNAL(connected()), this, SLOT(slotconnected()));
     QObject::connect(referee, SIGNAL(detectionStart()), this, SLOT(slotdetectionStart()));
     QObject::connect(referee, SIGNAL(gameStart()), this, SLOT(slotgameStart()));
     QObject::connect(referee, SIGNAL(trueColorOfTeam(TeamColor)), this, SLOT(slotgetTruecolor(TeamColor)));
     QObject::connect(referee, SIGNAL(gameOver()), this, SLOT(slotgameOver()));
     QObject::connect(referee, SIGNAL(stopMovement()), this, SLOT(slotstopMovement()));
     QObject::connect(referee, SIGNAL(abValues(double,double)), this, SLOT(slotabValues(double,double)));

}

     SONG::~SONG()
{
     delete referee;
}

bool SONG::Test()
{
int k=0;int t=0;
for (k=0;k<=1000000000;k++)
{ for (t=0;t<900000000;t++){}
    if (k%300000000==0)
    {std::cout << " k= " << k<< std::endl;}
    if(k==1000000000)
    {std::cout << " finished " <<  std::endl;}
return true;
}
//robot.next=Robot.done;
}

//connect to Angelina
void SONG::Connect(const QString &ip, int port)
{

     referee->connectToServer(ip,port);
     connected = true;connect_again = false;
}

//tell Angelina that we are ready
void SONG::ReportReady()
{
     referee->reportReady();
}

//tell Angelina our detected color
void SONG::TelltoTeamColor(TeamColor color)
{
     ROS_INFO(" we have tell a color! ");
     referee->tellTeamColor(color);
}

//tell Angelina our A/B ratio
void SONG::TellAbRatio(double ratio)
{
     referee->tellAbRatio(ratio);

     ROS_INFO(" we have detected a,b gesendet! ");
}

//tell Angelina the goal
void SONG::ReportGoal()
{
     referee->reportGoal();
}

//tell Angelina an Alive signal
void SONG::slotSendAlive()
{
     referee->sendAlive();
}

//tell Angelina our latest position
void SONG::TellEgoPos(double x, double y)
{
     ROS_INFO(" tell our latest position: ");
     referee->tellEgoPos(10, 10);
}

void SONG::slotTellPos()
{
     referee->tellEgoPos(posx, posy);
}

int  SONG::slotTellback()
{
     referee->tellEgoPos(7, 7);
     return 1;
}

void SONG::sendalive_timer()
{
     QTimer *timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(slotSendAlive()));
     timer->start(10000);
}

void SONG::sendposition_timer()
{
     QTimer *timer30 = new QTimer(this);
     connect(timer30, SIGNAL(timeout()), this, SLOT(slotTellPos()));
     timer30->start(5000);
     //timer30->setSingleShot(true);
}

int  SONG::senddetect_timer()
{
     int c=0;
     QTimer *timer50 = new QTimer(this);
     QObject::connect(timer50, SIGNAL(timeout()), this, SLOT(slotTellback()));
     c= slotTellback();
     timer50->start(7000);timer50->setSingleShot(true);
     ROS_INFO(" nmxbvnx ");
     return c;
}
//void SONG::slotToggleAliveTimer(bool autotransmit)
//{
//if (autotransmit)
//		aliveTimer->start(20000);
//	else
//		aliveTimer->stop();
//}


//tell Angelina we are done
void SONG::ReportDone()
{
     referee->reportDone();
}

//Signale:
//Receive signal that we are disconnected
void SONG::slotconnected()
{
     ROS_INFO(" we are connect! ") ;
     connected = true;
}

//Receive signal that we are disconnected
void SONG::slotdisconnected()
{
     disconnected = true;
     ROS_INFO(" we are disconnected! ") ;
     //referee->slotDisconnected();
}

//Receive signal to start the detection
void SONG::slotdetectionStart()
{
     detection_Start= true;
     pause_signal=false;
}

//Receive the a-default  value and b-default value
void SONG::slotabValues(double a, double b)
{
     ab_default = true;
     a_default = a;
     b_default = b;
     //std::cout<<" a_default= "<<endl;
     std::cout << " a_default= " << a_default << std::endl;
     std::cout << " b_default= " << b_default << std::endl;
     ROS_INFO(" we have true a,b received! ") ;
}

//Receive game started signal
void SONG::slotgameStart()
{
     disconnected=false;
     detection_Start=false;
     game_Start=true;
     pause_signal=false;
     //changeStatus(status_select_target);
}

//Receive the true data for our team color
void SONG::slotgetTruecolor(TeamColor color)
{
     if (color == blue)
    {
     true_color = blue;
     false_color = yellow;

    }
     else
    {
     true_color = yellow;
     false_color = blue;
    }
     if (detected_color != color)
    {
     cd_wrong = true;
    }
}

// Receive a gameover signal
void SONG::slotgameOver()
{
     game_Over=true;
}

// Receive a pause signal
void SONG::slotstopMovement()
{
     pause_signal=true;
}
