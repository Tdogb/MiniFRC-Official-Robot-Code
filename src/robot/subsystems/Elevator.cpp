/*
Move the steppers here
*/
#include "Elevator.h"
#include "robot/defs.h"

Stepper rotationStepper(ROTATION_STEP_PIN, ROTATION_DIR_PIN); //step pin, dir pin
Stepper leadscrewStepper(LEADSCREW_STEP_PIN,LEADSCREW_DIR_PIN);
StepControl rotationController;
StepControl leadscrewController;

Elevator::Elevator(/* args */)
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
}

void Elevator::setRotation(float rotation) {
    Serial.println("");
    Serial.print("Rotation set to: ");
    Serial.print(rotation);
}