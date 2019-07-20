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

void debugTimedUpdate();
void debugUntimedUpdate();
void encoderUpdate();
void followerUpdate();

int32_t encoderPositions[2]; //left, right

Stepper rotationStepper(ROTATION_STEP_PIN, ROTATION_DIR_PIN); //step pin, dir pin
Stepper leadscrewStepper(LEADSCREW_STEP_PIN,LEADSCREW_DIR_PIN);
Encoder leftEncoder(L_ENC_A, L_ENC_B);
Encoder rightEncoder(R_ENC_A, R_ENC_B);
Brushed leftMotor(L_MOTOR_FWD, L_MOTOR_RVS, L_MOTOR_EN, leftEncoder);
Brushed rightMotor(R_MOTOR_FWD, R_MOTOR_RVS, R_MOTOR_EN, rightEncoder);

Elevator elevator(leadscrewStepper, rotationStepper);
Drivetrain drivetrain(leftMotor, rightMotor);
Mechanisms mechanisms(1);
Follower follower(1);

Superstructure superstructure(elevator,drivetrain,mechanisms);
Schedular sch;
SuperstructureMath ss;

void setup() {
	Serial.begin(9600);
	while(!Serial) {;}
    sch.addUntimedTask("encoderUpdate", &encoderUpdate, REQUIRED);
    sch.addTimedTask("follwerupdate", &followerUpdate, AUTO, Chrono::MILLIS, 10);
	sch.addTimedTask("debugTimedUpdate", &debugTimedUpdate, DEBUG, Chrono::MILLIS, 20);
    sch.addUntimedTask("debugUntimedUpdate", &debugUntimedUpdate, DEBUG);
}

void loop() {
	sch.update();
}

void debugTimedUpdate() {
    follower.printPosition();
}

void debugUntimedUpdate() {
}

void followerUpdate() {
    follower.update();
}

void encoderUpdate() {
    encoderPositions[0] = leftEncoder.read();
    encoderPositions[1] = rightEncoder.read();
}

