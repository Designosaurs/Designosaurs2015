task main() {
	float angle_before_goal;

    placerInit();
    goalGrabberUp();

    // waitForStart();

    bMotorReflected[left_drive] = true;
    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);


    // Starting from top of ramp, go place the ball in the goal.
    goForwardDistance(6.1, 100);
    stop();

    // Record the angle before we find the goal
    angle_before_goal = total_angle;
    GoalPlacer();
    jogForwardCm( 10, 10 );
    stop();
    goalGrabberDown();
    // Now go back to that angle
    pivotToTotalAngle(angle_before_goal);

    // GO PARK THE TUBE
    BackwardsArcToAngle(80, 0.3, 50);
    ResetTrip();
    goBackwardDistance(1.5, 80);
    BackwardsArcToAngle(80, 0.3, 5); // 5 degrees aims us at wall.
    ResetTrip();
    goBackwardDistance(4.2, 80);
    pivotToTotalAngle(-80); // Place in goal.
    ResetTrip();
    goForwardDistance(0.7, 40);
    stop();
}
