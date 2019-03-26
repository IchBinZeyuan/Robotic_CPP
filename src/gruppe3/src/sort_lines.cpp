#include <iostream>
#include "sort_lines.h"
using namespace Eigen;
MatrixXd sort_lines(MatrixXd coord_i, double A_main, double B_main, double C_main, double sort_th, double tangent_main, int sign, double dense_th) {
    long num   = coord_i.rows();
    double sum = 0;
    double distance;
    int count  = 0;
    int num_output   = 0;
    int num_th = 2;
    double C_sort    = sign * INFINITY;
    int group_sort   = 0;
    VectorXd C       = VectorXd::Zero(num);
    VectorXd inlier  = VectorXd::Zero(num);
    VectorXd distant = VectorXd::Zero(num);
    VectorXd final   = VectorXd::Zero(num);
    double nominator = sqrt(A_main*A_main + B_main*B_main);
    MatrixXd coord_o;

    for (int i=0; i<num; i++){
        C(i) = - A_main*coord_i(i,0) - B_main*coord_i(i,1);
    }

    for (int i = 0; i < num; i++) {
        inlier = VectorXd::Zero(num);
        if ((sign * C(i) > 0) && (fabs(C(i)-C_main)/nominator>2.5) && (fabs(C(i)-C_main)/nominator<5 )) {
            inlier(i) = 1;
            sum = C(i);
            count = 1;
            if (i != num - 1) {
                for (int j = i + 1; j < num; j++) {
                    if ((sign * C(j) > 0) && (fabs(C(j) - sum/count) < sort_th*nominator)) {
                        inlier(j) = 1;
                        sum += C(j);
                        count++;
                    }
                }
            }
            distant = inlier;
            for (int m=0; m<num-1; m++){
                if (distant(m)==1){
                    for (int n=m+1; n<num; n++){
                        if(distant(n)==1){
                            distance = sqrt(pow((coord_i(m,0)-coord_i(n,0)), 2) + pow((coord_i(m,1)-coord_i(n,1)), 2));
                            if (distance<dense_th)
                                distant(n) = 0;
                        }
                    }
                }
            }
            if (distant.sum() > num_th ) {
                num_th = inlier.sum();
                C_sort = sum / count;
                num_output = count;
                final = inlier;
            }
            else if (distant.sum()==num_th && sign*sum/count<sign*C_sort) {
                num_th = inlier.sum();
                C_sort = sum / count;
                num_output = count;
                final = inlier;
            }
        }
    }

    if (num_output != 0){
        coord_o = MatrixXd::Zero(num_output, 2);
        int j = 0;
        for (int i=0; i<num; i++){
            if (final(i) == 1){
                coord_o(j, 0) = coord_i(i, 0);
                coord_o(j, 1) = coord_i(i, 1);
                j++;
            }
        }
    }
    else{
        coord_o = MatrixXd::Zero(1, 2);
    }

//    std::cout<<"threshold="<<sort_th*nominator<<std::endl;
    return coord_o;
}
