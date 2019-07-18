#include "Brushed.h"
#include <Arduino.h>

Brushed::Brushed(const int _FWDPin, const int _RVSPin, const int _enPin, const bool _enPinMode)
{
    FWDPin = _FWDPin;
    RVSPin = _RVSPin;
    enPin = _enPin;
    enPinMode = _enPinMode;
    pinMode(FWDPin, OUTPUT);
    pinMode(RVSPin, OUTPUT);
    pinMode(enPin, OUTPUT);
    if(enPinMode) {
        analogWriteFrequency(FWDPin, 600);
        analogWriteFrequency(RVSPin, 600);
    }
    else {
        analogWriteFrequency(FWDPin, 600);
        analogWriteFrequency(RVSPin, 600);
        digitalWrite(enPin, HIGH);
    }
}

Brushed::~Brushed()
{
}