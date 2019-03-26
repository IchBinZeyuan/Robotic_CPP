#ifndef FIND_PFOSTEN_SORT_LINES_H
#define FIND_PFOSTEN_SORT_LINES_H

#include <Eigen/Dense>
#include <cmath>
Eigen::MatrixXd sort_lines(Eigen::MatrixXd coord_i, double A_main, double B_main, double C_main, double sort_th, double tangent_main, int sign, double dense_th);

#endif //FIND_PFOSTEN_SORT_LINES_H
