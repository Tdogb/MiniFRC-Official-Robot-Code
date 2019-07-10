#include <vector>
#ifndef __QUEUE_H__
#define __QUEUE_H__

class Queue
{
private:
    std::vector<void(*)(int)> vqueue;
    std::vector<int> arguments;
    bool* monitoringValue;

public:
    Queue();
    void update();
    void addToQueue(void (*ptr)(int), int argument);
    void addMeasuingValue(bool* _monitoringValue);
};


#endif // __QUEUE_H__