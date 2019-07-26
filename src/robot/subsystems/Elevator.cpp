/*
Move the steppers here
*/
#include "Elevator.h"
#include "robot/defs.h"
#include <Arduino.h>

#define LEADSCREW_RATIO 0.008 //8mm per revolution
constexpr float ROTATION_RATIO = 2*PI*(24/56);

Elevator::Elevator(Stepper &_leadscrewStepper, Stepper &_rotationStepper)
:leadscrewStepper(_leadscrewStepper), rotationStepper(_rotationStepper)
{
    rotationStepper.setAcceleration(4000);
    rotationStepper.setMaxSpeed(25000);
    leadscrewStepper.setAcceleration(30000);
    leadscrewStepper.setMaxSpeed(130000);
    rotationStepper.setTargetAbs(0);
    leadscrewStepper.setTargetAbs(0);
}

Elevator::~Elevator() 
{
}

void Elevator::setHeight(float height) {
    Serial.println("");
    Serial.print("Height set to: ");
    Serial.print(height);
    float newValue = convertElevatorUnits(height, LEADSCREW, ACTUAL);
    heightStepSetpoint += newValue;
    rotationStepSetpoint -= newValue;
}

void Elevator::setRotation(float rotation) {
    Serial.println("");
    Serial.print("Rotation set to: ");
    Serial.print(rotation);
    float newValue = convertElevatorUnits(rotation, ROTATION, ACTUAL);
    rotationStepSetpoint += newValue;
    heightStepSetpoint -= newValue;
}

void Elevator::update() {
    if(!leadscrewController.isRunning() && heightStepSetpoint != leadscrewStepper.getPosition()) {
        leadscrewController.moveAsync(leadscrewStepper);
    }
    height = convertElevatorUnits(leadscrewStepper.getPosition(), LEADSCREW, STEPS);

    if(!rotationController.isRunning() && rotationStepSetpoint != rotationStepper.getPosition()) {
        rotationController.moveAsync(rotationStepper);
    }
    rotation = convertElevatorUnits(rotationStepper.getPosition(), ROTATION, STEPS);

}

template<typename T>
float Elevator::convertElevatorUnits(T var, stepper_e stepper, conversionName_e convertFrom) {
    switch (convertFrom) {
    case STEPS:
        switch(stepper) {
            case LEADSCREW:
                return (float)var*LEADSCREW_RATIO/200;
            case ROTATION:
                return (float)var*ROTATION_RATIO/200;
        }
        break;
    case ACTUAL:
        switch(stepper) {
            case LEADSCREW:
                return 200*(float)var/LEADSCREW_RATIO;
            case ROTATION:
                return 200*((float)var/ROTATION_RATIO);
        }
        break;
    }
    return 0;
}