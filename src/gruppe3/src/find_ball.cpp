#include <iostream>
#include "find_ball.h"
using namespace Eigen;
using namespace std;

MatrixXd find_ball(MatrixXd lidar, double a, double b, bool start_from)
{
    int i, j, ii;
    double edge = 0.15;
    double xx, yy;
    double max_distance = 0;
    MatrixXd ball_coord = MatrixXd::Zero(lidar.rows(), 2);
    ii = 0;
    for (i=0; i<lidar.rows(); i++){
        if (lidar(i,0)>edge && lidar(i,0)<b-edge && lidar(i,1)>1.5*a-edge && lidar(i,1)<2*a+edge ){
            ball_coord.row(ii) = lidar.row(i);
            ii++;
        }
    }
    MatrixXd result = ball_coord.topRows(ii);
    for (i=0; i<ii-1; i++ ){
        for (j=0; j<ii-i-1; j++){
            if ((result(j,0) > result(j+1,0) && start_from==0) || (result(j,0) < result(j+1,0) && start_from==1) ){
                xx = result(j,0);
                yy = result(j,1);
                result(j,0)   = result(j+1,0);
                result(j,1)   = result(j+1,1);
                result(j+1,0) = xx;
                result(j+1,1) = yy;
            }
        }
    }
    return result;

}
