task UpdateJoystickTask() {
    while(true) {
        getJoystickSettings(joystick);
        DriverController();
        GunnerController();
        wait1Msec(50);
    }
}
