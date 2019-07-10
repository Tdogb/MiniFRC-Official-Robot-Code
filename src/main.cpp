#include <Arduino.h>
#include "robot/Schedular.h"

void update1Sec();
void update500Millis();
void updateUntimed();

Schedular sch;

void setup() {
	Serial.begin(9600);
	sch.addTask(sch.REQUIRED, &update1Sec, 1, Chrono::SECONDS);
	sch.addTask(sch.REQUIRED, &update500Millis, 500, Chrono::MILLIS);
	sch.addTask(sch.REQUIRED, &updateUntimed);
}

void loop() {
	sch.update();
}

void update1Sec() {
	Serial.println("1");
}

void update500Millis() {
	Serial.println("0");
}

void updateUntimed() {
	Serial.print("2");
}