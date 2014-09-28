task main() {
    waitForStart();

    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    accel(0,100);
    goForwardDistance(3,100);
    accel(100,20);
    goForwardDistance(5,100);
    stop();
}