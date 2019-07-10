#ifndef __SCHEDULAR_H__
#define __SCHEDULAR_H__
#include <Chrono.h>
#include <vector>
#include <Arduino.h>
#include <stdint.h>
#include <cstdlib>

class Schedular
{
private:
    struct timedTask_s {
        void (*ptr)();
        Chrono* timer;
        unsigned long updateFrequency;
    };
    struct untimedTask_s {
        void (*ptr)();
    };
    std::vector<Schedular::timedTask_s> timedTasks;
    std::vector<untimedTask_s> untimedTasks;
public:
    Schedular();
    enum type_e {
        REQUIRED = 0,
        DEBUG = 1,
        AUTO = 2,
        TELEOP = 3
    };
    //TODO: Add ability to add task before another one
    void addTask(type_e type, void (*ptr)(), long updateFrequency = 0, Chrono::Resolution timeQuantity = Chrono::MICROS);
    void update();
};

#endif // __SCHEDULAR_H__