#ifndef __SUPERSTRUCTUREMATH_H__
#define __SUPERSTRUCTUREMATH_H__
#include <BasicLinearAlgebra.h>
#include <Arduino.h>

class SuperstructureMath
{
private:
    /* data */
public:
    SuperstructureMath(/* args */);
    ~SuperstructureMath();
    void printMatrix(BLA::Matrix<3,3> *mat);
    void setElevatorHeight(float height);
    bool calculateElevatorRotation(float theta);
    bool calculateMechanismRotation(float theta);
};


#endif // __SUPERSTRUCTUREMATH_H__
