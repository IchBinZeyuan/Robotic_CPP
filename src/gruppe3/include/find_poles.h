#ifndef FIND_POLES_H
#define FIND_POLES_H

#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include "lidar_main.h"
playground find_poles(Eigen::MatrixXd coord_i, double colinear_th, double dense_th, double div_th, double ortho_th, int direction, double a, double b);

#endif //FIND_PFOSTEN_FIND_COLINEAR_H
