#ifndef __TASK_H__
#define __TASK_H__
#include <Chrono.h>
#include <Arduino.h>

enum type_e {
    REQUIRED = 0,
    DEBUG = 1,
    AUTO = 2,
    TELEOP = 3
};

struct untimedTask_s {
    public:
        String id;
        type_e type;
        void (*ptr)();
};
struct timedTask_s {
    public:
        String id;
        type_e type;
        void (*ptr)();
        int timerIndex;
        Chrono::Resolution timeQuantity;
        long updateFrequency;
};


#endif // __TASK_H__
