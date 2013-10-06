/*
|----\             
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/

// Wait Tenths
// Wait with checking the exectutor, so drive routines still work.
void WaitTenths( int TenthsToWait )
{
	long valTime2= 0;
	ClearTimer(T2);
	while( valTime2 < TenthsToWait * 100)
	{
		Executor();
		valTime2 = time1[T2];
	}
}

////////// MOVEMENT GROUPS ///////////////////////////
//////////////////////  GOALS ///////////////////////////////////
void ToFront3( void )
{
	MoveSwivel( 0 );
	MoveWrist( 90 );
	MoveTwoAxes(  FRONT3_SHOULDER, FRONT3_ELBOW);
	PlaySound(soundBlip);
	MoveTwoAxes(  FRONT3_SHOULDER, FRONT3_ELBOW);
	MoveWrist( FRONT3_WRIST);
	if (Beeps) PlaySound(soundBlip);
	ArmState = FRONT3 ;
	VectorJoy = false;
}

void ToFront2( void )
{
	MoveSwivel( 0 );
	MoveWrist( 90 );
	MoveTwoAxes(  FRONT2_SHOULDER, FRONT2_ELBOW);
	PlaySound(soundBlip);
	MoveTwoAxes(  FRONT2_SHOULDER, FRONT2_ELBOW);
	MoveWrist( FRONT2_WRIST);
	if (Beeps) PlaySound(soundBlip);
	ArmState = FRONT2 ;
	VectorJoy = true;
}

void ToFront1( void )
{
	MoveSwivel( 0 );
	MoveWrist( 90 );
	MoveTwoAxes(  FRONT1_SHOULDER, FRONT1_ELBOW);
	PlaySound(soundBlip);
	MoveTwoAxes(  FRONT1_SHOULDER, FRONT1_ELBOW);
	MoveWrist( FRONT1_WRIST);
	if (Beeps) PlaySound(soundBlip);
	ArmState = FRONT1 ;
	VectorJoy = true;
}


void PlaceGoal( void )
{
	// Wirst down a bit:
	MoveWrist( (int) fWristPosDeg -12);
	WaitTenths( 3 );
	servo[Claw] = CLAW_OPEN;
	WaitTenths( 3 );
	// Now get clear of the goal:
	motor[Shoulder] =  -20;
	WaitTenths( 4 );
	StopArm();
	if (Beeps) PlaySound(soundBlip);
}


//////////////  TRAVEL / HOME //////////////////////////////////////////

void ToTravel( void )
{
	MoveWrist(TRAVEL_WRIST);
	MoveSwivel( 0 );
	MoveTwoAxes(  TRAVEL_SHOULDER, TRAVEL_ELBOW);
	if (Beeps) PlaySound(soundBlip);
	ArmState = TRAVEL;
	VectorJoy = false;
}

void ToStraightUp( void )
{
	MoveSwivel( 0 );
	MoveWrist( 45 );
	MoveTwoAxes(  0, 0);
	MoveTwoAxes(  0, 0);
	if (Beeps) PlaySound(soundBlip);
	MoveWrist(0);
	ArmState = STRAIGHT_UP;
	VectorJoy = false;
}

void GoHomeQuick( void )
{
	servo[Claw] = CLAW_CLOSED;
	MoveWrist( 56 );
	WaitTenths( 2 );
	MoveWrist( WRIST_HOME  );
	WaitTenths( 2 );
	MoveSwivel( SWIVEL_HOME );
	MoveOneAxis( ELBOW_HOME - 10, ELBOW, MAX_POWER);
	MoveOneAxis( SHOULDER_HOME + 10, SHOULDER, MAX_POWER);
	HomeArm();
}


// We used timed things, just in case home has not been established.
void LeaveHome( void )
{
	if (Beeps) PlaySound(soundBlip);
	motor[Shoulder] =  20;
	motor[Elbow] = -20;
	MoveWrist( 0 );
	WaitTenths( 6 );
	fWristSpeed = 0;
	StopArm();
	MoveSwivel( 0 );
	if (Beeps) PlaySound(soundBlip);
	// wait10Msec( 1000 );
}

////////////////////  RING RETRIEVAL ///////////////////////////////////////////////
void ToFrontFloor( void )
{

	MoveSwivel( 0 );
	servo[Claw] = CLAW_OPEN;
	MoveWrist( 70 );
	// First get a little above the floor
	MoveTwoAxes(  FRONT_FLOOR_SHOULDER + 5, FRONT_FLOOR_ELBOW);
	MoveTwoAxes(  FRONT_FLOOR_SHOULDER + 5, FRONT_FLOOR_ELBOW);
	MoveWrist( FRONT_FLOOR_WRIST);
	if (Beeps) PlaySound(soundBlip);
	// Now bring the shoulder down
	MoveOneAxis( FRONT_FLOOR_SHOULDER, SHOULDER, MAX_POWER);
	MoveOneAxis( FRONT_FLOOR_SHOULDER, SHOULDER, MAX_POWER);
	PlaySound(soundBlip);
	ArmState = FRONT_FLOOR ;
	VectorJoy = true;
}


void RingFromFloor( void )
{
	// Move the shoulder down slightly.
	//MoveOneAxis( FRONT_FLOOR_SHOULDER - 5, SHOULDER, MAX_POWER);
	motor[Shoulder] =  -20;
	WaitTenths( 8 );


	if (Beeps) PlaySound(soundBlip);

	// Test code to see if we went down right amount.
	// StopArm();
	// PlaySound(soundFastUpwardTones);
	// WaitTenths(100);



	// Move the elbow out, wrist down, while closing the claw.
	motor[Shoulder] =  0;
	motor[Elbow] = 10;
	servoChangeRate[Claw] = 4;
	servo[Claw]= CLAW_CLOSED;
	fWristSpeed = -1;
	WaitTenths( 10 );
	fWristSpeed = 0;
	StopArm();
	if (Beeps) PlaySound(soundBlip);

	// Move the shoulder up to get it so it does not drag on the floor.
	fWristSpeed = 2;
	MoveOneAxis( FRONT_FLOOR_SHOULDER, SHOULDER, MAX_POWER);
	fWristSpeed = 0;
}


void ToRingDisp( void )
{
	MoveSwivel( 0 );
	//MoveWrist( 45 );
	MoveWrist( RINGDISP_WRIST);
	// MoveSwivel( RINGDISP_SWIVEL );
	servo[Claw] = CLAW_OPEN;
	MoveTwoAxes(  RINGDISP_SHOULDER, RINGDISP_ELBOW);
	ArmState = RINGDISP ;
	VectorJoy = true;
}

// Grab from Ring Dispenser.
// Operator can keep button closed to extend this.
void RingFromDispenser( void )
{
	servo[Claw] = CLAW_CLOSED;
	WaitTenths( 3 );
	if (Beeps) PlaySound(soundBlip);
	motor[Shoulder] =  20;
	motor[Elbow] = -30;
	fWristSpeed = 1;
	WaitTenths( 4 );
	fWristSpeed = 0;
	StopArm();
	if (Beeps) PlaySound(soundBlip);
}


void ToRingSpiller( void )
{
	MoveSwivel( 0 );
	servo[Claw] = CLAW_CLOSED;
	if (Beeps) PlaySound(soundBlip);
	MoveWrist( 45);
	servo[Claw] = CLAW_CLOSED;
	MoveTwoAxes(  RINGSPILL_SHOULDER +5, RINGSPILL_ELBOW + 60);
	if (Beeps) PlaySound(soundBlip);
	MoveWrist( 0 );
	WaitTenths( 5 );
	MoveSwivel( -88 );
	WaitTenths( 5 );
	MoveWrist( 79 );
	MoveTwoAxes(  RINGSPILL_SHOULDER + 5, RINGSPILL_ELBOW);
	MoveTwoAxes(  RINGSPILL_SHOULDER, RINGSPILL_ELBOW);


	//MoveSwivel( RINGSPILL_SWIVEL );
	ArmState = RINGSPILL ;
	VectorJoy = true;
}


void SpillRings( void )
{
	long valTime2= 0;

	// First down a little
	motor[Elbow] = -20;
	if (Beeps) PlaySound(soundBlip);
	WaitTenths( 8 );

	// Test code to see if we went down right amount.
	// StopArm();
	// PlaySound(soundFastUpwardTones);
	// WaitTenths(100);

	// Now, slide rings as longs as blue button pressed:
	valTime2= 0;
	motor[Elbow] = -20;
	motor[Shoulder] =  16;
	ClearTimer(T2);
	while ( valTime2 < 200)
	{
		Executor();
		valTime2 = time1[T2];
		if (joy1Btn(1) == 1) 	ClearTimer(T2);
	}
	StopArm();
	if (Beeps) PlaySound(soundBlip);
}

void LeaveRingSpill( void )
{
	MoveWrist( 0 );
	WaitTenths( 5 );
	MoveSwivel( 0 );
	WaitTenths( 5 );
}
