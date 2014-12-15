task UpdateJoystickTask() {
    while(true) {
        getJoystickSettings(joystick);
        StartTask(DriverController);
        StartTask(GunnerController);
        wait1Msec(50);
    }
}
