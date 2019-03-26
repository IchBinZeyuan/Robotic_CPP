#ifndef FIND_PFOSTEN_FIND_ORTHOGONAL_H
#define FIND_PFOSTEN_FIND_ORTHOGONAL_H

#include <Eigen/Dense>
#include <cmath>
Eigen::MatrixXd find_orthogonal(Eigen::MatrixXd coord_main, Eigen::MatrixXd coord_i, double ortho_th, double tangent_ortho);

#endif //FIND_PFOSTEN_FIND_ORTHOGONAL_H
