task UpdateJoystickTask() {
    while(true) {
        getJoystickSettings(joystick);
        int y1 = joystick.joy1_y1;
        int y2 = joystick.joy1_y2;
        int x1 = joystick.joy1_x1;
        int x2 = joystick.joy1_x2;

        int PWR_LEFT = (0.78 * y1) * (DRIVE_POWER / 100);
        int PWR_RIGHT = (0.78 * y2) * (DRIVE_POWER / 100);

        motor[left_drive] = PWR_LEFT;
        motor[right_drive] = PWR_LEFT;

        wait1Msec(50);
    }
}