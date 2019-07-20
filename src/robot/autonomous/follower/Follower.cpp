#include "Follower.h"

#define leftDeltaPosition realDeltaPositions[0]
#define rightDeltaPosition realDeltaPositions[1]

Follower::Follower(Superstructure &_superstructure)
:superstructure(_superstructure)
{
    path = {
        0.2,-0.2,
        0.43,0.5
    };
}

Follower::~Follower()
{
}
Matrix<2,1> previousPt;
Matrix<2,1> nextPt;
void Follower::update() {
    updatePosition();
    previousPt = {
        path(currentPointIndex - 1,0) - robotPosition(0),
        path(currentPointIndex - 1,1) - robotPosition(1)
    };
    nextPt = {
        path(currentPointIndex,0) - robotPosition(0),
        path(currentPointIndex,1) - robotPosition(1)
    };
    calculateLookahead(previousPt, nextPt);
    //Serial << leftWheelVelocitySetpoint << " " << rightWheelVelocitySetpoint << '\n';
    //Serial.println(leftWheelVelocitySetpoint,6);
    superstructure.setDrivetrainState({leftWheelVelocitySetpoint, rightWheelVelocitySetpoint});
}

void Follower::calculateLookahead(Matrix<2,1> previousPoint, Matrix<2,1> nextPoint) {
    Matrix<2,1> d = nextPoint-previousPoint;
    float a = dot(d,d);
    float b = 2*dot(previousPoint, d);
    float c = dot(previousPoint, previousPoint) - powf(LOOKAHEAD_DISTANCE,2);
    float discriminent = powf(b,2) - 4*a*c;
    //Serial << "PT: " << previousPoint(0) << " D0: "<< d(0) << " D1: " << d(1) << " a: " << a << " b: " << b << " c: " << c 
    //    << " discriminent: " << discriminent << " robotPositionX " << robotPosition(0) << " robotPositionY " << robotPosition(1) << '\n';
    if(discriminent < 0) {

    }
    else {
        discriminent = sqrtf(discriminent);
        float t1 = (-b-discriminent)/(2*a);
        float t2 = (-b+discriminent)/(2*a);
        if(t1 >= 0 && t1 <= 1 && t1 >= t2) {
            intersectionPoint = previousPoint + (d * t1);
        }
        if(t2 >= 0 && t2 <= 1 && t2 >= t1) {
            intersectionPoint = previousPoint + (d * t2);
        }
    }
    float a1 = -tanf(heading);
    float c1 = -a1 * robotPosition(0)-robotPosition(1);
    float curvature = 2*(abs(a1*intersectionPoint(0)+1*intersectionPoint(1)+c1)/(sqrtf(powf(a1,2)+1)))/(powf(LOOKAHEAD_DISTANCE,2));
    float targetVelocity = 0.1; //TEMP
    leftWheelVelocitySetpoint = (targetVelocity * (2 + curvature * WHEELBASE_RADIUS*2))/2;
    rightWheelVelocitySetpoint = (targetVelocity * (2 - curvature * WHEELBASE_RADIUS*2))/2;
    Serial.println(""); 
    Serial.print(intersectionPoint(0), 6);
    Serial.print('\t');
    Serial.print(intersectionPoint(1), 6);
}

float Follower::dot(Matrix<2,1> val1, Matrix<2,1> val2) {
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