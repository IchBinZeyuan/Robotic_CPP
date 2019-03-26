#include "PredictPoints.h"
#define PI 3.14159265358979323846
using namespace Eigen;
using namespace std;
playground PredictPoints(Matrix<double, 2, Dynamic> datagroup1, Matrix<double, 2, Dynamic> datagroup2, double theta, double a_pre  ){
//导入数据datagroup1，datagroup2，theta，points_vector
    //3点数据
//    double theta = -0.461363941001257;
//    double points_vector = tan(theta);
//    cout << "theta =" << endl << theta << endl << endl;
//    cout << "points_vector =" << endl << points_vector << endl << endl;
//
//    Matrix<double, 2, Dynamic> datagroup1 = MatrixXd::Zero(2, 3);
//    Matrix<double, 2, Dynamic> datagroup2 = MatrixXd::Zero(2, 3);
//    datagroup1(0, 0) = -0.999966039333420;datagroup1(1, 0) = 0.153476049834836;
//    datagroup1(0, 1) = -0.705792310157629;datagroup1(1, 1) = 0.0175216555515422;
//    datagroup1(0, 2) = 1.08413104952632;datagroup1(1, 2) = -0.882421820322422;
//    datagroup2(0, 0) = 0.348664834269911;datagroup2(1, 0) = 2.65533170746547;
//    datagroup2(0, 1) = 0.632036620236838;datagroup2(1, 1) = 2.56091313856041;
//    datagroup2(0, 2) = 2.35828617623127;datagroup2(1, 2) = 1.64525902684280;
//    cout << "datagroup1 =" << endl << datagroup1 << endl << endl;
//    cout << "datagroup2 =" << endl << datagroup2 << endl << endl;



    playground prediction;
//    //5点数据
//    double theta = 0.864665177792946;
    double points_vector = tan(theta);
//    Matrix<double, 2, Dynamic> datagroup1 = MatrixXd::Zero(2, 5);
//    Matrix<double, 2, Dynamic> datagroup2 = MatrixXd::Zero(2, 5);
//    datagroup1 << -0.728347895110084,-0.534307441222346, -0.00496265778395290,0.380068129339544,0.742080667883283,0.0877619871723321,0.316887755986846,0.960721707271682,1.40159634091403,1.84238213505266;
//    datagroup2 << 1.43182270502287,1.64260216120889,2.15347868493068,2.52657237825535,2.85664930489133,-1.79093100645261,-1.53869024935135,-0.911323039204724,-0.466975476544473,-0.0372233740772741;
    //
    // cout << "theta =" << endl << theta << endl << endl;
    // cout << "points_vector =" << endl << points_vector << endl << endl;
    // cout << "datagroup1 =" << endl << datagroup1 << endl << endl;
    // cout << "datagroup2 =" << endl << datagroup2 << endl << endl;

    //数据预处理

    int num1 = datagroup1.cols();
    int num2 = datagroup2.cols();
    Matrix<double, 1, Dynamic> line_b1 = MatrixXd::Zero(1, num1);
    Matrix<double, 1, Dynamic> line_b2 = MatrixXd::Zero(1, num2);
    Matrix<double, 2, Dynamic> data_after_pre_1 = MatrixXd::Zero(2, num1);
    Matrix<double, 2, Dynamic> data_after_pre_2 = MatrixXd::Zero(2, num2);
    double line_b1_value = 0;
    double line_b2_value = 0;
    for (int i = 0; i < num1; i++) {
        line_b1(i) = datagroup1(1,i) - points_vector * datagroup1(0,i);
        line_b2(i) = datagroup2(1,i) - points_vector * datagroup2(0,i);
    }
    line_b1_value = line_b1.mean();
    line_b2_value = line_b2.mean();
    for (int i = 0; i < num1; i++) {
        data_after_pre_1(0,i) = (points_vector * (datagroup1(1,i) - line_b1_value) + datagroup1(0,i))/(points_vector*points_vector+1);
        data_after_pre_1(1,i) = points_vector * data_after_pre_1(0,i) + line_b1_value;
        data_after_pre_2(0,i) = (points_vector * (datagroup2(1,i) - line_b2_value) + datagroup2(0,i))/(points_vector*points_vector+1);
        data_after_pre_2(1,i) = points_vector * data_after_pre_2(0,i) + line_b2_value;
    }
    datagroup1 = data_after_pre_1;
    datagroup2 = data_after_pre_2;
    // cout << "after preprocessing: datagroup1 =" << endl << datagroup1 << endl << endl;
    // cout << "after preprocessing: datagroup2 =" << endl << datagroup2 << endl << endl;
//排列数据 并 加载预定义矩阵

    if (points_vector < 0 || points_vector == 0 ) {
        for (int i = 0; i < num1-1; i++) {
            for (int j = i+1; j < num1; j++){
                if (datagroup1(0,i) > datagroup1(0,j)){
                    Matrix<double, 2, 1> ex1 = MatrixXd::Zero(2, 1);
                    ex1 = datagroup1.col(j);
                    datagroup1.col(j) = datagroup1.col(i);
                    datagroup1.col(i) = ex1;
                }
                if (datagroup2(0,i) > datagroup2(0,j)){
                    Matrix<double, 2, 1> ex2 = MatrixXd::Zero(2, 1);
                    ex2 = datagroup2.col(j);
                    datagroup2.col(j) = datagroup2.col(i);
                    datagroup2.col(i) = ex2;
                }
            }
        }
    }
    else if (points_vector > 0) {
        for (int i = 0; i < num1-1; i++) {
            for (int j = i+1; j < num1; j++){
                if (datagroup1(0,i) < datagroup1(0,j)){
                    Matrix<double, 2, 1> ex1 = MatrixXd::Zero(2, 1);
                    ex1 = datagroup1.col(j);
                    datagroup1.col(j) = datagroup1.col(i);
                    datagroup1.col(i) = ex1;
                }
                if (datagroup2(0,i) < datagroup2(0,j)){
                    Matrix<double, 2, 1> ex2 = MatrixXd::Zero(2, 1);
                    ex2 = datagroup2.col(j);
                    datagroup2.col(j) = datagroup2.col(i);
                    datagroup2.col(i) = ex2;
                }
            }
        }
    }
    else {
        for (int i = 0; i < num1-1; i++) {
            for (int j = i+1; j < num1; j++){
                if (datagroup1(1,i) < datagroup1(1,j)){
                    Matrix<double, 2, 1> ex1 = MatrixXd::Zero(2, 1);
                    ex1 = datagroup1.col(j);
                    datagroup1.col(j) = datagroup1.col(i);
                    datagroup1.col(i) = ex1;
                }
                if (datagroup2(1,i) < datagroup2(1,j)){
                    Matrix<double, 2, 1> ex2 = MatrixXd::Zero(2, 1);
                    ex2 = datagroup2.col(j);
                    datagroup2.col(j) = datagroup2.col(i);
                    datagroup2.col(i) = ex2;
                }
            }
        }
    }
    // cout << "datagroup1 with arrangment =" << endl << datagroup1 << endl << endl;
    // cout << "datagroup2 with arrangment =" << endl << datagroup2 << endl << endl;

    Matrix<double, Dynamic, Dynamic> distance;
    Matrix<double, Dynamic, Dynamic> points_position;
    if (num1 == 7 && num2 == 7) {
        distance = MatrixXd::Zero(1, 6);
        points_position = MatrixXd::Zero(1, 7);
        distance(0, 0) = 0.2500; distance(0, 1) = 0.7500; distance(0, 2) = 0.5000;
        distance(0, 3) = 0.5000; distance(0, 4) = 0.7500; distance(0, 5) = 0.2500;
        // cout << "distance =" << endl << distance << endl << endl;
        points_position << 1,1,1,1,1,1,1;
        // cout << "points_position =" << endl << points_position << endl << endl;
    }
    if (num1 == 6 && num2 == 6) {
        distance = MatrixXd::Zero(7, 5);
        points_position = MatrixXd::Zero(7, 7);
        distance(0, 0) = 0.7500;   distance(0, 1) = 0.5000;   distance(0, 2) = 0.5000;   distance(0, 3) = 0.7500;   distance(0, 4) = 0.2500;
        distance(1, 0) = 1.0000;   distance(1, 1) = 0.5000;   distance(1, 2) = 0.5000;   distance(1, 3) = 0.7500;   distance(1, 4) = 0.2500;
        distance(2, 0) = 0.2500;   distance(2, 1) = 1.2500;   distance(2, 2) = 0.5000;   distance(2, 3) = 0.7500;   distance(2, 4) = 0.2500;
        distance(3, 0) = 0.2500;   distance(3, 1) = 0.7500;   distance(3, 2) = 1.0000;   distance(3, 3) = 0.7500;   distance(3, 4) = 0.2500;
        distance(4, 0) = 0.2500;   distance(4, 1) = 0.7500;   distance(4, 2) = 0.5000;   distance(4, 3) = 1.2500;   distance(4, 4) = 0.2500;
        distance(5, 0) = 0.2500;   distance(5, 1) = 0.7500;   distance(5, 2) = 0.5000;   distance(5, 3) = 0.5000;   distance(5, 4) = 1.0000;
        distance(6, 0) = 0.2500;   distance(6, 1) = 0.7500;   distance(6, 2) = 0.5000;   distance(6, 3) = 0.5000;   distance(6, 4) = 0.7500;
        // cout << "distance =" << endl << distance << endl << endl;
        points_position << 0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0;
        // cout << "points_position =" << endl << points_position << endl << endl;
    }
    if (num1 == 5 && num2 == 5) {
        distance = MatrixXd::Zero(21, 4);
        points_position = MatrixXd::Zero(21, 7);
        distance(0, 0) = 0.5000;    distance(0, 1) = 0.5000;    distance(0, 2) = 0.7500;    distance(0, 3) = 0.2500;
        distance(1, 0) = 1.2500;    distance(1, 1) = 0.5000;    distance(1, 2) = 0.7500;    distance(1, 3) = 0.2500;
        distance(2, 0) = 0.7500;    distance(2, 1) = 1.0000;    distance(2, 2) = 0.7500;    distance(2, 3) = 0.2500;
        distance(3, 0) = 0.7500;    distance(3, 1) = 0.5000;    distance(3, 2) = 1.2500;    distance(3, 3) = 0.2500;
        distance(4, 0) = 0.7500;    distance(4, 1) = 0.5000;    distance(4, 2) = 0.5000;    distance(4, 3) = 1.0000;
        distance(5, 0) = 0.7500;    distance(5, 1) = 0.5000;    distance(5, 2) = 0.5000;    distance(5, 3) = 0.7500;
        distance(6, 0) = 1.5000;    distance(6, 1) = 0.5000;    distance(6, 2) = 0.7500;    distance(6, 3) = 0.2500;
        distance(7, 0) = 1.0000;    distance(7, 1) = 1.0000;    distance(7, 2) = 0.7500;    distance(7, 3) = 0.2500;
        distance(8, 0) = 1.0000;    distance(8, 1) = 0.5000;    distance(8, 2) = 1.2500;    distance(8, 3) = 0.2500;
        distance(9, 0) = 1.0000;    distance(9, 1) = 0.5000;    distance(9, 2) = 0.5000;    distance(9, 3) = 1.0000;
        distance(10, 0) = 1.0000;   distance(10, 1) = 0.5000;    distance(10, 2) = 0.5000;    distance(10, 3) = 0.7500;
        distance(11, 0) = 0.2500;   distance(11, 1) = 1.7500;    distance(11, 2) = 0.7500;    distance(11, 3) = 0.2500;
        distance(12, 0) = 0.2500;   distance(12, 1) = 1.2500;    distance(12, 2) = 1.2500;    distance(12, 3) = 0.2500;
        distance(13, 0) = 0.2500;   distance(13, 1) = 1.2500;    distance(13, 2) = 0.5000;    distance(13, 3) = 1.0000;
        distance(14, 0) = 0.2500;   distance(14, 1) = 1.2500;    distance(14, 2) = 0.5000;    distance(14, 3) = 0.7500;
        distance(15, 0) = 0.2500;   distance(15, 1) = 0.7500;    distance(15, 2) = 1.7500;    distance(15, 3) = 0.2500;
        distance(16, 0) = 0.2500;   distance(16, 1) = 0.7500;    distance(16, 2) = 1.0000;    distance(16, 3) = 1.0000;
        distance(17, 0) = 0.2500;   distance(17, 1) = 0.7500;    distance(17, 2) = 1.0000;    distance(17, 3) = 0.7500;
        distance(18, 0) = 0.2500;   distance(18, 1) = 0.7500;    distance(18, 2) = 0.5000;    distance(18, 3) = 1.5000;
        distance(19, 0) = 0.2500;   distance(19, 1) = 0.7500;    distance(19, 2) = 0.5000;    distance(19, 3) = 1.2500;
        distance(20, 0) = 0.2500;   distance(20, 1) = 0.7500;    distance(20, 2) = 0.5000;    distance(20, 3) = 0.5000;
        // cout << "distance =" << endl << distance << endl << endl;
        points_position << 0,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0;
        // cout << "points_position =" << endl << points_position << endl << endl;
    }
    if (num1 == 4 && num2 == 4) {
        distance = MatrixXd::Zero(35, 3);
        points_position = MatrixXd::Zero(35, 7);
        distance(0, 0) = 0.5000; distance(0, 1) = 0.7500; distance(0, 2) = 0.2500;
        distance(1, 0) = 1.0000; distance(1, 1) = 0.7500; distance(1, 2) = 0.2500;
        distance(2, 0) = 0.5000; distance(2, 1) = 1.2500; distance(2, 2) = 0.2500;
        distance(3, 0) = 0.5000; distance(3, 1) = 0.5000; distance(3, 2) = 1.0000;
        distance(4, 0) = 0.5000; distance(4, 1) = 0.5000; distance(4, 2) = 0.7500;
        distance(5, 0) = 1.7500; distance(5, 1) = 0.7500; distance(5, 2) = 0.2500;
        distance(6, 0) = 1.2500; distance(6, 1) = 1.2500; distance(6, 2) = 0.2500;
        distance(7, 0) = 1.2500; distance(7, 1) = 0.5000; distance(7, 2) = 1.0000;
        distance(8, 0) = 1.2500; distance(8, 1) = 0.5000; distance(8, 2) = 0.7500;
        distance(9, 0) = 0.7500; distance(9, 1) = 1.7500; distance(9, 2) = 0.2500;
        distance(10, 0) = 0.7500; distance(10, 1) = 1.0000; distance(10, 2) = 1.0000;
        distance(11, 0) = 0.7500; distance(11, 1) = 1.0000; distance(11, 2) = 0.7500;
        distance(12, 0) = 0.7500; distance(12, 1) = 0.5000; distance(12, 2) = 1.5000;
        distance(13, 0) = 0.7500; distance(13, 1) = 0.5000; distance(13, 2) = 1.2500;
        distance(14, 0) = 0.7500; distance(14, 1) = 0.5000; distance(14, 2) = 0.5000;
        distance(15, 0) = 2.0000; distance(15, 1) = 0.7500; distance(15, 2) = 0.2500;
        distance(16, 0) = 1.5000; distance(16, 1) = 1.2500; distance(16, 2) = 0.2500;
        distance(17, 0) = 1.5000; distance(17, 1) = 0.5000; distance(17, 2) = 1.0000;
        distance(18, 0) = 1.5000; distance(18, 1) = 0.5000; distance(18, 2) = 0.7500;
        distance(19, 0) = 1.0000; distance(19, 1) = 1.7500; distance(19, 2) = 0.2500;
        distance(20, 0) = 1.0000; distance(20, 1) = 1.0000; distance(20, 2) = 1.0000;
        distance(21, 0) = 1.0000; distance(21, 1) = 1.0000; distance(21, 2) = 0.7500;
        distance(22, 0) = 1.0000; distance(22, 1) = 0.5000; distance(22, 2) = 1.5000;
        distance(23, 0) = 1.0000; distance(23, 1) = 0.5000; distance(23, 2) = 1.2500;
        distance(24, 0) = 1.0000; distance(24, 1) = 0.5000; distance(24, 2) = 0.5000;
        distance(25, 0) = 0.2500; distance(25, 1) = 2.5000; distance(25, 2) = 0.2500;
        distance(26, 0) = 0.2500; distance(26, 1) = 1.7500; distance(26, 2) = 1.0000;
        distance(27, 0) = 0.2500; distance(27, 1) = 1.7500; distance(27, 2) = 0.7500;
        distance(28, 0) = 0.2500; distance(28, 1) = 1.2500; distance(28, 2) = 1.5000;
        distance(29, 0) = 0.2500; distance(29, 1) = 1.2500; distance(29, 2) = 1.2500;
        distance(30, 0) = 0.2500; distance(30, 1) = 1.2500; distance(30, 2) = 0.5000;
        distance(31, 0) = 0.2500; distance(31, 1) = 0.7500; distance(31, 2) = 2.0000;
        distance(32, 0) = 0.2500; distance(32, 1) = 0.7500; distance(32, 2) = 1.7500;
        distance(33, 0) = 0.2500; distance(33, 1) = 0.7500; distance(33, 2) = 1.0000;
        distance(34, 0) = 0.2500; distance(34, 1) = 0.7500; distance(34, 2) = 0.5000;
        // cout << "distance =" << endl << distance << endl << endl;
        points_position
                << 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0;
        // cout << "points_position =" << endl << points_position << endl << endl;
    }
    if (num1 == 3 && num2 == 3) {
        distance = MatrixXd::Zero(35, 2);
        points_position = MatrixXd::Zero(35, 7);
        distance(0, 0) = 0.7500; distance(0, 1) = 0.2500;
        distance(1, 0) = 1.2500; distance(1, 1) = 0.2500;
        distance(2, 0) = 0.5000; distance(2, 1) = 1.0000;
        distance(3, 0) = 0.5000; distance(3, 1) = 0.7500;
        distance(4, 0) = 1.7500; distance(4, 1) = 0.2500;
        distance(5, 0) = 1.0000; distance(5, 1) = 1.0000;
        distance(6, 0) = 1.0000; distance(6, 1) = 0.7500;
        distance(7, 0) = 0.5000; distance(7, 1) = 1.5000;
        distance(8, 0) = 0.5000; distance(8, 1) = 1.2500;
        distance(9, 0) = 0.5000; distance(9, 1) = 0.5000;
        distance(10, 0) = 2.5000; distance(10, 1) = 0.2500;
        distance(11, 0) = 1.7500; distance(11, 1) = 1.0000;
        distance(12, 0) = 1.7500; distance(12, 1) = 0.7500;
        distance(13, 0) = 1.2500; distance(13, 1) = 1.5000;
        distance(14, 0) = 1.2500; distance(14, 1) = 1.2500;
        distance(15, 0) = 1.2500; distance(15, 1) = 0.5000;
        distance(16, 0) = 0.7500; distance(16, 1) = 2.0000;
        distance(17, 0) = 0.7500; distance(17, 1) = 1.7500;
        distance(18, 0) = 0.7500; distance(18, 1) = 1.0000;
        distance(19, 0) = 0.7500; distance(19, 1) = 0.5000;
        distance(20, 0) = 2.7500; distance(20, 1) = 0.2500;
        distance(21, 0) = 2.0000; distance(21, 1) = 1.0000;
        distance(22, 0) = 2.0000; distance(22, 1) = 0.7500;
        distance(23, 0) = 1.5000; distance(23, 1) = 1.5000;
        distance(24, 0) = 1.5000; distance(24, 1) = 1.2500;
        distance(25, 0) = 1.5000; distance(25, 1) = 0.5000;
        distance(26, 0) = 1.0000; distance(26, 1) = 2.0000;
        distance(27, 0) = 1.0000; distance(27, 1) = 1.7500;
        distance(28, 0) = 1.0000; distance(28, 1) = 1.0000;
        distance(29, 0) = 1.0000; distance(29, 1) = 0.5000;
        distance(30, 0) = 0.2500; distance(30, 1) = 2.7500;
        distance(31, 0) = 0.2500; distance(31, 1) = 2.5000;
        distance(32, 0) = 0.2500; distance(32, 1) = 1.7500;
        distance(33, 0) = 0.2500; distance(33, 1) = 1.2500;
        distance(34, 0) = 0.2500; distance(34, 1) = 0.7500;
        // cout << "distance =" << endl << distance << endl << endl;

        points_position
                << 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0;
        // cout << "points_position =" << endl << points_position << endl << endl;
    }

//计算2组点各点之间的距离 points_range_G1 points_range_G2
    Matrix<double, Dynamic, Dynamic> points_range_G1;
    Matrix<double, Dynamic, Dynamic> points_range_G2;
    points_range_G1 = MatrixXd::Zero(1, num1-1);
    points_range_G2 = MatrixXd::Zero(1, num2-1);
    for (int i = 0; i < num1-1; i++) {
        points_range_G1(0, i) = fabs(sqrt(pow((datagroup1(0, i) - datagroup1(0, i + 1)), 2) +
                                             pow((datagroup1(1, i) - datagroup1(1, i + 1)), 2)));
        points_range_G2(0, i) = fabs(sqrt(pow((datagroup2(0, i) - datagroup2(0, i + 1)), 2) +
                                             pow((datagroup2(1, i) - datagroup2(1, i + 1)), 2)));
    }
    // cout << "points_range_G1 =" << endl << points_range_G1 << endl << endl;
    // cout << "points_range_G2 =" << endl << points_range_G2 << endl << endl;

//将两组距离矩阵和预定义矩阵进行比较，并返回索引,根据索引确定两组点的具体位置和缺失点的位置
//将两组距离矩阵和预定义矩阵进行比较，并返回索引,根据索引确定两组点的具体位置和缺失点的位置
Matrix<double, Dynamic, Dynamic> error_matrix_G1;
Matrix<double, Dynamic, Dynamic> error_matrix_G1_new;
Matrix<double, Dynamic, Dynamic> points_range_G1_re;
Matrix<double, Dynamic, Dynamic> errorposition_G1;
Matrix<double, Dynamic, Dynamic> sumoferror_G1;
Matrix<double, Dynamic, Dynamic> real_points_position_G1;
Matrix<double, Dynamic, Dynamic> real_points_position_G2;
Matrix<double, Dynamic, Dynamic> real_points_position_G1_final;
Matrix<double, Dynamic, Dynamic> real_points_position_G2_final;

if (num1 != 3){
    if (num1 == 7){
        error_matrix_G1_new = MatrixXd::Zero(1, 5);
        Matrix<double, 1, 1> allone = MatrixXd::Ones(1, 1);
        points_range_G1_re = allone * points_range_G1;
    }
    else if (num1 == 6){
        error_matrix_G1_new = MatrixXd::Zero(7, 4);
        Matrix<double, 7, 1> allone = MatrixXd::Ones(7, 1);
        points_range_G1_re = allone * points_range_G1;
    }
    else if (num1 == 5){
        error_matrix_G1_new = MatrixXd::Zero(21, 3);
        Matrix<double, 21, 1> allone = MatrixXd::Ones(21, 1);
        points_range_G1_re = allone * points_range_G1;
    }
    else if (num1 == 4){
        error_matrix_G1_new = MatrixXd::Zero(35, 2);
        Matrix<double, 35, 1> allone = MatrixXd::Ones(35, 1);
        points_range_G1_re = allone * points_range_G1;
    }
    //error_matrix_G1 = abs(distance.array() / points_range_G1_re.array());
    error_matrix_G1 = abs( points_range_G1_re.array() / distance.array());
    cout << "error_matrix_G1 =" << endl << error_matrix_G1 << endl << endl;

    for (int j = 0; j < error_matrix_G1.rows(); j++){
        for (int i = 0; i < num1 - 2; i++) {
            error_matrix_G1_new(j,i) = abs(error_matrix_G1(j,i) - error_matrix_G1(j,i+1));
        }
    }
    cout << "error_matrix_G1_new =" << endl << error_matrix_G1_new << endl << endl;

    sumoferror_G1 = error_matrix_G1_new.rowwise().sum();
    cout << "sumoferror_G1 =" << endl << sumoferror_G1 << endl << endl;

    ptrdiff_t x,y;
    double minofsumoferror_G1 = sumoferror_G1.minCoeff(&x,&y);
    cout << "The minimal value of sumoferror_G1 =" << endl << minofsumoferror_G1 << endl << endl;
    cout << "The index of sumoferror_G1 =" << endl << x << endl << endl;

    errorposition_G1 = MatrixXd::Zero(1,7-num1);
    int z = 0;
    for (int i=0; i<7; i++){
         if (points_position.row(x)(i) == 0) {
             errorposition_G1(z) = i;
             z++;
         }
    }
    cout << "errorposition_G1 =" << endl << errorposition_G1 << endl << endl;
    }
    else {
        error_matrix_G1_new = MatrixXd::Zero(35, 1);
        Matrix<double, 35, 1> allone = MatrixXd::Ones(35, 1);
        points_range_G1_re = allone * points_range_G1;

        error_matrix_G1 = abs( points_range_G1_re.array() / distance.array());
        cout << "error_matrix_G1 =" << endl << error_matrix_G1 << endl << endl;


        for (int j = 0; j < error_matrix_G1.rows(); j++){
            for (int i = 0; i < num1 - 2; i++) {
                error_matrix_G1_new(j,i) = abs(error_matrix_G1(j,i)- a_pre) + abs(error_matrix_G1(j,i+1)- a_pre);
            }
        }
        cout << "error_matrix_G1_new =" << endl << error_matrix_G1_new << endl << endl;

        sumoferror_G1 = error_matrix_G1_new.rowwise().sum();
        cout << "sumoferror_G1 =" << endl << sumoferror_G1 << endl << endl;

        ptrdiff_t x,y;
        double minofsumoferror_G1 = sumoferror_G1.minCoeff(&x,&y);
        cout << "The minimal value of sumoferror_G1 =" << endl << minofsumoferror_G1 << endl << endl;
        cout << "The index of sumoferror_G1 =" << endl << x << endl << endl;

        if (x == 5 || x == 28){
          Matrix<double, Dynamic, Dynamic> xxx5 = points_range_G1.array() / distance.row(5).array();
          Matrix<double, Dynamic, Dynamic> xxx28 = points_range_G1.array() / distance.row(28).array();
          Matrix<double, Dynamic, Dynamic> sumofxxx5 = xxx5.rowwise().sum();
          Matrix<double, Dynamic, Dynamic> sumofxxx28 = xxx28.rowwise().sum();
          if ((sumofxxx5(0)-a_pre) < (sumofxxx28(0)-a_pre)){
            x = 5;
          }
          else{
            x = 28;
          }
        }

        errorposition_G1 = MatrixXd::Zero(1,7-num1);
        int z = 0;
        for (int i=0; i<7; i++){
             if (points_position.row(x)(i) == 0) {
                 errorposition_G1(z) = i;
                 z++;
             }
        }
        cout << "errorposition_G1 =" << endl << errorposition_G1 << endl << endl;
    }


    real_points_position_G1 = MatrixXd::Ones(2, 7);
    real_points_position_G2 = MatrixXd::Ones(2, 7);
    int numdata = real_points_position_G1.cols();
    int num = errorposition_G1.cols();
    for (int k=0; k<num; k++){
        if(errorposition_G1(k) == 0){
            real_points_position_G1(0,0) = 0;
            real_points_position_G1(1,0) = 0;
            real_points_position_G2(0,0) = 0;
            real_points_position_G2(1,0) = 0;
        }
        else if(errorposition_G1(k) == 1){
            real_points_position_G1(0,1) = 0;
            real_points_position_G1(1,1) = 0;
            real_points_position_G2(0,1) = 0;
            real_points_position_G2(1,1) = 0;
        }
        else if(errorposition_G1(k) == 2){
            real_points_position_G1(0,2) = 0;
            real_points_position_G1(1,2) = 0;
            real_points_position_G2(0,2) = 0;
            real_points_position_G2(1,2) = 0;
        }
        else if(errorposition_G1(k) == 3){
            real_points_position_G1(0,3) = 0;
            real_points_position_G1(1,3) = 0;
            real_points_position_G2(0,3) = 0;
            real_points_position_G2(1,3) = 0;
        }
        else if(errorposition_G1(k) == 4){
            real_points_position_G1(0,4) = 0;
            real_points_position_G1(1,4) = 0;
            real_points_position_G2(0,4) = 0;
            real_points_position_G2(1,4) = 0;
        }
        else if(errorposition_G1(k) == 5){
            real_points_position_G1(0,5) = 0;
            real_points_position_G1(1,5) = 0;
            real_points_position_G2(0,5) = 0;
            real_points_position_G2(1,5) = 0;
        }
        else{
            real_points_position_G1(0,6) = 0;
            real_points_position_G1(1,6) = 0;
            real_points_position_G2(0,6) = 0;
            real_points_position_G2(1,6) = 0;
        }
    }
    int w = 0;
    for (int k=0; k<7; k++){
        if(real_points_position_G1(0,k) == 1 && real_points_position_G1(1,k) == 1){
            real_points_position_G1(0,k) = datagroup1(0,w);
            real_points_position_G1(1,k) = datagroup1(1,w);
            real_points_position_G2(0,k) = datagroup2(0,w);
            real_points_position_G2(1,k) = datagroup2(1,w);
            w++;
        }
    }
    // cout << "real_points_position_G1 =" << endl << real_points_position_G1 << endl << endl;
    // cout << "real_points_position_G2 =" << endl << real_points_position_G2 << endl << endl;

//计算b值
    Matrix<double, 1, Dynamic> a;
    Matrix<double, 1, Dynamic> b;
    double a_value = 0;
    double b_value = 0;

    b = MatrixXd::Zero(1, num1);;
    int j = 0;
    for (int i=0; i<7; i++) {
        if(real_points_position_G1(0,i) != 0){
            b(0,j) = fabs(sqrt(pow((real_points_position_G1(0,i) - real_points_position_G2(0,i)),2) + pow((real_points_position_G1(1,i) - real_points_position_G2(1,i)),2)));
            j++;
        }
    }
    b_value = b.mean();
    // cout << "b_value =" << endl << b_value << endl << endl;
//计算a值
    if (num1 == 7){
        a = MatrixXd::Zero(1, 21);;
    }
    else if (num1 == 6){
        a = MatrixXd::Zero(1, 15);;
    }
    else if (num1 == 5){
        a = MatrixXd::Zero(1, 10);;
    }
    else if (num1 == 4){
        a = MatrixXd::Zero(1, 6);;
    }
    else {
        a = MatrixXd::Zero(1, 3);;
    }

    int k = 0;
    if (real_points_position_G1(0,0)!=0 && real_points_position_G1(1,0)!=0){
        if (real_points_position_G1(0,1)!=0 && real_points_position_G1(1,1)!=0){
            a(0,k) = 4 * fabs(sqrt(pow((real_points_position_G1(0,0) - real_points_position_G1(0,1)),2) + pow((real_points_position_G1(1,0) - real_points_position_G1(1,1)),2)));
            k++;
        }
        if (real_points_position_G1(0,2)!=0 && real_points_position_G1(1,2)!=0){
            a(0,k) =     fabs(sqrt(pow((real_points_position_G1(0,0) - real_points_position_G1(0,2)),2) + pow((real_points_position_G1(1,0) - real_points_position_G1(1,2)),2)));
            k++;
        }
        if (real_points_position_G1(0,3)!=0 && real_points_position_G1(1,3)!=0){
            a(0,k) = 2/3.0 * fabs(sqrt(pow((real_points_position_G1(0,0) - real_points_position_G1(0,3)),2) + pow((real_points_position_G1(1,0) - real_points_position_G1(1,3)),2)));
            k++;
        }
        if (real_points_position_G1(0,4)!=0 && real_points_position_G1(1,4)!=0){
            a(0,k) = 1/2.0 * fabs(sqrt(pow((real_points_position_G1(0,0) - real_points_position_G1(0,4)),2) + pow((real_points_position_G1(1,0) - real_points_position_G1(1,4)),2)));
            k++;
        }
        if (real_points_position_G1(0,5)!=0 && real_points_position_G1(1,5)!=0){
            a(0,k) = 4/11.0 * fabs(sqrt(pow((real_points_position_G1(0,0) - real_points_position_G1(0,5)),2) + pow((real_points_position_G1(1,0) - real_points_position_G1(1,5)),2)));
            k++;
        }
        if (real_points_position_G1(0,6)!=0 && real_points_position_G1(1,6)!=0){
            a(0,k) = 1/3.0 * fabs(sqrt(pow((real_points_position_G1(0,0) - real_points_position_G1(0,6)),2) + pow((real_points_position_G1(1,0) - real_points_position_G1(1,6)),2)));
            k++;
        }
    }
    if (real_points_position_G1(0,1)!=0 && real_points_position_G1(1,1)!=0){
        if (real_points_position_G1(0,2)!=0 && real_points_position_G1(1,2)!=0){
            a(0,k) = 4/3.0 * fabs(sqrt(pow((real_points_position_G1(0,1) - real_points_position_G1(0,2)),2) + pow((real_points_position_G1(1,1) - real_points_position_G1(1,2)),2)));
            k++;
        }
        if (real_points_position_G1(0,3)!=0 && real_points_position_G1(1,3)!=0){
            a(0,k) = 4/5.0 * fabs(sqrt(pow((real_points_position_G1(0,1) - real_points_position_G1(0,3)),2) + pow((real_points_position_G1(1,1) - real_points_position_G1(1,3)),2)));
            k++;
        }
        if (real_points_position_G1(0,4)!=0 && real_points_position_G1(1,4)!=0){
            a(0,k) = 4/7.0 * fabs(sqrt(pow((real_points_position_G1(0,1) - real_points_position_G1(0,4)),2) + pow((real_points_position_G1(1,1) - real_points_position_G1(1,4)),2)));
            k++;
        }
        if (real_points_position_G1(0,5)!=0 && real_points_position_G1(1,5)!=0){
            a(0,k) = 2/5.0 * fabs(sqrt(pow((real_points_position_G1(0,1) - real_points_position_G1(0,5)),2) + pow((real_points_position_G1(1,1) - real_points_position_G1(1,5)),2)));
            k++;
        }
        if (real_points_position_G1(0,6)!=0 && real_points_position_G1(1,6)!=0){
            a(0,k) = 4/11.0 * fabs(sqrt(pow((real_points_position_G1(0,1) - real_points_position_G1(0,6)),2) + pow((real_points_position_G1(1,1) - real_points_position_G1(1,6)),2)));
            k++;
        }
    }
    if (real_points_position_G1(0,2)!=0 && real_points_position_G1(1,2)!=0){
        if (real_points_position_G1(0,3)!=0 && real_points_position_G1(1,3)!=0){
            a(0,k) = 2 * fabs(sqrt(pow((real_points_position_G1(0,2) - real_points_position_G1(0,3)),2) + pow((real_points_position_G1(1,2) - real_points_position_G1(1,3)),2)));
            k++;
        }
        if (real_points_position_G1(0,4)!=0 && real_points_position_G1(1,4)!=0){
            a(0,k) =     fabs(sqrt(pow((real_points_position_G1(0,2) - real_points_position_G1(0,4)),2) + pow((real_points_position_G1(1,2) - real_points_position_G1(1,4)),2)));
            k++;
        }
        if (real_points_position_G1(0,5)!=0 && real_points_position_G1(1,5)!=0){
            a(0,k) = 4/7.0 * fabs(sqrt(pow((real_points_position_G1(0,2) - real_points_position_G1(0,5)),2) + pow((real_points_position_G1(1,2) - real_points_position_G1(1,5)),2)));
            k++;
        }
        if (real_points_position_G1(0,6)!=0 && real_points_position_G1(1,6)!=0){
            a(0,k) = 1/2.0 * fabs(sqrt(pow((real_points_position_G1(0,2) - real_points_position_G1(0,6)),2) + pow((real_points_position_G1(1,2) - real_points_position_G1(1,6)),2)));
            k++;
        }
    }
    if (real_points_position_G1(0,3)!=0 && real_points_position_G1(1,3)!=0){
        if (real_points_position_G1(0,4)!=0 && real_points_position_G1(1,4)!=0){
            a(0,k) = 2 * fabs(sqrt(pow((real_points_position_G1(0,3) - real_points_position_G1(0,4)),2) + pow((real_points_position_G1(1,3) - real_points_position_G1(1,4)),2)));
            k++;
        }
        if (real_points_position_G1(0,5)!=0 && real_points_position_G1(1,5)!=0){
            a(0,k) = 4/5.0 * fabs(sqrt(pow((real_points_position_G1(0,3) - real_points_position_G1(0,5)),2) + pow((real_points_position_G1(1,3) - real_points_position_G1(1,5)),2)));
            k++;
        }
        if (real_points_position_G1(0,6)!=0 && real_points_position_G1(1,6)!=0){
            a(0,k) = 2/3.0 * fabs(sqrt(pow((real_points_position_G1(0,3) - real_points_position_G1(0,6)),2) + pow((real_points_position_G1(1,3) - real_points_position_G1(1,6)),2)));
            k++;
        }
    }
    if (real_points_position_G1(0,4)!=0 && real_points_position_G1(1,4)!=0){
        if (real_points_position_G1(0,5)!=0 && real_points_position_G1(1,5)!=0){
            a(0,k) = 4/3.0 * fabs(sqrt(pow((real_points_position_G1(0,4) - real_points_position_G1(0,5)),2) + pow((real_points_position_G1(1,4) - real_points_position_G1(1,5)),2)));
            k++;
        }
        if (real_points_position_G1(0,6)!=0 && real_points_position_G1(1,6)!=0){
            a(0,k) =    fabs(sqrt(pow((real_points_position_G1(0,4) - real_points_position_G1(0,6)),2) + pow((real_points_position_G1(1,4) - real_points_position_G1(1,6)),2)));
            k++;
        }
    }
    if (real_points_position_G1(0,5)!=0 && real_points_position_G1(1,5)!=0){
        if (real_points_position_G1(0,6)!=0 && real_points_position_G1(1,6)!=0){
            a(0,k) = 4 * fabs(sqrt(pow((real_points_position_G1(0,5) - real_points_position_G1(0,6)),2) + pow((real_points_position_G1(1,5) - real_points_position_G1(1,6)),2)));
            k++;
        }
    }
    a_value = a.mean();
    // cout << "a_value =" << endl << a_value << endl << endl;
//计算最终位置
//group1
    real_points_position_G1_final = MatrixXd::Ones(2, 7);

    number0:
    if (real_points_position_G1(0,0)!=0 && real_points_position_G1(1,0)!=0){
        real_points_position_G1_final(0,0) = real_points_position_G1(0,0);
        real_points_position_G1_final(1,0) = real_points_position_G1(1,0);
        if(real_points_position_G1(0,1)==0 && real_points_position_G1(1,1)==0){
            if(theta > 0){
                real_points_position_G1_final(0,1) = real_points_position_G1(0,0) - 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,0) - 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,1) = real_points_position_G1(0,0) + 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,0) - 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 1) = real_points_position_G1(0, 1);
            real_points_position_G1_final(1, 1) = real_points_position_G1(1, 1);
        }
        if(real_points_position_G1(0,2)==0 && real_points_position_G1(1,2)==0){
            if(theta > 0){
                real_points_position_G1_final(0,2) = real_points_position_G1(0,0) - a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,0) - a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,2) = real_points_position_G1(0,0) + a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,0) - a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 2) = real_points_position_G1(0, 2);
            real_points_position_G1_final(1, 2) = real_points_position_G1(1, 2);
        }
        if(real_points_position_G1(0,3)==0 && real_points_position_G1(1,3)==0){
            if(theta > 0){
                real_points_position_G1_final(0,3) = real_points_position_G1(0,0) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,0) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,3) = real_points_position_G1(0,0) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,0) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 3) = real_points_position_G1(0, 3);
            real_points_position_G1_final(1, 3) = real_points_position_G1(1, 3);
        }
        if(real_points_position_G1(0,4)==0 && real_points_position_G1(1,4)==0){
            if(theta > 0){
                real_points_position_G1_final(0,4) = real_points_position_G1(0,0) - 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,0) - 2 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,4) = real_points_position_G1(0,0) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,0) - 2 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 4) = real_points_position_G1(0, 4);
            real_points_position_G1_final(1, 4) = real_points_position_G1(1, 4);
        }
        if(real_points_position_G1(0,5)==0 && real_points_position_G1(1,5)==0){
            if(theta > 0){
                real_points_position_G1_final(0,5) = real_points_position_G1(0,0) - 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,0) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,5) = real_points_position_G1(0,0) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,0) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 5) = real_points_position_G1(0, 5);
            real_points_position_G1_final(1, 5) = real_points_position_G1(1, 5);
        }
        if(real_points_position_G1(0,6)==0 && real_points_position_G1(1,6)==0){
            if(theta > 0){
                real_points_position_G1_final(0,6) = real_points_position_G1(0,0) - 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,0) - 3 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,6) = real_points_position_G1(0,0) + 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,0) - 3 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 6) = real_points_position_G1(0, 6);
            real_points_position_G1_final(1, 6) = real_points_position_G1(1, 6);
        }
    }

    number1:
    if (real_points_position_G1(0,1)!=0 && real_points_position_G1(1,1)!=0){
        real_points_position_G1_final(0,1) = real_points_position_G1(0,1);
        real_points_position_G1_final(1,1) = real_points_position_G1(1,1);
        if(real_points_position_G1(0,0)==0 && real_points_position_G1(1,0)==0){
            if(theta > 0){
                real_points_position_G1_final(0,0) = real_points_position_G1(0,1) + 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,1) + 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,0) = real_points_position_G1(0,1) - 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,1) + 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number2;
        }
        if(real_points_position_G1(0,2)==0 && real_points_position_G1(1,2)==0){
            if(theta > 0){
                real_points_position_G1_final(0,2) = real_points_position_G1(0,1) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,1) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,2) = real_points_position_G1(0,1) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,1) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 2) = real_points_position_G1(0, 2);
            real_points_position_G1_final(1, 2) = real_points_position_G1(1, 2);
        }
        if(real_points_position_G1(0,3)==0 && real_points_position_G1(1,3)==0){
            if(theta > 0){
                real_points_position_G1_final(0,3) = real_points_position_G1(0,1) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,1) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,3) = real_points_position_G1(0,1) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,1) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 3) = real_points_position_G1(0, 3);
            real_points_position_G1_final(1, 3) = real_points_position_G1(1, 3);
        }
        if(real_points_position_G1(0,4)==0 && real_points_position_G1(1,4)==0){
            if(theta > 0){
                real_points_position_G1_final(0,4) = real_points_position_G1(0,1) - 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,1) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,4) = real_points_position_G1(0,1) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,1) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 4) = real_points_position_G1(0, 4);
            real_points_position_G1_final(1, 4) = real_points_position_G1(1, 4);
        }
        if(real_points_position_G1(0,5)==0 && real_points_position_G1(1,5)==0){
            if(theta > 0){
                real_points_position_G1_final(0,5) = real_points_position_G1(0,1) - 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,1) - 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,5) = real_points_position_G1(0,1) + 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,1) - 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 5) = real_points_position_G1(0, 5);
            real_points_position_G1_final(1, 5) = real_points_position_G1(1, 5);
        }
        if(real_points_position_G1(0,6)==0 && real_points_position_G1(1,6)==0){
            if(theta > 0){
                real_points_position_G1_final(0,6) = real_points_position_G1(0,1) - 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,1) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,6) = real_points_position_G1(0,1) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,1) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 6) = real_points_position_G1(0, 6);
            real_points_position_G1_final(1, 6) = real_points_position_G1(1, 6);
        }
    }

    number2:
    if (real_points_position_G1(0,2)!=0 && real_points_position_G1(1,2)!=0){
        real_points_position_G1_final(0,2) = real_points_position_G1(0,2);
        real_points_position_G1_final(1,2) = real_points_position_G1(1,2);
        if(real_points_position_G1(0,0)==0 && real_points_position_G1(1,0)==0){
            if(theta > 0){
                real_points_position_G1_final(0,0) = real_points_position_G1(0,2) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,2) +  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,0) = real_points_position_G1(0,2) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,2) +  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number3;
        }
        if(real_points_position_G1(0,1)==0 && real_points_position_G1(1,1)==0){
            if(theta > 0){
                real_points_position_G1_final(0,1) = real_points_position_G1(0,2) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,2) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,1) = real_points_position_G1(0,2) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,2) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 1) = real_points_position_G1(0, 1);
            real_points_position_G1_final(1, 1) = real_points_position_G1(1, 1);
        }
        if(real_points_position_G1(0,3)==0 && real_points_position_G1(1,3)==0){
            if(theta > 0){
                real_points_position_G1_final(0,3) = real_points_position_G1(0,2) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,2) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,3) = real_points_position_G1(0,2) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,2) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 3) = real_points_position_G1(0, 3);
            real_points_position_G1_final(1, 3) = real_points_position_G1(1, 3);
        }
        if(real_points_position_G1(0,4)==0 && real_points_position_G1(1,4)==0){
            if(theta > 0){
                real_points_position_G1_final(0,4) = real_points_position_G1(0,2) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,2) -  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,4) = real_points_position_G1(0,2) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,2) -  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 4) = real_points_position_G1(0, 4);
            real_points_position_G1_final(1, 4) = real_points_position_G1(1, 4);
        }
        if(real_points_position_G1(0,5)==0 && real_points_position_G1(1,5)==0){
            if(theta > 0){
                real_points_position_G1_final(0,5) = real_points_position_G1(0,2) - 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,2) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,5) = real_points_position_G1(0,2) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,2) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 5) = real_points_position_G1(0, 5);
            real_points_position_G1_final(1, 5) = real_points_position_G1(1, 5);
        }
        if(real_points_position_G1(0,6)==0 && real_points_position_G1(1,6)==0){
            if(theta > 0){
                real_points_position_G1_final(0,6) = real_points_position_G1(0,2) - 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,2) - 2 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,6) = real_points_position_G1(0,2) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,2) - 2 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 6) = real_points_position_G1(0, 6);
            real_points_position_G1_final(1, 6) = real_points_position_G1(1, 6);
        }
    }


    number3:
    if (real_points_position_G1(0,3)!=0 && real_points_position_G1(1,3)!=0){
        real_points_position_G1_final(0,3) = real_points_position_G1(0,3);
        real_points_position_G1_final(1,3) = real_points_position_G1(1,3);
        if(real_points_position_G1(0,0)==0 && real_points_position_G1(1,0)==0){
            if(theta > 0){
                real_points_position_G1_final(0,0) = real_points_position_G1(0,3) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,3) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,0) = real_points_position_G1(0,3) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,3) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number4;
        }
        if(real_points_position_G1(0,1)==0 && real_points_position_G1(1,1)==0){
            if(theta > 0){
                real_points_position_G1_final(0,1) = real_points_position_G1(0,3) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,3) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,1) = real_points_position_G1(0,3) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,3) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 1) = real_points_position_G1(0, 1);
            real_points_position_G1_final(1, 1) = real_points_position_G1(1, 1);
        }
        if(real_points_position_G1(0,2)==0 && real_points_position_G1(1,2)==0){
            if(theta > 0){
                real_points_position_G1_final(0,2) = real_points_position_G1(0,3) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,3) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,2) = real_points_position_G1(0,3) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,3) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 2) = real_points_position_G1(0, 2);
            real_points_position_G1_final(1, 2) = real_points_position_G1(1, 2);
        }
        if(real_points_position_G1(0,4)==0 && real_points_position_G1(1,4)==0){
            if(theta > 0){
                real_points_position_G1_final(0,4) = real_points_position_G1(0,3) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,3) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,4) = real_points_position_G1(0,3) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,3) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 4) = real_points_position_G1(0, 4);
            real_points_position_G1_final(1, 4) = real_points_position_G1(1, 4);
        }
        if(real_points_position_G1(0,5)==0 && real_points_position_G1(1,5)==0){
            if(theta > 0){
                real_points_position_G1_final(0,5) = real_points_position_G1(0,3) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,3) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,5) = real_points_position_G1(0,3) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,3) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 5) = real_points_position_G1(0, 5);
            real_points_position_G1_final(1, 5) = real_points_position_G1(1, 5);
        }
        if(real_points_position_G1(0,6)==0 && real_points_position_G1(1,6)==0){
            if(theta > 0){
                real_points_position_G1_final(0,6) = real_points_position_G1(0,3) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,3) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,6) = real_points_position_G1(0,3) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,3) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 6) = real_points_position_G1(0, 6);
            real_points_position_G1_final(1, 6) = real_points_position_G1(1, 6);
        }
    }

    number4:
    if (real_points_position_G1(0,4)!=0 && real_points_position_G1(1,4)!=0){
        real_points_position_G1_final(0,4) = real_points_position_G1(0,4);
        real_points_position_G1_final(1,4) = real_points_position_G1(1,4);
        if(real_points_position_G1(0,0)==0 && real_points_position_G1(1,0)==0){
            if(theta > 0){
                real_points_position_G1_final(0,0) = real_points_position_G1(0,4) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,4) + 2  * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,0) = real_points_position_G1(0,4) - 2  * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,4) + 2  * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number5;
        }
        if(real_points_position_G1(0,1)==0 && real_points_position_G1(1,1)==0){
            if(theta > 0){
                real_points_position_G1_final(0,1) = real_points_position_G1(0,4) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,4) + 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,1) = real_points_position_G1(0,4) - 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,4) + 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 1) = real_points_position_G1(0, 1);
            real_points_position_G1_final(1, 1) = real_points_position_G1(1, 1);
        }
        if(real_points_position_G1(0,2)==0 && real_points_position_G1(1,2)==0){
            if(theta > 0){
                real_points_position_G1_final(0,2) = real_points_position_G1(0,4) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,4) +  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,2) = real_points_position_G1(0,4) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,4) +  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 2) = real_points_position_G1(0, 2);
            real_points_position_G1_final(1, 2) = real_points_position_G1(1, 2);
        }
        if(real_points_position_G1(0,3)==0 && real_points_position_G1(1,3)==0){
            if(theta > 0){
                real_points_position_G1_final(0,3) = real_points_position_G1(0,4) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,4) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,3) = real_points_position_G1(0,4) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,4) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 3) = real_points_position_G1(0, 3);
            real_points_position_G1_final(1, 3) = real_points_position_G1(1, 3);
        }
        if(real_points_position_G1(0,5)==0 && real_points_position_G1(1,5)==0){
            if(theta > 0){
                real_points_position_G1_final(0,5) = real_points_position_G1(0,4) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,4) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,5) = real_points_position_G1(0,4) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,4) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 5) = real_points_position_G1(0, 5);
            real_points_position_G1_final(1, 5) = real_points_position_G1(1, 5);
        }
        if(real_points_position_G1(0,6)==0 && real_points_position_G1(1,6)==0){
            if(theta > 0){
                real_points_position_G1_final(0,6) = real_points_position_G1(0,4) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,4) -  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,6) = real_points_position_G1(0,4) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,4) -  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 6) = real_points_position_G1(0, 6);
            real_points_position_G1_final(1, 6) = real_points_position_G1(1, 6);
        }
    }


    number5:
    if (real_points_position_G1(0,5)!=0 && real_points_position_G1(1,5)!=0){
        real_points_position_G1_final(0,5) = real_points_position_G1(0,5);
        real_points_position_G1_final(1,5) = real_points_position_G1(1,5);
        if(real_points_position_G1(0,0)==0 && real_points_position_G1(1,0)==0){
            if(theta > 0){
                real_points_position_G1_final(0,0) = real_points_position_G1(0,5) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,5) + 11/4.0  * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,0) = real_points_position_G1(0,5) - 11/4.0  * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,5) + 11/4.0  * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number6;
        }
        if(real_points_position_G1(0,1)==0 && real_points_position_G1(1,1)==0){
            if(theta > 0){
                real_points_position_G1_final(0,1) = real_points_position_G1(0,5) + 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,5) + 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,1) = real_points_position_G1(0,5) - 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,5) + 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 1) = real_points_position_G1(0, 1);
            real_points_position_G1_final(1, 1) = real_points_position_G1(1, 1);
        }
        if(real_points_position_G1(0,2)==0 && real_points_position_G1(1,2)==0){
            if(theta > 0){
                real_points_position_G1_final(0,2) = real_points_position_G1(0,5) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,5) + 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,2) = real_points_position_G1(0,5) - 7/4.0 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,5) + 7/4.0 *  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 2) = real_points_position_G1(0, 2);
            real_points_position_G1_final(1, 2) = real_points_position_G1(1, 2);
        }
        if(real_points_position_G1(0,3)==0 && real_points_position_G1(1,3)==0){
            if(theta > 0){
                real_points_position_G1_final(0,3) = real_points_position_G1(0,5) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,5) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,3) = real_points_position_G1(0,5) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,5) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 3) = real_points_position_G1(0, 3);
            real_points_position_G1_final(1, 3) = real_points_position_G1(1, 3);
        }
        if(real_points_position_G1(0,4)==0 && real_points_position_G1(1,4)==0){
            if(theta > 0){
                real_points_position_G1_final(0,4) = real_points_position_G1(0,5) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,5) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,4) = real_points_position_G1(0,5) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,5) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 4) = real_points_position_G1(0, 4);
            real_points_position_G1_final(1, 4) = real_points_position_G1(1, 4);
        }
        if(real_points_position_G1(0,6)==0 && real_points_position_G1(1,6)==0){
            if(theta > 0){
                real_points_position_G1_final(0,6) = real_points_position_G1(0,5) - 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,5) - 1/4.0 *  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,6) = real_points_position_G1(0,5) + 1/4.0 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,6) = real_points_position_G1(1,5) - 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 6) = real_points_position_G1(0, 6);
            real_points_position_G1_final(1, 6) = real_points_position_G1(1, 6);
        }
    }

    number6:
    if (real_points_position_G1(0,6)!=0 && real_points_position_G1(1,6)!=0){
        real_points_position_G1_final(0,6) = real_points_position_G1(0,6);
        real_points_position_G1_final(1,6) = real_points_position_G1(1,6);
        if(real_points_position_G1(0,0)==0 && real_points_position_G1(1,0)==0){
            if(theta > 0){
                real_points_position_G1_final(0,0) = real_points_position_G1(0,6) + 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,6) + 3 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,0) = real_points_position_G1(0,6) - 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,0) = real_points_position_G1(1,6) + 3 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number7;
        }
        if(real_points_position_G1(0,1)==0 && real_points_position_G1(1,1)==0){
            if(theta > 0){
                real_points_position_G1_final(0,1) = real_points_position_G1(0,6) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,6) + 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,1) = real_points_position_G1(0,6) - 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,1) = real_points_position_G1(1,6) + 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 1) = real_points_position_G1(0, 1);
            real_points_position_G1_final(1, 1) = real_points_position_G1(1, 1);
        }
        if(real_points_position_G1(0,2)==0 && real_points_position_G1(1,2)==0){
            if(theta > 0){
                real_points_position_G1_final(0,2) = real_points_position_G1(0,6) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,6) + 2 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,2) = real_points_position_G1(0,6) - 2 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,2) = real_points_position_G1(1,6) + 2 *  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 2) = real_points_position_G1(0, 2);
            real_points_position_G1_final(1, 2) = real_points_position_G1(1, 2);
        }
        if(real_points_position_G1(0,3)==0 && real_points_position_G1(1,3)==0){
            if(theta > 0){
                real_points_position_G1_final(0,3) = real_points_position_G1(0,6) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,6) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,3) = real_points_position_G1(0,6) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,3) = real_points_position_G1(1,6) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 3) = real_points_position_G1(0, 3);
            real_points_position_G1_final(1, 3) = real_points_position_G1(1, 3);
        }
        if(real_points_position_G1(0,4)==0 && real_points_position_G1(1,4)==0){
            if(theta > 0){
                real_points_position_G1_final(0,4) = real_points_position_G1(0,6) + a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,6) + a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,4) = real_points_position_G1(0,6) - a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,4) = real_points_position_G1(1,6) + a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 4) = real_points_position_G1(0, 4);
            real_points_position_G1_final(1, 4) = real_points_position_G1(1, 4);
        }
        if(real_points_position_G1(0,5)==0 && real_points_position_G1(1,5)==0){
            if(theta > 0){
                real_points_position_G1_final(0,5) = real_points_position_G1(0,6) + 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,6) + 1/4.0 *  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G1_final(0,5) = real_points_position_G1(0,6) - 1/4.0 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G1_final(1,5) = real_points_position_G1(1,6) + 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G1_final(0, 5) = real_points_position_G1(0, 5);
            real_points_position_G1_final(1, 5) = real_points_position_G1(1, 5);
        }
    }
    number7:
    // cout << "real_points_position_G1_final =" << endl << real_points_position_G1_final << endl << endl;

    //group2

    real_points_position_G2_final = MatrixXd::Ones(2, 7);

    number8:
    if (real_points_position_G2(0,0)!=0 && real_points_position_G2(1,0)!=0){
        real_points_position_G2_final(0,0) = real_points_position_G2(0,0);
        real_points_position_G2_final(1,0) = real_points_position_G2(1,0);
        if(real_points_position_G2(0,1)==0 && real_points_position_G2(1,1)==0){
            if(theta > 0){
                real_points_position_G2_final(0,1) = real_points_position_G2(0,0) - 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,0) - 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,1) = real_points_position_G2(0,0) + 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,0) - 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 1) = real_points_position_G2(0, 1);
            real_points_position_G2_final(1, 1) = real_points_position_G2(1, 1);
        }
        if(real_points_position_G2(0,2)==0 && real_points_position_G2(1,2)==0){
            if(theta > 0){
                real_points_position_G2_final(0,2) = real_points_position_G2(0,0) - a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,0) - a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,2) = real_points_position_G2(0,0) + a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,0) - a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 2) = real_points_position_G2(0, 2);
            real_points_position_G2_final(1, 2) = real_points_position_G2(1, 2);
        }
        if(real_points_position_G2(0,3)==0 && real_points_position_G2(1,3)==0){
            if(theta > 0){
                real_points_position_G2_final(0,3) = real_points_position_G2(0,0) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,0) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,3) = real_points_position_G2(0,0) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,0) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 3) = real_points_position_G2(0, 3);
            real_points_position_G2_final(1, 3) = real_points_position_G2(1, 3);
        }
        if(real_points_position_G2(0,4)==0 && real_points_position_G2(1,4)==0){
            if(theta > 0){
                real_points_position_G2_final(0,4) = real_points_position_G2(0,0) - 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,0) - 2 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,4) = real_points_position_G2(0,0) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,0) - 2 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 4) = real_points_position_G2(0, 4);
            real_points_position_G2_final(1, 4) = real_points_position_G2(1, 4);
        }
        if(real_points_position_G2(0,5)==0 && real_points_position_G2(1,5)==0){
            if(theta > 0){
                real_points_position_G2_final(0,5) = real_points_position_G2(0,0) - 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,0) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,5) = real_points_position_G2(0,0) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,0) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 5) = real_points_position_G2(0, 5);
            real_points_position_G2_final(1, 5) = real_points_position_G2(1, 5);
        }
        if(real_points_position_G2(0,6)==0 && real_points_position_G2(1,6)==0){
            if(theta > 0){
                real_points_position_G2_final(0,6) = real_points_position_G2(0,0) - 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,0) - 3 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,6) = real_points_position_G2(0,0) + 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,0) - 3 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 6) = real_points_position_G2(0, 6);
            real_points_position_G2_final(1, 6) = real_points_position_G2(1, 6);
        }
    }

    number9:
    if (real_points_position_G2(0,1)!=0 && real_points_position_G2(1,1)!=0){
        real_points_position_G2_final(0,1) = real_points_position_G2(0,1);
        real_points_position_G2_final(1,1) = real_points_position_G2(1,1);
        if(real_points_position_G2(0,0)==0 && real_points_position_G2(1,0)==0){
            if(theta > 0){
                real_points_position_G2_final(0,0) = real_points_position_G2(0,1) + 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,1) + 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,0) = real_points_position_G2(0,1) - 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,1) + 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number10;
        }
        if(real_points_position_G2(0,2)==0 && real_points_position_G2(1,2)==0){
            if(theta > 0){
                real_points_position_G2_final(0,2) = real_points_position_G2(0,1) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,1) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,2) = real_points_position_G2(0,1) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,1) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 2) = real_points_position_G2(0, 2);
            real_points_position_G2_final(1, 2) = real_points_position_G2(1, 2);
        }
        if(real_points_position_G2(0,3)==0 && real_points_position_G2(1,3)==0){
            if(theta > 0){
                real_points_position_G2_final(0,3) = real_points_position_G2(0,1) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,1) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,3) = real_points_position_G2(0,1) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,1) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 3) = real_points_position_G2(0, 3);
            real_points_position_G2_final(1, 3) = real_points_position_G2(1, 3);
        }
        if(real_points_position_G2(0,4)==0 && real_points_position_G2(1,4)==0){
            if(theta > 0){
                real_points_position_G2_final(0,4) = real_points_position_G2(0,1) - 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,1) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,4) = real_points_position_G2(0,1) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,1) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 4) = real_points_position_G2(0, 4);
            real_points_position_G2_final(1, 4) = real_points_position_G2(1, 4);
        }
        if(real_points_position_G2(0,5)==0 && real_points_position_G2(1,5)==0){
            if(theta > 0){
                real_points_position_G2_final(0,5) = real_points_position_G2(0,1) - 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,1) - 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,5) = real_points_position_G2(0,1) + 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,1) - 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 5) = real_points_position_G2(0, 5);
            real_points_position_G2_final(1, 5) = real_points_position_G2(1, 5);
        }
        if(real_points_position_G2(0,6)==0 && real_points_position_G2(1,6)==0){
            if(theta > 0){
                real_points_position_G2_final(0,6) = real_points_position_G2(0,1) - 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,1) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,6) = real_points_position_G2(0,1) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,1) - 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 6) = real_points_position_G2(0, 6);
            real_points_position_G2_final(1, 6) = real_points_position_G2(1, 6);
        }
    }

    number10:
    if (real_points_position_G2(0,2)!=0 && real_points_position_G2(1,2)!=0){
        real_points_position_G2_final(0,2) = real_points_position_G2(0,2);
        real_points_position_G2_final(1,2) = real_points_position_G2(1,2);
        if(real_points_position_G2(0,0)==0 && real_points_position_G2(1,0)==0){
            if(theta > 0){
                real_points_position_G2_final(0,0) = real_points_position_G2(0,2) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,2) +  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,0) = real_points_position_G2(0,2) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,2) +  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number11;
        }
        if(real_points_position_G2(0,1)==0 && real_points_position_G2(1,1)==0){
            if(theta > 0){
                real_points_position_G2_final(0,1) = real_points_position_G2(0,2) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,2) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,1) = real_points_position_G2(0,2) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,2) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 1) = real_points_position_G2(0, 1);
            real_points_position_G2_final(1, 1) = real_points_position_G2(1, 1);
        }
        if(real_points_position_G2(0,3)==0 && real_points_position_G2(1,3)==0){
            if(theta > 0){
                real_points_position_G2_final(0,3) = real_points_position_G2(0,2) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,2) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,3) = real_points_position_G2(0,2) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,2) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 3) = real_points_position_G2(0, 3);
            real_points_position_G2_final(1, 3) = real_points_position_G2(1, 3);
        }
        if(real_points_position_G2(0,4)==0 && real_points_position_G2(1,4)==0){
            if(theta > 0){
                real_points_position_G2_final(0,4) = real_points_position_G2(0,2) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,2) -  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,4) = real_points_position_G2(0,2) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,2) -  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 4) = real_points_position_G2(0, 4);
            real_points_position_G2_final(1, 4) = real_points_position_G2(1, 4);
        }
        if(real_points_position_G2(0,5)==0 && real_points_position_G2(1,5)==0){
            if(theta > 0){
                real_points_position_G2_final(0,5) = real_points_position_G2(0,2) - 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,2) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,5) = real_points_position_G2(0,2) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,2) - 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 5) = real_points_position_G2(0, 5);
            real_points_position_G2_final(1, 5) = real_points_position_G2(1, 5);
        }
        if(real_points_position_G2(0,6)==0 && real_points_position_G2(1,6)==0){
            if(theta > 0){
                real_points_position_G2_final(0,6) = real_points_position_G2(0,2) - 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,2) - 2 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,6) = real_points_position_G2(0,2) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,2) - 2 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 6) = real_points_position_G2(0, 6);
            real_points_position_G2_final(1, 6) = real_points_position_G2(1, 6);
        }
    }


    number11:
    if (real_points_position_G2(0,3)!=0 && real_points_position_G2(1,3)!=0){
        real_points_position_G2_final(0,3) = real_points_position_G2(0,3);
        real_points_position_G2_final(1,3) = real_points_position_G2(1,3);
        if(real_points_position_G2(0,0)==0 && real_points_position_G2(1,0)==0){
            if(theta > 0){
                real_points_position_G2_final(0,0) = real_points_position_G2(0,3) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,3) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,0) = real_points_position_G2(0,3) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,3) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number12;
        }
        if(real_points_position_G2(0,1)==0 && real_points_position_G2(1,1)==0){
            if(theta > 0){
                real_points_position_G2_final(0,1) = real_points_position_G2(0,3) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,3) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,1) = real_points_position_G2(0,3) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,3) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 1) = real_points_position_G2(0, 1);
            real_points_position_G2_final(1, 1) = real_points_position_G2(1, 1);
        }
        if(real_points_position_G2(0,2)==0 && real_points_position_G2(1,2)==0){
            if(theta > 0){
                real_points_position_G2_final(0,2) = real_points_position_G2(0,3) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,3) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,2) = real_points_position_G2(0,3) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,3) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 2) = real_points_position_G2(0, 2);
            real_points_position_G2_final(1, 2) = real_points_position_G2(1, 2);
        }
        if(real_points_position_G2(0,4)==0 && real_points_position_G2(1,4)==0){
            if(theta > 0){
                real_points_position_G2_final(0,4) = real_points_position_G2(0,3) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,3) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,4) = real_points_position_G2(0,3) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,3) - 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 4) = real_points_position_G2(0, 4);
            real_points_position_G2_final(1, 4) = real_points_position_G2(1, 4);
        }
        if(real_points_position_G2(0,5)==0 && real_points_position_G2(1,5)==0){
            if(theta > 0){
                real_points_position_G2_final(0,5) = real_points_position_G2(0,3) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,3) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,5) = real_points_position_G2(0,3) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,3) - 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 5) = real_points_position_G2(0, 5);
            real_points_position_G2_final(1, 5) = real_points_position_G2(1, 5);
        }
        if(real_points_position_G2(0,6)==0 && real_points_position_G2(1,6)==0){
            if(theta > 0){
                real_points_position_G2_final(0,6) = real_points_position_G2(0,3) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,3) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,6) = real_points_position_G2(0,3) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,3) - 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 6) = real_points_position_G2(0, 6);
            real_points_position_G2_final(1, 6) = real_points_position_G2(1, 6);
        }
    }

    number12:
    if (real_points_position_G2(0,4)!=0 && real_points_position_G2(1,4)!=0){
        real_points_position_G2_final(0,4) = real_points_position_G2(0,4);
        real_points_position_G2_final(1,4) = real_points_position_G2(1,4);
        if(real_points_position_G2(0,0)==0 && real_points_position_G2(1,0)==0){
            if(theta > 0){
                real_points_position_G2_final(0,0) = real_points_position_G2(0,4) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,4) + 2  * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,0) = real_points_position_G2(0,4) - 2  * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,4) + 2  * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number13;
        }
        if(real_points_position_G2(0,1)==0 && real_points_position_G2(1,1)==0){
            if(theta > 0){
                real_points_position_G2_final(0,1) = real_points_position_G2(0,4) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,4) + 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,1) = real_points_position_G2(0,4) - 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,4) + 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 1) = real_points_position_G2(0, 1);
            real_points_position_G2_final(1, 1) = real_points_position_G2(1, 1);
        }
        if(real_points_position_G2(0,2)==0 && real_points_position_G2(1,2)==0){
            if(theta > 0){
                real_points_position_G2_final(0,2) = real_points_position_G2(0,4) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,4) +  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,2) = real_points_position_G2(0,4) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,4) +  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 2) = real_points_position_G2(0, 2);
            real_points_position_G2_final(1, 2) = real_points_position_G2(1, 2);
        }
        if(real_points_position_G2(0,3)==0 && real_points_position_G2(1,3)==0){
            if(theta > 0){
                real_points_position_G2_final(0,3) = real_points_position_G2(0,4) + 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,4) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,3) = real_points_position_G2(0,4) - 1/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,4) + 1/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 3) = real_points_position_G2(0, 3);
            real_points_position_G2_final(1, 3) = real_points_position_G2(1, 3);
        }
        if(real_points_position_G2(0,5)==0 && real_points_position_G2(1,5)==0){
            if(theta > 0){
                real_points_position_G2_final(0,5) = real_points_position_G2(0,4) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,4) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,5) = real_points_position_G2(0,4) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,4) - 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 5) = real_points_position_G2(0, 5);
            real_points_position_G2_final(1, 5) = real_points_position_G2(1, 5);
        }
        if(real_points_position_G2(0,6)==0 && real_points_position_G2(1,6)==0){
            if(theta > 0){
                real_points_position_G2_final(0,6) = real_points_position_G2(0,4) -  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,4) -  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,6) = real_points_position_G2(0,4) +  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,4) -  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 6) = real_points_position_G2(0, 6);
            real_points_position_G2_final(1, 6) = real_points_position_G2(1, 6);
        }
    }


    number13:
    if (real_points_position_G2(0,5)!=0 && real_points_position_G2(1,5)!=0){
        real_points_position_G2_final(0,5) = real_points_position_G2(0,5);
        real_points_position_G2_final(1,5) = real_points_position_G2(1,5);
        if(real_points_position_G1(0,0)==0 && real_points_position_G2(1,0)==0){
            if(theta > 0){
                real_points_position_G2_final(0,0) = real_points_position_G2(0,5) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,5) + 11/4.0  * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,0) = real_points_position_G2(0,5) - 11/4.0  * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,5) + 11/4.0  * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number14;
        }
        if(real_points_position_G2(0,1)==0 && real_points_position_G2(1,1)==0){
            if(theta > 0){
                real_points_position_G2_final(0,1) = real_points_position_G2(0,5) + 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,5) + 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,1) = real_points_position_G2(0,5) - 10/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,5) + 10/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 1) = real_points_position_G2(0, 1);
            real_points_position_G2_final(1, 1) = real_points_position_G2(1, 1);
        }
        if(real_points_position_G2(0,2)==0 && real_points_position_G2(1,2)==0){
            if(theta > 0){
                real_points_position_G2_final(0,2) = real_points_position_G2(0,5) + 7/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,5) + 7/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,2) = real_points_position_G2(0,5) - 7/4.0 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,5) + 7/4.0 *  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 2) = real_points_position_G2(0, 2);
            real_points_position_G2_final(1, 2) = real_points_position_G2(1, 2);
        }
        if(real_points_position_G2(0,3)==0 && real_points_position_G2(1,3)==0){
            if(theta > 0){
                real_points_position_G2_final(0,3) = real_points_position_G2(0,5) + 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,5) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,3) = real_points_position_G2(0,5) - 5/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,5) + 5/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 3) = real_points_position_G2(0, 3);
            real_points_position_G2_final(1, 3) = real_points_position_G2(1, 3);
        }
        if(real_points_position_G2(0,4)==0 && real_points_position_G2(1,4)==0){
            if(theta > 0){
                real_points_position_G2_final(0,4) = real_points_position_G2(0,5) + 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,5) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,4) = real_points_position_G2(0,5) - 3/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,5) + 3/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 4) = real_points_position_G2(0, 4);
            real_points_position_G2_final(1, 4) = real_points_position_G2(1, 4);
        }
        if(real_points_position_G2(0,6)==0 && real_points_position_G2(1,6)==0){
            if(theta > 0){
                real_points_position_G2_final(0,6) = real_points_position_G2(0,5) - 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,5) - 1/4.0 *  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,6) = real_points_position_G2(0,5) + 1/4.0 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,6) = real_points_position_G2(1,5) - 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 6) = real_points_position_G2(0, 6);
            real_points_position_G2_final(1, 6) = real_points_position_G2(1, 6);
        }
    }

    number14:
    if (real_points_position_G2(0,6)!=0 && real_points_position_G2(1,6)!=0){
        real_points_position_G2_final(0,6) = real_points_position_G2(0,6);
        real_points_position_G2_final(1,6) = real_points_position_G2(1,6);
        if(real_points_position_G2(0,0)==0 && real_points_position_G2(1,0)==0){
            if(theta > 0){
                real_points_position_G2_final(0,0) = real_points_position_G2(0,6) + 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,6) + 3 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,0) = real_points_position_G2(0,6) - 3 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,0) = real_points_position_G2(1,6) + 3 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            goto number15;
        }
        if(real_points_position_G2(0,1)==0 && real_points_position_G2(1,1)==0){
            if(theta > 0){
                real_points_position_G2_final(0,1) = real_points_position_G2(0,6) + 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,6) + 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,1) = real_points_position_G2(0,6) - 11/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,1) = real_points_position_G2(1,6) + 11/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 1) = real_points_position_G2(0, 1);
            real_points_position_G2_final(1, 1) = real_points_position_G2(1, 1);
        }
        if(real_points_position_G2(0,2)==0 && real_points_position_G1(1,2)==0){
            if(theta > 0){
                real_points_position_G2_final(0,2) = real_points_position_G2(0,6) + 2 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,6) + 2 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,2) = real_points_position_G2(0,6) - 2 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,2) = real_points_position_G2(1,6) + 2 *  a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 2) = real_points_position_G2(0, 2);
            real_points_position_G2_final(1, 2) = real_points_position_G2(1, 2);
        }
        if(real_points_position_G2(0,3)==0 && real_points_position_G2(1,3)==0){
            if(theta > 0){
                real_points_position_G2_final(0,3) = real_points_position_G2(0,6) + 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,6) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,3) = real_points_position_G2(0,6) - 3/2.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,3) = real_points_position_G2(1,6) + 3/2.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 3) = real_points_position_G2(0, 3);
            real_points_position_G2_final(1, 3) = real_points_position_G2(1, 3);
        }
        if(real_points_position_G2(0,4)==0 && real_points_position_G2(1,4)==0){
            if(theta > 0){
                real_points_position_G2_final(0,4) = real_points_position_G2(0,6) + a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,6) + a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,4) = real_points_position_G2(0,6) - a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,4) = real_points_position_G2(1,6) + a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 4) = real_points_position_G2(0, 4);
            real_points_position_G2_final(1, 4) = real_points_position_G2(1, 4);
        }
        if(real_points_position_G2(0,5)==0 && real_points_position_G2(1,5)==0){
            if(theta > 0){
                real_points_position_G2_final(0,5) = real_points_position_G2(0,6) + 1/4.0 * a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,6) + 1/4.0 *  a_value * fabs(cos(PI/2-theta));
            }
            else{
                real_points_position_G2_final(0,5) = real_points_position_G2(0,6) - 1/4.0 *  a_value * fabs(sin(PI/2-theta));
                real_points_position_G2_final(1,5) = real_points_position_G2(1,6) + 1/4.0 * a_value * fabs(cos(PI/2-theta));
            }
        }
        else {
            real_points_position_G2_final(0, 5) = real_points_position_G2(0, 5);
            real_points_position_G2_final(1, 5) = real_points_position_G2(1, 5);
        }
    }
    number15:
    // cout << "real_points_position_G2_final =" << endl << real_points_position_G2_final << endl << endl;






////group2
//    real_points_position_G2_final = MatrixXd::Ones(2, 7);
//    for (int i=0; i<7; i++){
//        if(theta > 0){
//            real_points_position_G2_final(0,i) = real_points_position_G1_final(0,i) + b_value * fabs(sin(theta));
//            real_points_position_G2_final(1,i) = real_points_position_G1_final(1,i) - b_value * fabs(cos(theta));
//        }
//        else{
//            real_points_position_G2_final(0,i) = real_points_position_G1_final(0,i) + b_value * fabs(sin(theta));
//            real_points_position_G2_final(1,i) = real_points_position_G1_final(1,i) + b_value * fabs(cos(theta));
//        }
//    }
//    cout << "real_points_position_G2_final =" << endl << real_points_position_G2_final << endl << endl;


/////////////
//tell which points are from lidar
    Matrix<double, Dynamic, Dynamic> real_points_position_lidar1;
    Matrix<double, Dynamic, Dynamic> real_points_position_lidar2;
    real_points_position_lidar1 = MatrixXd::Ones(3, 7);
    real_points_position_lidar2 = MatrixXd::Ones(3, 7);
    real_points_position_lidar1.row(0) = real_points_position_G1_final.row(0);
    real_points_position_lidar2.row(0) = real_points_position_G2_final.row(0);
    real_points_position_lidar1.row(1) = real_points_position_G1_final.row(1);
    real_points_position_lidar2.row(1) = real_points_position_G2_final.row(1);
    int num_er = errorposition_G1.cols();
    for (int k=0; k<num_er; k++){
        if(errorposition_G1(k) == 0){
            real_points_position_lidar1(2,0) = 0;
            real_points_position_lidar2(2,0) = 0;
        }
        else if(errorposition_G1(k) == 1){
            real_points_position_lidar1(2,1) = 0;
            real_points_position_lidar2(2,1) = 0;
        }
        else if(errorposition_G1(k) == 2){
            real_points_position_lidar1(2,2) = 0;
            real_points_position_lidar2(2,2) = 0;
        }
        else if(errorposition_G1(k) == 3){
            real_points_position_lidar1(2,3) = 0;
            real_points_position_lidar2(2,3) = 0;
        }
        else if(errorposition_G1(k) == 4){
            real_points_position_lidar1(2,4) = 0;
            real_points_position_lidar2(2,4) = 0;
        }
        else if(errorposition_G1(k) == 5){
            real_points_position_lidar1(2,5) = 0;
            real_points_position_lidar2(2,5) = 0;
        }
        else{
            real_points_position_lidar1(2,6) = 0;
            real_points_position_lidar2(2,6) = 0;
        }
    }
/////////
//真实的lidar点index为1，预测点的index为0
////////
    prediction.coord_1 = real_points_position_lidar1.transpose();
    prediction.coord_2 = real_points_position_lidar2.transpose();
    prediction.a       = a_value;
    prediction.b       = b_value;
    return prediction;
}
