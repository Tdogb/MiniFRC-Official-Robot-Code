#include <Arduino.h>
#include "robot/Schedular.h"
#include "robot/superstructure/Superstructure.h"

void update1Sec();
void update500Millis();
void updateUntimed();
void elevatorUpdate();

Schedular sch;
unsigned long pastMicros = 0;
unsigned long currentMicros = 0;
//Superstructure superstructure;


void setup() {
	Serial.begin(9600);
	while(!Serial) {;}
	sch.addTask("elevatorUpdate", &elevatorUpdate, REQUIRED, Chrono::SECONDS, 1);
	sch.addTask("elevatorUpdate2", &update1Sec, REQUIRED, Chrono::SECONDS, 1);

}

void loop() {
	sch.update();
}

void elevatorUpdate() {
	currentMicros = micros();
	Serial.println(currentMicros-pastMicros);
	pastMicros = currentMicros;
	//Serial.println("Schedular working");
	//superstructure.setSuperstructureState((elevatorState_s){1,2});
}


void update1Sec() {
	//Serial.println("SEC");
}

// void update500Millis() {
// 	Serial.println("0");
// }

// void updateUntimed() {
// 	Serial.print("2");
// }