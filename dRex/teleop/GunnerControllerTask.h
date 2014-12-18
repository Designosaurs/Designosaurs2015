task GunnerControllerTask {
	int y1,y2, x1, x2;

	while( true ){
		y1 = joystick.joy2_y1;
		y2 = joystick.joy2_y2;
		x1 = joystick.joy2_x1;
		x2 = joystick.joy2_x2;

		// Left joystick Y controls lift.
		if(abs(y1) > GUNNER_DEADBAND) {
			if (y1 > 0)	y1 -= GUNNER_DEADBAND;
			else y1 += GUNNER_DEADBAND;
			pwrLift = y1 * 0.5; // Set max speed here.
			motor[lift] = pwrLift;
			} else {
			motor[lift] = 0;
		}

		// Right joystick Y controls elbow
		if(abs(y2) > GUNNER_DEADBAND) {
			if (y2 > 0)	y2 -= GUNNER_DEADBAND;
			else y2 += GUNNER_DEADBAND;
			servoChangeRate[ elbow ] = 5;
			elbowPos -= y2 * 0.1;   // Set speed here.
			elbowPos = clamp255(elbowPos);
			servo[elbow] = (int) elbowPos;
		}

		// Right joystick X controls wrist.
		if(abs(x2) > GUNNER_DEADBAND) {
			if(x2 > 0)	 {
				x2 -= GUNNER_DEADBAND;
				} else {
				x2 += GUNNER_DEADBAND;
			}
			servoChangeRate[ wrist ] = 5;
			wristPos -= x2 * 0.1; // Set speed here.
			wristPos = clamp255(wristPos);
			servo[wrist] = (int) wristPos;
		}

		// Left joystick X allows slow control of harvester.
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
			liftToFloor();
		}

		// Left (blue) button
		if(joy2Btn(01)) {
			liftToCenterGoal();
		}

		// Right upper trigger - stop harvester
		if(joy2Btn(08)) {
			motor[harvester] = 100;
		}

		if(joy2Btn(06)) {
			harvesterTo(0);
		}

		switch(joystick.joy2_TopHat) {
		case 0: // TOP
			moveLift( 1 );
			motor[ lift ] = 0;

			break;
		case 1: // TOP RIGHT
			harvesterTo(0);
			break;
		case 2: // RIGHT
			tuck();
			break;
		case 3: // BOTTOM RIGHT

			break;
		case 4: // BOTTOM
			moveLift( -1 );
			motor[ lift ] = 0;

			break;
		case 5: // BOTTOM LEFT

			break;
		case 6: // LEFT
			untuck();
			break;
		case 7: // TOP LEFT

			break;
		default:

			break;
		}

		wait1Msec( 50 );
	}
}
