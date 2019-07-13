#include "Schedular.h"


Schedular::Schedular() {

}

void Schedular::addTask(String id, void (*ptr)(), type_e type, Chrono::Resolution timeQuantity, long updateFrequency, String beforeTask) {
    Chrono* timer = NULL;
    int insertAtIndex = -1;
    for(size_t i = 0; i < timedTasks.size(); i++) {
        timedTask_s task = timedTasks.at(i);
        if(task.updateFrequency == updateFrequency && task.timeQuantity == timeQuantity) {
            timer = task.timer;
        }
        if(beforeTask==task.id) {
            insertAtIndex = i;
        }
    }
    if(timer == NULL) {
        timers.push_back(Chrono(timeQuantity));
        timer = &timers.back();
    }
    timedTask_s task;
    task.id = id; task.type = type; task.ptr = ptr; task.timer = timer; task.timeQuantity = timeQuantity; task.updateFrequency = updateFrequency;
    if(insertAtIndex >= 0) {
        timedTasks.insert(timedTasks.begin() + insertAtIndex, task);
    }
    else {
        timedTasks.push_back(task);
    }
}

void Schedular::addTask(untimedTask_s task, String beforeTask) {
    untimedTasks.push_back(task);
}

void Schedular::update() {
    for(auto task : untimedTasks) {
        task.ptr();
    }
    for(auto task : timedTasks) {
        if(!(task.timer->isRunning()) || task.timer->hasPassed(task.updateFrequency)) {
            task.ptr();
            task.timer->stop();
        }
    }
    for(size_t i = 0; i < timers.size()-1; i++) {
        timers.at(i).start();
    }
}

/*
Add funciton which will not allow items to be queued if they are not a certain type
*/

