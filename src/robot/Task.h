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

struct task_s {
    public:
        String id;
        type_e type;
        void (*ptr)();
};
struct timedTask_s : public task_s {
    public:
        Chrono* timer;
        Chrono::Resolution timeQuantity;
        long updateFrequency;
};
struct untimedTask_s : public task_s {
};

#endif // __TASK_H__
