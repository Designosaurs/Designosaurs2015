/*
|----\
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/

// EXECUTOR
// Called frequently during every loop.
// Handles all the background level tasks:
//		Drive
//		Encoder reading and speed determination.
//		Joystick reading.

//////////////////// Maintain the LClaw position, based on WristSpeed //////////////////
int ClampToByte( int Input )
{
	short Output;
	if (Input > 255) return 255;
	if (Input < 0) return 0;
	Output = (short) Input;
	return Output;
}

// LClaw postion is maintained in degrees.
#define WRIST_HI_LIMIT   65
#define WRIST_LOW_LIMIT (-25)


/////////////////////// DRIVE ////////////////////////////////////////////

#define HI_GEAR 1
#define LO_GEAR 3
void Drive( void )
{
	int y1;
	int y2;

	// If Joy1 has taken control, it takes over.
	if (Joy1Drive)
	{
		y1 = 	 joystick.joy1_y1;
		y2 = 	 joystick.joy1_y2;
		UsingHiGear = Joy1HiGear;
	}
	else
	{
		y1 = 	 joystick.joy2_y1;
		y2 = 	 joystick.joy2_y2;
		UsingHiGear = Joy2HiGear;
	}

	if (abs(y2) > JOY_DEADBAND)
	{
		if (UsingHiGear)
			motor[LeftDrive] = -y2 / HI_GEAR;
		else
			motor[LeftDrive] = -y2 / LO_GEAR;
	}
	else
	{
		motor[LeftDrive] = 0;
	}

	if (abs(y1) > JOY_DEADBAND)
	{
		if (UsingHiGear)
			motor[RightDrive] = y1 /HI_GEAR ;
		else	motor[RightDrive] = y1 / LO_GEAR;
	}
	else
	{
		motor[RightDrive] = 0;
	}
}

//////////////////////  EXECUTOR /////////////////////////////////
// Maintain a time rhat will do stuff every 50 mS, as
// long as you call it more often than that.

#define STALL_THRESHOLD 12
#define STALL_TIME 8

void 	ResetStall( void )
{
	StallCount[0] = 0;
	StallCount[1] = 0;
	Stalled[0] = 0;
	Stalled[1] = 0;
}

void Every50mS( void )
{
	int i;
	long valTime1;
	valTime1 = time1[T1];
	if (valTime1 > 50)
	{
		ClearTimer(T1);
		// Speed and stall detection
		for(i=0; i<=1; i++)
		{
			AxisSpeed[i] = EncRead[ i ] - PriorEncRead[ i ];
			PriorEncRead[i] = EncRead[i];
			if (abs(AxisSpeed[i]) < STALL_THRESHOLD)
			{
				StallCount[ i ]+= 1;
				if (StallCount[ i ] > STALL_TIME)
				{
					Stalled[i] = 1;
					StallCount[ i ] = STALL_TIME;
				}
			}
			else
			{
				StallCount[ i ] = 0;
				Stalled[ i ] = 0;
			}
		}

		//StringFormat(sDisplay, "S: %3d E: %3d W: %3d", ShoulderPos, ElbowPos, WristPos);
		nxtDisplayString(3, "S: %3d @ %3d  ", AxisPos[ 0 ], AxisSpeed[0]);
		nxtDisplayString(4, "E: %3d @ %3d  ", AxisPos[ 1 ], AxisSpeed[ 1 ]);
		//nxtDisplayString(5, "W: %5d   ", fWristPosDeg);
		//nxtDisplayString(6, "SW: %5d   ", fSwivelPosDeg);
		nxtDisplayString(7, "Stalled? %1d %1d", Stalled[0], Stalled[1]);
	}
}


void Executor( void )
{
	// int JoyButtons;
	getJoystickSettings(joystick);     // update buttons and joysticks


	// See if Joy1 is overriding
	if (joy1Btn(8) == 1)
	{
		Joy1Drive = true;
		Joy1HiGear = false;
	}
	else if (joy1Btn(6) == 1)
	{
		Joy1Drive = true;
		Joy1HiGear = true;
	}
	else
		Joy1Drive = false;

	// Look for Joy2 Gear Shift
	if (joy2Btn(6)) Joy2HiGear = true;
	if (joy2Btn(8))Joy2HiGear = false;

	Every50mS();
	Drive();

	// Encoder is 360 lines, X 4 because of quadrature.
	// Shoulder gear ratio is 12:1.
	// So, to get degrees, divide by (12 * 4) = 48
	//
	EncRead[ 0 ] =  nMotorEncoder[Shoulder];
	RelAxisPos[ 0 ] = EncRead[ 0 ] / 48;
	AxisPos[ 0 ] = RelAxisPos[ 0 ] +  SHOULDER_HOME -  HomeAxisRead[0];


	// Elbow Gear ratio is 6 : 1
	// So to get degrees, divide by (6 * 4) = 24
	EncRead[ 1 ] = nMotorEncoder[Elbow];
	RelAxisPos[ 1 ] = EncRead[ 1 ] / 24;
	AxisPos[ 1 ] = RelAxisPos[ 1 ] + ELBOW_HOME -  HomeAxisRead[1];

}
