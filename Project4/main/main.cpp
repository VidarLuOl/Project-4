#include <iostream>
#include <chrono>
#include <armadillo>
#include "mpi/mpi.h"
#include "ising.h"


using namespace std;
using namespace arma;


int main(int nargs, char *args[])
{
    int size = 20;
    int MC = 1000000;
    double temp = 1;
    double T_s = 2.0, T_e = 2.4;
    double min = (T_e - T_s)/MC;
    double av_E, E_var, av_M, M_var, abs_M, M_abs_var, H_C, Su, Su_abs;

    string Opg = "Both";
    Mat<double> arr;



    auto start = chrono::high_resolution_clock::now();


    ofstream file;

    /*____________Array filled with 1________________*/
    if(Opg == "Ones" || Opg == "Both"){
        file.open("Ones.txt");
        arr = ones(size, size);
        file << MC << endl;
        file << T_s << " " << T_e << endl;

        for(float MC = 10; MC < 1010; MC+=10){
            mat test = ising(arr, size, MC, temp);

            av_E = test(0);
            E_var = test(1);
            av_M = test(2);
            M_var = test(3);
            abs_M = test(4);
            M_abs_var = test(5);

            H_C = E_var/(temp*temp);
            Su = M_var/(temp);
            Su_abs = M_abs_var/(temp);

            file << av_E << " " << av_M << " " << abs_M << " " << H_C << " " << Su << " " << Su_abs << " " << temp << endl;
        }

        file.close();
    }



    /*________Array filled with random numbers_______*/
    if(Opg == "Random" || Opg == "Both"){
        file.open("Random.txt");
        file << MC << endl;
        file << T_s << " " << T_e << endl;

        arma_rng::set_seed_random();
        arr = randu(size, size);

        mat::iterator end = arr.end();

        for(mat::iterator start = arr.begin(); start != end; start++){
            if(*start > 0.5){
                *start = 1;
            }
            else{
                *start = -1;
            }
        }

        for(float MC = 10; MC < 10000; MC+=100){
            mat test = ising(arr, size, MC, temp);

            av_E = test(0);
            E_var = test(1);
            av_M = test(2);
            M_var = test(3);
            abs_M = test(4);
            M_abs_var = test(5);

            H_C = E_var/(temp*temp);
            Su = M_var/(temp);
            Su_abs = M_abs_var/(temp);

            file << av_E << " " << av_M << " " << abs_M << " " << H_C << " " << Su << " " << Su_abs << " " << temp << endl;
        }

        file.close();
    }




    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = (finish - start);
    cout << "Time = " << elapsed.count() << " s " << endl;
    return 0;
}

