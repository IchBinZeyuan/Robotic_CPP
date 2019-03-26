#include <iostream>
#include "predict2.h"
#include "trans_coordinate.h"
#include "find_poles.h"
#include "gnuplot-iostream.h"
#include <vector>


using namespace Eigen;
using namespace std;

playground predict2(MatrixXd coord_1, MatrixXd coord_2, double angle, double distance_x, double distance_y, double lidarthreshold, MatrixXd lidarpoints, double a, double b){
    // std::cout << "coord_1 "<<coord_1.rows()<<"/"<<coord_1.cols()<<std::endl;
    // std::cout << "coord_2 "<<coord_2.rows()<<"/"<<coord_2.cols()<<std::endl;
    int lidarnum = lidarpoints.rows();
    int direction;  // 11:from left to right; 12: right to left; 21: bottom to up; 22:top to bottom
    MatrixXd real_points = MatrixXd::Zero(14, 2);
    MatrixXd real_points_new = MatrixXd::Zero(14, 2);
    MatrixXd lidarpoints_new = MatrixXd::Zero(lidarnum,3);

    real_points.topRows(7) = coord_1.leftCols(2);
    real_points.bottomRows(7) = coord_2.leftCols(2);

    real_points_new = trans_coordinate(real_points, angle, -distance_x, -distance_y, 0, 0);
    cout<<"real_points_new = "<<endl<<real_points_new<<endl;

    if (abs(real_points_new(0,0) - real_points_new(6,0)) > abs(real_points_new(0,1) - real_points_new(6,1))){
        if (real_points_new(0,0) < real_points_new(6,0)){
            direction = 11;
        }
        else{
            direction = 12;
        }
    }
    else{
        if (real_points_new(0,1) < real_points_new(6,1)){
            direction = 21;
        }
        else{
            direction = 22;
        }
    }




    int ii = 0;
    double dist;
    for (int i = 0; i < lidarnum; i++) {
        for (int j = 0; j < 14; j++) {
            dist = fabs(sqrt(pow(lidarpoints(i,0)-real_points_new(j,0),2) + pow(lidarpoints(i,1)-real_points_new(j,1),2)));
            if (dist < lidarthreshold) {
                lidarpoints_new(ii, 0) = lidarpoints(i, 0);
                lidarpoints_new(ii, 1) = lidarpoints(i, 1);
                lidarpoints_new(ii, 2) = j+1;
                ii++;
            }
        }
    }
    cout<<"coordinates = "<<endl<<lidarpoints_new<<endl;

    playground result = find_poles(lidarpoints_new.topRows(ii), 0.1, 0.25, 0.05, 0.08, direction, a, b);

    return result;
}
