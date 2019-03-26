#ifndef FIND_PFOSTEN_FIND_TANGENT_H
#define FIND_PFOSTEN_FIND_TANGENT_H

#include <Eigen/Dense>
#include <cmath>

struct line{
    double tangent_main;
    double A_main, B_main, C_main;
    Eigen::MatrixXd coord_main, coord_rest;
    bool success;
};
line find_tangent(Eigen::MatrixXd coord_1, Eigen::MatrixXd coord_2, double colinear_th, double dense_th, double div_th);

#endif //FIND_PFOSTEN_FIND_TANGENT_H
