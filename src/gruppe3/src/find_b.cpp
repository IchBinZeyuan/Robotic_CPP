#include <iostream>
#include "find_b.h"
using namespace Eigen;
playground find_b(MatrixXd coord_1, MatrixXd coord_2, double A, double B) {
    playground result;
    int i, j;
    double C1=0, C2=0;
    double d1, d2;
    double direction_x, direction_y;

    for (i=0; i<coord_1.rows(); i++){
        C1 += -A*coord_1(i,0) - B*coord_1(i,1);
    }
    for (i=0; i<coord_2.rows(); i++){
        C2 += -A*coord_2(i,0) - B*coord_2(i,1);
    }
    C1 = C1 / coord_1.rows();
    C2 = C2 / coord_2.rows();

    d1 = fabs(C1) / sqrt(A*A + B*B);
    d2 = fabs(C2) / sqrt(A*A + B*B);

    if(d1 < d2){
        direction_x = (C1*A)/(A*A+B*B);
        direction_y = (C1*B)/(A*A+B*B);
        result.d1 = (d1+d2)/2.0 - d1;
    }
    else{
        direction_x = (C2*A)/(A*A+B*B);
        direction_y = (C2*B)/(A*A+B*B);
        result.d1 = (d1+d2)/2.0 - d2;
    }

    if (fabs(direction_y)<1e-5){
        if (direction_x < 0 ){
            result.angle_turn = 3.1416/2;
        }
        if (direction_x > 0 ){
            result.angle_turn = -3.1416/2;
        }
    }
    else{
        result.angle_turn = -atan(direction_x/direction_y);
        if(direction_y < 0){
            result.angle_turn -= 3.1416;
        }
    }
    while(result.angle_turn < -3.1416){
        result.angle_turn += 2*3.1416;
    }
    while(result.angle_turn > 3.1416){
        result.angle_turn -= 2*3.1416;
    }
    result.coord_1 = MatrixXd::Zero(7,2);
    result.coord_2 = MatrixXd::Zero(7,2);
    result.angle = 0;
    result.d2 = 0;
    result.success = 1;

    std::cout<<
    std::cout<<"Turn angle:"<<result.angle_turn/3.1416*180<<std::endl;
    std::cout<<"d1:"<<d1<<std::endl;
    std::cout<<"d2::"<<d2<<std::endl;
    std::cout<<"Go forward::"<<result.d1<<std::endl;


    return result;
}
