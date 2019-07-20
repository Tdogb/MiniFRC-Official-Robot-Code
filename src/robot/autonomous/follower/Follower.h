#ifndef __FOLLOWER_H__
#define __FOLLOWER_H__
#include "robot/autonomous/Vector2D.h"
#include <stdint.h>
#include <Arduino.h>
#include "robot/defs.h"
#include <BasicLinearAlgebra.h>

using namespace BLA;
#define LOOKAHEAD_DISTANCE 0.5

class Follower
{
private:
    Matrix<2,1> robotPosition = {0,0};
    Matrix<2,1> lookaheadCircle = {LOOKAHEAD_DISTANCE, 0};
    int32_t previousEncoderPositions[2];
    int currentPointIndex = 0;
    float heading = 0;
    float previousHeading = 0;
    void updatePosition();
    void calculateLookahead(Matrix<2,1> previousPoint, Matrix<2,1> nextPoint);
public:
    Follower(int a);
    ~Follower();
    void update();
    void printPosition();
};

#endif // __FOLLOWER_H__
