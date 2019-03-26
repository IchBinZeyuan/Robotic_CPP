#include <iostream>
#include "find_colinear.h"
using namespace Eigen;
MatrixXd find_colinear(MatrixXd coord_i, double tangent_th, double tangent_main)
{
    long num = coord_i.rows();
    double tan1, tan2, tan3, tan_diff1, tan_diff2, tan_diff3;
    VectorXi index = VectorXi::Zero(num);

    for (int i=0; i<num-2; i++){
        for (int j=i+1; j<num-1; j++){
            if (fabs(coord_i(i,0)-coord_i(j,0))<1e-5)
                tan1 = 3.1416/2;
            else
                tan1 = atan((coord_i(i, 1) - coord_i(j, 1)) / (coord_i(i, 0) - coord_i(j, 0)));

            tan_diff1 = fabs(tan1-tangent_main);
            if (tan_diff1>3.1416/2){
                tan_diff1 = 3.1416 - tan_diff1;
            }
            if (tan_diff1<tangent_th){
                for (int k=j+1; k<num; k++){
                    if (fabs(coord_i(i,0)-coord_i(k,0))<1e-5)
                        tan2 = 3.1416/2;
                    else
                        tan2 = atan((coord_i(i, 1) - coord_i(k, 1)) / (coord_i(i, 0) - coord_i(k, 0)));

                    if (fabs(coord_i(j,0)-coord_i(k,0))<1e-5)
                        tan3 = 3.1416/2;
                    else
                        tan3 = atan((coord_i(j, 1) - coord_i(k, 1)) / (coord_i(j, 0) - coord_i(k, 0)));

                    tan_diff2 = fabs(tan2-tangent_main);
                    if (tan_diff2>3.1416/2){
                        tan_diff2 = 3.1416 - tan_diff2;
                    }
                    tan_diff3 = fabs(tan2-tangent_main);
                    if (tan_diff3>3.1416/2){
                        tan_diff3 = 3.1416 - tan_diff3;
                    }
                    if (tan_diff2 < tangent_th && tan_diff3 < tangent_th){
                        index(i) = 1;
                        index(j) = 1;
                        index(k) = 1;
                    }
                }
            }
        }
    }

    int num_colinear = index.sum();
//    std::cout<<num_colinear<<std::endl;
    MatrixXd coord_o = MatrixXd::Zero(num_colinear, 2);
    int j = 0;
    for (int i=0; i<num; i++){
        if (index(i)==1){
            coord_o(j, 0) = coord_i(i, 0);
            coord_o(j, 1) = coord_i(i, 1);
            j++;
        }
    }

    return coord_o;

}
