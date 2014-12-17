// Macro all happen as part of the Gunner Controller Task.

bool stopMacro( void ) {
	bool rtnValue = joy2Btn(09);
	return 	rtnValue;
}

void debugStep() {
	PlaySound(soundBlip);
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
	// Tuck position 1
	servo[elbow] = 209;
	servo[wrist] = 132;
	wait1Msec( 100 );
	debugStep();

	// Tucked, but loose 2
	servoChangeRate[ elbow ] = 5;
	servoChangeRate[ wrist ] = 5;
	servo[elbow] = 192;
	servo[wrist] = 119;
	wait1Msec( 200 );
	debugStep();

	// Up a little 3
	servo[elbow] = 192;
	servo[wrist] = 102;
	moveLift( 3.0 );
	motor[lift] = 0;
	debugStep();

	// up a little 4
	servo[elbow] = 192;
	servo[wrist] = 102;
	moveLift( 3.8);
	motor[lift] = 0;
	debugStep();


		// up a little 6
	servo[elbow] = 240;
	servo[wrist] = 67;
	moveLift( 4.3 );
	motor[lift] = 0;
	debugStep();

	// Waypoint 7
	servo[elbow] = 2013;
	servo[wrist] = 56;
	moveLift( 6.7 );
	motor[lift] = 0;
	debugStep();


}


void tuck() {
	servoChangeRate[ elbow ] = 5;
	servoChangeRate[ wrist ] = 5;
	// start from 4
	servo[elbow] = 192;
	servo[wrist] = 102;
	moveLift( 3.6 );

	// 3
	servo[elbow] = 192;
	servo[wrist] = 102;
	moveLift( 3.3 );

	// Tucked, but loose 2
	moveLift( 0.5 );  // move to close to home.
	motor[lift] = -5;	// power lightly down
	wait1Msec( 200 ); // for a little time.
	motor[lift] = 0;	// now motor off.

	servo[elbow] = 192;
	servo[wrist] = 119;
	wait1Msec( 200 );

	// Tuck position 1
	servo[elbow] = 209;
	servo[wrist] = 132;

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