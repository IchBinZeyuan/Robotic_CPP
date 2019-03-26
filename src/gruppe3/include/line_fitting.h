#ifndef LINE_FITTING_H
#define LINE_FITTING_H

#include <Eigen/Dense>
#include <cmath>

struct fitted_line{
    double angle;
    double distance;
};
fitted_line line_fitting(Eigen::MatrixXf coord);

#endif
