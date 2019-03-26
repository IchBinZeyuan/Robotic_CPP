#include <iostream>
#include "line_fitting.h"
using namespace Eigen;
fitted_line line_fitting(MatrixXf coord)
{
  std::cout<<"coord = "<<std::endl<<coord<<std::endl;
  fitted_line result;
  float t1=0, t2=0, t3=0, t4=0;
  int count = 0;
  for (int i=0; i < coord.rows(); i++) {
      if(coord(i,0)!= coord(i,0) || coord(i,1)!= coord(i,1)){
        continue;
      }
      t1 += coord(i,0) * coord(i,0);
      t2 += coord(i,0);
      t3 += coord(i,0) * coord(i,1);
      t4 += coord(i,1);
      count++;
  }
  float a = (t3*count - t2*t4) / (t1*count - t2*t2);
  float b = (t1*t4 - t2*t3) / (t1*count - t2*t2);
  result.angle = atan(a);
  result.distance = fabs(b) / sqrt(a*a + 1);

  std::cout<<"a = "<<std::endl<<a<<std::endl;
  std::cout<<"b = "<<std::endl<<b<<std::endl;
  std::cout<<"coord.rows() = "<<std::endl<<coord.rows()<<std::endl;

  std::cout<<"result.angle = "<<std::endl<<result.angle<<std::endl;
  std::cout<<"result.distance = "<<std::endl<<result.distance<<std::endl;
  return result;

}
