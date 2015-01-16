bool is_reversed = false;

task DriverControllerTask {
	int y1, y2;
	int pwrLeft, pwrRight;

	while( true ){
		getJoystickSettings(joystick);
		//motor[left_drive] = 10;
		//motor[right_drive] = 10;
		//return;

		y1 = joystick.joy1_y1;
		y2 = joystick.joy1_y2;

		if(abs(y1) > DEADBAND) {
			if(y1 > 0) {
				y1 -= DEADBAND;
				} else {
				y1 += DEADBAND;
			}
			pwrLeft = y1 * 0.86 * drivePower * 0.01; //Negative value for Y1 means joystick forward.
			if(is_reversed) {
				motor[right_drive] = -pwrLeft;
			} else motor[left_drive] = pwrLeft;
		} else {
			if(is_reversed) {
				motor[right_drive] = 0;
			} else motor[left_drive] = 0;
		}

		if(abs(y2) > DEADBAND) {
			if(y2 > 0) {
				y2 -= DEADBAND;
				} else {
				y2 += DEADBAND;
			}
			pwrRight = y2 * 0.86 * drivePower * 0.01;
			if(is_reversed) {
				motor[left_drive] = -pwrRight;
			} else motor[right_drive] = pwrRight;
		} else {
			if(is_reversed) {
				motor[left_drive] = 0;
			} else motor[right_drive] = 0;
		}

		if(joy1Btn(06)) {
			drivePower = 100;
		}

		if(joy1Btn(08)) {
			drivePower = 40;
		}

		if(joy1Btn(05)) {
			goalGrabberUp();
		}

		if(joy1Btn(07)) {
			goalGrabberDown();
			//PlaySound(soundDownwardTones);
		}

		if(joy1Btn(09)) {
			initPlacer();
		}

		if(joy1Btn(10)) {
			placeBall();
		}

		if(joy1Btn(04)) is_reversed = false;

		if(joy1Btn(02)) is_reversed = true;

		switch(joystick.joy1_TopHat) {
		case 0: // TOP
			// Pivot nudge forward.
			if(!is_reversed) {
				motor[left_drive] = 25;
				motor[right_drive] = 25;
			} else {
				motor[left_drive] = -25;
				motor[right_drive] = -25;
			}
			wait1Msec(200);
			motor[left_drive] = 0;
			motor[right_drive] = 0;
		break;
		case 1: // TOP RIGHT

		break;
		case 2: // RIGHT
			// Pivot nudge to right.
			if(!is_reversed) {
				motor[left_drive] = 25;
				motor[right_drive] = -25;
			} else {
				motor[left_drive] = -25;
				motor[right_drive] = 25;
			}
			wait1Msec(200);
			motor[left_drive] = 0;
			motor[right_drive] = 0;
		break;
		case 3: // BOTTOM RIGHT

		break;
		case 4: // BOTTOM
			// Pivot nudge backward.
			if(!is_reversed) {
				motor[left_drive] = -25;
				motor[right_drive] = -25;
			} else {
				motor[left_drive] = 25;
				motor[right_drive] = 25;
			}
			wait1Msec(200);
			motor[left_drive] = 0;
			motor[right_drive] = 0;
		break;
		case 5: // BOTTOM LEFT

		break;
		case 6: // LEFT
			// Pivot nudge to left.
			if(!is_reversed) {
				motor[left_drive] = -25;
				motor[right_drive] = 25;
			} else {
				motor[left_drive] = 25;
				motor[right_drive] = -25;
			}
			wait1Msec(200);
			motor[left_drive] = 0;
			motor[right_drive] = 0;
		break;
		case 7: // TOP LEFT

		break;
		default:

		break;
		}
		wait1Msec(50);
	}
}
