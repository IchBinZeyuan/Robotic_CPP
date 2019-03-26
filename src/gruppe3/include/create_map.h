
#ifndef FIND_PFOSTEN_CREATE_MAP_H
#define FIND_PFOSTEN_CREATE_MAP_H

#include <Eigen/Dense>
#include "lidar_main.h"
#include <cmath>

playground create_map(Eigen::MatrixXd coord_1, Eigen::MatrixXd coord_2, double tangent_ortho, double tangent_main, double a, double b);


#endif //FIND_PFOSTEN_CREATE_MAP_H
