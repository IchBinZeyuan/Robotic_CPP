#include <utility>
#include <mat.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <boost/tuple/tuple.hpp>
#include "load_data.h"
using namespace Eigen;
using namespace std;

MatrixXd load_data()
{
    MATFile *pmatFile;
    mxArray *pMxArray;
    Gnuplot gp;
    double *a;
    int N, M;
    MatrixXd coord_ori;

    pmatFile = matOpen("/Users/liuyiming/Studying/Leistungskurs C++/dataprocessing/new_coord_ori2.mat","r");
    if (!pmatFile) cout << "ERROR: Cannot OPEN the MAT-File.\n";
    else
    {
        int ElementNum = 0;
        char **ElementDir = matGetDir(pmatFile, &ElementNum);
        if (!ElementDir) cout << "ERROR: Cannot READ the MAT-File.\n";
        else {
            pMxArray = matGetVariable(pmatFile, ElementDir[0]);
            M = (int) mxGetM(pMxArray); //高
            N = (int) mxGetN(pMxArray); //宽

            coord_ori = MatrixXd::Zero(M, 4);
            a = (double *) mxGetData(pMxArray);
            for (int j=0; j<N; j++)
            {
                for (int i=0; i<M; i++)
                {
                    coord_ori(i,j)=a[j*M+i];
                    coord_ori(i,3) = sqrt(coord_ori(i, 0)*coord_ori(i, 0) + coord_ori(i, 1)*coord_ori(i, 1));
                    if (coord_ori(i,3) < 1e-5)
                        coord_ori(i,2) = 0;
                    else
                        coord_ori(i,2) = asin(coord_ori(i,0) / coord_ori(i,3));

                    if (coord_ori(i,1) < 0)
                        coord_ori(i,2) = ((int)(coord_ori(i,2)>=0) - (int)(coord_ori(i,2)<0))*3.1416 - coord_ori(i,2);


                }
            }
        }
    }
    matClose(pmatFile);

    return coord_ori;
}
