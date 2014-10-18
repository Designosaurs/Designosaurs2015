task main() {
    placerInit();
    // waitForStart();

    bMotorReflected[left_drive] = true;

    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    goForwardDistance(6.5,100);
    stop();
    goToTube();

    BackwardsArcToAngle(80, 0.1, 50);
    ResetTrip();
    //PlaySound(soundDownwardTones);
    // goBackwardDistance( 2, 80);
    //PlaySound(soundDownwardTones);

    // 5 degrees seems to be about right to get it
    // pointed at the back wall.
    BackwardsArcToAngle(80, 0.1, 5);
    ResetTrip();
    goBackwardDistance(4, 80);
    pivotToTotalAngle(-80); // Place in goal.
    stop();
    ResetTrip();
    goForwardDistance(0.5, 80);
    goForwardDistance(6.5,100);
    stop();
	while(true) {
        wait1Msec(50);
    }
}
