/*
|----\
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/
///////////////////////////  CHECK JOYSTICK FOR MACRO REQUESTS ////////////////////////////////
// Check to see if the user has requested a new state.  If not, return UNDEFINED
// Used by DoMacros

TypeArmState CheckMacroRequest() {
	if (joy1Btn(4) == 1) return PLACE_HIGH;
	if (joy1Btn(2) == 1) return PLACE_MID;
	if (joy1Btn(3) == 1) return PLACE_LOW;
	if (joy1Btn(1) == 1) return GET_BLOCKS;
	if (joystick.joy1_TopHat == 7) return QUICK_HOME;

	/*
	if(joystick.joy1_TopHat == 0) return TRAVEL_PLACE;
	// Appears to be stuck reading at 0, commenting out for now.
	if(joystick.joy1_TopHat == 2) return STRAIGHT_UP;
	if(joystick.joy1_TopHat == 4) return TRAVEL_GET;
	if(joystick.joy1_TopHat == 6)	return QUICK_HOME;
	if(joystick.joy1_TopHat == 8)	return QUICK_HOME;
	*/
	// if all else fails, or if nothing's pressed
	return UNDEFINED;
}

void DoMacros() {
	ReqArmState = CheckMacroRequest();
	switch(ReqArmState) {
		case PLACE_LOW:
			actionPlaceLow();
		break;
		case PLACE_MID:
			actionPlaceMid();
		break;
		case PLACE_HIGH:
			actionPlaceHigh();
		break;
	case GET_BLOCKS:
			actionGetBlocks();
		break;
		case TRAVEL_PLACE:
			actionTravelPlace();
		break;
		case TRAVEL_GET:
			actionTravelGet();
		break;
		case STRAIGHT_UP:
			actionStraightUp();
		break;
		case QUICK_HOME:
			servo[RClaw] = RCLAW_CLOSED;
			servo[LClaw] = LCLAW_CLOSED;
			actionHome();
		break;
		case UNDEFINED:
			// do nothing
		break;
		default:
			//crashwitherr("Unknown armstate");
	}
}
