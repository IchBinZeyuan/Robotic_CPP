#ifndef TRANS_X_Y_H
#define TRANS_X_Y_H

#include <cmath>
struct coord_struct{
    double x,y;
};

coord_struct trans_x_y(double x, double y, double angle, double dx1, double dy1, double dx2, double dy2);
#endif
