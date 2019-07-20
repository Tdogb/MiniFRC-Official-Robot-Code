/*
Superstructure class contains all of the subsystem instances
Supersturcture.setElevatorHeight --> resolve collisions --> run subsystem
*/
#ifndef __SUPERSTRUCTURE_H__
#define __SUPERSTRUCTURE_H__
#include "robot/subsystems/Elevator.h"
#include "robot/subsystems/Mechanisms.h"
#include "robot/subsystems/Drivetrain.h"
#include "States.hpp"

class Superstructure
{
public:
    Superstructure(Elevator &_elevator, Drivetrain &_drivetrain, Mechanisms &_mechanisms);
    void setSuperstructureState(elevatorState_s newElevatorState);
    void setSuperstructureState(ballState_s newBallState);
    void setSuperstructureState(hatchState_s newHatchState);
    void setDrivetrainState(drivetrainState_s newState);
private:
    Elevator &elevator;
    Drivetrain &drivetrain;
    Mechanisms &mechanisms;
    elevatorState_s currentElevatorState;
    ballState_s currentBallState;
    hatchState_s currentHatchState;
    drivetrainState_s currentDrivetrainState;

    void commandElevatorState(elevatorState_s newElevatorState);
    void commandBallState(ballState_s newBallState);
    void commandHatchState(hatchState_s newHatchState);
    int convertThetaToSteps(float theta);

};


#endif // __SUPERSTRUCTURE_H__
