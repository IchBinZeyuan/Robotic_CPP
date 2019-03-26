#include <iostream>
#include "trans_c_o.h"


coord_struct trans_c_o(double x, double y, double angle1, double dx1, double dy1, double angle2, double dx2, double dy2){
    coord_struct robot_rot, robot, result;
    robot = trans_x_y(x, y, -angle1, 0, 0, -dx1, -dy1);
    robot_rot = trans_x_y(robot.x, robot.y, -angle2, 0, 0, 0, 0);
    result.x = dx2 + robot_rot.y;
    result.y = dy2 - robot_rot.x;
    std::cout<<"robot coordinate: "<<robot.x<<"  "<<robot.y<<std::endl;
    std::cout<<"odom coordinate: "<<result.x<<"  "<<result.y<<std::endl;
    return result;
}
