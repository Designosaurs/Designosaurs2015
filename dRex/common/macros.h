// Macro all happen as part of the Gunner Controller Task.

//void harvesterTo(int target_in_degrees) {
//	until(nMotorEncoder[harvester] % 1440 < ((target_in_degrees * 16) + 20)) {
//		motor[harvester] = 8;
//	}
//	until(nMotorEncoder[harvester] % 1440 > ((target_in_degrees * 16) - 20)) {
//		motor[harvester] = -8;
//	}
//	motor[harvester] = 0;
//}


void waitForHarvester(){
	if (run_harvester) {
		run_harvester = false;
		wait1Msec( 1000 );

}

}

bool stopMacro( void ) {
	bool rtnValue = joy2Btn(09);
	if (rtnValue) motor[ lift ] = 0;
	return 	rtnValue;
}

void debugStep() {
	return;
	PlaySound(soundBlip);
	//return;
	// wait for button pressed
	while( !joy2Btn( 07 ))		wait1Msec( 50 );

	// wait for button released
	while( joy2Btn( 07)) wait1Msec( 50 );

}


// Note that this does not stop at the end!
void moveLift( float to_height ){
	if (lift_inches < to_height ) {
		while( lift_inches < to_height ) {
			motor[ lift ] = 30;
			if (stopMacro()) break;
			wait1Msec( 20 );
		}
		} else {
		while( lift_inches > to_height ) {
			motor[ lift ] = -10;
			if (stopMacro()) break;
			wait1Msec( 20 );
		}
	}
	motor[lift] = 0;
}

void untuck() {
	waitForHarvester();
	//harvesterTo(20);
	servoChangeRate[ elbow ] = 2;
	servoChangeRate[ wrist ] = 2;

	// Tuck position 0
	servo[elbow] = 245;
	servo[wrist] = 120;
	wait1Msec( 100 );
	debugStep();

	// Center wrist servo between harvester and bar, slightly tilt cup 1
	servo[elbow] = 240;
	servo[wrist] = 107;
	wait1Msec( 100 );
	debugStep();

	// Raise just alittle
	moveLift( 3.3 );
	motor[lift] = 0;
	debugStep();

	// Up and wrsit servo back 3
	servo[elbow] = 245;
	servo[wrist] = 107;
	moveLift( 5.4);
	motor[lift] = 0;
	debugStep();


	// up, servo back to keep from hitting harvester
	servo[elbow] = 255;
	servo[wrist] = 84;
	moveLift( 7.22 );
	motor[lift] = 0;
	debugStep();

	// Clear
	servo[elbow] = 255;
	servo[wrist] = 84;
	moveLift( 11.5 );
	motor[lift] = 0;
	debugStep();
}


void tuck() {
	waitForHarvester();
	//harvesterTo(-20);
	servoChangeRate[ elbow ] = 1;
	servoChangeRate[ wrist ] = 1;
	// start from 4
	servo[elbow] = 255;
	servo[wrist] = 120;
	moveLift( 5.55 );
	motor[lift] = 0;
	debugStep();

	servo[elbow] = 243;
	servo[wrist] = 120;
	moveLift( 3.3 );
	motor[lift] = 0;
	debugStep();

	servo[elbow] = 235;
	servo[wrist] = 120;
	moveLift( 0.5 );  // move to close to home.
	motor[lift] = -5;	// power lightly down
	wait1Msec( 400 ); // for a little time.
	motor[lift] = 0;	// now motor off.
	nMotorEncoder[lift] = 0; // This is our new zero
	debugStep();

	// tilt cup back and wedge it back
	servo[elbow] = 245;
	servo[wrist] = 80;
	wait1Msec( 200 );
	debugStep();

	// Now level the up-- uses back of cup to lock in place
	servo[wrist] = 120;
	debugStep();

}

//void liftUntuck() {

//}

void liftToFloor() {
	servoChangeRate[ elbow ] = 10;
	servoChangeRate[ wrist ] = 10;
	servo[elbow] = 255;
	servo[wrist] = 84;
	moveLift( 13 );
	debugStep();

	tuck();
}

void liftToHighGoal() {
	untuck();
	moveLift( 16.3);
	debugStep();

	servoChangeRate[ elbow ] = 5;
	servoChangeRate[ wrist ] = 5;
	servo[elbow] = 137;
	servo[wrist] = 194;
	wait1Msec( 300 );
	debugStep();

	servo[elbow] = 0;
	servo[wrist] = 255;
	debugStep();
}

void liftToCenterGoal() {
	untuck();
	moveLift( 26.55 );
	debugStep();

	servoChangeRate[ elbow ] = 5;
	servoChangeRate[ wrist ] = 5;
	//servo[elbow] = 137;
	//servo[wrist] = 194;
	//wait1Msec( 300 );
	//debugStep();

	servo[elbow] = 129;
	servo[wrist] = 204;
	debugStep();
}

void liftPlace() {
	servoChangeRate[ wrist ] = 5;
	servo[wrist] = 96;
}
