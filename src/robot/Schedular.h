#ifndef __SCHEDULAR_H__
#define __SCHEDULAR_H__
#include <Chrono.h>
#include <vector>
#include <Arduino.h>
#include <stdint.h>
#include <cstdlib>
#include "Task.h"

class Schedular
{
private:
    std::vector<timedTask_s> timedTasks;
    std::vector<untimedTask_s> untimedTasks;
public:
    Schedular();

    //TODO: Add ability to add task before another one
    void addTask(timedTask_s task, String beforeTask = "");
    void addTask(untimedTask_s task, String beforeTask = "");

    void update();
};

#endif // __SCHEDULAR_H__