/*
Contains:
- Stepper objects

Methods:
setElevatorHeight --> only run by superstructure class
setElevatorRotation --> only run by superstructure class
*/

#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__

#include <TeensyStep.h>

class Elevator
{
private:
    Stepper &leadscrewStepper;
    Stepper &rotationStepper;
    StepControl rotationController;
    StepControl leadscrewController;
public:
    Elevator(Stepper &_leadscrewStepper, Stepper &_rotationStepper);
    ~Elevator();
    void setHeight(float height);
    void setRotation(float rotation);
};


#endif // __ELEVATOR_H__
