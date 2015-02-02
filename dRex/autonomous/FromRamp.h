// We check for goal a few times.
// We only stop if we cannot find it any time.
bool haveGoal = false;
void checkForGoal(){
	if (SensorValue[ultrasonic] < 30) {
		haveGoal = true;
		PlaySound(soundUpwardTones);
		}
}


void GoalFromRamp(){
    float angle_before_goal = 0;

    // Starting from top of ramp, go place the ball in the goal.
    goForwardDistance(4.7, 40);
    DetectObstacles = 20;
    if(goForwardDistance(2.2, 50)) {
    	// Blocked, so just stop, rather than risk damage.
    	PlaySound(soundDownwardTones);
    	stopAndWait();
  	}
    DetectObstacles = 0;
    stop();
    //stopAndWait();
    // Record the angle before we find the goal
    angle_before_goal = total_angle;
    GoalPlacer();
    //pivotDegrees(-3, 80); // Compensate for hardware being slightly off center
    jogForwardCm(17, 10);
    stop();
    goalGrabberDown();
    wait1Msec(1000);
    // Now go back to that angle
    pivotToTotalAngle(angle_before_goal, 40);

    // GO PARK THE TUBE
    BackwardsArcToAngle(50, 0.3, 50);
 		checkForGoal();
   	goBackwardDistance(1.8, 70);
   	checkForGoal();
    BackwardsArcToAngle(50, 0.3, -5); // 5 degrees aims us at wall.
   	checkForGoal();
   	if (haveGoal == false) stopAndWait();
    goBackwardDistance(4.2, 70);
    pivotToTotalAngle(-100, 50); // Place in parking zone.
    ResetTrip();
    //goForwardDistance(0.5, 40);
    StopAndDone();
}
