#ifndef TRANS_COORDINATE_H
#define TRANS_COORDINATE_H

#include <Eigen/Dense>
#include <cmath>

Eigen::MatrixXd trans_coordinate(Eigen::MatrixXd coord_i, double angle, double dx, double dy, double dx2, double dy2);
#endif
