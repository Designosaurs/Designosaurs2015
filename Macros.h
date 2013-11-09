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
	servo [LClaw] = LCLAW_OPEN;
	servo [RClaw] = RCLAW_OPEN;
	PlaySound(soundBlip);
	ArmState = GET_BLOCKS;
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
	MoveTwoAxes(PLACE_BLOCKS_LOW_SHOUDLER,PLACE_BLOCKS_LOW_ELBOW);
	MoveTwoAxes(PLACE_BLOCKS_LOW_SHOUDLER,PLACE_BLOCKS_LOW_ELBOW);
	//wait10Msec(90);
	//servo [LClaw] = LCLAW_OPEN;
	//servo [RClaw] = RCLAW_OPEN;
	//wait10Msec(90);
	//actionGetBlocks();
	if (Beeps) PlaySound(soundBlip);
	ArmState = PLACE_LOW;
}

void actionPlaceMid() {
	MoveTwoAxes(PLACE_BLOCKS_MID_SHOUDLER,PLACE_BLOCKS_MID_ELBOW);
	MoveTwoAxes(PLACE_BLOCKS_MID_SHOUDLER,PLACE_BLOCKS_MID_ELBOW);
	//wait10Msec(90);
	//servo [LClaw] = LCLAW_OPEN;
	//servo [RClaw] = RCLAW_OPEN;
	//wait10Msec(90);
	//actionGetBlocks();
	if (Beeps) PlaySound(soundBlip);
	ArmState = PLACE_MID;
}

void actionPlaceHigh() {
	MoveTwoAxes(PLACE_BLOCKS_HIGH_SHOUDLER,PLACE_BLOCKS_HIGH_ELBOW);
	MoveTwoAxes(PLACE_BLOCKS_HIGH_SHOUDLER,PLACE_BLOCKS_HIGH_ELBOW);
	//wait10Msec(90);
	//servo [LClaw] = LCLAW_OPEN;
	//servo [RClaw] = RCLAW_OPEN;
	//wait10Msec(90);
	//actionGetBlocks();
	if (Beeps) PlaySound(soundBlip);
	ArmState = PLACE_HIGH;
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
