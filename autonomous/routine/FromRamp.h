task main() {
	float angle_before_goal;

    placerInit();
    goalGrabberUp();

    waitForStart();

    bMotorReflected[left_drive] = true;
    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);


    // Starting from top of ramp, go place the ball in the goal.
    goForwardDistance(4.1, 80);
    DetectObstacles = 20;
    if (goForwardDistance(6.1, 60))
    	IfBlocked();
    DetectObstacles = 0;
    stop();

    // Record the angle before we find the goal
    angle_before_goal = total_angle;
    GoalPlacer();
    pivotDegrees(-3, 80); // Compensate for hardware being slightly off center
    jogForwardCm(10, 10);
    stop();
    goalGrabberDown();
    wait1Msec(1000);
    // Now go back to that angle
    pivotToTotalAngle(angle_before_goal, MAX_SPEED);

    // GO PARK THE TUBE
    BackwardsArcToAngle(50, 0.3, 50);
    ResetTrip();
    goBackwardDistance(1.5, 50);
    // If we don't still have the tube, we are done.
    if (SensorValue[ultrasonic] > 20) StopAndDone();
    BackwardsArcToAngle(50, 0.3, 5); // 5 degrees aims us at wall.
    if (SensorValue[ultrasonic] > 20) StopAndDone();
    goBackwardDistance(4.2, 50);
    pivotToTotalAngle(-80, 50); // Place in goal.
    ResetTrip();
    goForwardDistance(0.7, 40);
    stop();
}
