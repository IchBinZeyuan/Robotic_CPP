#ifndef FIND_PATH_H
#define FIND_PATH_H

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

double find_path(Eigen::MatrixXd lidar, double a, double b, double origin_y);

#endif //FIND_PATH_H
