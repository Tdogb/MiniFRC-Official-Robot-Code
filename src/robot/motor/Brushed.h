#ifndef __BRUSHED_H__
#define __BRUSHED_H__
#include <Encoder.h>
#include <FastPID.h>

class Brushed
{
private:
    const float pidUpdateFreq = 10000;
    const float maxVoltage = 24000; //milivolts
    int FWDPin;
    int RVSPin;
    int enPin;
    float velocitySetpoint;
    Encoder &encoder;
    float &encoderVelocity;
    FastPID pid;
    void commandVoltage(float voltage);
public:
    Brushed(const int _FWDPin, const int _RVSPin, const int _enPin, Encoder &_encoder, float &_encoderVelocity, const float _Kp, const float _Ki, const float _Kd);
    ~Brushed();
    void commandVelocity(float velocity);
    float getVelocity();
    void pidStep();
};

#endif // __BRUSHED_H__
