#include <iostream>
#include "find_path.h"
using namespace Eigen;
using namespace std;

double find_path(MatrixXd lidar, double a, double b, double origin_y)
{
    int i, j, ii;
    double edge = 0.3;
    double max_distance = 0;
    double evan;
    double x_middle = 0.0;
    VectorXd court_points1 = VectorXd::Zero(lidar.rows());
    court_points1(0) = edge;
    ii = 1;
    for (i=0; i<lidar.rows(); i++){
        if (lidar(i,0)>edge && lidar(i,0)<b-edge && lidar(i,1)>origin_y && lidar(i,1)<2.7*a ){
            court_points1(ii) = lidar(i, 0);
            ii++;
        }
    }
    court_points1(ii) = b-edge;
    VectorXd court_points2 = court_points1.head(ii+1);

    for (i=0; i<ii; i++ ){
        for (j=0; j<ii-i; j++){
            if (court_points2(j) > court_points2(j+1)){
                evan = court_points2(j);
                court_points2(j) = court_points2(j+1);
                court_points2(j+1) = evan;
            }
        }
    }
    // std::cout<<"court_points = "<<std::endl<<court_points2<<std::endl;

    for (i=0; i<ii; i++){
        if (court_points2(i+1)-court_points2(i) > max_distance){
            x_middle     = (court_points2(i+1)+court_points2(i))/2;
            max_distance = court_points2(i+1)-court_points2(i);
            // std::cout<<"x_middle = "<<x_middle<<"  max_distance = "<<max_distance<<"  i = "<<i<<std::endl;
        }
    }
    return x_middle;

}
