task UpdateJoystickTask() {
    while(true) {
        getJoystickSettings(joystick);
        int y1 = joystick.joy1_y1;
        int y2 = joystick.joy1_y2;
        int x1 = joystick.joy1_x1;
        int x2 = joystick.joy1_x2;

        PWR_LEFT = y1 * 0.78;
        PWR_RIGHT = y2 * 0.78;

        if(abs(PWR_LEFT) > DEADBAND) {
            motor[left_drive] = PWR_LEFT * DRIVE_POWER * 0.01;
        } else {
            motor[left_drive] = 0;
            PWR_LEFT = 0;
        }

        if(abs(PWR_RIGHT) > DEADBAND) {
            motor[right_drive] = PWR_RIGHT * DRIVE_POWER * 0.01;
        } else {
            motor[right_drive] = 0;
            PWR_RIGHT = 0;
        }

        if(joy1Btn(06)) {
            DRIVE_POWER = 90;
        }

        if(joy1Btn(08)) {
            DRIVE_POWER = 40;
        }

        if(joy1Btn(05)) {
            goalGrabberUp();
        }

        if(joy1Btn(07)) {
            goalGrabberDown();
        }

        switch(joystick.joy1_TopHat) {
            case 0:
                dpad.TOP = true;
                break;
            case 1:
                dpad.TOP_RIGHT = true;
                break;
            case 2:
                dpad.RIGHT = true;
                break;
            case 3:
                dpad.BOTTOM_RIGHT = true;
                break;
            case 4:
                dpad.BOTTOM = true;
                break;
            case 5:
                dpad.BOTTOM_LEFT = true;
                break;
            case 6:
                dpad.LEFT = true;
                break;
            case 7:
                dpad.TOP_LEFT = true;
                break;
            default:
                dpad.TOP = false;
                dpad.LEFT = false;
                dpad.RIGHT = false;
                dpad.BOTTOM = false;
                dpad.BOTTOM_LEFT = false;
                dpad.BOTTOM_RIGHT = false;
                dpad.TOP_LEFT = false;
                dpad.TOP_RIGHT = false;
        }

        wait1Msec(50);
    }
}
