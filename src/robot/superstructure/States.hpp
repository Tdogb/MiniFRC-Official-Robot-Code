#ifndef __STATES_HPP__
#define __STATES_HPP__
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

struct drivetrainState_s {
    float rightVelocity = 0;
    float leftVelocity = 0;
};


#endif // __STATES_HPP__
