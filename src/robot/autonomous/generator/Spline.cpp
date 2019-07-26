#include "Spline.h"

#define ARC_TIMESTEP 0.001

Matrix<2,4> splineMatrix;
Matrix<2,4> firstDerivative;
Matrix<2,4> secondDerivative;
RefMatrix<1,4,Array<2,4>> xRefMat(splineMatrix.Submatrix(Slice<0,1>(),Slice<0,4>()));
RefMatrix<1,4,Array<2,4>> yRefMat(splineMatrix.Submatrix(Slice<1,2>(),Slice<0,4>()));

RefMatrix<1,4,Array<2,4>> xRef1Mat(firstDerivative.Submatrix(Slice<0,1>(),Slice<0,4>()));
RefMatrix<1,4,Array<2,4>> yRef1Mat(firstDerivative.Submatrix(Slice<1,2>(),Slice<0,4>()));

RefMatrix<1,4,Array<2,4>> xRef2Mat(secondDerivative.Submatrix(Slice<0,1>(),Slice<0,4>()));
RefMatrix<1,4,Array<2,4>> yRef2Mat(secondDerivative.Submatrix(Slice<1,2>(),Slice<0,4>()));

Spline::Spline(Matrix<2,1> &_p0, Matrix<2,1> &_p1, Matrix<2,1> &_t0, Matrix<2,1> &_t1)
:p0(_p0),p1(_p1),t0(_t0),t1(_t1)
{
    Matrix<4,4> basisMatrix = {
       2,  -2,  1,  1,
      -3,   3, -2, -1,
       0,   0,  1,  0,
       1,   0,  0,  0
    };
    Matrix<4,2> controlMatrix = ((~p0)&&(~p1))&&((~t0)&&(~t1));
    // Same as:
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
    for(int i = 0; i < 4; i++) {
        firstDerivative(0,i) *= firstDerivativeCoef[i];
        firstDerivative(1,i) *= firstDerivativeCoef[i];

        secondDerivative(0,i) *= secondDerivativeCoef[i];
        secondDerivative(1,i) *= secondDerivativeCoef[i];
    }
    /* Calculate arclength */
    getPointsAtArclength(0.01);
}

Spline::~Spline()
{
}

std::vector<Matrix<2,1>> Spline::getPointsAtArclength(float arclengthStep) {
    std::vector<Matrix<2,1>> output;
    /*
        Iterate though spline from 0 to 1
        Taking the integral with the timestep
        Once it goes past the arclength step, then add this point to the output
    */
    float integral = 0;
    for(float i = 0; i < 1; i+=ARC_TIMESTEP) { //Should be kept with these start and end conditions
        Serial.println(getNthDerivative(0, {i,i})(0),6);
        integral += ARC_TIMESTEP * 0.5*(getNthDerivative(0, {i,i})(1) * getNthDerivative(1, {i,i})(0) + getNthDerivative(0, {i+1,i+1})(1) * getNthDerivative(1, {i+1,i+1})(0));
        if(integral >= (output.size()+1)*arclengthStep) {
            output.push_back(getNthDerivative(0, {i,i}));
        }
    }
    totalArclength = integral;
    return output;
}

/*
 return: dx/dy NOT dy/dx
*/
Matrix<2,1> Spline::getNthDerivative(int derivativeOrder, Matrix<2,1> point) {
    Matrix<2,1> output;
    Matrix<1,4> pointXMatrix;
    Matrix<1,4> pointYMatrix;

    switch(derivativeOrder) {
        /*
        Not sure what I am thinking here, shouldn't these matricies be multiplied by the derivative coef at some point
         */
        case 0:
            pointXMatrix = {
                powf(point(0),3),   powf(point(0),2),   point(0),   1
            };
            pointYMatrix = {
                powf(point(1),3),   powf(point(1),2),   point(1),   1
            };
            output = (pointXMatrix * ~xRefMat)&&(pointYMatrix * ~yRefMat);
            break;
        case 1:
            pointXMatrix = {
                powf(point(0),2),   point(0),   1,   0
            };
            pointYMatrix = {
                powf(point(1),2),   point(1),   1,   0
            };
            output = (pointXMatrix * ~xRef1Mat)&&(pointYMatrix * ~yRef1Mat);
            break;
        case 2:
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