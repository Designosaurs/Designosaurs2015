task main() {
    placerInit();
    //waitForStart();

    bMotorReflected[left_drive] = true;

    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);
    // goForwardTime( 4, -80);

    //accel(0,80);
    //goForwardDistance(6,80);
    //accel(80,0);


    //accel(0,-80);
    //goBackwardDistance(6,80);
    //accel(-80,0);

    // pivotToTotalAngle( 90 );

    goForwardDistance(7,80);
    stop();
    PlaySound(soundDownwardTones);
    wait1Msec( 1000 );
    BackwardsArcToAngle( 80, 0.1, 50);
    ResetTrip();
    //PlaySound(soundDownwardTones);
    goBackwardDistance( 2, 80);
    //PlaySound(soundDownwardTones);
    // 5 degrees seems to be about right to get it
    // pointed at the back wall.
		BackwardsArcToAngle( 80, 0.1, 5);
    ResetTrip();
    goBackwardDistance( 4, 80);
    stop();
		while( 1 );

}
