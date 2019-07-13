#include <Arduino.h>
#include "robot/Schedular.h"
#include "robot/superstructure/Superstructure.h"

void update1Sec();
void update500Millis();
void updateUntimed();
void elevatorUpdate();

Schedular sch;
Superstructure superstructure;


void setup() {
	Serial.begin(9600);
	while(!Serial) {;}
	sch.addTask("elevatorUpdate", &elevatorUpdate, REQUIRED, Chrono::MILLIS, 100);
}

void loop() {
	sch.update();
}

void elevatorUpdate() {
	superstructure.setSuperstructureState((elevatorState_s){1,2});
}


// void update1Sec() {
// 	Serial.println("1");
// }

// void update500Millis() {
// 	Serial.println("0");
// }

// void updateUntimed() {
// 	Serial.print("2");
// }