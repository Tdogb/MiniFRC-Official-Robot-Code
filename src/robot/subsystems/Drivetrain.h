#ifndef __DRIVETRAIN_H__
#define __DRIVETRAIN_H__
#include "robot/motor/Brushed.h"

class Drivetrain
{
private:
    Brushed &leftMotor;
    Brushed &rightMotor;
public:
    Drivetrain(Brushed &_leftMotor, Brushed &_rightMotor);
    ~Drivetrain();
    void update();
};

#endif // __DRIVETRAIN_H__
