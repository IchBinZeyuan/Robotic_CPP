#include <iostream>
#include "trans_coordinate.h"
using namespace Eigen;
// dx,dy: move after turning, dx2,dy2: move before turning
MatrixXd trans_coordinate(MatrixXd coord_i, double angle, double dx, double dy, double dx2, double dy2)
{
    MatrixXd coord_o = MatrixXd::Zero(coord_i.rows(), 2);
    for (int i=0; i<coord_i.rows(); i++){
        coord_o(i,0) = (coord_i(i,0)+dx2)*cos(angle) + (coord_i(i,1)+dy2)*sin(angle)+ dx ;
        coord_o(i,1) = -(coord_i(i,0)+dx2)*sin(angle) + (coord_i(i,1)+dy2)*cos(angle) + dy;
    }
    return coord_o;
}
