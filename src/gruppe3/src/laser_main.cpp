#include "laser_main.h"
#include "gnuplot-iostream.h"
#include "cal_coordinate.h"
#include "clear_angle.h"
#include "clear_average.h"
#include "find_tangent.h"
#include "find_colinear.h"
#include "sort_lines.h"
#include "find_ortho.h"
#include "PredictPoints.h"
#include "create_map.h"
#include "find_b.h"
using namespace Eigen;
using namespace std;
const double PI = 3.14159265358979323846;

playground lidar_main(VectorXd ranges, bool full_map) {
    Gnuplot gp1, gp2, gp3, gp4, gp44, gp5, gp6, gp7, gp8, gp9;
    double *a;
    int N, M;
    int count;
    int i,j;
    playground result;
    double tangent_main, tangent_ortho;
    double angle_min = -3.12413907051;
    double angle_max = 3.14159274101;
    MatrixXd coord_l, coord_c1, coord_a, coord_c2, coord_colinear, coord_ortho,coord_1, coord_2, coord_ortho2;
    vector<boost::tuple<double, double> > pts_1, pts_2, pts_3, pts_4, pts_44, pts_5, pts_6, pts_7, pts_8, pts_9;

    // average
    double overlap_th = 0.1;

    // clear1
    double reduce_rate_1 = 0.8;
    int angle_num_1 = 36;
    int max_num_1 = 4;

    // clear2
    double reduce_rate_2 = 0.8;
    int angle_num_2 = 36;
    int max_num_2 = 4;

    // find tangent
    double colinear_th = 0.05;
    double dense_th    = 0.25;
    double div_th      = 0.05;

    // find colinear candidates
    double tangent_th = 0.1;

    // find orthogonal candidates
    double ortho_th = 0.1;

    // sort lines
    double sort_th = 0.15;

// load data=======================================================================================
    // coord = load_data();
    coord_l=cal_coordinate(ranges, 1);

    if (coord_l.rows() == 0){
        result.success = 0;
        return result;
    }
    for (i=0; i<coord_l.rows(); i++) {
        pts_9.push_back(boost::make_tuple(
                coord_l(i, 0),
                coord_l(i, 1)));
    }

    gp9 << "plot '-' with points title '0-load data'\n";
    gp9.send1d(pts_9);


//  find main direction=============================================================================
    cout<<"RANSAC==========================="<<endl;
    line line_main = find_tangent(coord_c2, colinear_th, dense_th, div_th);
    if (line_main.success == 0){
        result.success = 0;
        return result;
    }
    tangent_main = line_main.tangent_main;

    cout<<"tangent_main="<<tangent_main<<endl;
    tangent_ortho = tangent_main - PI/2;
    if (tangent_ortho < -PI/2)
        tangent_ortho = tangent_ortho + PI;

    for (i=0; i<line_main.coord_main.rows(); i++) {
        pts_4.push_back(boost::make_tuple(
                line_main.coord_main(i, 0),
                line_main.coord_main(i, 1)));
    }

    gp4 << "plot '-' with points title '4-RANSAC main direction'\n";
    gp4.send1d(pts_4);

    // for (i=0; i<line_main.coord_rest.rows(); i++) {
    //     pts_44.push_back(boost::make_tuple(
    //             line_main.coord_rest(i, 0),
    //             line_main.coord_rest(i, 1)));
    // }
    //
    // gp44 << "plot '-' with points title '4-RANSAC rest'\n";
    // gp44.send1d(pts_44);

    cout<<"found RANSAC candidates,"<<line_main.coord_main.rows()<<endl;

//  find colinear points=============================================================================
cout<<"find colinear candidates==========================="<<endl;

    coord_colinear = find_colinear(line_main.coord_rest, tangent_th, tangent_main);

    for (i=0; i<line_main.coord_main.rows(); i++) {
        pts_5.push_back(boost::make_tuple(
                line_main.coord_main(i, 0),
                line_main.coord_main(i, 1)));
    }
    for (i=0; i<coord_colinear.rows(); i++) {
        pts_5.push_back(boost::make_tuple(
                coord_colinear(i, 0),
                coord_colinear(i, 1)));
    }

    if (coord_colinear.rows() == 0){
        result.success = 0;
        return result;
    }

    gp5 << "plot '-' with points title '5-colinear candidates'\n";
    gp5.send1d(pts_5);
    cout<<"find colinear candidates,"<<coord_colinear.rows()<<endl;

//  find orthogonal candidates=======================================================================
cout<<"find orthogonal candidates==========================="<<endl;
    twin ortho1;
    ortho1 = find_ortho(line_main.coord_main, coord_colinear, ortho_th, tangent_ortho, 0);

    for (i=0; i<ortho1.coord_1.rows(); i++) {
        pts_6.push_back(boost::make_tuple(
                ortho1.coord_1(i, 0),
                ortho1.coord_1(i, 1)));
    }
    for (i=0; i<ortho1.coord_2.rows(); i++) {
        pts_6.push_back(boost::make_tuple(
                ortho1.coord_2(i,0),
                ortho1.coord_2(i,1)));
    }

    if (ortho1.coord_1.rows() < 3 || ortho1.coord_2.rows() < 3 ){
        result.success = 0;
        return result;
    }

    gp6 << "plot '-' with points title '6-orthogonal candidates'\n";
    gp6.send1d(pts_6);
    cout<<"find orthogonal candidates,"<<ortho1.coord_1.rows()<<endl;
    cout<<"find orthogonal candidates,"<<ortho1.coord_2.rows()<<endl;


//  sort lines=======================================================================================
    coord_1 = ortho1.coord_1;
    cout<<"sort lines==========================="<<endl;
    if (line_main.C_main>0){
        coord_2 = sort_lines(ortho1.coord_2, line_main.A_main, line_main.B_main, line_main.C_main, sort_th, tangent_main, -1, dense_th);
    }
    else{
        coord_2 = sort_lines(ortho1.coord_2, line_main.A_main, line_main.B_main, line_main.C_main, sort_th, tangent_main, 1, dense_th);
    }

    cout<<"sort candidates,"<<coord_1.rows()<<'/'<<coord_2.rows()<<endl;

    for (i=0; i<coord_1.rows(); i++) {
        pts_2.push_back(boost::make_tuple(
                coord_1(i, 0),
                coord_1(i, 1)));
    }
    for (i=0; i<coord_2.rows(); i++) {
        pts_2.push_back(boost::make_tuple(
                coord_2(i,0),
                coord_2(i,1)));
    }

    if (coord_2.rows() < 3){
        result.success = 0;
        return result;
    }
    gp2 << "plot '-' with points title '6,1-sorted lines candidates'\n";
    gp2.send1d(pts_2);


//  find orthogonal for the second time========================================================================
    cout<<"find orthogonal for the second time==========================="<<endl;
    twin ortho2;
    ortho2 = find_ortho(coord_1, coord_2, ortho_th, tangent_ortho, 1);

    for (i=0; i<ortho2.coord_1.rows(); i++) {
        pts_7.push_back(boost::make_tuple(
                ortho2.coord_1(i, 0),
                ortho2.coord_1(i, 1)));
    }
    for (i=0; i<ortho2.coord_2.rows(); i++) {
        pts_7.push_back(boost::make_tuple(
                ortho2.coord_2(i,0),
                ortho2.coord_2(i,1)));
    }
    gp7 << "plot '-' with points title '7-final pfosten'\n";
    gp7.send1d(pts_7);

    if (ortho2.coord_1.rows() < 3 || ortho2.coord_2.rows() < 3 || ortho2.coord_1.rows() != ortho2.coord_2.rows()){
        result.success = 0;
        return result;
    }


    cout<<"find final orthogonal candidates,"<<ortho2.coord_1.rows()<<endl;
    cout<<"find final orthogonal candidates,"<<ortho2.coord_2.rows()<<endl;

    if (full_map){
    // >Prediction ========================================================================================================
        cout<<"Prediction==========================="<<endl;
        twin prediction;
        prediction = PredictPoints(ortho2.coord_1.transpose(), ortho2.coord_2.transpose(), tangent_main);
        if (prediction.coord_1.rows() != 7 || prediction.coord_2.rows() != 7){
            result.success = 0;
            return result;
        }
        for (i=0; i<prediction.coord_1.rows(); i++) {
            pts_8.push_back(boost::make_tuple(
                    prediction.coord_1(i, 0),
                    prediction.coord_1(i, 1)));
        }
        for (i=0; i<prediction.coord_2.rows(); i++) {
            pts_8.push_back(boost::make_tuple(
                    prediction.coord_2(i,0),
                    prediction.coord_2(i,1)));
        }

        gp8 << "plot '-' with points title '8-Prediction'\n";
        gp8.send1d(pts_8);
        cout<<"find positive candidates,"<<prediction.coord_1.rows()<<endl;
        cout<<"find negative candidates,"<<prediction.coord_2.rows()<<endl;

        result = create_map(prediction.coord_1, prediction.coord_2, tangent_ortho, tangent_main, 1.2, 3.0);
        result.success = 1;
    }

    else{
        result = find_b(ortho2.coord_1, ortho2.coord_2, line_main.A_main, line_main.B_main );
    }
    return result;
}
