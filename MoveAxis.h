/*
|----\
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/

//  MOVE FUNCTIONS

void StopArm() {
	motor[Elbow] = 0;
	motor[Shoulder] = 0;
}

// Time-out if we cannot get there in 10 seconds.

#define MOVE_TIMEOUT (5000 + (100 / MAX_POWER) * 2000)

void MoveOneAxis(int Dest, TAxisN AxisN, int Power) {
	int pwr;
	long valTime2;
	ClearTimer(T2);

	tMotor AxisToMove = AxisMotors[ AxisN ];
	Executor();

	if(AxisPos[AxisN] < Dest) {
		while(AxisPos[ AxisN ] < Dest) {
			Executor();
			pwr = Power * AxisSigns[ AxisN ];
			motor[ AxisToMove ] = pwr ;
			valTime2 = time1[T2];
			if(valTime2 > MOVE_TIMEOUT) {
				StopArm();
				PlaySound(soundLowBuzz);
				MoveTimedout = true;
				return;
			}
			if(joystick.joy1_Buttons == ){ // stop macros
				StopArm();
				return;
			}
		}
	} else {
		while(AxisPos[AxisN] > Dest) {
			Executor();
			motor[ AxisToMove ] = -Power * AxisSigns[ AxisN ];
			valTime2 = time1[T2];
			if(valTime2 > MOVE_TIMEOUT) {
				StopArm();
				//logMsg("Movement timed out.");
				PlaySound(soundLowBuzz);
				MoveTimedout = true;
				return;
			}
			if(joystick.joy1_TopHat == 6) {
				StopArm();
				return;
			}
		}
	}
	// Now stop the motor:
	motor[AxisToMove] = 0;
	return;
}



////////////////   MOVE TWO AXIS SIMULTANEOUSLY ////////////////
//  This defines how close we get to position before we slow down.
// So, if we are at pwr 40, slow down at 5 degrees
#define CLOSE_TO_POSITION (MAX_POWER / 8)

void MoveTwoAxes(int ShoulderDest, int ElbowDest) {
	int ShoulderPower;
	bool ShoulderMoveDir = 0;
	bool ShoulderInPos = 0;

	int ElbowPower;
	bool ElbowMoveDir = 0;
	bool ElbowInPos = 0;
	long valTime2;
	ClearTimer(T2);


	// SHOULDER: Figure out the sign of the move, and set the motor power.
	ShoulderPower = MAX_POWER;
	if(ShoulderDest > AxisPos[SHOULDER]) {
		ShoulderMoveDir = true; // Positive direct move
	} else {
		ShoulderPower *= -1;
		ShoulderMoveDir = false;
	}
	// And start the motor moving.
	motor[Shoulder] = ShoulderPower;

	// ELBOW: Figure out the sign of the move, and set the motor power.
	ElbowPower =  MAX_POWER;
	if (ElbowDest > AxisPos[ELBOW]) {
		ElbowMoveDir = true;  // POSITIVE DIRECTION ELBOW MOVE
	} else {
		ElbowMoveDir = false;
		ElbowPower *= -1;
	}
	motor[Elbow]= ElbowPower;

	// Now run as long as either Shoulder or Elbow is not yet in position.
	while(!ShoulderInPos || !ElbowInPos) {
		Executor();

		// SHOULDER:
		// If not already in posistion, look to see if it has crossed
		// the destination.
		if(!ShoulderInPos) {
			// If it is close, cut the power.
			if(abs(ShoulderDest - AxisPos[SHOULDER]) < CLOSE_TO_POSITION) {
				motor[Shoulder] = ShoulderPower / 2;
			}
			if(ShoulderMoveDir) {
				if(ShoulderDest < AxisPos[SHOULDER]) {
					motor[ Shoulder ] = 0;
					ShoulderInPos = true;
				}
			} else {
				if(ShoulderDest > AxisPos[SHOULDER]) {
					motor[ Shoulder ] = 0;
					ShoulderInPos = true;
				}
			}
		}

		// Elbow:
		// If not already in posistion, look to see if it has crossed
		// the destination.
		if(!ElbowInPos) {
			// If it is close, cut the power.
			if(abs(ElbowDest - AxisPos[ELBOW]) < CLOSE_TO_POSITION) {
				motor[Elbow] = ElbowPower / 2;
			}
			if(ElbowMoveDir) {
				if(ElbowDest < AxisPos[ELBOW]) {
					motor[Elbow] = 0;
					ElbowInPos = true;
				}
			} else {
				if(ElbowDest > AxisPos[ ELBOW ]) {
					motor[Elbow] = 0;
					ElbowInPos = true;
				}
			}
		}
		// Detect Move Time-Out
		valTime2 = time1[T2];
		if(valTime2 > MOVE_TIMEOUT) {
			StopArm();
			//logMsg("Movement timed out.");
			PlaySound(soundLowBuzz);
			MoveTimedout = true;
			return;
		}
	}
	return;
}
