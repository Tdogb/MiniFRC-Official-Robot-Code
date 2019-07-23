#include <Arduino.h>
#include <TeensyStep.h>
#include "robot/Schedular.h"
#include "robot/superstructure/Superstructure.h"
#include "robot/subsystems/Drivetrain.h"
#include "robot/subsystems/Elevator.h"
#include "robot/subsystems/Mechanisms.h"
#include "robot/defs.h"
#include "robot/superstructure/SuperstructureMath.h"
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
void ISR_ROUTINE_L();
void ISR_ROUTINE_R();

int32_t encoderPositions[2]; //left, right
float encoderVelocities[2];
int32_t previousPosition[2] = {0,0};

// elapsedMicros timeLeft;
// elapsedMicros timeRight;
// int32_t elapsedTimeLeft;
// int32_t elapsedTimeRight;
// int32_t stepsLeft = 0;
// int32_t stepsRight = 0;

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
Mechanisms mechanisms(1);

Superstructure superstructure(elevator,drivetrain,mechanisms);
Schedular sch;
SuperstructureMath ss;

Follower follower(superstructure);

void setup() {
	Serial.begin(9600);
    pinMode(R_ENC_ALT, INPUT);
    pinMode(L_ENC_ALT, INPUT);
    pinMode(LED_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(R_ENC_ALT), ISR_ROUTINE_R, RISING);
    attachInterrupt(digitalPinToInterrupt(L_ENC_ALT), ISR_ROUTINE_L, RISING);
	while(!Serial) {;}

    sch.addUntimedTask("encoderPositionUpdate", &encoderPositionUpdate, REQUIRED);
    sch.addTimedTask("encoderVelocityUpdate", &encoderVelocityUpdate, REQUIRED, Chrono::MICROS, 50);
    sch.addTimedTask("follwerupdate", &followerUpdate, AUTO, Chrono::MILLIS, 200); //Should be 10 millis
    sch.addTimedTask("pidUpdate", &pidUpdate, REQUIRED, Chrono::MICROS, 100);
	sch.addTimedTask("debugTimedUpdate", &debugTimedUpdate, DEBUG, Chrono::MILLIS, 150);
    sch.addUntimedTask("debugUntimedUpdate", &debugUntimedUpdate, DEBUG);
}

void loop() {
	sch.update();
}

void debugTimedUpdate() {
    follower.printPosition();
    //Serial << encoderVelocities[1] << '\n';
}

void debugUntimedUpdate() {
}

void encoderPositionUpdate() {
    encoderPositions[0] = leftEncoder.read();
    encoderPositions[1] = rightEncoder.read();
}

void encoderVelocityUpdate() {
    encoderVelocities[0] = leftVelocityEncoder.readVelocity();
    encoderVelocities[1] = rightVelocityEncoder.readVelocity();
}

void pidUpdate() {
    leftMotor.pidStep();
    rightMotor.pidStep();
}

void followerUpdate() {
    follower.update();
}

void ISR_ROUTINE_L() {
    //Serial.println("ISR");
    leftVelocityEncoder.ISR_ROUTINE();
}

void ISR_ROUTINE_R() {
    rightVelocityEncoder.ISR_ROUTINE();
}