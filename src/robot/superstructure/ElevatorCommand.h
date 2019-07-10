#ifndef __ELEVATORCOMMAND_H__
#define __ELEVATORCOMMAND_H__

#include "Command.h"

class ElevatorCommand: public Command
{
private:
    /* data */
public:
    ElevatorCommand(/* args */); //Command rotation, height change, etc
    ~ElevatorCommand();
    void setElevatorHeight();
    void setElevatorRotation();
};


#endif // __ELEVATORCOMMAND_H__
