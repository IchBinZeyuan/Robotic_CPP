#include <iostream>
#include "clear_area.h"
using namespace Eigen;
playground clear_area(MatrixXd coord_i, double dist2line_1, double dist2line_2, double bias)
{
    std::cout<<"begin to clear area"<<std::endl;
    int i, j, ii, jj;
    playground  result;
    long num = coord_i.rows();
    MatrixXd coord_1 = MatrixXd::Zero(num, 2);
    MatrixXd coord_2 = MatrixXd::Zero(num, 2);
    std::cout<<"num = "<<num<<std::endl;

    ii = 0;
    for (i=0; i<num; i++){
        if(fabs(coord_i(i,0))<=4 && fabs(coord_i(i,1)+dist2line_1)<=bias){
            // std::cout<<"1  i = "<<i<< coord_i.row(i) <<std::endl;
            coord_1(ii,0) = coord_i(i,0);
            coord_1(ii,1) = coord_i(i,1);
            ii++;
        }
    }

    jj = 0;
    for (i=0; i<num; i++){
        if(fabs(coord_i(i,0))<=4 && fabs(coord_i(i,1)-dist2line_2)<=bias){
          // std::cout<<"2  i = "<<i<<std::endl;
          coord_2(jj,0) = coord_i(i,0);
          coord_2(jj,1) = coord_i(i,1);
          jj++;
        }
    }
    std::cout<<"ii = "<<ii<<"    jj = "<<jj<<std::endl;
    result.coord_1 = coord_1.topRows(ii);
    result.coord_2 = coord_2.topRows(jj);

    std::cout<<"coord1"<<std::endl<<result.coord_1<<std::endl;
    std::cout<<"coord2"<<std::endl<<result.coord_2<<std::endl;

    return result;
}
