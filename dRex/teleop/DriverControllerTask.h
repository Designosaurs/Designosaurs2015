task DriverControllerTask {
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
        pwrLeft = y1 * 0.86 * drivePower * 0.01; //Negative value for Y1 means joystick forward.
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