task main() {
    switchState(STATE_WAIT);

    //waitForStart();

   StartTask(UpdateJoystickTask);

   waitForStart();
}