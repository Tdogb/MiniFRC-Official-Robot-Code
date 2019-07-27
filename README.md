# MiniFRC Robot Code
Runs on Teensy 3.5 microcontroller
## Features:
* Motion profile generation (cubic spline)
* Pure pursuit tracking algorithm
* Dynamic realtime 3D superstructure collision detection
* Velocity PID controller
* Memory optimized code
* Memory optimized schedular

## Command Structure:
robotState_s --> Superstructure class --> Subsystem class --> Individual component classes

## Classes:
- **Superstructure simulation**: robot/superstructure/SuperstructureMath.cpp
- **Path follower**: robot/autonomous/follower/Follower.cpp
- **Schedular**: robot/Schedular.cpp
## TODO:
* Elevator collision resolution
* Model based feedforward
