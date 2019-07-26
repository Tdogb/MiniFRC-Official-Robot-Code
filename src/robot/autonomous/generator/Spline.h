#ifndef __SPLINE_H__
#define __SPLINE_H__
#include <BasicLinearAlgebra.h>
#include <vector>
using namespace BLA;

class Spline
{
private:
    Matrix<2,1> &p0, &p1, &t0, &t1;
    float totalArclength = 0;
    // enum derivativeOrder_e { //Big brain move here O.o
    //     ZERO,
    //     FIRST,
    //     SECOND,
    // };

    Matrix<2,1> getNthDerivative(int derivativeOrder, Matrix<2,1> point);
public:
    Spline(Matrix<2,1> &_p0, Matrix<2,1> &_p1, Matrix<2,1> &_t0, Matrix<2,1> &_t1);
    ~Spline();
    std::vector<Matrix<2,1>> getPointsAtArclength(float arclength);
};

#endif // __SPLINE_H__
