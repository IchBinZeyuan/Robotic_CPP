#include <iostream>
#include "trans_x_y.h"

// dx,dy: move after turning, dx2,dy2: move before turning
//type:1: court-->odom
//type:11, 12: court-->odom
//type:11, 12: court-->odom
//type:11, 12: court-->odom

coord_struct trans_x_y(double x, double y, double angle, double dx1, double dy1, double dx2, double dy2)
{
    coord_struct result;
    result.y = -(x+dx2)*sin(angle) + (y+dy2)*cos(angle)+dy1;
    result.x = (x+dx2)*cos(angle) + (y+dy2)*sin(angle)+dx1;

    return result;
}
