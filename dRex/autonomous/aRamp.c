#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     right_drive,   tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     left_drive,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     harvester,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    placer,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    goal_grab,            tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*

_____             _
|  __ \          (_)
| |  | | ___  ___ _  __ _ _ __   ___  ___  __ _ _   _ _ __ ___
| |  | |/ _ \/ __| |/ _` | '_ \ / _ \/ __|/ _` | | | | '__/ __|
| |__| |  __/\__ \ | (_| | | | | (_) \__ \ (_| | |_| | |  \__ \
|_____/ \___||___/_|\__, |_| |_|\___/|___/\__,_|\__,_|_|  |___/
					 __/ |
					|___/                            Team #6369
Autonomous Code: 2014-2015 (Cascade Effect)
*/

#include "JoystickDriver.c"
#include "a_globals.h"
#include "..\common\bot_specific.h"
#include "..\common\init.h"
#include "..\common\functions.h"
#include "..\common\servo.h"
#include "drive.h"
#include "sonar.h"
#include "..\sensor\ultrasonic.h"
#include "..\common\UpdateLiftEncoderTask.h"
#include "..\common\UpdateDriveBearings.h"
#include "..\common\UpdateDisplayTask.h"
#include "FromParking.h"
#include "IfBlocked.h"
#include "FromRamp.h"

// If this is true, will stop if blocked:
bool KickstandIfBlocked = true;

task main() {
    initDisplay();
    goalGrabberUp();
    initPlacer();
    initElbow();
    initWrist();
    initDriveConfig();

    waitForStart();
    eraseDisplay();
    StartTask(UpdateLiftEncoderTask);
    StartTask(UpdateDisplayTask);
    StartTask(UpdateDriveBearingsTask);

    GoalFromRamp();
}
