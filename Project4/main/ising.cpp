#include <array>
#include <iostream>
#include <armadillo>
#include <random>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include "mpi/mpi.h"

using namespace arma;
using namespace std;

mat ising(mat& arr, int s, int MC, float T){
    //  Energy
    float E = 0;
    //  Expected energy, energy squared, expected magnetic, magnetic squared, absolute value of M
    float av_E = 0,      av_EE = 0,      av_M = 0,          av_MM=0,          abs_M=0;

    //_______________ Initial values ___________
    float M = accu(arr);
    for(int i = 0; i < s-1; i++){
        for(int j = 0; j < s-1; j++){
            E -= arr(i,j) * (arr(i+1, j) + arr(i, j+1));
        }
    }

    for(int i = 0; i < s-1; i++){
        E -= arr(i, s-1) * (arr(i+1, s-1) + arr(i, 0));
        E -= arr(s-1, i) * (arr(s-1, i+1) + arr(0, i));
    }

    E -= arr(s-1, s-1) * (arr(s-1, 0) + arr(0, s-1));

    av_E = E;
    av_EE = pow(E, 2);

    av_M = M;
    av_MM = pow(M, 2);


    //____________________________________________

    int N = s*s, x, y;
    float Ex = E;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    Mat<double> w = vec(17);
    for (int de = -8; de <= 8; de += 4){
      w(de+8) = exp(-de/T);
    }
    /*
    ofstream file;
    if(M == s*s){
        file.open("Ones.txt");
    }
    else{
        file.open("Random.txt");
    }
    file << MC << endl;
    file << av_E << " " << av_M << endl;
    */


    for(int cycle = 1; cycle < MC; cycle++){
        for(int loop = 0; loop < N; loop++){
            x = rand() % s;
            y = rand() % s;

            Ex = 2*arr(x, y) * (arr((x+1)%s, y) + arr((x+s-1)%s, y) + arr(x, (y+s-1)%s) + arr(x, (y+1)%s));

            if(dis(gen) <= w(Ex + 8)){
                arr(x,y) *= -1;
                E += Ex;
                M += 2*arr(x,y);
            }


        }
        av_E += E;
        av_EE += E*E;
        av_M += M;
        av_MM += M*M;
        abs_M += abs(M);
    }
    //file.close();

    av_E /= MC;
    av_M /= MC;
    av_EE /= MC;
    av_MM /= MC;
    abs_M /= MC;

    float E_var = (av_EE - pow(av_E, 2))/(s*s);
    float M_var = (av_MM - pow(av_M, 2))/(s*s);
    float M_abs_var = (av_MM - pow(abs_M, 2))/(s*s);

    av_E /= (s*s);
    av_M /= (s*s);
    abs_M /= (s*s);

    Mat<double> ret = {av_E, E_var, av_M, M_var, abs_M, M_abs_var};


    return ret;
}
