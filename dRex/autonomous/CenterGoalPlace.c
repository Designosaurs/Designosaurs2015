#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S3,     HTIRS2,              sensorI2CCustom)
#pragma config(Sensor, S4,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           motorA,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     right_drive,   tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     left_drive,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     harvester,     tmotorTetrix, PIDControl)
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
Judge Demo Program: 2014-2015 (Cascade Effect)
*/

#include "JoystickDriver.c"
#include "a_globals.h"
#include "..\common\bot_specific.h"
#include "..\common\init.h"
#include "..\common\functions.h"
#include "..\common\servo.h"
#include "..\sensor\drivers\hitechnic-irseeker-v2.h"
#include "..\sensor\GetIR.h"
#include "..\common\macros.h"
#include "..\common\UpdateLiftEncoderTask.h"
#include "..\common\UpdateDriveBearings.h"
#include "..\common\HarvesterTask.h"
#include "drive.h"
#include "sonar.h"

task main() {
    initDisplay();
    goalGrabberUp();
    initPlacer();
    initElbow();
    initWrist();
    initDriveConfig();

    eraseDisplay();
    StartTask(UpdateLiftEncoderTask);
    StartTask(HarvesterTask);
    StartTask(UpdateDriveBearingsTask);

    goForwardDistance(2.0, 80);
    goToRange(43, 40);
    float angle_before_ir = total_angle;
    PointToIR();
    liftToCenterGoal();
    wait1Msec(500);
    liftPlace();
    wait1Msec(500);
    liftToFloor();
    pivotToTotalAngle(angle_before_ir, 70);
    wait1Msec(500);
    pivotDegrees(90, 70);
    goForwardDistance(1, 80);
    pivotDegrees(-90, 70);
    goForwardDistance(3.0, 80);
}
