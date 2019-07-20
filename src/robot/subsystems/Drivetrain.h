#ifndef __DRIVETRAIN_H__
#define __DRIVETRAIN_H__
#include "robot/motor/Brushed.h"
#include "robot/superstructure/States.hpp"

class Drivetrain
{
private:
    Brushed &leftMotor;
    Brushed &rightMotor;
public:
    Drivetrain(Brushed &_leftMotor, Brushed &_rightMotor);
    ~Drivetrain();
    void update();
    void setVelocityState(drivetrainState_s newState);
};

#endif // __DRIVETRAIN_H__
