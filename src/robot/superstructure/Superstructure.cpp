#include "Superstructure.h"

Superstructure::Superstructure(Elevator &_elevator, Drivetrain &_drivetrain, Mechanisms &_mechanisms)
:elevator(_elevator), drivetrain(_drivetrain), mechanisms(_mechanisms)
{
    currentElevatorState.height = 0;
    currentElevatorState.theta = 0;
    currentBallState.manipulatorState = OFF;
    currentBallState.ballTheta = 0;
    currentHatchState.manipulatorState = OFF;
    currentHatchState.hatchTheta = 0;
}

void Superstructure::setSuperstructureState(elevatorState_s newState) {
    for(float stepInterval = 0; stepInterval < convertThetaToSteps(currentElevatorState.theta-newState.theta); stepInterval++) {

    }
    //TEMP
    commandElevatorState(newState);

}

void Superstructure::setSuperstructureState(ballState_s newBallState) {
    if(newBallState.ballTheta <= 0) {

    }
    else {
        commandBallState(newBallState);
    }
}

void Superstructure::setSuperstructureState(hatchState_s newHatchState) {

}

void Superstructure::commandElevatorState(elevatorState_s newElevatorState) {
    elevator.setHeight(newElevatorState.height);
    elevator.setRotation(newElevatorState.theta);
}

void Superstructure::commandBallState(ballState_s newBallState) {

}

void Superstructure::commandHatchState(hatchState_s newHatchState) {

}

int Superstructure::convertThetaToSteps(float theta) {
    return 0;
}