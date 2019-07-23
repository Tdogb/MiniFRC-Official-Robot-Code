#ifndef __FOLLOWER_H__
#define __FOLLOWER_H__
#include "robot/autonomous/Vector2D.h"
#include <stdint.h>
#include <Arduino.h>
#include "robot/defs.h"
#include <BasicLinearAlgebra.h>
#include "robot/autonomous/generator/Path.h"
#include "robot/superstructure/Superstructure.h"

using namespace BLA;
#define LOOKAHEAD_DISTANCE 0.3
#define POINT_TOLERANCE 0.0127 //Normally would be 0.0127

class Follower
{
private:
    Matrix<6,2> path = {
        0,0,
        0.09,0.215,
        0.246,0.39,
        0.43,0.5,
        0.58,0.645,
        0.656,0.83
    };
    Superstructure &superstructure;
    Matrix<2,1> robotPosition = {0,0};
    Matrix<2,1> intersectionPoint;

    float rightWheelVelocitySetpoint;
    float leftWheelVelocitySetpoint;

    int32_t previousEncoderPositions[2];
    int currentPointIndex = 1;
    float heading = 0;
    float previousHeading = 0;
    void updatePosition();
    void calculateLookahead();
    float dot(Matrix<2,1> val1, Matrix<2,1> val2);
    bool calculateIntersectionPoint(Matrix<2,1> previousPoint, Matrix<2,1> nextPoint);
    void detectPointPassed();
public:
    Follower(Superstructure &_superstructure);
    ~Follower();
    void update();
    void printPosition();
};

#endif // __FOLLOWER_H__
