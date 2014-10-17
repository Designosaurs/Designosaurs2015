#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,    ultrasonic,               sensorSONAR)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     right_drive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     left_drive,   	tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    placer,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  _____            _
 |  __ \          (_)
 | |  | | ___  ___ _  __ _ _ __   ___  ___  __ _ _   _ _ __ ___
 | |  | |/ _ \/ __| |/ _` | '_ \ / _ \/ __|/ _` | | | | '__/ __|
 | |__| |  __/\__ \ | (_| | | | | (_) \__ \ (_| | |_| | |  \__ \
 |_____/ \___||___/_|\__, |_| |_|\___/|___/\__,_|\__,_|_|  |___/
                      __/ |
                     |___/                            Team #6369
 Autonomous Code: 2014-2015 (Cascade Effect)

 */

//#include "JoystickDriver.c"
#include "system/vars.h"
#include "config/drive.h"
#include "config/sonar.h"
#include "system/drive.h"
#include "system/servo.h"
#include "system/sonar.h"
#include "task/UpdateEncoderTask.h"
#include "task/DebugTask.h"
#include "task/MainTask.h"
