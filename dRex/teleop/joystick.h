/*
 * Responds to the driver and gunner joysticks.
 * Handles the processing of the buttons and what they correspond to
 */
const int DEADBAND = 12;
const float scale = 100 / (128 - DEADBAND);
int drivePower = 100;

/*
 * Driver Controller
 * y1 & y2 to drive
 */
void DriverController() {
    int pwrLeft, pwrRight;
    int y1 = joystick.joy1_y1;
    int y2 = joystick.joy1_y2;

    if(abs(y1) > DEADBAND) {
        if(y1 > 0) {
            y1 -= DEADBAND;
        } else {
            y1 += DEADBAND;
        }
        pwrLeft = y1 * scale * drivePower * 0.01;
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
        pwrRight = y2 * scale * drivePower * 0.01;
        motor[right_drive] = pwrRight;
    } else {
        motor[right_drive] = 0;
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
void GunnerController() {
    int y1 = joystick.joy2_y1;
    int y2 = joystick.joy2_y2;
    int x1 = joystick.joy2_x1;
    int x2 = joystick.joy2_x2;
    int pwrLift;

    if(abs(y1) > DEADBAND) {
        if (y1 > 0)	y1 -= DEADBAND;
        else y1 += DEADBAND;
        pwrLift = y1 * 0.5; // Set max speed here.
        motor[lift] = pwrLift;
    } else {
        motor[lift] = 0;
    }

    if(abs(y2) > DEADBAND) {
        if (y2 > 0)	y2 -= DEADBAND;
        else y2 += DEADBAND;
        elbowPos += y2 * 0.01;   // Set speed here.
        servo[elbow] = (int) elbowPos;
    }

    if(abs(x2) > DEADBAND) {
        if(x2 > 0)	 {
            x2 -= DEADBAND;
        } else {
            x2 += DEADBAND;
        }
        wristPos += x2 * 0.01;   // Set speed here.
        servo[wrist] = (int) wristPos;
    }

    if(abs(x1) > DEADBAND) {
        servo[harvester] = (int) x1 * 0.5;
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
    if(joy2Btn(06)) {
        motor[harvester] = 100;
    }

    if(joy2Btn(08)) {
        motor[harvester] = 0;
    }

}
