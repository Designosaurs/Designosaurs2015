task main() {
    placerInit();
    wait10Msec( 100 );
    // waitForStart();

    bMotorReflected[left_drive] = true;
    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    GoalPlacer();
    //preciseAimer();
    while(true) {
        wait1Msec(50);
    	}
    // PLACE IN GOAL
    // Start ideally between 1 and 1.5 feet away.
    // raiseBall();
    //pointToNearest( true );
    //PlaySound(soundDownwardTones);
    //wait10Msec( 100 );
    //pivotDegrees( 3 );
    //stop();
    //PlaySound(soundDownwardTones);
   	//wait10Msec( 100 );
    //goToRange( 20 );
    //stop();
    //placeBall();

    //while(true) {
    //    wait1Msec(50);
    //	}

    // Starting from top of ramp, go place the ball in the goal.
    goForwardDistance(6.5,100);
    stop();

    // PLACE IN GOAL
    // Start ideally between 1 and 1.5 feet away.
    //raiseBall();
    //pointToNearest( true );
    //PlaySound(soundDownwardTones);
    ////wait10Msec( 100 );
    //goToRange( 20 );
    //stop();
    //placeBall();

    //while(true) {
    //    wait1Msec(50);
    //	}



    // GO PARK THE TUBE
    BackwardsArcToAngle(80, 0.1, 50);
    ResetTrip();
    // goBackwardDistance( 2, 80);
    BackwardsArcToAngle(80, 0.1, 5); // 5 degrees aims us at all.
    ResetTrip();
    goBackwardDistance(4, 80);
    pivotToTotalAngle(-80); // Place in goal.
    ResetTrip();
    goForwardDistance(0.5, 80);
    stop();


}
