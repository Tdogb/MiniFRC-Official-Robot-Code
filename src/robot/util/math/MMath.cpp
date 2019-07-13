#include <cstdlib>
#include "MMath.h"

using namespace MMath;

void multiplyScalar(double **M, double S, size_t rows, size_t cols) {
    for(size_t c; c < cols; c++) {
        for(size_t r; r < rows; r++) {
            M[c][r] *= S;
        }
    }
}

void addScalar(double **M, double S, double axis[], size_t rows, size_t cols) {
    for(size_t c; c < cols; c++) {
        for(size_t r; r < rows; r++) {
            M[c][r] += S*axis[r];
        }
    }
}

template<class M, class V>
M testLinIndependence() {
}