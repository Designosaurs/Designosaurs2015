task main() {
    waitForStart();

    bMotorReflected[left_drive] = true;

    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    accel(0,100);
    goForwardDistance(3,100);
    accel(100,5);
    goForwardDistance(5,5);
    stop();
}