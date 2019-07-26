#include "Drivetrain.h"

Drivetrain::Drivetrain(Brushed &_leftMotor, Brushed &_rightMotor)
:leftMotor(_leftMotor), rightMotor(_rightMotor)
{

}

Drivetrain::~Drivetrain()
{
}

void Drivetrain::update() {

}

void Drivetrain::setVelocityState(drivetrainState_s newState) {
    leftMotor.commandVelocity(newState.leftVelocity);
    rightMotor.commandVelocity(newState.rightVelocity);
}