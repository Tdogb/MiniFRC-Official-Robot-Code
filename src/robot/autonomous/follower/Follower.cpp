#include "Follower.h"

#define leftDeltaPosition realDeltaPositions[0]
#define rightDeltaPosition realDeltaPositions[1]
#define LOOKAHEAD_DISTANCE 0.01

Follower::Follower(int a)
{
}

Follower::~Follower()
{
}

void Follower::calculateLookahead() {
    Vector2D deltaPos = {robotPosition.x};
}

void Follower::updatePosition() {
    extern int32_t encoderPositions[2];
    int32_t deltaPositions[2] = {encoderPositions[0]-previousEncoderPositions[0], encoderPositions[1]-previousEncoderPositions[1]};
    float realDeltaPositions[2];
    for(int i = 0; i < 2; i++) {
        realDeltaPositions[i] = WHEEL_DIA*deltaPositions[i]/4096.f; //CPR*gear ratio
    }
    heading += (leftDeltaPosition-rightDeltaPosition)/WHEELBASE_RADIUS;
    //Technically need to compensate for the circle of radius 0.04 in the middle of the robot (see diagram)
    //This depends on where we are measuring the position from, center of mass or center of differential drive

    robotPosition.x += cosf(heading)*((leftDeltaPosition+rightDeltaPosition)/2);
    robotPosition.y += sinf(heading)*((leftDeltaPosition+rightDeltaPosition)/2);

    previousEncoderPositions[0] = encoderPositions[0];
    previousEncoderPositions[1] = encoderPositions[1];
}

void Follower::printPosition() {
    Serial.println("");
    Serial.print(robotPosition.x,6);
    Serial.print('\t');
    Serial.print(robotPosition.y,6);
    Serial.print('\t');
    Serial.print(heading);
}