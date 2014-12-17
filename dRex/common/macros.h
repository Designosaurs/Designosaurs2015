// Macro all happen as part of the Gunner Controller Task.

bool stopMacro( void ) {
	bool rtnValue = joy2Btn(09);
	return 	rtnValue;
}

void debugStep() {
	PlaySound(soundBlip);
	return;
	// wait for button released
	while( joy2Btn( 07)) {
		wait1Msec( 50 );
	}
	// wait for button pressed
	while( !joy2Btn( 07 )){
		wait1Msec( 50 );
	}

	wait10Msec( 100 );
}


// Note that this does not stop at the end!
void moveLift( float to_height ){
	if (lift_inches < to_height ) {
		while( lift_inches < to_height ) {
			running_macro = true;
			motor[ lift ] = 10;
			if (stopMacro()) break;
			wait1Msec( 20 );
		}
		} else {
		while( lift_inches > to_height ) {
			running_macro = true;
			motor[ lift ] = -5;
			if (stopMacro()) break;
			wait1Msec( 20 );
		}
	}
	running_macro = false;
}

void untuck() {
	servoChangeRate[ elbow ] = 1;
	servoChangeRate[ wrist ] = 1;

	// Tuck position 0
	servo[elbow] = 240;
	servo[wrist] = 120;
	wait1Msec( 1000 );
	debugStep();

	// Center wrist servo between harvester and bar, slightly tilt cup 1
	servo[elbow] = 235;
	servo[wrist] = 107;
	wait1Msec( 1000 );
	debugStep();

	// Raise just alittle 2
	moveLift( 3.3 );
	motor[lift] = 0;
	debugStep();

	// Up and wrsit servo back 3
	servo[elbow] = 240;
	servo[wrist] = 107;
	moveLift( 5.4);
	motor[lift] = 0;
	debugStep();


		// up, servo back to keep from hitting harvester
	servo[elbow] = 250;
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
		servoChangeRate[ elbow ] = 1;
	servoChangeRate[ wrist ] = 1;
	// start from 4
	servo[elbow] = 255;
	servo[wrist] = 84;
	moveLift( 5.55 );
	motor[lift] = 0;
	debugStep();

	servo[elbow] = 248;
	servo[wrist] = 84;
	moveLift( 3.3 );
	motor[lift] = 0;
	debugStep();

	servo[elbow] = 240;
	servo[wrist] = 120;
	moveLift( 0.5 );  // move to close to home.
	motor[lift] = -5;	// power lightly down
	wait1Msec( 300 ); // for a little time.
	motor[lift] = 0;	// now motor off.


}

//void liftUntuck() {

//}

void liftToFloor() {

}

void liftToHighGoal() {

}

void liftToCenterGoal() {

}

void liftPlace() {

}

void harvesterTo(int target_in_degrees) {
	until(nMotorEncoder[harvester] % 1440 < ((target_in_degrees * 16) + 20)) {
		motor[harvester] = 8;
	}
	until(nMotorEncoder[harvester] % 1440 > ((target_in_degrees * 16) - 20)) {
		motor[harvester] = -8;
	}
	motor[harvester] = 0;
}
