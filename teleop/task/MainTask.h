task main() {
    switchState(STATE_WAIT);

    StartTask(UpdateJoystickTask);

    waitForStart();

    switchState(STATE_RUN);

    while(systemState.running) {
        wait1Msec(100);
    }
}