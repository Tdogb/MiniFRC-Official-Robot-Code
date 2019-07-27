#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include <TeensyStep.h>
#include "robot/Schedular.h"
#include "robot/superstructure/Superstructure.h"
#include "robot/subsystems/Drivetrain.h"
#include "robot/subsystems/Elevator.h"
#include "robot/subsystems/Mechanisms.h"
#include "robot/defs.h"
#include "robot/superstructure/SuperstructureMath.hpp"
#include "robot/motor/Brushed.h"
#include "robot/autonomous/follower/Follower.h"
#include <Encoder.h>
#include "robot/sensor/VelocityEncoder.h"

void debugTimedUpdate();
void debugUntimedUpdate();
void encoderPositionUpdate();
void encoderVelocityUpdate();
void followerUpdate();
void pidUpdate();
void subsystemsUpdate();
void ISR_ROUTINE_L();
void ISR_ROUTINE_R();

int32_t encoderPositions[2]; //left, right
float encoderVelocities[2];
int32_t previousPosition[2] = {0,0};

VelocityEncoder leftVelocityEncoder{};
VelocityEncoder rightVelocityEncoder{};

Stepper rotationStepper(ROTATION_STEP_PIN, ROTATION_DIR_PIN); //step pin, dir pin
Stepper leadscrewStepper(LEADSCREW_STEP_PIN,LEADSCREW_DIR_PIN);
Encoder leftEncoder(L_ENC_A, L_ENC_B);
Encoder rightEncoder(R_ENC_A, R_ENC_B);
Brushed leftMotor(L_MOTOR_FWD, L_MOTOR_RVS, L_MOTOR_EN, leftEncoder, encoderVelocities[0], 0.1f, 0.f, 0.f);
Brushed rightMotor(R_MOTOR_FWD, R_MOTOR_RVS, R_MOTOR_EN, rightEncoder, encoderVelocities[1], 0.1f, 0.f, 0.f);

Elevator elevator(leadscrewStepper, rotationStepper);
Drivetrain drivetrain(leftMotor, rightMotor);
Mechanisms mechanisms{};

Superstructure superstructure(elevator,drivetrain,mechanisms);
Schedular sch;
SuperstructureMath ss;

Follower follower(superstructure);

#endif // __MAIN_H__
