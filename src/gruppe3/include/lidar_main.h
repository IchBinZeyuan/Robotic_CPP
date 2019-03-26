#ifndef LIDAR_MAIN_H
#define LIDAR_MAIN_H

#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <utility>
#include <math.h>
#include <iostream>
#include <stdio.h>

struct playground{
    Eigen::MatrixXd coord_1, coord_2;
    double a, b;
    double angle, angle_turn;
    double d1, d2;
    double dx, dy;
    bool success;
};
playground lidar_main(Eigen::MatrixXd coord_l, bool full_map, double dist2line1, double dist2line2);

#endif
