

void moveLift( float to_height ){
	if (lift_inches < to_height ) {
		while( lift_inches < to_height ) {
			running_macro = true;
			motor[ lift ] = 30;
			if (override_macro) break;
			wait1Msec( 20 );
		}
		} else {
		while( lift_inches > to_height ) {
			running_macro = true;
			motor[ lift ] = -5;
			if (override_macro) break;
			wait1Msec( 20 );
		}
	}
	running_macro = false;
}





	void liftUntuck() {

	}

	void liftToFloor() {

	}

	void liftToHighGoal() {

	}

	void liftToCenterGoal() {

	}

	void liftPlace() {

	}
