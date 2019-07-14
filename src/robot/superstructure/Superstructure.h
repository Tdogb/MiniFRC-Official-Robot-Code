/*
Superstructure class contains all of the subsystem instances
Supersturcture.setElevatorHeight --> resolve collisions --> run subsystem
*/
#ifndef __SUPERSTRUCTURE_H__
#define __SUPERSTRUCTURE_H__
#include "robot/subsystems/Elevator.h"
#include "robot/subsystems/Mechanisms.h"
#include "robot/subsystems/Drivetrain.h"
#include <Arduino.h>

enum manipulatorState_e {
    OFF,
    INTAKE,
    OUTTAKE
};

struct ballTheta_s { //In radians without PI
    float START = PI/2;
    float NEUTRAL = 0;
    float INTAKE = -PI/4;
    float OUTTAKE = PI/4;
    float OUTTAKE_HIGH = PI/3;
};

struct hatchTheta_s {
    float START = PI/2;
    float NEUTRAL = 0;
    float INTAKE = -PI/4;
    float OUTTAKE = PI/4;
};

struct superstructureState_s {
    public:

};

struct elevatorState_s {
    float theta;
    float height;
};

struct ballState_s {
    manipulatorState_e manipulatorState;
    float ballTheta;
};

struct hatchState_s {
    manipulatorState_e manipulatorState;
    float hatchTheta;
};


class Superstructure
{
public:
    Superstructure(Elevator &_elevator, Drivetrain &_drivetrain, Mechanisms &_mechanisms);
    void setSuperstructureState(elevatorState_s newElevatorState);
    void setSuperstructureState(ballState_s newBallState);
    void setSuperstructureState(hatchState_s newHatchState);
private:
    Elevator &elevator;
    Drivetrain &drivetrain;
    Mechanisms &mechanisms;
    elevatorState_s currentElevatorState;
    ballState_s currentBallState;
    hatchState_s currentHatchState;

    void commandElevatorState(elevatorState_s newElevatorState);
    void commandBallState(ballState_s newBallState);
    void commandHatchState(hatchState_s newHatchState);
    int convertThetaToSteps(float theta);

};


#endif // __SUPERSTRUCTURE_H__
