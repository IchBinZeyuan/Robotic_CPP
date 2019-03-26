#ifndef SONG_H
#define SONG_H
#include <QLineEdit>
#include <QListWidget>
#include <QRadioButton>
#include <QTimer>
#include <QWidget>
#include <QMap>
#include "ros/ros.h"
#include "referee.h"

class SONG:public QObject
{
	Q_OBJECT

	public:
		SONG(QObject *parent = 0);
                ~SONG();



	//private:
		QTimer *timer;
                QTimer *timer30;
                QTimer *timer50;
		Referee *referee;
                TeamColor true_color;
                TeamColor false_color;
                TeamColor detected_color;
                double a_default;
                double b_default;
                bool connected;
                bool connect_again;
                bool disconnected;
                bool detection_Start;
                bool trueColorOfTeam;
                bool ab_default;
                bool cd_wrong;
                bool game_Start;
                bool pause_signal;
                bool game_Over;
                double posx,posy;
								

                //methods:
                void sendalive_timer();
                void sendposition_timer();
                int  senddetect_timer();
                void TelltoTeamColor(TeamColor color );
                void Connect(const QString &ip, int port);
		void ReportReady();
                void TellAbRatio(double ratio);
		void ReportGoal();
		void TellEgoPos(double x, double y);
                void ReportDone();
                bool Test();
	public  Q_SLOTS:

                //signale:
                int  slotTellback();
                void slotTellPos();
                void slotSendAlive();
                void slotconnected();
                void slotdisconnected();
                void slotdetectionStart();
                void slotgameStart();
                void slotgetTruecolor(TeamColor color);
                void slotgameOver();
                void slotstopMovement();
                void slotabValues(double a, double b);




};

#endif /* SONG_H */
