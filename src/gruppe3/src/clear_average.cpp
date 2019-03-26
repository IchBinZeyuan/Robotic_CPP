#include <iostream>
#include "clear_average.h"
using namespace Eigen;
MatrixXd clear_average(MatrixXd coord_i, double overlap_th)
{
    long num = coord_i.rows();
    MatrixXd coord_o = MatrixXd::Zero(num, 4);
    MatrixXd result;
    VectorXi flag = VectorXi::Zero(num);
    double sum_x, sum_y, dist;
    int count;
    int ii = 0;

    for (int i=0; i<num-1; i++) {
        if (flag(i) == 0) {
            flag(i) = 1;
            sum_x = coord_i(i, 0);
            sum_y = coord_i(i, 1);
            count = 1;

            for (int j = i + 1; j < num; j++) {
                if (flag(j) == 0) {
                    dist = sqrt(pow((coord_i(j, 0) - sum_x / count), 2) + pow((coord_i(j, 1) - sum_y / count), 2));
                    if (dist < overlap_th) {
                        flag(j) = 1;
                        sum_x = sum_x + coord_i(j, 0);
                        sum_y = sum_y + coord_i(j, 1);
                        count++;
                    }
                }
            }

            coord_o(ii,0) = sum_x /count;
            coord_o(ii,1) = sum_y /count;
            coord_o(ii,3) = sqrt(coord_o(ii, 0)*coord_o(ii, 0) + coord_o(ii, 1)*coord_o(ii, 1));
            if (coord_o(ii,3) < 1e-5)
                coord_o(ii,2) = 0;
            else
                coord_o(ii,2) = asin(coord_o(ii,0) / coord_o(ii,3));

            if (coord_o(ii,1) < 0)
                coord_o(ii,2) = ((int)(coord_o(ii,2)>=0) - (int)(coord_o(ii,2)<0))*3.1416 - coord_o(ii,2);

            ii++;
        }
    }

    if(flag(num-1)==0)
    {
        coord_o(ii,0) = coord_i(num-1,0);
        coord_o(ii,1) = coord_i(num-1,1);
        coord_o(ii,3) = sqrt(coord_o(ii, 0)*coord_o(ii, 0) + coord_o(ii, 1)*coord_o(ii, 1));
        if (abs(coord_o(ii,3)) < 1e-5)
            coord_o(ii,2) = 0;
        else
            coord_o(ii,2) = asin(coord_o(ii,0) / coord_o(ii,3));

        if (coord_o(ii,1) < 0)
            coord_o(ii,2) = ((int)(coord_o(ii,2)>=0) - (int)(coord_o(ii,2)<0))*3.1416 - coord_o(ii,2);

        ii++;
    }

    result = coord_o.topRows(ii);
    return result;
}
