#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRSensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          Red,           tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          Yellow,        tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          Green,         tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Shoulder,      tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     Elbow,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     RightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LeftDrive,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    LClaw,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    RClaw,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    Claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
#include "hitechnic-irseeker-v2.h"
/*
|----\
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/

// About the setup:
// Shoulder and Elbow are both set up so postive motor => increasing encoder count.
// and increasing degrees on the motor.  (Clockwise rotation when fron is on your right)

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "Positions.h"

/*
#include "GetIR.h"
#include "TickAuto.h"
#include "MovesAuto.h"
#include "AlignPeg1.h"
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
int attempt = 0;
int state;
bool gaveUp = false;
bool inRange = false;

#define INIT 0
#define LOCATING 1
#define PLACING 3

bool bAtBeacon(void) {
        /* Declare variables */
        int zones[5];
        int average = 0;
        bool atBeacon = false;

        /* Read the infrared seeker into an array */
        HTIRS2readAllACStrength(IRSensor, zones[0], zones[1], zones[2], zones[3], zones[4]);

        /* Find the average infrared noise level */
        for(int i = 0; i < 5; i++) average += zones[i];
        average /= 5;

        /* If the critical zones are stronger than the noise, we are in range */
        if(((zones[1] - average) > 10) && ((zones[2] - average) > 10)) inRange = true;

        /* When we are in range and the critical zones are nearly equal (or we have overshot) we are at the beacon */
        if(inRange && ((zones[1] - zones[2]) > -15)) atBeacon = true;

        return atBeacon;
}

void updateDiagnosticsDisplay() {
	nxtDisplayTextLine(1, "--- 6369 ---");
	nxtDisplayTextLine(2, "Attempt %f/10.", attempt);
	nxtDisplayTextLine(3, "--- STATUS ---");
	switch(state) {
		case INIT:
			nxtDisplayTextLine(4, "Waiting");
		break;
		case LOCATING:
			nxtDisplayTextLine(4, "Finding Beacon");
		break;
		case PLACING:
			nxtDisplayTextLine(4, "Placing.");
		break;
	}
	if(gaveUp) {
		nxtDisplayTextLine(6, "Something went wrong.");
	}
}

task asyncTask() {
	while (true) {
		updateDiagnosticsDisplay();
	}
}

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	disableDiagnosticsDisplay();
	state = INIT;
	StartTask(asyncTask, 5);
	servo[Claw] = 0;
	return;
}

task main()
{
	initializeRobot();

	//waitForStart(); // Wait for the beginning of autonomous phase.

   while (bAtBeacon() == false) {
		PlaySound(soundFastUpwardTones);
		attempt++;
		state = LOCATING;
		motor[LeftDrive] = 20;
		motor[RightDrive] = 20;
		wait1Msec(500);
	}
	state = PLACING;
	servo[Claw] = 100;
}
