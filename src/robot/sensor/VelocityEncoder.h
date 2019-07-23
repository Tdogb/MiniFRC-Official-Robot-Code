#ifndef __VELOCITYENCODER_H__
#define __VELOCITYENCODER_H__
#include <Arduino.h>

class VelocityEncoder
{
private:
    volatile int32_t time = 0;
    volatile int32_t steps = 0;
    float encoderConversion = 0.000244140625; // 1/(256 * 16);
    float velocityIntegral = 0;
    float velocity = 0;
public:
    VelocityEncoder();
    ~VelocityEncoder();
    void ISR_ROUTINE();
    float readVelocity();
};


#endif // __VELOCITYENCODER_H__
