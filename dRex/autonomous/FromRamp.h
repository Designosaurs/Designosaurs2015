void GoalFromRamp(){
    float angle_before_goal = 0;

    // Starting from top of ramp, go place the ball in the goal.
    goForwardDistance(4.6, 40);
    DetectObstacles = 20;
    if(goForwardDistance(2.1, 50)) IfBlocked();
    DetectObstacles = 0;
    stop();
    //stopAndWait();
    // Record the angle before we find the goal
    angle_before_goal = total_angle;
    GoalPlacer();
    pivotDegrees(-8, 80); // Compensate for hardware being slightly off center
    jogForwardCm(17, 10);
    stop();
    goalGrabberDown();
    wait1Msec(1000);
    // Now go back to that angle
    pivotToTotalAngle(angle_before_goal, 40);

    // GO PARK THE TUBE
    BackwardsArcToAngle(50, 0.3, 50);
    goBackwardDistance(1.8, 70);
    // If we don't still have the tube, we are done.
    BackwardsArcToAngle(50, 0.3, -5); // 5 degrees aims us at wall.
    goBackwardDistance(4.2, 70);
    pivotToTotalAngle(-100, 50); // Place in parking zone.
    ResetTrip();
    //goForwardDistance(0.5, 40);
    StopAndDone();
}
