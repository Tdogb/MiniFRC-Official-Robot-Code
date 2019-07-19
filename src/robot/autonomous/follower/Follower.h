#ifndef __FOLLOWER_H__
#define __FOLLOWER_H__
#include "robot/autonomous/Vector2D.h"
#include <stdint.h>
#include <Arduino.h>
#include "robot/defs.h"

class Follower
{
private:
    Vector2D robotPosition = {0,0};
    int32_t previousEncoderPositions[2];
    float heading = 0;
    float previousHeading = 0;
public:
    Follower(int a);
    ~Follower();
    void updatePosition();
    void printPosition();
    void calculateLookahead();
};

#endif // __FOLLOWER_H__
