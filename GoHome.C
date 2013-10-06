#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          Red,           tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          Yellow,        tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          Green,         tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Shoulder,      tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     Elbow,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     RightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LeftDrive,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    Wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    Swivel,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    Claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
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

#define MAX_POWER 30

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages coming from the controller.
//#include "Positions.h"
#include "Vars.h"
#include "Executor.h"
//#include "Joysticks.h"
//#include "ReadMacros.h"
#include "MoveAxis.h"
#include "Home.h"
//#include "Macros.h"

task main()
{
	// Initialize
	disableDiagnosticsDisplay();
	ClearTimer(T1);
	nMotorEncoder[Shoulder] = 0;
	nMotorEncoder[Elbow] = 0;

	// SLOWLY move the servos home.
	servoChangeRate[Wrist] = 2;
	servoChangeRate[Swivel] = 2;
	servo[ Wrist ] = WRIST_INIT_COUNTS;
	servo[Swivel] = SWIVEL_INIT_COUNTS;
	servo[Claw] = CLAW_CLOSED;

	// The excutor will also move the swivel and wrist.
	MoveWrist( WRIST_HOME  );
	MoveSwivel( SWIVEL_HOME );

	HomeArm();
	if (Beeps) PlaySound(soundUpwardTones);
	wait10Msec(100);


}
