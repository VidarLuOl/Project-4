#include <armadillo>
#include <catch.hpp>

using namespace arma;
using namespace std;


TEST_CASE("Test E_sum"){
    int s = 3;
    int E = 0;

    Mat<double> arr = {{-1, -1, 1},{1, -1, 1},{-1, 1, -1}};

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



    REQUIRE(E == Approx(6.0).epsilon(0.000000000001));
}


TEST_CASE("Test M_sum"){
    int s = 3;
    int E = 0;

    Mat<double> arr = {{-1, -1, 1},{1, -1, 1},{-1, -1, 1}};

    float M = accu(arr);



    REQUIRE(M == Approx(-1.0).epsilon(0.000000000001));
}
