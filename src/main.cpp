#include <Arduino.h>
#include <TeensyStep.h>
#include "robot/Schedular.h"
#include "robot/superstructure/Superstructure.h"
#include "robot/subsystems/Drivetrain.h"
#include "robot/subsystems/Elevator.h"
#include "robot/subsystems/Mechanisms.h"
#include "robot/defs.h"
#include "robot/superstructure/SuperstructureMath.h"

void elevatorUpdate();

Stepper rotationStepper(ROTATION_STEP_PIN, ROTATION_DIR_PIN); //step pin, dir pin
Stepper leadscrewStepper(LEADSCREW_STEP_PIN,LEADSCREW_DIR_PIN);

Elevator elevator(leadscrewStepper,rotationStepper);
Drivetrain drivetrain(1);
Mechanisms mechanisms(1);

Superstructure superstructure(elevator,drivetrain,mechanisms);
Schedular sch;
SuperstructureMath ss;

void setup() {
	Serial.begin(9600);
	while(!Serial) {;}
	sch.addTimedTask("elevatorUpdate", &elevatorUpdate, REQUIRED, Chrono::MILLIS, 1000);
}

void loop() {
	sch.update();
}

void elevatorUpdate() {
	//superstructure.setSuperstructureState((elevatorState_s){1,2});
	//ss.calculateElevatorRotation((float)(PI/2));
	ss.calculateMechanismRotation((float)PI/2);
}