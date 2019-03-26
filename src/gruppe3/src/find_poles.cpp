#include <iostream>
#include <vector>
#include "gnuplot-iostream.h"
#include "find_poles.h"
using namespace Eigen;
using namespace std;

playground find_poles(MatrixXd coord_i, double colinear_th, double dense_th, double div_th, double ortho_th, int direction, double a, double b)
{
    Gnuplot gp1, gp2, gp3;
    vector<boost::tuple<double, double> > pts_1, pts_2, pts_3;
    long num = coord_i.rows();
    double A1, B1, C1, A2, B2, C2;
    double final_A1, final_B1, final_C1, final_A2, final_B2, final_C2;
    double bias, nominator;
    double k, tan, mean, divergence;
    double tangent_main, tangent_ortho;
    int i, j, m, n, ii, jj, max_num;
    int inlier_count, outlier_count;
    int coord_1_cnt, coord_2_cnt;
    bool flag;
    bool line1_exist, line2_exist;
    double angle, angle_diff, best_for_now;
    VectorXi line1          = VectorXi::Zero(7);
    VectorXi line2          = VectorXi::Zero(7);
    VectorXi inlier         = VectorXi::Zero(num);
    VectorXi outlier        = VectorXi::Zero(num);
    VectorXi final_inlier   = VectorXi::Zero(num);
    VectorXi final_outlier  = VectorXi::Zero(num);
    MatrixXd final_coord_1, final_coord_2;
    MatrixXd coord_1 = MatrixXd::Zero(num, 3);
    MatrixXd coord_2 = MatrixXd::Zero(num, 3);
    MatrixXd coord_1_colinear, coord_2_colinear, rect_coord1, rect_coord2 ;

    VectorXd distance1,  bias_sum1, distance2, bias_sum2;
    VectorXi num1, num2;
    MatrixXi identification1, identification2;


    playground result;


    for (i=0; i<coord_i.rows(); i++) {
        pts_3.push_back(boost::make_tuple(
                coord_i(i, 0),
                coord_i(i, 1)));
    }
    gp3 << "plot '-' with points title 'original nearby lidar point'\n";
    gp3.send1d(pts_3);

    // find the first and the second lines
    coord_1_cnt = 0;
    coord_2_cnt = 0;
    for (i=0; i<num; i++){
        if (coord_i(i,2) <= 7){
            coord_1.row(coord_1_cnt) = coord_i.row(i);
            line1(coord_i(i, 2)-1) = 1;
            coord_1_cnt++;
        }
        else{
            coord_2.row(coord_2_cnt) = coord_i.row(i);
            line2(coord_i(i, 2)-8) = 1;
            coord_2_cnt++;
        }
    }
    // RANSAC for line 1
    max_num = 0;
    if (line1.sum() >=2){
        line1_exist = 1;
        for (i=0; i<coord_1_cnt-1; i++) {
            for(j=i+1; j<coord_1_cnt; j++) {
                if (sqrt(pow((coord_1(i, 1) - coord_1(j, 1)), 2) + pow((coord_1(i, 0) - coord_1(j, 0)), 2)) < dense_th){
                    continue;
                }
                if (fabs(coord_1(i, 0) - coord_1(j, 0)) < 1e-5) {
                    A1 = -1;
                    B1 = 0;
                    C1 = coord_1(i, 0);
                    tan = 3.1416/2;
                }
                else if (fabs(coord_1(i, 1) - coord_1(j, 1)) < 1e-5) {
                    A1 = 0;
                    B1 = -1;
                    C1 = coord_1(i, 1);
                    tan = 0;
                }
                else {
                    k = (coord_1(i, 1) - coord_1(j, 1)) / (coord_1(i, 0) - coord_1(j, 0));
                    if (k < 2 && k > -2) {
                        A1 = k;
                        B1 = -1.0;
                        C1 = coord_1(i, 1) - A1 * coord_1(i, 0);
                        tan = atan(k);
                    }
                    else {
                        A1 = -1.0;
                        B1 = 1 / k;
                        C1 = coord_1(i, 0) - B1 * coord_1(i, 1);
                        tan = atan(k);
                    }
                }
                //determine inliers and outliers
                nominator = sqrt(A1*A1 + B1*B1);
                ii = 0;
                jj = 0;
                for (m = 0; m < coord_1_cnt; m++) {
                    bias = (A1*coord_1(m,0) + B1*coord_1(m,1) + C1) / nominator;
                    if (fabs(bias) < colinear_th) {
                        inlier(ii) = m;
                        ii++;
                    }
                    if (ii > max_num){
                        max_num = ii;
                        final_inlier = inlier;
                        final_A1 = A1;
                        final_B1 = B1;
                        final_C1 = C1;

                        if (line1.sum() > line2.sum()){
                            tangent_main = tan;
                            tangent_ortho = tan + 3.1416/2;
                            if (tangent_ortho > 3.1416/2){
                                tangent_ortho -= 3.1416;
                            }
                        }
                    }
                }
            }
        }
        // cout<<"line 1 max_num"<<max_num<<endl;
        coord_1_colinear = MatrixXd::Zero(max_num, 3);
        for (i=0; i<max_num; i++){
            coord_1_colinear.row(i) = coord_1.row(final_inlier(i));
        }
        // cout<<"coord_1_colinear = "<<endl<<coord_1_colinear<<endl;
    }
    else{
        line1_exist = 0;
    }
    // cout<<"coord_1_colinear "<<endl<<coord_1_colinear<<endl;
    // RANSAC for line 2
    max_num = 0;
    if (line2.sum() >=2){
        line2_exist = 1;
        for (i=0; i<coord_2_cnt-1; i++) {
            for(j=i+1; j<coord_2_cnt; j++) {
                // Calculate line Ax+By+C=0
                if (sqrt(pow((coord_2(i, 1) - coord_2(j, 1)), 2) + pow((coord_2(i, 0) - coord_2(j, 0)), 2)) < dense_th){
                    continue;
                }
                if (fabs(coord_2(i, 0) - coord_2(j, 0)) < 1e-5) {
                    A2 = -1;
                    B2 = 0;
                    C2 = coord_2(i, 0);
                    tan = 3.1416/2;
                }
                else if (fabs(coord_2(i, 1) - coord_2(j, 1)) < 1e-5) {
                    A2 = 0;
                    B2 = -1;
                    C2 = coord_2(i, 1);
                    tan = 0;
                }
                else {
                    k = (coord_2(i, 1) - coord_2(j, 1)) / (coord_2(i, 0) - coord_2(j, 0));
                    if (k < 2 && k > -2) {
                        A2 = k;
                        B2 = -1.0;
                        C2 = coord_2(i, 1) - A2*coord_2(i, 0);
                        tan = atan(k);
                    }
                    else {
                        A2 = -1.0;
                        B2 = 1 / k;
                        C2 = coord_2(i, 0) - B2*coord_2(i, 1);
                        tan = atan(k);
                    }
                }
                //determine inliers and outliers
                nominator = sqrt(A2*A2 + B2*B2);
                ii = 0;
                jj = 0;
                for (m = 0; m < coord_2_cnt; m++) {
                    bias = (A2*coord_2(m,0) + B2*coord_2(m,1) + C2) / nominator;
                    if (fabs(bias) < colinear_th) {
                        inlier(ii) = m;
                        ii++;
                    }
                    if (ii > max_num){
                        max_num = ii;
                        final_inlier = inlier;
                        final_A2 = A2;
                        final_B2 = B2;
                        final_C2 = C2;

                        if (line1.sum() <= line2.sum()){
                            tangent_main = tan;
                            tangent_ortho = tan + 3.1416/2;
                            if (tangent_ortho > 3.1416/2){
                                tangent_ortho -= 3.1416;
                            }
                        }

                    }
                }
            }
        }
        coord_2_colinear = MatrixXd::Zero(max_num, 3);
        for (i=0; i<max_num; i++){
            coord_2_colinear.row(i) = coord_2.row(final_inlier(i));
        }
        // cout<<"coord_2_colinear = "<<endl<<coord_2_colinear<<endl;
    }
    else{
        line2_exist = 0;
    }

    if (line1_exist){
        for (i=0; i<coord_1_colinear.rows(); i++) {
            pts_1.push_back(boost::make_tuple(
                    coord_1_colinear(i, 0),
                    coord_1_colinear(i, 1)));
        }
    }
    if (line2_exist){
        for (i=0; i<coord_2_colinear.rows(); i++) {
            pts_1.push_back(boost::make_tuple(
                    coord_2_colinear(i, 0),
                    coord_2_colinear(i, 1)));
        }
    }
    // gp1 << "plot '-' with points title 'colinear lidar points'\n";
    gp1.send1d(pts_1);

    MatrixXi standard(7,7);
    standard <<0, 1, 4, 6, 8, 11, 12, -1, 0, 3, 5, 7, 10, 11, -4, -3, 0, 2, 4, 7, 8, -6, -5, -2, 0, 2, 5, 6, -8, -7, -4, -2, 0, 3, 4, -11, -10, -7, -5, -3, 0, 1, -12, -11, -8, -6, -4, -1, 0;

    double xx, yy, lbl;
    double bias1, min_bias1;
    int max_num1, best1, start1, end1, max_num2, best2, start2, end2;

    // If line 1 exist
    if (line1_exist && coord_1_colinear.rows()>=2){
        // 拟合到一条直线上
        rect_coord1 = MatrixXd::Zero(coord_1_colinear.rows(), 3);
        nominator = sqrt(final_A1*final_A1 + final_B1*final_B1);
        for (m = 0; m < coord_1_colinear.rows(); m++) {
            rect_coord1(m, 0) = (-final_A1*final_B1*coord_1_colinear(m, 1) + final_B1*final_B1*coord_1_colinear(m, 0) - final_A1*final_C1) / nominator;
            rect_coord1(m, 1) = (final_A1*final_A1*coord_1_colinear(m, 1) - final_A1*final_B1*coord_1_colinear(m, 0) - final_B1*final_C1) / nominator;
            rect_coord1(m, 2) = coord_1_colinear(m, 2);
        }
        // cout<<"rect_coord1 = "<<endl<<rect_coord1<<endl;
        // 排序
        for (m = 0; m < rect_coord1.rows()-1; m++) {
            for (n = 0; n < rect_coord1.rows()-m-1; n++) {
                if (fabs(A1+1)<1e-5 && ((rect_coord1(n,1)>rect_coord1(n+1,1) && direction==21)||(rect_coord1(n,1)<rect_coord1(n+1,1) && direction==22))) {
                    xx  = rect_coord1(n, 0);
                    yy  = rect_coord1(n, 1);
                    lbl = rect_coord1(n, 2);
                    rect_coord1(n, 0) = rect_coord1(n + 1, 0);
                    rect_coord1(n, 1) = rect_coord1(n + 1, 1);
                    rect_coord1(n, 2) = rect_coord1(n + 1, 2);
                    rect_coord1(n+1, 0) = xx;
                    rect_coord1(n+1, 1) = yy;
                    rect_coord1(n+1, 2) = lbl;
                }
                else if (fabs(B1+1)<1e-5 && ((rect_coord1(n,0)>rect_coord1(n+1,0) && direction==11)||(rect_coord1(n,0)<rect_coord1(n+1,0) && direction==12))) {
                    xx = rect_coord1(n, 0);
                    yy = rect_coord1(n, 1);
                    lbl = rect_coord1(n, 2);
                    rect_coord1(n, 0) = rect_coord1(n + 1, 0);
                    rect_coord1(n, 1) = rect_coord1(n + 1, 1);
                    rect_coord1(n, 2) = rect_coord1(n + 1, 2);
                    rect_coord1(n+1, 0) = xx;
                    rect_coord1(n+1, 1) = yy;
                    rect_coord1(n+1, 2) = lbl;
                }
            }
        }
        // cout<<"after sort rect_coord1 = "<<endl<<rect_coord1<<endl;
        distance1 = VectorXd::Zero(rect_coord1.rows());
        for (m = 0; m < rect_coord1.rows(); m++){
            distance1(m) = sqrt(pow(rect_coord1(m,0)-rect_coord1(0,0),2) + pow(rect_coord1(m,1)-rect_coord1(0,1),2));
        }

        num1 = VectorXi::Zero(rect_coord1.rows());
        identification1 = MatrixXi::Zero(rect_coord1.rows(),7);
        bias_sum1 = VectorXd::Zero(rect_coord1.rows());

        for (m=0; m<rect_coord1.rows(); m++){
            for (i=0; i<7; i++){
                min_bias1 = 10000;
                for(n=0; n<rect_coord1.rows(); n++){
                    if (rect_coord1(n,2) == i+1){
                        bias1 = fabs(distance1(n)-distance1(m)-1.0/4.0*a*standard(rect_coord1(m,2)-1,i));
                        if (bias1<0.1 && bias1<min_bias1){
                            identification1(m, i) = n+1;
                            min_bias1 = bias1;
                        }
                    }
                }
                // cout<<"min_bias1 = "<<min_bias1<<endl;
                if (identification1(m, i) != 0){
                    bias_sum1(m) += min_bias1;
                    num1(m) += 1;
                }
            }
        }
        // cout<<"identification1 = "<<endl<<identification1<<endl;
        max_num1 = num1.maxCoeff();
        if (max_num1 <2){
            line1_exist = 0;
        }
        else{
            best1=0;
            start1=7;
            end1=0;
            min_bias1 = 10000;
            for (m=0; m<rect_coord1.rows(); m++){
                if (num1(m)==max_num1 && bias_sum1(m)<min_bias1){
                    min_bias1 = bias_sum1(m);
                    best1 = m;
                }
            }
            cout<<"best1 = "<<best1<<endl;
            result.coord_1 = MatrixXd::Zero(7,3);
            for(m=0; m<7; m++){
                if(identification1(best1,m) != 0){
                    if (start1 == 7){
                        start1 = m;
                    }
                    end1 = m;
                    result.coord_1.row(m) = rect_coord1.row(identification1(best1,m)-1);
                }
            }
        }
    }

    if (line2_exist && coord_2_colinear.rows()>=2){
        rect_coord2 = MatrixXd::Zero(coord_2_colinear.rows(), 3);
        nominator = sqrt(final_A2*final_A2 + final_B2*final_B2);
        for (m = 0; m < coord_2_colinear.rows(); m++) {
            rect_coord2(m, 0) = (-final_A2*final_B2*coord_2_colinear(m, 1) + final_B2*final_B2*coord_2_colinear(m, 0) - final_A2*final_C2) / nominator;
            rect_coord2(m, 1) = (final_A2*final_A2*coord_2_colinear(m, 1) - final_A2*final_B2*coord_2_colinear(m, 0) - final_B2*final_C2) / nominator;
            rect_coord2(m, 2) = coord_2_colinear(m, 2);
        }
        // cout<<"rect_coord2 = "<<endl<<rect_coord2<<endl;
        // 排序
        for (m = 0; m < rect_coord2.rows()-1; m++) {
            for (n = 0; n < rect_coord2.rows()-m-1; n++) {
                if (fabs(A2+1)<1e-5 && ((rect_coord2(n,1)>rect_coord2(n+1,1) && direction==21)||(rect_coord2(n,1)<rect_coord2(n+1,1) && direction==22))) {
                    xx  = rect_coord2(n, 0);
                    yy  = rect_coord2(n, 1);
                    lbl = rect_coord2(n, 2);
                    rect_coord2(n, 0) = rect_coord2(n + 1, 0);
                    rect_coord2(n, 1) = rect_coord2(n + 1, 1);
                    rect_coord2(n, 2) = rect_coord2(n + 1, 2);
                    rect_coord2(n+1, 0) = xx;
                    rect_coord2(n+1, 1) = yy;
                    rect_coord2(n+1, 2) = lbl;
                }
                else if (fabs(B2+1)<1e-5 && ((rect_coord2(n,0)>rect_coord2(n+1,0) && direction==11)||(rect_coord2(n,0)<rect_coord2(n+1,0) && direction==12))) {
                    xx  = rect_coord2(n, 0);
                    yy  = rect_coord2(n, 1);
                    lbl = rect_coord2(n, 2);
                    rect_coord2(n, 0) = rect_coord2(n + 1, 0);
                    rect_coord2(n, 1) = rect_coord2(n + 1, 1);
                    rect_coord2(n, 2) = rect_coord2(n + 1, 2);
                    rect_coord2(n+1, 0) = xx;
                    rect_coord2(n+1, 1) = yy;
                    rect_coord2(n+1, 2) = lbl;
                }
            }
        }
        // cout<<"after sort rect_coord2 = "<<endl<<rect_coord2<<endl;
        //Calculate diatance coordinate
        distance2 = VectorXd::Zero(rect_coord2.rows());

        for (m = 0; m < rect_coord2.rows(); m++){
            distance2(m) = sqrt(pow(rect_coord2(m,0)-rect_coord2(0,0),2) + pow(rect_coord2(m,1)-rect_coord2(0,1),2));
        }

        num2 = VectorXi::Zero(rect_coord2.rows());
        identification2 = MatrixXi::Zero(rect_coord2.rows(),7);
        bias_sum2 = VectorXd::Zero(rect_coord2.rows());

        for (m=0; m<rect_coord2.rows(); m++){
            for (i=0; i<7; i++){
                min_bias1 = 10000;
                for(n=0; n<rect_coord2.rows(); n++){
                    if (rect_coord2(n,2) == i+8){
                        bias1 = fabs(distance2(n)-distance2(m)-1.0/4.0*a*standard(rect_coord2(m,2)-8,i));
                        if (bias1<0.1 && bias1<min_bias1){
                            identification2(m, i) = n+1;
                            min_bias1 = bias1;
                        }
                    }
                }
                if (identification2(m, i) != 0){
                    bias_sum2(m) += min_bias1;
                    num2(m) += 1;
                }
            }
        }
        // cout<<"identification2 = "<<endl<<identification2<<endl;
        max_num2 = num2.maxCoeff();
        if (max_num2 < 2){
            line2_exist = 0;
        }
        else{
            best2=0;
            start2=7;
            end2=0;

            min_bias1 = 10000;
            for (m=0; m<rect_coord2.rows(); m++){
                if (num2(m)==max_num2 && bias_sum2(m)<min_bias1){
                    min_bias1 = bias_sum2(m);
                    best2 = m;
                }
            }
            // cout<<"best2 = "<<best2<<endl;
            result.coord_2 = MatrixXd::Zero(7,3);
            for(m=0; m<7; m++){
                if(identification2(best2,m) != 0){
                    if(start2 == 7){
                        start2 = m;
                    }
                    end2 = m;
                    result.coord_2.row(m) = rect_coord2.row(identification2(best2,m)-1);
                }
            }
        }
    }

    double direction_x1, direction_x2, direction_y1, direction_y2, nom1, nom2;
    //Calculate angle
    if (line1_exist){
        direction_x1 = result.coord_1(end1,0) - result.coord_1(start1,0);
        direction_y1 = result.coord_1(end1,1) - result.coord_1(start1,1);
        nom1 = sqrt(pow(direction_x1,2)+pow(direction_y1,2));
        direction_x1 = direction_x1 / nom1;
        direction_y1 = direction_y1 / nom1;
    }
    else{
        direction_x1 = 0;
        direction_y1 = 0;
    }
    if (line2_exist){
        direction_x2 = result.coord_2(end2,0) - result.coord_2(start2,0);
        direction_y2 = result.coord_2(end2,1) - result.coord_2(start2,1);
        nom2 = sqrt(pow(direction_x2,2)+pow(direction_y2,2));
        direction_x2 = direction_x2 / nom2;
        direction_y2 = direction_y2 / nom2;
    }
    else{
        direction_x2 = 0;
        direction_y2 = 0;
    }
    // cout<<"direction_x1 = "<<direction_x1<<"direction_y1 = "<<direction_y1<<"direction_x2 = "<<direction_x2<<"direction_y2 = "<<direction_y2<<endl;
    if (line1_exist == 0 && line2_exist == 0){
        result.success = 0;
        return result;
    }
    else{
        if (fabs(direction_y1+direction_y2)<1e-5){
            if ((direction_x1+direction_x2)>0){
                result.angle = -3.1416/2;
            }
            else{
                result.angle = 3.1416/2;
            }
        }
        else{
            result.angle = atan(-(direction_x1+direction_x2) / (direction_y1+direction_y2));
            if ((direction_y1+direction_y2) < 0){
                result.angle += 3.1416;
            }
            while (result.angle>2*3.1416){
                result.angle -= 2*3.1416;
            }
            while (result.angle<-2*3.1416){
                result.angle += 2*3.1416;
            }
        }
        // cout<<"angle = "<<result.angle/3.1416*180<<endl;
        // cout<<"result.coord_1 = "<<endl<<result.coord_1<<endl;
        // cout<<"result.coord_2 = "<<endl<<result.coord_2<<endl;

        for (i=0; i<result.coord_1.rows(); i++) {
            pts_2.push_back(boost::make_tuple(
                    result.coord_1(i, 0),
                    result.coord_1(i, 1)));
        }
        for (i=0; i<result.coord_2.rows(); i++) {
            pts_2.push_back(boost::make_tuple(
                    result.coord_2(i, 0),
                    result.coord_2(i, 1)));
        }
        gp2 << "plot '-' with points title 'IDENTIFIED lidar points'\n";
        gp2.send1d(pts_2);

        // calculate dx & dy
        MatrixXd court_coord(14,2);
        court_coord << 0, 0, 0, 0.25*a, 0, a, 0, 1.5*a, 0, 2.0*a, 0, 2.75*a, 0, 3.0*a, b, 0, b, 0.25*a, b, a, b, 1.5*a, b, 2.0*a, b, 2.75*a, b, 3.0*a;
        // cout<<"court_coord = "<<endl<<court_coord<<endl;
        double dx=0, dy=0;
        int count;
        count = 0;
        if (line1_exist){
            for (m=0; m<7; m++){
                if ( result.coord_1(m,2) != 0){
                    // cout<<"court_coord = "<< court_coord.row(result.coord_1(m,2)-1)<<endl<< "robot coord = "<<result.coord_1.row(m)<<endl;
                    dx += court_coord(result.coord_1(m,2)-1,0) - result.coord_1(m,0)*cos(result.angle) - result.coord_1(m,1)*sin(result.angle);
                    dy += court_coord(result.coord_1(m,2)-1,1) + result.coord_1(m,0)*sin(result.angle) - result.coord_1(m,1)*cos(result.angle);
                    count++;
                }
            }
        }
        if (line2_exist){
            for (m=0; m<7; m++){
                if ( result.coord_2(m,2) != 0){
                    // cout<<"court_coord = "<< court_coord.row(result.coord_2(m,2)-1)<<endl<< "robot coord = "<<result.coord_2.row(m)<<endl;
                    dx += court_coord(result.coord_2(m,2)-1,0) - result.coord_2(m,0)*cos(result.angle) - result.coord_2(m,1)*sin(result.angle);
                    dy += court_coord(result.coord_2(m,2)-1,1) + result.coord_2(m,0)*sin(result.angle) - result.coord_2(m,1)*cos(result.angle);
                    count++;
                }
            }
        }
        result.dx = dx/count;
        result.dy = dy/count;
        result.success = 1;
        // cout<<"dx = "<<result.dx<<"  dy = "<<result.dy<< endl;
        return result;
    }

}
