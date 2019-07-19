#include "Spline.h"


Spline::Spline(Matrix<2,1> &_p0, Matrix<2,1> &_p1, Matrix<2,1> t0, Matrix<2,1> t1)
:p0(_p0),p1(_p1)
{
    Matrix<4,4> basisMatrix = {
       2,  -2,  1,  1,
      -3,   3, -2, -1,
       0,   0,  1,  0,
       1,   0,  0,  0
    };
    Matrix<4,2> controlMatrix = (~p0)&&(~p1)&&(~t0)&&(~t1);
    // = {
    //     p0.x,   p0.y,
    //     p1.x,   p1.y,
    //     t0.x,   t0.y,
    //     t1.x,   t0.y
    // };
    Matrix<4,2> pretransposedSplineMatrix;
    Multiply(basisMatrix,controlMatrix,pretransposedSplineMatrix);
    splineMatrix = ~pretransposedSplineMatrix;

    //Derivatives
    Matrix<4,1> firstDerivativeCoef = {
         3,
         2,
         1,
         0
    };
    Matrix<4,1> secondDerivativeCoef = {
        2,
        1,
        0,
        0
    };
    RefMatrix<1,4,Array<2,4>> xRefMat(splineMatrix.Submatrix(Slice<0,0>(),Slice<0,3>()));
    RefMatrix<1,4,Array<2,4>> yRefMat(splineMatrix.Submatrix(Slice<1,1>(),Slice<0,3>()));
    Matrix<1,4> tempXFirstDerivMat;
    Matrix<1,4> tempYFirstDerivMat;
    Matrix<1,4> tempXSecondDerivMat;
    Matrix<1,4> tempYSecondDerivMat;
    tempXFirstDerivMat = firstDerivativeCoef * xRefMat;
    tempYFirstDerivMat = firstDerivativeCoef * yRefMat;
    tempXSecondDerivMat = secondDerivativeCoef * tempXFirstDerivMat;
    tempYSecondDerivMat = secondDerivativeCoef * tempYFirstDerivMat;
    firstDerivative = tempXFirstDerivMat && tempYFirstDerivMat;
    secondDerivative = tempXSecondDerivMat && tempYSecondDerivMat;
}

Spline::~Spline()
{
}

std::vector<Matrix<2,1>> Spline::getPointsAtArclength(float arclengthStep) {
    std::vector<Matrix<2,1>> output;
    for(float i = arclengthStep; i <= totalArclength; i+=arclengthStep) {

    }
}

Matrix<2,1> Spline::getNthDerivative(derivativeOrder_e derivativeOrder, Matrix<2,1> point) {
    switch(derivativeOrder) {
        case ZERO:
            Matrix<1,4> pointMatrix = {
                powf(point(0),3),   powf(point(0),2),   point(0),   1
            };
            
            return {splineMatrix};
            break; 
    }
}