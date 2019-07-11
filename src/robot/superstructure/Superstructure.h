/*
Superstructure class contains all of the subsystem instances
Supersturcture.setElevatorHeight --> resolve collisions --> run subsystem
*/
#ifndef __SUPERSTRUCTURE_H__
#define __SUPERSTRUCTURE_H__
#include "robot/subsystems/Elevator.h"
#include "robot/subsystems/Mechanisms.h"

struct superstructureState_s {
};

struct elevatorState_s: superstructureState_s {
};

struct mechanismState_s: superstructureState_s {
};


class Superstructure
{
private:
    Elevator elevator;
    Mechanisms mechanisms;
public:
    Superstructure(/* args */);
    ~Superstructure();
    void setSuperstructureState(superstructureState_s newState);
};


#endif // __SUPERSTRUCTURE_H__
