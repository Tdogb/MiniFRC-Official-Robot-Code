#include "Schedular.h"


Schedular::Schedular() {

}

void Schedular::addTimedTask(String id, void (*ptr)(), type_e type, Chrono::Resolution timeQuantity, long updateFrequency, String beforeTask) {
    int timerIndex = -1;
    int insertAtIndex = -1;
    for(size_t i = 0; i < timedTasks.size(); i++) {
        timedTask_s task = timedTasks.at(i);
        if(task.updateFrequency == updateFrequency && task.timeQuantity == timeQuantity) {
            timerIndex = task.timerIndex;
        }
        if(beforeTask==task.id) {
            insertAtIndex = i;
        }
    }
    if(timerIndex == -1) {
        timers.push_back({Chrono(timeQuantity), updateFrequency, false});
        timerIndex = timers.size()-1;
    }
    // timedTask_s task;
    // task.id = id; task.type = type; task.ptr = ptr; task.timerIndex = timerIndex; task.timeQuantity = timeQuantity; task.updateFrequency = updateFrequency;
    if(insertAtIndex >= 0) {
        timedTasks.insert(timedTasks.begin() + insertAtIndex,{id, type, ptr, timerIndex, timeQuantity, updateFrequency});
    }
    else {
        timedTasks.push_back({id, type, ptr, timerIndex, timeQuantity, updateFrequency});
    }
}

void Schedular::addUntimedTask(untimedTask_s task, String beforeTask) {
    untimedTasks.push_back(task);
}

void Schedular::update() {
    for(size_t i = 0; i < untimedTasks.size(); i++) {
        untimedTasks[i].ptr();
    }
    for(size_t i = 0; i < timers.size(); i++) {
        timers[i].updated = false;
        if(timers[i].timer.hasPassed(timers[i].updateFrequency, true)) {
            timers[i].updated = true;
        }
    }
    for(size_t i = 0; i < timedTasks.size(); i++) {
        if(timers[timedTasks[i].timerIndex].updated) {
            timedTasks[i].ptr();
        }
    }
}

/*
Add function which will not allow items to be queued if they are not a certain type
*/

