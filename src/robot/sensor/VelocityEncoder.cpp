#include "VelocityEncoder.h"

elapsedMicros elapsedTime;

VelocityEncoder::VelocityEncoder()
{

}

VelocityEncoder::~VelocityEncoder()
{

}

void VelocityEncoder::ISR_ROUTINE() {
    float vel = (encoderConversion / (elapsedTime*0.000001))*6.283185;;
    velocityIntegral += vel;
    velocity = vel;
    elapsedTime = 0;
    steps++;
}

float VelocityEncoder::readVelocity() {
    if(elapsedTime > 1e5) {
        return 0;
    }
    if(steps == 0) { return velocity; }
    float output = velocityIntegral/steps;
    steps = 0;
    velocityIntegral = 0;
    return output;
}