#include <iostream>
#include "cal_coordinate.h"
#include "clear_average.h"
using namespace Eigen;
MatrixXd cal_coordinate(VectorXd ranges, bool clear)
{
    MatrixXd coord = MatrixXd::Zero(ranges.size(), 4);
    MatrixXd coord_o;
    int ii = 0;
    double angle_min = -3.12413907051;
    double angle_max = 3.14159274101;
    double angle_increment = (angle_max - angle_min)/360;
    for (int i=0; i<ranges.size(); i++){
        if(ranges(i) != 0){
            coord(ii,3) = ranges(i);
            coord(ii,2) = angle_min + (i%360)*angle_increment;
            coord(ii,0) = coord(ii,3) * sin(coord(ii,2));
            coord(ii,1) = coord(ii,3) * -cos(coord(ii,2));
            ii++;
        }
    }

    if (clear){
        coord_o = clear_average(coord.topRows(ii), 0.1);
    }
    else{
        coord_o = coord.topRows(ii);
    }
    return coord_o;
}
