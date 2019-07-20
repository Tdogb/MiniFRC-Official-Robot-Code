#include "Spline.h"
Matrix<2,4> splineMatrix;
Matrix<2,4> firstDerivative;
Matrix<2,4> secondDerivative;
RefMatrix<1,4,Array<2,4>> xRefMat(splineMatrix.Submatrix(Slice<0,1>(),Slice<0,4>()));
RefMatrix<1,4,Array<2,4>> yRefMat(splineMatrix.Submatrix(Slice<1,2>(),Slice<0,4>()));

RefMatrix<1,4,Array<2,4>> xRef1Mat(firstDerivative.Submatrix(Slice<0,1>(),Slice<0,4>()));
RefMatrix<1,4,Array<2,4>> yRef1Mat(firstDerivative.Submatrix(Slice<1,2>(),Slice<0,4>()));

RefMatrix<1,4,Array<2,4>> xRef2Mat(secondDerivative.Submatrix(Slice<0,1>(),Slice<0,4>()));
RefMatrix<1,4,Array<2,4>> yRef2Mat(secondDerivative.Submatrix(Slice<1,2>(),Slice<0,4>()));

Spline::Spline(Matrix<2,1> &_p0, Matrix<2,1> &_p1, Matrix<2,1> t0, Matrix<2,1> t1)
:p0(_p0),p1(_p1)
{
    Matrix<4,4> basisMatrix = {
       2,  -2,  1,  1,
      -3,   3, -2, -1,
       0,   0,  1,  0,
       1,   0,  0,  0
    };
    Matrix<4,2> controlMatrix = ((~p0)&&(~p1))&&((~t0)&&(~t1));
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
    float firstDerivativeCoef[] = {
         3,
         2,
         1,
         0
    };
    float secondDerivativeCoef[] = {
        2,
        1,
        0,
        0
    };
    // Matrix<1,4> tempXFirstDerivMat;
    // Matrix<1,4> tempYFirstDerivMat;
    // Matrix<1,4> tempXSecondDerivMat;
    // Matrix<1,4> tempYSecondDerivMat;
    for(int i = 0; i < 4; i++) {
        firstDerivative(0,i) *= firstDerivativeCoef[i];
        firstDerivative(1,i) *= firstDerivativeCoef[i];

        secondDerivative(0,i) *= secondDerivativeCoef[i];
        secondDerivative(1,i) *= secondDerivativeCoef[i];
    }
    // tempXFirstDerivMat = ~(firstDerivativeCoef * xRefMat);//4x1 * 1x4
    // tempYFirstDerivMat = firstDerivativeCoef * yRefMat;
    // tempXSecondDerivMat = secondDerivativeCoef * tempXFirstDerivMat;
    // tempYSecondDerivMat = secondDerivativeCoef * tempYFirstDerivMat;
    // firstDerivative = tempXFirstDerivMat && tempYFirstDerivMat; //Woudnt this create a 8x1 matrix?
    // secondDerivative = tempXSecondDerivMat && tempYSecondDerivMat;

    /* Calculate arclength */

}

Spline::~Spline()
{
}

std::vector<Matrix<2,1>> Spline::getPointsAtArclength(float arclengthStep) {
    std::vector<Matrix<2,1>> output;
    for(float i = arclengthStep; i <= totalArclength; i+=arclengthStep) { //Correct
    
        /* Calculating integral */
        for(float a = i; a <= 1; a+=0.01) {

        }
    }
    return output;
}

Matrix<2,1> Spline::getNthDerivative(derivativeOrder_e derivativeOrder, Matrix<2,1> point) {
    Matrix<2,1> output;
    Matrix<1,4> pointXMatrix;
    Matrix<1,4> pointYMatrix;

    switch(derivativeOrder) {
        case ZERO:
            pointXMatrix = {
                powf(point(0),3),   powf(point(0),2),   point(0),   1
            };
            pointYMatrix = {
                powf(point(1),3),   powf(point(1),2),   point(1),   1
            };
            output = (pointXMatrix * ~xRefMat)&&(pointYMatrix * ~yRefMat);
            break;
        case FIRST:
            pointXMatrix = {
                powf(point(0),2),   point(0),   1,   0
            };
            pointYMatrix = {
                powf(point(1),2),   point(1),   1,   0
            };
            output = (pointXMatrix * ~xRef1Mat)&&(pointYMatrix * ~yRef1Mat);
            break;
        case SECOND:
            pointXMatrix = {
                point(0),   1,   0,   0
            };
            pointYMatrix = {
                point(1),   1,   0,   0
            };
            output = (pointXMatrix * ~xRef2Mat)&&(pointYMatrix * ~yRef2Mat);
            break;
    }
    return output;
}