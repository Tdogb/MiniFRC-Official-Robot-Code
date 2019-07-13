#include <cstdlib>
#include "MMath.h"
//#include <robot/superstructure/BallIntakeGeo.h>

using namespace MMath;

void multiplyScalar(double **M, double S, size_t rows, size_t cols) {
    for(size_t c = 0; c < cols; c++) {
        for(size_t r = 0; r < rows; r++) {
            M[c][r] *= S;
        }
    }
}

void addScalar(double *M[3], double S, int axis, size_t rows, size_t cols) {
    for(size_t c = 0; c < cols; c++) {
        //BallGeometry::geo[c][axis] += S;
    }
}