#include "Schedular.h"


Schedular::Schedular() {

}

void Schedular::addTask(timedTask_s task, String beforeTask) {
    //timedTasks.push_back((timedTask_s){ptr, new Chrono(timeQuantity), updateFrequency});
    timedTasks.push_back(task);
}

void Schedular::addTask(untimedTask_s task, String beforeTask) {
    untimedTasks.push_back(task);
}

void Schedular::update() {
    for(auto task : untimedTasks) {
        task.ptr();
    }
    for(auto task : timedTasks) {
        if(task.timer->hasPassed(task.updateFrequency),true) {
            task.ptr();
        }
    }
}

/*
Add funciton which will not allow items to be queued if they are not a certain type
*/

