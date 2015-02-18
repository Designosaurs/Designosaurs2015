// Show each of the sensor readings.
// IR Seeker outputs

#define HAS_IR
int acS1, acS2, acS3, acS4, acS5 = 0;
int Center6 = 0;  // Aim with respect to the center of direction 6.  Positive means to the right.

void GetIR(void) {
	// read the current modulated signal direction
	dirAC = HTIRS2readACDir(HTIRS2);

	// Read the individual signal strengths of the internal sensors
	HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 );

	PeakIR = acS1;
	if (acS2 > PeakIR) PeakIR = acS2;
	if (acS3 > PeakIR) PeakIR = acS3;
	if (acS4 > PeakIR) PeakIR = acS4;
	if (acS5 > PeakIR) PeakIR = acS5;

	// Compute Center6 -- a value that will be zero when running straight down the middle,
	// Positive when slightly to the right.
	// Limited to +/- 10
	Center6 = acS4 - acS3;
	if (Center6 > 10) Center6 = 10;
	if (Center6 < -10) Center6 = -10;


}

int Sign( int InVal) {
	if (InVal >= 0) return 1;
	else return -1;
}

////////////////////////////////////////////////////////////////
// Points to direction 6 of the IR sensor.
// The zones are of uneven widths, and direction 6 is one of the narrow ones.
// The center of direction 6 is about 30 degrees to the right of straight.
// So, in most applications the sensor will NOT be pointed straight at the target.
// This function will pivot the robot until it points to the center of zone 6.
// It will return true if it suceeds, false if it fails.
// Must have PID control, because it puts very low speed values to the motors.

bool PointToIR( void ) {
	int PivotSpeed = 0;
	int initialSign = 0;
	int numTrys = 0;

	GetIR();
	if (PeakIR < 60) return false;
	initialSign = Sign( Center6 );

	while( true ){
		GetIR();
		PivotSpeed = Center6;
		motor[right_drive] = -PivotSpeed;
		motor[left_drive] = PivotSpeed;

		// End when it is sraight on or just crosses sign.
		if ((Sign( Center6) != initialSign)||( Center6 == 0)) {
			motor[right_drive] = 0;
			motor[left_drive] = 0;
			return true;
		}

		if (PeakIR < 60) {
			motor[right_drive] = 0;
			motor[left_drive] = 0;
			return false;
		}
		if (numTrys++ > 100) return false;

		wait10Msec( 10 );
	}
}

// Before calling this, point to the IR beacon.
// This will drive slowly, maintaining pointing at the IR beacon,
// until it is within the passed range.
// Return false if fail.
bool FollowIRtoRange( int range ) {
	int numTrys = 0;

	while(SensorValue[ultrasonic] > range) {
		GetIR();
		if ((PeakIR < 50)|| (numTrys > 500)) {
			motor[right_drive] = 0;
			motor[left_drive] = 0;
			return false;
		}
		motor[left_drive] = 30 + Center6;
		motor[right_drive] = 30 - Center6;
		wait1Msec(20);
		numTrys++;
	}

	motor[right_drive] = 0;
	motor[left_drive] = 0;
	return true;
}
