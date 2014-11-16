void GoalFromRamp(){
	float angle_before_goal = 0;

    // Starting from top of ramp, go place the ball in the goal.
    goForwardDistance(4.1, 80);
    DetectObstacles = 20;
    if (goForwardDistance(2, 60))
    	IfBlocked();
    DetectObstacles = 0;
    stop();

    // Record the angle before we find the goal
    angle_before_goal = total_angle;
    GoalPlacer();
    //pivotDegrees(-3, 80); // Compensate for hardware being slightly off center
    jogForwardCm(15, 10);
    stop();
    goalGrabberDown();
    wait1Msec(1000);
    // Now go back to that angle
    pivotToTotalAngle(angle_before_goal, 40);

    // GO PARK THE TUBE
    BackwardsArcToAngle(50, 0.3, 50);
    goBackwardDistance(2.0, 70);
    // If we don't still have the tube, we are done.
    BackwardsArcToAngle(50, 0.3, 0); // 5 degrees aims us at wall.
    goBackwardDistance(3.9, 70);
    pivotToTotalAngle(-90, 50); // Place in goal.
    ResetTrip();
    goForwardDistance(0.7, 40);
    StopAndDone();
}
