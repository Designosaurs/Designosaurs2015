#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     Shoulder,      tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     Elbow,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     RightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LeftDrive,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    LClaw,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    RClaw,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    Claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    AutoRing,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
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
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Team 6369 Includes

//Sets the maximum power at which the tetrix arm motors can move.
// Zero to 100.
#define MAX_POWER 60


#include "Positions.h"
#include "Vars.h"
#include "Executor.h"
#include "Joysticks.h"
#include "MoveAxis.h"
#include "Home.h"
#include "Macros.h"
#include "ReadMacros.h"



void initializeRobot()
{
	// Place code here to initialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	// Initialize
	disableDiagnosticsDisplay();
	ClearTimer(T1);
	nMotorEncoder[Shoulder] = 0;
	nMotorEncoder[Elbow] = 0;
	servoChangeRate[LClaw] = 4;  // Not too fast-- do not want drop the ring.
	servoChangeRate[RClaw] = 4;
	servo[AutoRing] = 0;
	servo[ LClaw ] = WRIST_INIT_COUNTS;
	servo[RClaw] = SWIVEL_INIT_COUNTS;
	servo[Claw] = CLAW_CLOSED;
	ArmState = HOME;
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

	// Comment this out for testing with "Basic Joystick." But leave it in for competition!
	// waitForStart();   // wait for start of tele-op phase

	// TEST CODE
	// Adjust hardware so RClaw neutral is straight.
	//while(1){servo[RClaw] = 128;}
	// Adjust hardware so LClaw is straight ahead.
	//while(1)  { 		Executor(); MoveWrist( 0 ); }

	MoveWrist( WRIST_HOME  );
	MoveSwivel( SWIVEL_HOME );


	nxtDisplayTextLine(0, "RT BTN: DEMO" );
	while(1)
	{
		if(nNxtButtonPressed == 1)                        // if the current pressed button is 1 (the Right Arrow):
		{

			break;
		}
		Executor();
	}

	LeaveHome();
	ToRingSpiller();
	SpillRings();
	LeaveRingSpill( );
	PlaySound(soundFastUpwardTones);
	WaitTenths(30);

	ToFrontFloor( );
	RingFromFloor( );
	PlaySound(soundFastUpwardTones);
	WaitTenths(30);


	ToFront3( );
	PlaySound(soundFastUpwardTones);
	WaitTenths(30);

	ToFront2( );
	PlaySound(soundFastUpwardTones);
	WaitTenths(30);

	ToFront1( );
	PlaySound(soundFastUpwardTones);
	WaitTenths(30);

	PlaceGoal();
	PlaySound(soundFastUpwardTones);
	WaitTenths(30);



	HomeArm();

}
