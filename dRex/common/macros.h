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
	servoChangeRate[ elbow ] = 2;
	servoChangeRate[ wrist ] = 2;

	// Cup centered between harvester
	servo[elbow] = 217;
	servo[wrist] = 120;  // cup level
	wait1Msec( 100 );
	debugStep();

	// Tilt cup slightly up.
	servo[elbow] = 217;
	servo[wrist] = 107;
	wait1Msec( 100 );
	debugStep();


	// Raise a bit.  Elbow slightly back to compensate
	servo[elbow] = 235;
	servo[wrist] = 107;
	moveLift( 5.4);
	motor[lift] = 0;
	debugStep();


	// up, servo back to keep from hitting harvester
	servo[elbow] = 247;
	servo[wrist] = 100;
	moveLift( 8.8 );
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

	// This is to just inside the tines of the harvester
		servo[elbow] = 245;
	servo[wrist] = 120;
	moveLift( 9.55 );
	motor[lift] = 0;
	debugStep();
	//PlaySound(soundDownwardTones);


	// Into the harvester
	servo[elbow] = 250;
	servo[wrist] = 120;
	moveLift( 5.55 );
	motor[lift] = 0;
	debugStep();
	//PlaySound(soundFastUpwardTones);

	// into the pocket, elbow slightly forward
	servo[elbow] = 220;
	servo[wrist] = 120;
	moveLift( 3.3 );
	motor[lift] = 0;
	debugStep();

	// Cup centered between harvester, lcok it down.
	servo[elbow] = 217;
	servo[wrist] = 120;  // cup level
	wait1Msec( 100 );
	debugStep();
	moveLift( 0.5 );  // move to close to home.
	motor[lift] = -5;	// power lightly down
	wait1Msec( 400 ); // for a little time.
	while( 	!liftStopped ) {  // Now, keep going until stopped
		PlaySound(soundBlip );
		wait1Msec( 10 );

	}
	motor[lift] = 0;	// now motor off.
	nMotorEncoder[lift] = 0; // This is our new zero
	debugStep();

	// Now move the cup back slightly.
	servo[elbow] = 233;
	servo[wrist] = 120;
	updateServoPos( );
	wait1Msec( 200 );
	debugStep();

	// Now level the up-- uses back of cup to lock in place
	servo[wrist] = 120;
	updateServoPos( );
	debugStep();
}

void liftToFloor() {
	servoChangeRate[ elbow ] = 10;
	servoChangeRate[ wrist ] = 10;
	servo[elbow] = 255;
	servo[wrist] = 84;
	wait1Msec( 300 ); // give the servos a head start.
	moveLift( 13 );
	debugStep();

	tuck();
	LiftPos = 0;
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

	servo[elbow] = 40;
	servo[wrist] = 255;
	wait1Msec( 300 );
	// Slow for the last approach.
	servoChangeRate[ elbow ] = 2;
	servo[elbow] = 0;

	updateServoPos( );
	debugStep();
	LiftPos = 1;
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

	servo[elbow] = 120;
	servo[wrist] = 204;
	updateServoPos( );
	debugStep();
	LiftPos = 2;
}

void liftPlace() {
	servoChangeRate[ wrist ] = 5;
	servo[wrist] = 96;
}
