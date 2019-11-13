#include <iostream>
#include <chrono>
#include <armadillo>
#include "ising.h"

using namespace std;
using namespace arma;

mat pro(const mat& arr){
    mat y = arr*2.0;
    return y;
}


int main()
{
    int size = 3;

    arma_rng::set_seed_random();
    Mat<double> arr = randu(size, size);

    cout << arr << endl;

    mat::iterator end = arr.end();

    for(mat::iterator start = arr.begin(); start != end; start++){
        if(*start > 0.5){
            *start = 1;
        }
        else{
            *start = -1;
        }
    }

    //Mat<double> arr = {{-1, -1, 1}, {1, -1 , 1}, {-1, 1, -1}};


    cout << arr << endl;

    auto start = chrono::high_resolution_clock::now();
    if(size < 3){
        s_ising(arr, size);
    }
    else{
        l_ising(arr, size);
    }
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = (finish - start);
    cout << "Time = " << elapsed.count() << " s " << endl;
    return 0;
}

