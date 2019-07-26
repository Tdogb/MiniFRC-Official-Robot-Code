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

    enum conversionName_e {
        STEPS,
        ACTUAL
    };
    enum stepper_e {
        LEADSCREW,
        ROTATION
    };

    float heightOffset = 0;
    float height, rotation = 0;
    float heightSteps, headingSteps, heightStepSetpoint, rotationStepSetpoint = 0;
    template<typename T>
    float convertElevatorUnits(T var, stepper_e stepper, conversionName_e convertFrom);
    
public:
    Elevator(Stepper &_leadscrewStepper, Stepper &_rotationStepper);
    ~Elevator();
    void setHeight(float height);
    float &getHeight() { return height; }
    void setRotation(float rotation);
    float &getRotation() { return rotation; }
    void update();
    void periodicUpdate();
};


#endif // __ELEVATOR_H__
