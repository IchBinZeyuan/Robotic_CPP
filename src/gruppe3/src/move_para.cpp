#include <iostream>
#include "move_para.h"
using namespace std;
move move_para(double init_angle, double x1, double y1, double x2, double y2){
    move result;
    double angle;
    double dir_y = y2 - y1;
    double dir_x = x2 - x1;

    if (fabs(dir_y)<1e-5){
        if (dir_x>0){
            angle = -3.1416/2;
        }
        else{
            angle = 3.1416/2;
        }
    }
    else{
        angle = atan(-dir_x / dir_y);
        if (dir_y < 0){
            angle += 3.1416;
        }
    }
    result.angle = init_angle + angle;
    while (result.angle < -3.1416){
        result.angle += 2*3.1416;
    }
    while (result.angle > 3.1416){
        result.angle -= 2*3.1416;
    }

    result.distance = sqrt(pow(dir_x, 2) + pow(dir_y, 2));
    return result;
}
