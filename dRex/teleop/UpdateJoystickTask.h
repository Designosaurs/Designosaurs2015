const int DEADBAND = 12;
const float scale = 100 / (128 - DEADBAND);

int drivePower = 100;

///////////////////////  DRIVER /////////////////////////////////////////////
void DriverController() {
	int pwrLeft, pwrRight;
	int y1 = joystick.joy1_y1;
	int y2 = joystick.joy1_y2;

	if(abs(y1) > DEADBAND) {
		if (y1 > 0)	y1 -= DEADBAND;
		else y1 += DEADBAND;
		pwrLeft = y1 * scale * drivePower * 0.01;
		motor[left_drive] = pwrLeft;
		} else {
		motor[left_drive] = 0;
	}
	if(abs(y2) > DEADBAND) {
		if (y2 > 0)	y2 -= DEADBAND;
		else y2 += DEADBAND;
		pwrRight = y2 * scale * drivePower * 0.01;
		motor[right_drive] = pwrRight;
		} else {
		motor[left_drive] = 0;
	}

	if(abs(pwrRight) > DEADBAND) {
		motor[right_drive] = pwrRight * drivePower * 0.01;
		} else {
		motor[right_drive] = 0;
	}

	if(joy1Btn(06)) {
		drivePower = 90;
	}

	if(joy1Btn(08)) {
		drivePower = 40;
	}

	if(joy1Btn(05)) {
		goalGrabberUp();
	}

	if(joy1Btn(07)) {
		goalGrabberDown();
	}

	switch(joystick.joy1_TopHat) {
	case 0:  // DPAD TOP
		break;
	case 1: // DPAD TOP RIGHT
		break;
	case 2: // DPAD RIGHT
		placerDown();
		break;
	case 3: // DPAD BOTTOM RIGHT
		break;
	case 4: // DPAD BOTTOM
		break;
	case 5: // DPAD BOTTOM LEFT
		break;
	case 6: // DPAD LEFT
		placerPlace();
		break;
	case 7: // DPAD TOP LEFT
		break;
	default:
	}
}

//////////////////// GUNNER ////////////////////////////////////////////////
// Left Joy Y => Scissors up or down.
// Right Joy Y => Elbow
// Right Joy X => Wrist
// High deadband-- normally will not be used.

void GunnerController() {
	int y1 = joystick.joy2_y1;
	int y2 = joystick.joy2_y2;
	int pwrLift;

	if(abs(y1) > 28) {
		pwrLift = y1 - 28;
		motor[left_drive] = pwrLift;
		} else {
		motor[left_drive] = 0;
	}



}


////////////////////////   UPDATE JOYSTICK TASK /////////////////////////////////////////
task UpdateJoystickTask() {
	while(true) {
		getJoystickSettings(joystick);
		DriverController();
		GunnerController();
		wait1Msec(50);
	}
}
