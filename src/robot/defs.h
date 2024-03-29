#define WHEEL_DIA 0.051
#define WHEELBASE_RADIUS 0.101
#define WHEELBASE_DIA 0.202

#define X_BUTTON 1
#define TRI_BUTTON 3
#define SQR_BUTTON 0
#define O_BUTTON 2

#define L1 4
#define L2 5
#define R1 6
#define R2 7

#define DPAD_UP 8
#define DPAD_RIGHT 9
#define DPAD_DOWN 10
#define DPAD_LEFT 11

//Controls

#define LEVEL_UP DPAD_UP
#define LEVEL_DOWN DPAD_DOWN
#define ROTATION_LEFT_COURSE DPAD_LEFT
#define ROTATION_RIGHT_COURSE DPAD_RIGHT
#define ROTATION_LEFT_FINE SQR_BUTTON
#define ROTATION_RIGHT_FINE O_BUTTON
#define THROTTLE_AXIS yLAxis
#define TURN_AXIS xRAxis
#define BALL_INTAKE BUT_
#define BALL_OUTTAKE BUT_R1
#define HATCH_INTAKE L2
#define HATCH_OUTTAKE L1

//Packet size
#define ML 4

//Pins
#define LED_PIN 13
#define PCB
#ifdef PCB
#define ROTATION_STEP_PIN 6
#define ROTATION_DIR_PIN 8
#define LEADSCREW_STEP_PIN 7
#define LEADSCREW_DIR_PIN 9

#define R_MOTOR_FWD 5
#define R_MOTOR_RVS 4
#define R_MOTOR_EN 22

#define L_MOTOR_FWD 2
#define L_MOTOR_RVS 3
#define L_MOTOR_EN 23

#define L_ENC_A 26
#define L_ENC_B 27
#define R_ENC_A 24
#define R_ENC_B 25

#define L_ENC_ALT 28 
#define R_ENC_ALT 29

#else

#define ROTATION_STEP_PIN 11
#define ROTATION_DIR_PIN 12
#define LEADSCREW_STEP_PIN 29
#define LEADSCREW_DIR_PIN 30

#define R_MOTOR_FWD 6
#define R_MOTOR_RVS 5
#define R_MOTOR_EN 7

#define L_MOTOR_FWD 3
#define L_MOTOR_RVS 4
#define L_MOTOR_EN 2

#define L_ENC_A 9
#define L_ENC_B 10
#define R_ENC_A 25
#define R_ENC_B 26

#define L_ENC_ALT 8 
#define R_ENC_ALT 27

#endif