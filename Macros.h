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

void actionGetBlocks()
{
	// First get a little above the floor
	MoveTwoAxes(GET_BLOCKS_SHOULDER+5, GET_BLOCKS_ELBOW);
	MoveTwoAxes(GET_BLOCKS_SHOULDER+5, GET_BLOCKS_ELBOW);
	if (Beeps) PlaySound(soundBlip);
	// Now bring the shoulder down
	MoveOneAxis(GET_BLOCKS_SHOULDER, SHOULDER, MAX_POWER);
	MoveOneAxis(GET_BLOCKS_SHOULDER, SHOULDER, MAX_POWER);
	PlaySound(soundBlip);
	ArmState = GET_BLOCKS;
	VectorJoy = true;
}

void actionStraightUp() {
	MoveTwoAxes(0,0);
	MoveTwoAxes(0,0);
	if (Beeps) PlaySound(soundBlip);
}

void actionHome() {
	HomeArm();
}

void actionPlaceLow() {
}

void actionPlaceMid() {
}

void actionPlaceHigh() {
}
//////////////  TRAVEL / HOME //////////////////////////////////////////
void actionTravelGet() {
	MoveTwoAxes(0,0);
	MoveTwoAxes(0,0);
	if (Beeps) PlaySound(soundBlip);
}

void actionTravelPlace() {
	MoveTwoAxes(0,0);
	MoveTwoAxes(0,0);
	if (Beeps) PlaySound(soundBlip);
}

void GoHomeQuick( void )
{
	servo[Claw] = CLAW_CLOSED;
	WaitTenths( 2 );
	WaitTenths( 2 );
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
	WaitTenths( 6 );
	fWristSpeed = 0;
	StopArm();
	if (Beeps) PlaySound(soundBlip);
	// wait10Msec( 1000 );
}
