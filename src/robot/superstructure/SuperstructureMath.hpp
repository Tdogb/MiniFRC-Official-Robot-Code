#ifndef __SUPERSTRUCTUREMATH_H__
#define __SUPERSTRUCTUREMATH_H__
#include <BasicLinearAlgebra.h>
#include <Arduino.h>

class SuperstructureMath
{
private:
    BLA::Matrix<3,3> BallGeometry =
    {
        -0.064648f,   0.064648f,  0.064648f,
        0.111350f,   0.060219f,  0.060219f,
        0.012000f,   0.012000f,  0.030242f
    };

    BLA::Matrix<3,2> FloorGeometry =
    {
        -0.075f,  0.075f,
        0.085f, -0.085f,
        0.000f,  0.000f
    };

    BLA::Matrix<3,3> axisMat = {
        0,        0,       0,
        0.0505,   0.0505,  0.0505,
        0,        0,       0
    };

    BLA::Matrix<3,1> E1 = {
        1,
        0,
        0
    };
    BLA::Matrix<3,3> elevatorRotationMat;
    BLA::Matrix<3,3> mechanismRotationMat;
    BLA::Matrix<3,3> tempMatrix;
    BLA::Matrix<3,3> tempMatrix2;
    BLA::Matrix<3,1> tempMatrix3;
    bool contains(const float &n0, const float &n1, const float &n2);

public:
    SuperstructureMath(/* args */);
    ~SuperstructureMath();
    void printMatrix(BLA::Matrix<3,3> *mat);
    void setElevatorHeight(float height);
    bool calculateElevatorRotation(float theta);
    bool calculateMechanismRotation(float theta);
    bool detectCollision();
};


#endif // __SUPERSTRUCTUREMATH_H__
