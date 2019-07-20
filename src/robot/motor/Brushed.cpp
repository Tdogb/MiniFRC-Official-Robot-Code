#include "Brushed.h"
#include <Arduino.h>

Brushed::Brushed(const int _FWDPin, const int _RVSPin, const int _enPin, Encoder &_encoder, float &_encoderVelocity, const float Kp, const float Ki, const float Kd)
:encoder(_encoder), encoderVelocity(_encoderVelocity)
{
    pid.configure(Kp, Ki, Kd, pidUpdateFreq, 16, true);
    pid.setOutputRange(-maxVoltage, maxVoltage);
    FWDPin = _FWDPin;
    RVSPin = _RVSPin;
    enPin = _enPin;
    pinMode(_FWDPin, OUTPUT);
    pinMode(_RVSPin, OUTPUT);
    pinMode(_enPin, OUTPUT);
    analogWriteFrequency(_FWDPin, 600);
    analogWriteFrequency(_RVSPin, 600);
}

Brushed::~Brushed()
{
}

void Brushed::commandVoltage(float VoltageMV) {
    if(VoltageMV != 0) {
        if(VoltageMV > 0) {
            analogWrite(RVSPin, 0);
            analogWrite(FWDPin, 256*(VoltageMV/maxVoltage));
        }
        else {
            analogWrite(FWDPin, 0);
            analogWrite(RVSPin, -256*(VoltageMV/maxVoltage));
        }
    }
    else {
        analogWrite(FWDPin, 0);
        analogWrite(RVSPin, 0);
    }
}

void Brushed::pidStep() {
    commandVoltage(pid.step(velocitySetpoint, encoderVelocity));
}

void Brushed::commandVelocity(float velocity) {
    velocitySetpoint = velocity;
}