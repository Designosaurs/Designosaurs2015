task main() {
    placerInit();
    // waitForStart();

    bMotorReflected[left_drive] = true;
    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    goToRange( 10 );
    while(true) {
        wait1Msec(50);
    	}

    // Starting from top of ramp, go place the ball in the goal.
    goForwardDistance(6.5,100);
    stop();
    goToTube();

    // Go from placing the goal to parking the tube.
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
    ResetTrip();
    goForwardDistance(0.5, 80);
    stop();


}
