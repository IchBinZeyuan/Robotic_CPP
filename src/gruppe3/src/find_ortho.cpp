#include <iostream>
#include "find_ortho.h"
using namespace Eigen;
twin find_ortho(MatrixXd coord_i_pos, MatrixXd coord_i_neg, double ortho_th, double tangent_ortho, bool sort)
{
    long num_pos = coord_i_pos.rows();
    long num_neg = coord_i_neg.rows();
    VectorXi index_pos;
    VectorXi index_neg;
    VectorXi index_pos2;
    VectorXi index_neg2;
    VectorXd angle_bias;
    if (num_pos > num_neg){
        angle_bias = VectorXd::Zero(num_pos);
        index_pos = VectorXi::Zero(num_pos);
        index_neg = VectorXi::Zero(num_pos);
        index_pos2 = VectorXi::Zero(num_pos);
        index_neg2 = VectorXi::Zero(num_pos);
    }
    else{
        angle_bias = VectorXd::Zero(num_neg);
        index_pos = VectorXi::Zero(num_neg);
        index_neg = VectorXi::Zero(num_neg);
        index_pos2 = VectorXi::Zero(num_neg);
        index_neg2 = VectorXi::Zero(num_neg);
    }
    VectorXi flag_repeat;
    double angle, angle1, angle2;
    twin orthogonal;
    int i, j, ii=0, jj;
    double best_for_now;
    double angle_diff, angle_diff_min;
    bool flag = 0;

    std::cout<<"num_pos ="<< num_pos<<"num_neg ="<< num_neg<<std::endl;

    if(sort){
        for(i=0; i<num_pos; i++){
            best_for_now = 3.1416;
            flag = 0;
            for(j=0; j<num_neg; j++){
                if (fabs(coord_i_pos(i,0)-coord_i_neg(j,0)) < 1e-5)
                    angle = 3.1416/2;
                else
                    angle = atan((coord_i_pos(i,1)-coord_i_neg(j,1)) / (coord_i_pos(i,0)-coord_i_neg(j,0)));

                angle_diff = fabs(angle-tangent_ortho);
                while(angle_diff > 3.1416){
                    angle_diff = 2*3.1416 - angle_diff;
                }
                // std::cout<<i<<"/"<<j<<"  angle_diff"<<angle_diff<<",  ortho_th"<<ortho_th<<",  best_for_now"<<best_for_now<<std::endl;
                if (angle_diff<ortho_th && angle_diff<best_for_now){
                    index_pos(ii) = i;
                    index_neg(ii) = j;
                    angle_bias(ii) = angle_diff;
                    best_for_now  = fabs(angle_diff);
                    flag = 1;
                }
            }
            if (flag == 1){
                ii++;
                // std::cout<<"====ii = "<<ii<<std::endl;
            }
        }

        flag_repeat = VectorXi::Zero(ii);
        jj = 0;
        for (i=0; i<ii; i++){
            if (flag_repeat(i) == 0){
                index_pos2(jj) = index_pos(i);
                index_neg2(jj) = index_neg(i);
                angle_diff_min = angle_bias(i);
                if (i<ii-1){
                    for (j=i+1; j<ii; j++){
                        if (index_neg(i) == index_neg(j)){
                            flag_repeat(j) = 1;
                            if (angle_bias(j) < angle_diff_min){
                                index_pos2(jj) = index_pos(j);
                                index_neg2(jj) = index_neg(j);
                                angle_diff_min = angle_bias(j);
                            }
                        }
                    }
                }
                jj++;
            }
        }

        orthogonal.coord_1 = MatrixXd::Zero(jj,2);
        orthogonal.coord_2 = MatrixXd::Zero(jj,2);

        for(i = 0; i<jj; i++){
            orthogonal.coord_1(i,0) = coord_i_pos(index_pos2(i),0);
            orthogonal.coord_1(i,1) = coord_i_pos(index_pos2(i),1);
            orthogonal.coord_2(i,0) = coord_i_neg(index_neg2(i),0);
            orthogonal.coord_2(i,1) = coord_i_neg(index_neg2(i),1);
        }
    }

    else{
        for(i=0; i<num_pos; i++){
            for(j=0; j<num_neg; j++){
                if (fabs(coord_i_pos(i,0)-coord_i_neg(j,0))<1e-5)
                    angle = 3.1416/2;
                else
                    angle = atan((coord_i_pos(i,1)-coord_i_neg(j,1)) / (coord_i_pos(i,0)-coord_i_neg(j,0)));

                angle_diff = fabs(angle-tangent_ortho);
                if (angle_diff > 3.1416/2){
                    angle_diff = 3.1416-angle_diff;
                }
                if (angle_diff<ortho_th){
                    index_pos(i) = 1;
                    index_neg(j) = 1;
                }
            }
        }

        orthogonal.coord_1 = MatrixXd::Zero(index_pos.sum(), 2);
        orthogonal.coord_2 = MatrixXd::Zero(index_neg.sum(), 2);

        j=0;
        for(i=0; i<num_pos; i++){
            if (index_pos(i) == 1){
                orthogonal.coord_1(j,0) = coord_i_pos(i,0);
                orthogonal.coord_1(j,1) = coord_i_pos(i,1);
                j++;
            }
        }

        j=0;
        for(i=0; i<num_neg; i++){
            if (index_neg(i) == 1){
                orthogonal.coord_2(j,0) = coord_i_neg(i,0);
                orthogonal.coord_2(j,1) = coord_i_neg(i,1);
                j++;
            }
        }

    }


    return orthogonal;
}
