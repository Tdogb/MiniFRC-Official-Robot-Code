#ifndef __BRUSHED_H__
#define __BRUSHED_H__
#include <Encoder.h>

class Brushed
{
private:
    int FWDPin;
    int RVSPin;
    int rampTime;
    bool enPinMode;
    int enPin;
    Encoder &encoder;
public:
    Brushed(const int _FWDPin, const int _RVSPin, const int _enPin, Encoder &_encoder);
    ~Brushed();
    void commandVoltage(float voltage);
    void commandVelocity(float velocity);
    float getVelocity();
};

#endif // __BRUSHED_H__
