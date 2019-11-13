#include <array>
#include <iostream>
#include <armadillo>
#include <math.h>
#include <stdlib.h>

using namespace arma;
using namespace std;

mat s_ising(mat& arr, int s){
    // Antar verdiene enten er -1 eller 1
    // Er en 2x2 matrix

    // Her finner vi Mean Energy[E]
    int E = - arr(0,0) * (arr(0,1) + arr(0,1) + arr(1,0) + arr(1,0));
    E = E - arr(1,1) * (arr(0,1) + arr(0,1) + arr(1,0) + arr(1,0));
    cout << "E = " << E << endl;

    // Her finner vi Mean Magnetization[M]
    int M = accu(arr);

    srand(time(NULL));

    int x,y;
    int MC = 3;
    int Ex = 0;
    for(int i = 0; i < MC; i++){
        cout << "_________________________________________" << endl;
        x = rand() % s;
        y = rand() % s;
        arr(x,y) *= -1;
        cout << arr << endl;

        Ex = - arr(0,0) * (arr(0,1) + arr(0,1) + arr(1,0) + arr(1,0));
        Ex = Ex - arr(1,1) * (arr(0,1) + arr(0,1) + arr(1,0) + arr(1,0));
        if(abs(Ex) > abs(E)){
            arr(x,y) *= -1;
            cout << "It dosen't change" << endl;
        }
        cout << "Ex = " << Ex << endl;
    }



    // Her finner vi Specific Heat[C]



    cout << "M = " << M << endl;
    return arr;
}

mat l_ising(mat& arr, int s){
    int MC = 4;
    int M = accu(arr);

    int E = 0;

    // Oppe til venstre
    E += -arr(0,0) * (arr(1,0) + arr(0,1) + arr(s-1,0) + arr(0,s-1));

    // Oppe til høyre
    E += -arr(0,s-1) * (arr(0,s-2) + arr(0,0) + arr(s-1,s-1) + arr(1,s-1));

    // Nede til venstre
    E += -arr(s-1,0) * (arr(s-2,0) + arr(0,0) + arr(s-1,s-1) + arr(s-1, 1));

    // Nede til høyre
    E += -arr(s-1,s-1) * (arr(s-1,s-2) + arr(s-2,s-1) + arr(0,s-1) + arr(s-1,0));

    mat tmp_1 = arr.col(0);
    mat tmp_2 = arr.col(s-1);
    mat tmp_3 = arr.col(1);
    mat tmp_4 = arr.col(s-2);
    // For søylene
    for(int i = 1; i < s-1; i++){
        E += -tmp_1(i) * (tmp_1(i-1) + tmp_1(i+1) + tmp_2(i) + tmp_3(i));
        E += -tmp_2(i) * (tmp_2(i-1) + tmp_2(i+1) + tmp_1(i) + tmp_4(i));
    }

    tmp_1 = arr.row(0);
    tmp_2 = arr.row(s-1);
    tmp_3 = arr.row(1);
    tmp_4 = arr.row(s-2);
    for(int i = 1; i < s-1; i++){
        E += -tmp_1(i) * (tmp_1(i-1) + tmp_1(i+1) + tmp_2(i) + tmp_3(i));
        E += -tmp_2(i) * (tmp_2(i-1) + tmp_2(i+1) + tmp_1(i) + tmp_4(i));
    }

    for(int i = 1; i < s-1; i++){
        for(int j = 1; j < s-1; j++){
            E += -arr(i,i) * (arr(i-1,i) + arr(i+1,i) + arr(i,i-1) + arr(i,i+1));
        }
    }

    cout << "Start E = " << E << " Start M = " << M << endl;
    int Ex, x, y;
    for(int cycle = 0; cycle < MC; cycle++){
        Ex = 0;
        x = rand() % s;
        y = rand() % s;
        arr(x,y) *= -1;

        Ex += -arr(0,0) * (arr(1,0) + arr(0,1) + arr(s-1,0) + arr(0,s-1));
        Ex += -arr(0,s-1) * (arr(0,s-2) + arr(0,0) + arr(s-1,s-1) + arr(1,s-1));
        Ex += -arr(s-1,0) * (arr(s-2,0) + arr(0,0) + arr(s-1,s-1) + arr(s-1, 1));
        Ex += -arr(s-1,s-1) * (arr(s-1,s-2) + arr(s-2,s-1) + arr(0,s-1) + arr(s-1,0));

        tmp_1 = arr.col(0);
        tmp_2 = arr.col(s-1);
        tmp_3 = arr.col(1);
        tmp_4 = arr.col(s-2);

        for(int i = 1; i < s-1; i++){
            Ex += -tmp_1(i) * (tmp_1(i-1) + tmp_1(i+1) + tmp_2(i) + tmp_3(i));
            Ex += -tmp_2(i) * (tmp_2(i-1) + tmp_2(i+1) + tmp_1(i) + tmp_4(i));
        }

        tmp_1 = arr.row(0);
        tmp_2 = arr.row(s-1);
        tmp_3 = arr.row(1);
        tmp_4 = arr.row(s-2);
        for(int i = 1; i < s-1; i++){
            Ex += -tmp_1(i) * (tmp_1(i-1) + tmp_1(i+1) + tmp_2(i) + tmp_3(i));
            Ex += -tmp_2(i) * (tmp_2(i-1) + tmp_2(i+1) + tmp_1(i) + tmp_4(i));
        }

        for(int i = 1; i < s-1; i++){
            for(int j = 1; j < s-1; j++){
                Ex += -arr(i,i) * (arr(i-1,i) + arr(i+1,i) + arr(i,i-1) + arr(i,i+1));
            }
        }
        if(Ex < E){
            M = accu(arr);
            cout << "______________________________" << endl;
            cout << "Succsess!" << endl;
            cout << arr << endl;
            cout << "Ex = " << Ex << " E = " << E << " M = " << M << endl;
            E = Ex;
        }
        else{
            cout << "______________________________" << endl;
            cout << "Failure!" << endl;
            cout << arr << endl;
            cout << "Ex = " << Ex << " E = " << E << " M = " << M << endl;
            arr(x,y) *= -1;
        }
    }
    return arr;
}
