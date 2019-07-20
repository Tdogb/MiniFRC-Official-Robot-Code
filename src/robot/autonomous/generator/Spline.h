#ifndef __SPLINE_H__
#define __SPLINE_H__
#include <BasicLinearAlgebra.h>
#include <vector>
using namespace BLA;

class Spline
{
private:
    BLA::Matrix<2,1> &p0;
    BLA::Matrix<2,1> &p1;
    float totalArclength = 0;
    enum derivativeOrder_e {
        ZERO,
        FIRST,
        SECOND,
    };

    Matrix<2,1> getNthDerivative(derivativeOrder_e derivativeOrder, Matrix<2,1> point);
public:
    Spline(Matrix<2,1> &_p0, Matrix<2,1> &_p1, Matrix<2,1> t0, Matrix<2,1> t1);
    ~Spline();
    std::vector<Matrix<2,1>> getPointsAtArclength(float arclength);
};

#endif // __SPLINE_H__
