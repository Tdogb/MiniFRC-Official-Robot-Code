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
    BLA::Matrix<2,4> splineMatrix = {0,0,0,0,0,0,0,0};
    BLA::Matrix<4,2> firstDerivative;
    BLA::Matrix<4,2> secondDerivative;
    RefMatrix<1,4,Array<2,4>> *xRefMat, *yRefMat, *xRef1Mat, *yRef1Mat, *xRef2Mat, *yRef2Mat;
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
