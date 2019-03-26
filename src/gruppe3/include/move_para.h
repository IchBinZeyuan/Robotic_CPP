#ifndef MOVE_PARA_H
#define MOVE_PARA_H

#include <cmath>
#include <math.h>
#include <iostream>

struct move{
    double angle;
    double distance;
};
move move_para(double init_angle, double x1, double y1, double x2, double y2);

#endif
