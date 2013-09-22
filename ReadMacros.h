/*
|----\             
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/
///////////////////////////  CHECK JOYSTICK FOR MACRO REQUESTS ////////////////////////////////
// Check to see if the user has requested a new state.  If not, return UNDEFINED
// Used by DoMacros

	TypeArmState CheckMacroRequest( void )
{
	if (joy1Btn(2) == 1) return FRONT1;
	if (joy1Btn(3) == 1) return FRONT2;
	if (joy1Btn(4) == 1) return FRONT3;

	if(joystick.joy1_TopHat == 0)		return TRAVEL;
	if(joystick.joy1_TopHat == 1)		return STRAIGHT_UP;
	if(joystick.joy1_TopHat == 2) return RINGSPILL;
	if(joystick.joy1_TopHat == 3) return RINGDISP;
	if(joystick.joy1_TopHat == 4) return FRONT_FLOOR;
	if(joystick.joy1_TopHat == 5) return QUICK_HOME;
	if(joystick.joy1_TopHat == 6)			// manual mode
	{
		VectorJoy = false;
		return UNDEFINED;
	}
	if(joystick.joy1_TopHat == 7) return HOME;

	// if all else fails, or if nothing's pressed
	return UNDEFINED;

}



////////////////////////////////  MAIN CONTROL -- DO MACROS /////////////////////////////////
void DoMacros( void )
{
	ReqArmState = CheckMacroRequest();

	// Check for Ring Grab from floor.
	if ((ArmState == FRONT_FLOOR) && (joy1Btn(1) == 1))
		RingFromFloor();

	// Check for Ring Grab from dispenser.
	if ((ArmState == RINGDISP) && (joy1Btn(1) == 1))
		RingFromDispenser();

	// Check for goal placer:
	if ((ArmState == FRONT1) || (ArmState == FRONT2) || (ArmState == FRONT3))
	{
		if(joy1Btn(1) == 1)
		{
			PlaceGoal();

		}
	}

	// Check spill rings
	if ((ArmState == RINGSPILL) && (joy1Btn(1) == 1))
		SpillRings();

	if (ReqArmState != UNDEFINED)
	{
		// If hand is on the floor, and another macro is requested
		// raise it before we do anything else.
		// if (ArmState == FRONT_FLOOR)
		// {
		//	MoveOneAxis( -60, SHOULDER, MAX_POWER);	// Elbow in for travel
		//	if (Beeps) PlaySound(soundBlip);
		//}
		// If we are home and another macro is requested, exit carefully.
		if (ArmState == HOME) LeaveHome();

		if (ArmState == RINGSPILL) LeaveRingSpill();


		if (ReqArmState == FRONT3) ToFront3();
		if (ReqArmState == FRONT2) ToFront2();
		if (ReqArmState == FRONT1) ToFront1();
		if (ReqArmState == FRONT_FLOOR) ToFrontFloor();

		if (ReqArmState == RINGSPILL) ToRingSpiller();
		if (ReqArmState == RINGDISP) ToRingDisp();
		if (ReqArmState == TRAVEL) ToTravel();
		if (ReqArmState == STRAIGHT_UP) ToStraightUp();
		if (ReqArmState == HOME) HomeArm();
		if (ReqArmState == QUICK_HOME) GoHomeQuick();
	}

}
