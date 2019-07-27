#include "main.h"

/*
------------------------------------------------
main contains static functions and objects
------------------------------------------------
*/

void setup() {
	Serial.begin(9600);
    pinMode(R_ENC_ALT, INPUT);
    pinMode(L_ENC_ALT, INPUT);
    pinMode(LED_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(R_ENC_ALT), ISR_ROUTINE_R, RISING);
    attachInterrupt(digitalPinToInterrupt(L_ENC_ALT), ISR_ROUTINE_L, RISING);
	while(!Serial) {;}

    sch.addUntimedTask("encoderPositionUpdate", &encoderPositionUpdate, REQUIRED);
    sch.addUntimedTask("subsystemsUpdate", &subsystemsUpdate, REQUIRED);
    sch.addTimedTask("encoderVelocityUpdate", &encoderVelocityUpdate, REQUIRED, Chrono::MICROS, 50);
    sch.addTimedTask("follwerupdate", &followerUpdate, AUTO, Chrono::MILLIS, 10); //Should be 10 millis
    sch.addTimedTask("pidUpdate", &pidUpdate, REQUIRED, Chrono::MICROS, 100);
	sch.addTimedTask("debugTimedUpdate", &debugTimedUpdate, DEBUG, Chrono::MILLIS, 150);
    sch.addUntimedTask("debugUntimedUpdate", &debugUntimedUpdate, DEBUG);
}

void loop() { sch.update(); }
void debugTimedUpdate() { }
void debugUntimedUpdate() { }

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
void subsystemsUpdate() {
    drivetrain.update();
    elevator.update();
}

void followerUpdate() { follower.update(); }
void ISR_ROUTINE_L() { leftVelocityEncoder.ISR_ROUTINE(); }
void ISR_ROUTINE_R() { rightVelocityEncoder.ISR_ROUTINE(); }