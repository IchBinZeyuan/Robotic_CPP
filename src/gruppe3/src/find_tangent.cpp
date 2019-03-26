#include <iostream>
#include "find_tangent.h"
using namespace Eigen;

line find_tangent(MatrixXd coord_1, MatrixXd coord_2, double colinear_th, double dense_th, double div_th)
{
    MatrixXd coord_i(coord_1.rows()+coord_2.rows(), 2);
    coord_i<<coord_1, coord_2;
    long num = coord_i.rows();
    int i, j, m, n, ii, jj;
    int inlier_count, outlier_count;
    bool found_five = 0;
    double A, B, C;
    double bias, nominator;
    double k, tan, mean, divergence;
    double xx,yy, dis;
    line line_main;
    double min_div= 10000.0;
    VectorXi inlier         = VectorXi::Zero(num);
    VectorXi outlier        = VectorXi::Zero(num);
    VectorXi final_inlier   = VectorXi::Zero(num);
    VectorXi final_outlier  = VectorXi::Zero(num);
    VectorXd ranges         = VectorXd::Zero(num);
    MatrixXd rect_coord     = MatrixXd::Zero(num,2);
    VectorXd distance       = VectorXd::Zero(num);


    // RANSAC
    for (i=0; i<num-1; i++) {
        for(j=i+1; j<num; j++) {
            // std::cout<<"begin RANSAC, i="<<i<<"  j="<<j<<std::endl;

            // Calculate line Ax+By+C=0
            if (sqrt(pow((coord_i(i, 1) - coord_i(j, 1)), 2) + pow((coord_i(i, 0) - coord_i(j, 0)), 2)) < dense_th){
                continue;
            }
            // std::cout<<"calculate line"<<std::endl;
            if (fabs(coord_i(i, 0) - coord_i(j, 0)) < 1e-5) {
                A = -1;
                B = 0;
                C = coord_i(i, 0);
                tan = 3.1416/2;
            }
            else if (fabs(coord_i(i, 1) - coord_i(j, 1)) < 1e-5) {
                A = 0;
                B = -1;
                C = coord_i(i, 1);
                tan = 0;
            }
            else {
                k = (coord_i(i, 1) - coord_i(j, 1)) / (coord_i(i, 0) - coord_i(j, 0));
                if (k < 2 && k > -2) {
                    A = k;
                    B = -1.0;
                    C = coord_i(i, 1) - A * coord_i(i, 0);
                    tan = atan(k);
                }
                else {
                    A = -1.0;
                    B = 1 / k;
                    C = coord_i(i, 0) - B * coord_i(i, 1);
                    tan = atan(k);
                }
            }
            if (fabs(tan)>0.5){
                continue;
            }
            //determine inliers and outliers
            // std::cout<<"determine inliers and outliers"<<std::endl;
            nominator = sqrt(A*A + B*B);
            ii = 0;
            jj = 0;
            for (m = 0; m < num; m++) {
                bias = (A * coord_i(m, 0) + B * coord_i(m, 1) + C) / nominator;
                if (fabs(bias) < colinear_th) {
                    inlier(ii) = m;
                    ii++;
                }
                else {
                    outlier(jj) = m;
                    jj++;
                }
            }
            // std::cout<<"end, ii="<<ii<<std::endl;
            if (ii >= 4) {
                // std::cout<<"ii >= 4, i = " << i <<"j = " << j <<std::endl;
                // 拟合到一条直线上
                for (m = 0; m < ii; m++) {
                    rect_coord(m, 0) = (-A * B * coord_i(inlier(m), 1) + B * B * coord_i(inlier(m), 0) - A * C) / nominator;
                    rect_coord(m, 1) = (A * A * coord_i(inlier(m), 1) - A * B * coord_i(inlier(m), 0) - B * C) / nominator;
                }

                // 从小到大排序
                for (m = 0; m < ii-1; m++) {
                    for (n = 0; n < ii-m-1; n++) {
                        if (fabs(A + 1) < 1e-5 && rect_coord(n, 1) > rect_coord(n + 1, 1)) {
                            xx = rect_coord(n, 0);
                            yy = rect_coord(n, 1);
                            rect_coord(n, 0) = rect_coord(n + 1, 0);
                            rect_coord(n, 1) = rect_coord(n + 1, 1);
                            rect_coord(n+1, 0) = xx;
                            rect_coord(n+1, 1) = yy;
                        }
                        else if (fabs(B+1)<1e-5 && rect_coord(n,1) > rect_coord(n+1,1)) {
                            xx = rect_coord(n, 0);
                            yy = rect_coord(n, 1);
                            rect_coord(n, 0) = rect_coord(n + 1, 0);
                            rect_coord(n, 1) = rect_coord(n + 1, 1);
                            rect_coord(n + 1, 0) = xx;
                            rect_coord(n + 1, 1) = yy;
                        }
                    }
                }
                if (fabs(A+1)<1e-5 && (rect_coord(0,1)+B*C/nominator)*(rect_coord(ii-1,1)+B*C/nominator)>=0) {
                    continue;
                }
                if (fabs(B+1)<1e-5 && (rect_coord(0,0)+A*C/nominator)*(rect_coord(ii-1,0)+A*C/nominator)>=0) {
                    continue;
                }
                // std::cout<<"sort the line"<<std::endl;
                // 计算相邻两点距离
                for (m = 0; m < ii-1; m++) {
                    distance(m) = sqrt(pow((rect_coord(m,0)-rect_coord(m+1,0)),2) + pow((rect_coord(m,1)-rect_coord(m+1,1)),2));
                }
                // std::cout<<"calculate distance"<<std::endl;
                //当有至少5个点时,判断是否符合1：3：2：2的情况
                if (ii >= 5) {
                    for (m = 0; m <= ii - 5; m++){
                        // std::cout<<"i ="<<i<<"j ="<<j<<"ii ="<<ii<<"m ="<<m<<std::endl;
                        mean = (distance(m) / 0.25 + distance(m + 1) / 0.75 + distance(m + 2) / 0.5 +
                                distance(m + 3) / 0.5) / 4.0;
                        divergence = (pow((distance(m) / 0.25 - mean), 2) +
                                     pow((distance(m + 1) / 0.75 - mean), 2) +
                                     pow((distance(m + 2) / 0.5 - mean), 2) +
                                     pow((distance(m + 3) / 0.5 - mean), 2))/4.0;
                         if (divergence < div_th && mean>1){
                             // std::cout<<"-----------------------divergence of 5 points = "<<divergence<< " min_div="<<min_div<<std::endl;
                         }
                        if (divergence < div_th && mean>1 && divergence < min_div*1.5) {
                            found_five = 1;
                            min_div = divergence*0.7;
                            inlier_count  = ii;
                            outlier_count = jj;
                            final_inlier  = inlier;
                            final_outlier = outlier;
                            line_main.A_main = A;
                            line_main.B_main = B;
                            line_main.C_main = C;
                            line_main.tangent_main = tan;
                            line_main.success = 1;
                        }
                    }
                }
                //当有至少5个点时,判断是否符合2:2:3:1的情况
                if (ii >= 5) {
                    for (m = 0; m <= ii - 5; m++){
                        // std::cout<<"i ="<<i<<"j ="<<j<<"ii ="<<ii<<"m ="<<m<<std::endl;
                        mean = (distance(m) / 0.5 + distance(m + 1) / 0.5 + distance(m + 2) / 0.75 +
                                distance(m + 3) / 0.25) / 4.0;
                        divergence = (pow((distance(m) / 0.5 - mean), 2) +
                                     pow((distance(m + 1) / 0.5 - mean), 2) +
                                     pow((distance(m + 2) / 0.75 - mean), 2) +
                                     pow((distance(m + 3) / 0.25 - mean), 2))/4.0;
                        if (divergence < div_th && mean>1){
                            // std::cout<<"--------------------------divergence of 5 points = "<<divergence<< " min_div="<<min_div<<std::endl;
                        }
                        if (divergence < div_th && mean>1 && divergence < min_div*1.5) {
                            found_five = 1;
                            min_div = divergence*0.7;
                            inlier_count  = ii;
                            outlier_count = jj;
                            final_inlier  = inlier;
                            final_outlier = outlier;
                            line_main.A_main = A;
                            line_main.B_main = B;
                            line_main.C_main = C;
                            line_main.tangent_main = tan;
                            line_main.success = 1;

                        }
                    }
                }
                //当有至少4个点时,判断是否符合1：3：2的情况
                if (ii>=4 && found_five == 0) {
                    for (m = 0; m <= ii - 4; m++){
                        // std::cout<<"i ="<<i<<"j ="<<j<<"ii ="<<ii<<"m ="<<m<<std::endl;
                        mean = (distance(m) / 0.25 + distance(m + 1) / 0.75 + distance(m + 2) / 0.5) / 3.0;
                        divergence = (pow((distance(m) / 0.25 - mean), 2) +
                                     pow((distance(m + 1) / 0.75 - mean), 2) +
                                     pow((distance(m + 2) / 0.5 - mean), 2))/3.0;
                        if (divergence < div_th && mean>1 && divergence < min_div) {
                            min_div = divergence;
                            inlier_count  = ii;
                            outlier_count = jj;
                            final_inlier  = inlier;
                            final_outlier = outlier;
                            line_main.A_main = A;
                            line_main.B_main = B;
                            line_main.C_main = C;
                            line_main.tangent_main = tan;
                            line_main.success = 1;
                        }
                    }

                //当有至少4个点时,判断是否符合2:3:1的情况
                    for (m = 0; m <= ii - 4; m++){
                        // std::cout<<"i ="<<i<<"j ="<<j<<"ii ="<<ii<<"m ="<<m<<std::endl;
                        mean = (distance(m) / 0.5 + distance(m + 1) / 0.75 + distance(m + 2) / 0.25) / 3.0;
                        divergence = (pow((distance(m) / 0.5 - mean), 2) +
                                     pow((distance(m + 1) / 0.75 - mean), 2) +
                                     pow((distance(m + 2) / 0.25 - mean), 2))/3.0;
                        if (divergence < div_th && mean>1 && divergence < min_div) {
                            min_div = divergence;
                            inlier_count  = ii;
                            outlier_count = jj;
                            final_inlier  = inlier;
                            final_outlier = outlier;
                            line_main.A_main = A;
                            line_main.B_main = B;
                            line_main.C_main = C;
                            line_main.tangent_main = tan;
                            line_main.success = 1;

                            // std::cout<<"total inliers"<<ii<<std::endl;
                            // std::cout << "detected four points in a row, 2:3:1" << std::endl;
                        }
                    }

                //当有至少4个点时,判断是否符合1：3：4的情况
                    for (m = 0; m <= ii - 4; m++){
                        // std::cout<<"i ="<<i<<"j ="<<j<<"ii ="<<ii<<"m ="<<m<<std::endl;
                        mean = (distance(m) / 0.25 + distance(m + 1) / 0.75 + distance(m + 2)) / 3.0;
                        divergence = (pow((distance(m) / 0.25 - mean), 2) +
                                     pow((distance(m + 1) / 0.75 - mean), 2) +
                                     pow((distance(m + 2) - mean), 2))/3.0;
                        if (divergence < div_th && mean>1 && divergence < min_div) {
                            min_div = divergence;
                            inlier_count  = ii;
                            outlier_count = jj;
                            final_inlier  = inlier;
                            final_outlier = outlier;
                            line_main.A_main = A;
                            line_main.B_main = B;
                            line_main.C_main = C;
                            line_main.tangent_main = tan;
                            line_main.success = 1;

                            // std::cout<<"total inliers"<<ii<<std::endl;
                            // std::cout << "detected four points in a row, 1:3:4" << std::endl;
                        }
                    }

                //当有至少4个点时,判断是否符合4:3:1的情况

                    for (m = 0; m <= ii - 4; m++){
                        // std::cout<<"i ="<<i<<"j ="<<j<<"ii ="<<ii<<"m ="<<m<<std::endl;
                        mean = (distance(m) + distance(m + 1) / 0.75 + distance(m + 2) / 0.25) / 3.0;
                        divergence = (pow((distance(m) - mean), 2) +
                                     pow((distance(m + 1) / 0.75 - mean), 2) +
                                     pow((distance(m + 2) / 0.25 - mean), 2))/3.0;
                        if (divergence<div_th && mean>1 && divergence<min_div) {
                            min_div = divergence;
                            inlier_count  = ii;
                            outlier_count = jj;
                            final_inlier  = inlier;
                            final_outlier = outlier;
                            line_main.A_main = A;
                            line_main.B_main = B;
                            line_main.C_main = C;
                            line_main.tangent_main = tan;
                            line_main.success = 1;

                            // std::cout<<"total inliers"<<ii<<std::endl;
                            // std::cout << "detected four points in a row, 4:3:1" << std::endl;
                        }
                    }
                }
            } //ii>=4
        } // j
    } // i
    std::cout<<"almost finished RANSAC"<<std::endl;
    std::cout<<"line_main.success"<<line_main.success<<std::endl;
    std::cout<<"final_inlier"<<final_inlier<<std::endl;
    std::cout<<"final_outlier"<<final_outlier<<std::endl;
    std::cout<<"coord_i"<<coord_i<<std::endl;

    // std::cout<<"final_inlier"<<std::endl<<final_inlier<<std::endl;
    // std::cout<<"inlier_count"<<inlier_count<<std::endl;
    // std::cout<<"final_outlier"<<std::endl<<final_outlier<<std::endl;
    // std::cout<<"outlier_count"<<outlier_count<<std::endl;
    if (line_main.success == 1){
        // std::cout<<"inlier count = "<<inlier_count<<"outlier count = "<<outlier_count<<std::endl;
        line_main.coord_main = MatrixXd::Zero(inlier_count,2);
        for (m=0; m<inlier_count; m++){
            line_main.coord_main(m,0) = coord_i(final_inlier(m),0);
            line_main.coord_main(m,1) = coord_i(final_inlier(m),1);
        }

        line_main.coord_rest = MatrixXd::Zero(outlier_count,2);
        for (m=0; m<outlier_count; m++){
            line_main.coord_rest(m,0) = coord_i(final_outlier(m),0);
            line_main.coord_rest(m,1) = coord_i(final_outlier(m),1);
        }
    }
    else{
        line_main.success = 0;
    }
    std::cout<<"finished RANSAC"<<std::endl;
    return line_main;

}
