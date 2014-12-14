/*
* Responds to the driver and gunner joysticks.
* Handles the processing of the buttons and what they correspond to
*/
const int DEADBAND = 12;
int drivePower = 100;

/*
* Driver Controller
* y1 & y2 to drive
*/


void DriverController() {
	int pwrLeft, pwrRight;
	//motor[left_drive] = 10;
	//motor[right_drive] = 10;
	//return;

	int y1 = joystick.joy1_y1;
	int y2 = joystick.joy1_y2;

	if(abs(y1) > DEADBAND) {
		if(y1 > 0) {
			y1 -= DEADBAND;
			} else {
			y1 += DEADBAND;
		}
		pwrLeft =  y1 * 0.86 * drivePower * 0.01; //Negative value for Y1 means joystick forward.
		motor[left_drive] = pwrLeft;
		} else {
		motor[left_drive] = 0;
	}

	if(abs(y2) > DEADBAND) {
		if(y2 > 0) {
			y2 -= DEADBAND;
			} else {
			y2 += DEADBAND;
		}
		pwrRight = y2 * 0.86 * drivePower * 0.01;
		motor[right_drive] = pwrRight;
		} else {
		motor[right_drive] = 0;
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
	}

	switch(joystick.joy1_TopHat) {
	case 0: // TOP

		break;
	case 1: // TOP RIGHT

		break;
	case 2: // RIGHT
		placerDown();
		break;
	case 3: // BOTTOM RIGHT

		break;
	case 4: // BOTTOM

		break;
	case 5: // BOTTOM LEFT

		break;
	case 6: // LEFT
		placerPlace();
		break;
	case 7: // TOP LEFT

		break;
	default:

		break;
	}
}

/*
* Gunner Controller
* Left Joy Y => Scissors up or down.
* Right Joy Y => Elbow
* Right Joy X => Wrist
* High deadband - normally will not be used.
* Top (yellow) = position for 3'
* Right (red) = place in goal.  (if positioned for 4', place at 4')
* Left (blue) = Center goal.
* Bottom (green) = floor
*/
int pwrLift;
#define GUNNER_DEADBAND 30
void GunnerController() {

	int y1 = joystick.joy2_y1;
	int y2 = joystick.joy2_y2;
	int x1 = joystick.joy2_x1;
	int x2 = joystick.joy2_x2;

	// Left joystick Y controls lift.
	if(abs(y1) > GUNNER_DEADBAND) {
		if (y1 > 0)	y1 -= GUNNER_DEADBAND;
		else y1 += GUNNER_DEADBAND;
		pwrLift = y1 * 0.5; // Set max speed here.
		motor[lift] = pwrLift;
		} else {
		motor[lift] = 0;
	}

	// Right joystic Y controls elbow
	if(abs(y2) > GUNNER_DEADBAND) {
		if (y2 > 0)	y2 -= GUNNER_DEADBAND;
		else y2 += GUNNER_DEADBAND;
		elbowPos -= y2 * 0.1;   // Set speed here.
	  elbowPos = clamp255( elbowPos );
		servo[elbow] = (int) elbowPos;
	}

	// Right joystick X controls wrist.
	if(abs(x2) > GUNNER_DEADBAND) {
		if(x2 > 0)	 {
			x2 -= GUNNER_DEADBAND;
			} else {
			x2 += GUNNER_DEADBAND;
		}
		wristPos -= x2 * 0.1;   // Set speed here.
		wristPos = clamp255( wristPos );
		servo[wrist] = (int) wristPos;
	}

	// Left joystick X allows sllow slow control of harvester.
	if(abs(x1) > GUNNER_DEADBAND) {
		if (x1 > 0)	x1 -= GUNNER_DEADBAND;
		else x1 += GUNNER_DEADBAND;
		motor[harvester] = x1;
	}

	// Top (yellow) = position for 3' High Goal
	if(joy2Btn(04)) {
		liftToHighGoal();
	}

	// Right (red) = place in goal. (if positioned for 4', place at 4')
	if(joy2Btn(03)) {
		liftPlace();
	}

	// Bottom (green) button
	if(joy2Btn(02)) {
		liftToCenterGoal();
	}

	// Left (blue) button
	if(joy2Btn(01)) {
		liftToFloor();
	}

	// Right upper trigger - stop harvester
	if(joy2Btn(08)) {
		motor[harvester] = 100;
	}

	if(joy2Btn(06)) {
		motor[harvester] = 0;
	}

}
