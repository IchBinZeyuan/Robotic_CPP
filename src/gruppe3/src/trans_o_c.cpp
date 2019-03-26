#include <iostream>
#include "trans_o_c.h"
#include "trans_x_y.h"

// dx,dy: move after turning, dx2,dy2: move before turning
//type:1: court-->odom



coord_struct trans_o_c(double x, double y, double angle1, double dx1, double dy1, double angle2, double dx2, double dy2)
{
  coord_struct robot, result;
  robot  = trans_x_y(-y, x, angle2, 0, 0, dy2, -dx2);
  result = trans_x_y(robot.x, robot.y, angle1, dx1, dy1, 0, 0);

  std::cout<<"robot coordinate: "<<robot.x<<"  "<<robot.y<<std::endl;
  std::cout<<"odom coordinate: "<<result.x<<"  "<<result.y<<std::endl;
  return result;
}
