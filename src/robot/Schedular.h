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
    struct task_s {
        String id; //Mabe change this to namespace or subclass?
        void (*ptr)();
    };
    struct timedTask_s : task_s {
        Chrono* timer;
        unsigned long updateFrequency;
    };
    struct untimedTask_s : task_s {
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
    void addTask(type_e type, void (*ptr)(), long updateFrequency = 0, Chrono::Resolution timeQuantity = Chrono::MICROS, task_s* insertBefore = NULL);
    void update();
};

#endif // __SCHEDULAR_H__