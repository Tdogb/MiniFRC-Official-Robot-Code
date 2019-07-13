#include "Superstructure.h"

Superstructure::Superstructure(/* args */)
{
    currentElevatorState.height = 0;
    currentElevatorState.theta = 0;
    currentBallState.manipulatorState = OFF;
    currentBallState.ballTheta = 0;
    currentHatchState.manipulatorState = OFF;
    currentHatchState.hatchTheta = 0;
}

Superstructure::~Superstructure()
{
}

void Superstructure::setSuperstructureState(elevatorState_s newState, bool commanded) {
    if(!commanded) {

    }
    else {
        commandElevatorState(newState);
    }
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

}

void Superstructure::commandBallState(ballState_s newBallState) {

}

void Superstructure::commandHatchState(hatchState_s newHatchState) {

}