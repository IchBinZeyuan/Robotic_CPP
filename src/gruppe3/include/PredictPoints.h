//
// Created by 刘一鸣 on 2018/12/21.
//

#ifndef FIND_PFOSTEN_PREDICTPOINTS_H
#define FIND_PFOSTEN_PREDICTPOINTS_H

#include "find_ortho.h"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "lidar_main.h"
playground PredictPoints(Eigen::Matrix<double, 2, Eigen::Dynamic> datagroup1, Eigen::Matrix<double, 2, Eigen::Dynamic> datagroup2, double theta, double a_pre);
#endif //FIND_PFOSTEN_PREDICTPOINTS_H
