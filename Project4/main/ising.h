#ifndef ISING_H
#define ISING_H
#include <armadillo>

using namespace arma;

mat ising(mat& arr, int s, int MC, float T);
#endif // ISING_H
