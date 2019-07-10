#include "Schedular.h"


Schedular::Schedular() {

}

void Schedular::addTask(type_e type, void (*ptr)(), long updateFrequency, Chrono::Resolution timeQuantity) {
    if(updateFrequency != 0) {
        timedTasks.push_back((timedTask_s){ptr, new Chrono(timeQuantity), updateFrequency});
    }
    else {
        untimedTasks.push_back((untimedTask_s){ptr});
    }
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

