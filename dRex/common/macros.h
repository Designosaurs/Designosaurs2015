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


void moveLift( float to_height ){
	int LiftPower = 30;


	if (lift_inches < to_height ) {
		// Move up to reach height.
		while( lift_inches < to_height ) {
			// Slow down when we get close-- but only if the lift is already
			// a ways up.
			if (( lift_inches > (to_height - 1)) && (lift_inches > 13)) LiftPower = 10;
			motor[ lift ] = LiftPower;
			if (stopMacro()) break;
			wait1Msec( 20 );
		}
		} else {
		// Starting from above-- move down to reach height.
		while( lift_inches > to_height ) {
			motor[ lift ] = -30;
			if (stopMacro()) break;
			wait1Msec( 20 );
		}
	}
	motor[lift] = 0;
}

///////////////////////////////////////////////////////////////////////////////////
void untuck() {
	waitForHarvester();
	servoChangeRate[ elbow ] = 2;
	servoChangeRate[ wrist ] = 2;

	// Cup centered between harvester
	servo[wrist] = 90;  // cup level
	wait1Msec( 100 );
	servo[elbow] = 217;
	wait1Msec( 100 );
	debugStep();

	// Tilt cup slightly up.
	//servo[elbow] = 217;
	//servo[wrist] = 90;
	//wait1Msec( 100 );
	//debugStep();


	// Raise a bit.  Elbow slightly back to compensate
	servo[elbow] = 217;
	servo[wrist] = 90;
	moveLift( 5.4);
	motor[lift] = 0;
	debugStep();


	// up, servo back to keep from hitting harvester
	servo[elbow] = 247;
	servo[wrist] = 90;
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

//////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////
void liftToHighGoal() {
	if (LiftPos == 0) untuck();
	moveLift( 19.1);
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
	if (LiftPos == 0) untuck();
	else {
		servo[elbow] = 120;
	servo[wrist] = 204;
	updateServoPos( );

}

	moveLift( 29.4);
	debugStep();

	servoChangeRate[ elbow ] = 5;
	servoChangeRate[ wrist ] = 5;
	//servo[elbow] = 137;
	//servo[wrist] = 194;
	//wait1Msec( 300 );
	//debugStep();

	//  Smaller elbow number means more toward the goal
	servo[elbow] = 105;
	servo[wrist] = 204;
	updateServoPos( );
	debugStep();
	LiftPos = 2;
}

void liftPlace() {
	servoChangeRate[ wrist ] = 5;
	servo[wrist] = 125;
}


/////////////////////////////////////////////////////////////////////////
void TossToCenterGoal() {
	if (LiftPos == 0) untuck();
	else {
		servo[elbow] = 120;
	servo[wrist] = 204;
	updateServoPos( );
	}

	moveLift( 28);  // Was 29.4
	debugStep();

	servoChangeRate[ elbow ] = 10;
	servoChangeRate[ wrist ] = 10;

	//  Smaller elbow number means more toward the goal
	servo[elbow] = 110;		// 105 would be slightly toward the goal.  This is intended to be about vertical.
	servo[wrist] = 150;   // Placing is 125 (down) This is intended to be about cup horizontal.
	updateServoPos( );
	debugStep();
	LiftPos = 2;
	wait1Msec( 800 );
	servo[elbow] = 170;		// 105 would be slightly toward the goal.  This is intended to be about vertical.
	wait1Msec( 800 );

}
