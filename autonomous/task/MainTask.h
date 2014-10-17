task main() {
    placerInit();
    //waitForStart();

    bMotorReflected[left_drive] = true;

    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    goForwardDistance(6,80);
    goToTube();

    stop();
}
