#ifndef PREDICT_2_H
#define PREDICT_2_H

#include <iostream>
#include <Eigen/Dense>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include "lidar_main.h"
playground predict2(Eigen::MatrixXd coord_1, Eigen::MatrixXd coord_2, double angle, double distance_x, double distance_y, double lidarthreshold, Eigen::MatrixXd lidarpoints, double a, double b);

#endif
