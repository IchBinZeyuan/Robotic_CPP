#include <iostream>
#include "find_orthogonal.h"
using namespace Eigen;
MatrixXd find_orthogonal(MatrixXd coord_main, MatrixXd coord_i, double ortho_th, double tangent_ortho)
{
    long num = coord_i.rows(), num_main = coord_main.rows();
    int num_ortho;
    VectorXi index_main = VectorXi::Zero(num_main);
    VectorXi index_i    = VectorXi::Zero(num);
    double angle;

    for(int i=0; i<num_main; i++){
        for(int j=0; j<num; j++){
            if (abs(coord_main(i,0) - coord_i(j,0)) < 1e-5)
                angle = 3.1416/2;
            else
                angle = atan((coord_main(i,1)-coord_i(j,1)) / (coord_main(i,0)-coord_i(j,0)));

            if (abs(angle - tangent_ortho)<ortho_th){
                index_main(i) = 1;
                index_i(j) = 1;
            }
        }
    }

    num_ortho = index_i.sum() + index_main.sum();
    MatrixXd coord_o = MatrixXd::Zero(num_ortho,2);

    int j = 0;
    for(int i=0; i<index_i.sum(); i++){
        if (index_i(i)==1){
            coord_o(j,0) = coord_i(i,0);
            coord_o(j,1) = coord_i(i,1);
            j++;
        }
    }
    for(int i=0; i<index_main.sum(); i++){
        if (index_main(i)==1){
            coord_o(j,0) = coord_main(i,0);
            coord_o(j,1) = coord_main(i,1);
            j++;
        }
    }

    return coord_o;
}
