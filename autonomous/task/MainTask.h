task main() {
    placerInit();
    //waitForStart();

    bMotorReflected[right_drive] = true;

    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    accel(0,100);
    goForwardDistance(3,50);
    accel(100,5);
    goForwardDistance(6,50);
    stop();

    placeBall();
}
