task main() {
    switchState(STATE_WAIT);

    StartTask(UpdateJoystickTask);

    waitForStart();
}