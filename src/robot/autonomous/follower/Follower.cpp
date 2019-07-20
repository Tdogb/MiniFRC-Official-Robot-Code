#include "Follower.h"

#define leftDeltaPosition realDeltaPositions[0]
#define rightDeltaPosition realDeltaPositions[1]

Follower::Follower(int a)
{
}

Follower::~Follower()
{
}

void Follower::update() {
    updatePosition();
    Matrix<2,1> prevPoint = {
        0.1,
        -1
    };
    Matrix<2,1> nextPoint = {
        0.1,
        1
    };
    calculateLookahead(prevPoint, nextPoint);
}

void Follower::calculateLookahead(Matrix<2,1> previousPoint, Matrix<2,1> nextPoint) {
    Matrix<2,1> d = nextPoint-previousPoint;
    float a = dot(d,d);
    float b = 2*dot(lookaheadCircle, d);
    float c = dot(lookaheadCircle, lookaheadCircle) - powf(LOOKAHEAD_DISTANCE,2);
    float discriminent = powf(b,2) - 4*a*c;
    Serial.println(discriminent);
    if(discriminent < 0) {

    }
    else {
        discriminent = sqrtf(discriminent);
        float t1 = (-b-discriminent)/(2*a);
        float t2 = (-b+discriminent)/(2*a);
        if(t1 >= 0 && t1 <= 1) {

        }
        if(t2 >= 0 && t2 <= 1) {
            
        }
    }
}

float dot(Matrix<2,1> val1, Matrix<2,1> val2) {
    return val1(0)*val2(0) + val1(1)*val2(1);
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
    Matrix<2,1> tempMatrix = {
        cosf(heading)*((leftDeltaPosition+rightDeltaPosition)/2),
        sinf(heading)*((leftDeltaPosition+rightDeltaPosition)/2)
    };
    robotPosition += tempMatrix;
    previousEncoderPositions[0] = encoderPositions[0];
    previousEncoderPositions[1] = encoderPositions[1];
}

void Follower::printPosition() {
    // Serial.println("");
    // Serial.print(robotPosition.x,6);
    // Serial.print('\t');
    // Serial.print(robotPosition.y,6);
    // Serial.print('\t');
    // Serial.print(heading);
}