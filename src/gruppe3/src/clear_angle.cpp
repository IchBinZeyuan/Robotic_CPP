#include <iostream>
#include "clear_angle.h"
using namespace Eigen;
MatrixXd clear_angle(MatrixXd coord_i, double reduce_rate, int angle_num, int max_num, double angle_min, double angle_max)
{

    long num = coord_i.rows();
    MatrixXd coord_o = MatrixXd::Zero(num, 4);
    MatrixXd result;
    // VectorXd angle = VectorXd::Zero(num);
    VectorXi neighbour;

    double angle1, angle2;
    double max_range, range_th;


    int ii = 0;
    for (int i =0; i<angle_num; i++){
        angle1 = angle_min + i*(angle_max - angle_min)/angle_num;
        angle2 = angle_min + (i+1)*(angle_max - angle_min)/angle_num;
        neighbour = VectorXi::Zero(num);
        max_range = 0;

        for (int j=0; j<num; j++){
            if(coord_i(j,2)>=angle1 && coord_i(j,2)<=angle2)
            {
                neighbour(j) = 1;
                if(max_range<coord_i(j,3))
                    max_range=coord_i(j,3);
            }
        }
        range_th = reduce_rate * max_range;

        if(neighbour.sum() > max_num) {
            for(int j=0; j<num; j++) {
                if(neighbour(j)==1 && coord_i(j,3)<range_th && fabs(coord_i(j,0))<4 && fabs(coord_i(j,1))<4) {
                    coord_o.row(ii) = coord_i.row(j);
                    ii++;
                }
            }
        }
        else {
            for(int j=0; j<num; j++) {
                if(neighbour(j)==1) {
                    coord_o.row(ii) = coord_i.row(j);
                    ii++;
                }
            }
        }
    }
    result = coord_o.topRows(ii);
    // int jj = 0;
    // for (int i=0; i<ii; i++){
    //     if (fabs(coord_o(i,0))>4 || fabs(coord_o(i,1))>4){
    //         result.row(jj) = coord_o.row(i);
    //         jj++;
    //     }
    // }

    return result;
}
