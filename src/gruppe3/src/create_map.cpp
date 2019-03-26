#include <iostream>
#include "create_map.h"
using namespace Eigen;
using namespace std;

playground create_map(MatrixXd coord_1, MatrixXd coord_2, double tangent_ortho, double tangent_main,double a, double b) {
    int i, j;
    playground result;
    double A, B, AA, BB, d1, d2, cos1, cos2;
    VectorXi index(7);
    double direction_x, direction_y;
    double origin_x, origin_y;
    double tangent_sum = 0;
    double pole_tangent;


    cout<<"a="<<a<<"  b="<<b<<endl;
    A = tan(tangent_ortho);
    B = -1;
    d1 = (fabs(A*coord_1(0,0) + B*coord_1(0,1)) + fabs(A*coord_2(0,0) + B*coord_2(0,1))) / sqrt(A*A+B*B) / 2;
    d2 = (fabs(A*coord_1(6,0) + B*coord_1(6,1)) + fabs(A*coord_2(6,0) + B*coord_2(6,1))) / sqrt(A*A+B*B) / 2;
    cout<<"d1="<<d1<<"  d2="<<d2<<endl;
    if (fabs(d1) < fabs(d2)){
        index << 0,1,2,3,4,5,6;
        if (fabs(coord_1(6,0)-coord_1(0,0)) < 1e-5){
            direction_x = 0;
            direction_y = fabs(coord_1(6,0)-coord_1(0,0));
            result.angle = (1 - fabs(coord_1(6,0)-coord_1(0,0))) * 3.1416;
        }
        else if (coord_1(6,0)-coord_1(0,0) > 0){
            direction_x = cos(tangent_main);
            direction_y = sin(tangent_main);
            result.angle = - 3.1416/2 + tangent_main;
        }
        else{
            direction_x = -cos(tangent_main);
            direction_y = -sin(tangent_main);
            result.angle = 3.1416/2 + tangent_main;
        }
    }
    else if (fabs(d1) > fabs(d2)){
        index << 6,5,4,3,2,1,0;
        if (fabs(coord_1(6,0)-coord_1(0,0)) <1e-5){
            direction_x = 0;
            direction_y = fabs(coord_1(0,0)-coord_1(6,0));
            result.angle = (1 - fabs(coord_1(0,0)-coord_1(6,0))) * 3.1416;
        }
        else if (coord_1(0,0)-coord_1(6,0) > 0){
            direction_x = cos(tangent_main);
            direction_y = sin(tangent_main);
            result.angle = - 3.1416/2 + tangent_main;
        }
        else{
            direction_x = -cos(tangent_main);
            direction_y = -sin(tangent_main);
            result.angle = 3.1416/2 + tangent_main;
        }
    }
    else
    cout<<"error: didn't find our side"<< endl;
    // cout<<"index: "<<index<<endl;

    // determine the original point-----------------------------------------------------------------------------------
    cos1 = -coord_1(index(0), 0)*direction_y + coord_1(index(0), 1)*direction_x;
    cos2 = -coord_2(index(0), 0)*direction_y + coord_2(index(0), 1)*direction_x;
    cout<<"next line"<<endl;
    cout<<"coord_1.rows()"<<coord_1.rows()<<"coord_2.rows()"<<coord_2.rows()<<endl;


    result.coord_1 = MatrixXd::Zero(7,3);
    result.coord_2 = MatrixXd::Zero(7,3);
    if (cos1 > 0 && cos2 < 0){
        origin_x = coord_1(index(0), 0);
        origin_y = coord_1(index(0), 1);
        cout<<"origin_x"<<origin_x<<endl;
        for (i=0; i<7; i++){
            cout<<"1---i="<<i<<endl;
            result.coord_1.row(i)  = coord_1.row(index(i));
            result.coord_2.row(i)  = coord_2.row(index(i));
        }
    }
    else if (cos1 < 0 && cos2 > 0){
        origin_x = coord_2(index(0), 0);
        origin_y = coord_2(index(0), 1);
        cout<<"origin_x"<<origin_x<<endl;
        for (i=0; i<7; i++){
            // cout<<"2---i="<<i<<"index(i)="<<index(i)<<"coord_2(index(i),0)="<<coord_2(index(i),0)<<endl;
            result.coord_1.row(i)  = coord_2.row(index(i));
            result.coord_2.row(i)  = coord_1.row(index(i));
        }
    }
    else
        cout<<"error: didn't find origin"<< endl;

    cout<<"===================================="<<endl;
    cout<<"Origin: x="<<origin_x<<"   y="<<origin_y<<endl;
    cout<<"Main direction: x="<<direction_x<<"   y="<<direction_y<<endl;
    cout<<"Main angle: "<<result.angle/3.1416*180<<endl;




    MatrixXd court_coord(14,2);
    court_coord << 0, 0, 0, 0.25*a, 0, a, 0, 1.5*a, 0, 2.0*a, 0, 2.75*a, 0, 3.0*a, b, 0, b, 0.25*a, b, a, b, 1.5*a, b, 2.0*a, b, 2.75*a, b, 3.0*a;
    // cout<<"court_coord = "<<endl<<court_coord<<endl;
    double dx=0, dy=0;
    int count;
    count = 0;
    for (i=0; i<7; i++){
        if(result.coord_1(i,2) != 0){
            dx += court_coord(i,0) - result.coord_1(i,0)*cos(result.angle) - result.coord_1(i,1)*sin(result.angle);
            dy += court_coord(i,1) + result.coord_1(i,0)*sin(result.angle) - result.coord_1(i,1)*cos(result.angle);
            count++;
        }
    }
    for (i=0; i<7; i++){
        if(result.coord_2(i,2) != 0){
            dx += court_coord(i+7,0) - result.coord_2(i,0)*cos(result.angle) - result.coord_2(i,1)*sin(result.angle);
            dy += court_coord(i+7,1) + result.coord_2(i,0)*sin(result.angle) - result.coord_2(i,1)*cos(result.angle);
            count++;
        }
    }
    result.dx = dx/count;
    result.dy = dy/count;
    result.a  = a;
    result.b  = b;
    cout<<"dx = "<<result.dx<<"  dy = "<<result.dy<< endl;


    return result;
}
