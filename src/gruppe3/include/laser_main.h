#ifndef FIND_PFOSTEN_LASER_MAIN_H
#define FIND_PFOSTEN_LASER_MAIN_H

#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <utility>
#include <math.h>
#include <iostream>
#include <stdio.h>

struct playground{
    Eigen::MatrixXd coord_1, coord_2;
    double origin_x, origin_y;
    double angle, angle_turn;
    double d1, d2;
    double dx, dy;
    bool success;
};
playground laser_main(Eigen::VectorXd ranges, bool full_map);

#endif
