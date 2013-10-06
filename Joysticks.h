/*
|----\             
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/

// Dinosaur Joystick Movement
//

int JoyScale( int JoyIn )
{
	int JoyOut;
	JoyOut = JoyIn;
	if ( JoyOut > 128) JoyOut = 128;
	if (JoyOut < -128) JoyOut = -128;
	return JoyOut;
}



//////////////////////////  Motor Vectors /////////////////////////////////////////////////////////////////
// Define the appropriate movements for the motors for the desired outcome for the Joystick control.
// For example, JoyUp_Shoulder means:
//		The user presses the joystick wanting the arm tip to go up, and the
//		The shoulder should move at the prescribed rate of speed.


////////////////////////  JOYSTICK MOVEMENT /////////////////////////////////////////////
// JoyPosition 0 to 128
// JOY_SPEED around 50


void JoyToMotor( tMotor MotorIndex, int JoyPosition, int PowerPos )

{

	if ( abs(JoyPosition) > JOY_DEADBAND)

	motor[ MotorIndex ] = JoyPosition * PowerPos / 128;

	else 	motor[ MotorIndex ] = 0;

}


void JoyToWrist( int JoyPosition, int PowerPos )
{
	if ( abs(JoyPosition) > JOY_DEADBAND)
		fWristSpeed = (float) JoyPosition * (float) PowerPos / 2000;
	else 	fWristSpeed = 0;
}

void JoyToSwivel( int JoyPosition, int PowerPos  )
{
	if ( abs(JoyPosition) > JOY_DEADBAND)
		fSwivelSpeed = (float) JoyPosition * (float) -PowerPos / 2000;
	else 	fSwivelSpeed = 0;
}

void ContolClaw( void )
{
	//servo[Claw]=0;

	if (joy1Btn(7) == 1)
	{
		servoChangeRate[RClaw] = 10;
		//PlaySound(soundBlip);
		servo[RClaw]= RCLAW_CLOSED;
	}
	
	if (joy1Btn(6) == 1)
	{
		servoChangeRate[LClaw] = 10;
		//PlaySound(soundBlip);
		servo[LClaw]= LCLAW_CLOSED;
	}
	
	if (joy1Btn(5) == 1)
	{
		servoChangeRate[RClaw] = 10;
		//PlaySound(soundBlip);
		servo[RClaw]= RCLAW_OPEN;
	}
	
	if (joy1Btn(8) == 1)
	{
		servoChangeRate[LClaw] = 10;
		//PlaySound(soundBlip);
		servo[LClaw]= LCLAW_OPEN;
	}
}


void MoveArmFromJoysticks( void )
{
	int y1;
	int y2;
	int x2;
	int x1;

	ContolClaw();

	// If joy1 driving, then do not have joy1 control the arm.
	if (Joy1Drive)
		return;

	y1 = JoyScale( joystick.joy1_y1 );
	y2 = JoyScale( joystick.joy1_y2 );
	x2 = JoyScale( joystick.joy1_x2 );
	x1 = JoyScale( joystick.joy1_x1 );

		// MANUAL MODE-- Each joystick axis controls a motor axie
		JoyToMotor( Shoulder, y1, MAX_POWER);
		// Elbow direction is reversed from shoulder:
		JoyToMotor( Elbow, y2, MAX_POWER );
		JoyToWrist( x1, MAX_POWER );
		JoyToSwivel( x2, MAX_POWER );

}
