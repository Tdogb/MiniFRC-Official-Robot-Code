#ifndef __BRUSHED_H__
#define __BRUSHED_H__

class Brushed
{
private:
    int FWDPin;
    int RVSPin;
    int rampTime;
    bool enPinMode;
    int enPin;
public:
    Brushed(const int _FWDPin, const int _RVSPin, const int _enPin, const bool _enPinMode);
    ~Brushed();
    void commandVoltage(float voltage);
    void commandVelocity();
};

#endif // __BRUSHED_H__
