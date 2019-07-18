#include <IntervalTimer.h>
#include <Encoder.h>
#include "RobotEncoder.h"
#include <robot/defs.h>
#include <avr/interrupt.h>
#include <avr/io.h>

elapsedMicros time_left;
elapsedMicros time_right;
uint32_t time_elapsed_left = 0;
uint32_t time_elapsed_right = 0;
volatile double encSpeed_right = 0;
volatile double encSpeed_left = 0;

void encoderInit()
{
    pinMode(L_ENC_A, INPUT);
    pinMode(L_ENC_B, INPUT);
    pinMode(R_ENC_A, INPUT);
    pinMode(R_ENC_B, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(L_ENC_A), updateEncoderLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(R_ENC_A), updateEncoderRight, RISING);
}

void updateEncoderLeft()
{
  time_elapsed_left = time_left;
  time_left = 0;
}

void updateEncoderRight() {
  time_elapsed_right = time_right;
  time_right = 0;
}

double readEncoder(bool leftSide) {
    if(time_elapsed_left != 0) {
      encSpeed_left = (double)3900/(double)time_elapsed_left;
    }
    else {
      encSpeed_left = 0;
    }
    if(time_elapsed_right != 0) {
      encSpeed_right = (double)3900/(double)time_elapsed_right;
    }
    else {
      encSpeed_right = 0;
    }
  return (leftSide ? encSpeed_left : encSpeed_right);
}