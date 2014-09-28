task main() {
    waitForStart();

    bMotorReflected[right_drive] = 1;

    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    accel(0,20);
    goForwardDistance(90,20);
    accel(20,5);
    goForwardDistance(5,5);
    stop();
}