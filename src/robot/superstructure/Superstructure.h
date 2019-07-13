/*
Superstructure class contains all of the subsystem instances
Supersturcture.setElevatorHeight --> resolve collisions --> run subsystem
*/
#ifndef __SUPERSTRUCTURE_H__
#define __SUPERSTRUCTURE_H__
#include "robot/subsystems/Elevator.h"
#include "robot/subsystems/Mechanisms.h"
#include <Arduino.h>

enum manipulatorState_e {
    OFF,
    INTAKE,
    OUTTAKE
};

struct ballTheta_s { //In radians without PI
    double START = PI/2;
    double NEUTRAL = 0;
    double INTAKE = -PI/4;
    double OUTTAKE = PI/4;
    double OUTTAKE_HIGH = PI/3;
};

struct hatchTheta_s {
    double START = PI/2;
    double NEUTRAL = 0;
    double INTAKE = -PI/4;
    double OUTTAKE = PI/4;
};

struct superstructureState_s {
    public:

};

struct elevatorState_s {
    double theta;
    double height;
};

struct ballState_s {
    manipulatorState_e manipulatorState;
    double ballTheta;
};

struct hatchState_s {
    manipulatorState_e manipulatorState;
    double hatchTheta;
};


class Superstructure
{
private:
    Elevator elevator;
    Mechanisms mechanisms;
    elevatorState_s currentElevatorState;
    ballState_s currentBallState;
    hatchState_s currentHatchState;

    void commandElevatorState(elevatorState_s newElevatorState);
    void commandBallState(ballState_s newBallState);
    void commandHatchState(hatchState_s newHatchState);
public:
    Superstructure(/* args */);
    void setSuperstructureState(elevatorState_s newElevatorState, bool commanded = false);
    void setSuperstructureState(ballState_s newBallState);
    void setSuperstructureState(hatchState_s newHatchState);
};


#endif // __SUPERSTRUCTURE_H__
