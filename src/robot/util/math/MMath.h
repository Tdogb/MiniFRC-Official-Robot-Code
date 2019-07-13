#ifndef __MMATH_H__
#define __MMATH_H__
#include <cstdlib>

namespace MMath {
    void multiplyScalar(double **M, double S, size_t rows, size_t cols);
    void addScalar(double **M, double S, double axis[], size_t rows, size_t cols);
}

#endif // __MMATH_H__
