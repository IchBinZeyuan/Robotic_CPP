#ifndef FIND_PFOSTEN_FIND_ORTHOGONAL2_H
#define FIND_PFOSTEN_FIND_ORTHOGONAL2_H

#include <Eigen/Dense>
#include <cmath>
struct twin{
    Eigen::MatrixXd coord_1, coord_2;
};
twin find_ortho(Eigen::MatrixXd coord_i_pos, Eigen::MatrixXd coord_i_neg, double ortho_th, double tangent_ortho, bool sort);


#endif //FIND_PFOSTEN_FIND_ORTHOGONAL2_H
