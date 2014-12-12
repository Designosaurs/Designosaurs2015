const int DEADBAND = 12;
const float scale = 100 / (128 - DEADBAND);

task UpdateJoystickTask() {
    while(true) {
        getJoystickSettings(joystick);
        DriverController();
        GunnerController();
        wait1Msec(50);
    }
}