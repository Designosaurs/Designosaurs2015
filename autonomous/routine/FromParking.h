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

    goForwardDistance(2, 90);

    if(SensorValue[ultrasonic] < 64) {
        // it's 3. Skinny end of center goal is toward us. Kickstand on right.
        ArcToAngle(80, 0.3, 55); // Arc to right
        goForwardDistance(2.5, 80); // Driving at an angle.
        ArcToAngle(80, 0.3, 0); // Straighten out again.
        ResetTrip();
        goForwardDistance(3.8, 80); // Drive through kickstand.
        pivotDegrees(-110, 80); // Other side of kickstand, turn left.
        ResetTrip();
        goForwardDistance(4, 100); // Drive in enemy territory.
    } else if(SensorValue[ultrasonic] < 130) {
        // it's 1. Flat part of goal is toward us.
        ArcToAngle(80, 0.3, 55); // Arc to right.
        goForwardDistance(2.5, 80); // Drive to angle.
        ArcToAngle(80, 0.3, 0); // Straighten out again.
        ResetTrip();
        goForwardDistance(0.3, 80); // Straight just a little bit.
        pivotDegrees(-110, 80);
        ResetTrip();
        goForwardDistance(4, 100); // Drive through kickstand.
        pivotDegrees(-20, 80); // Turn to the left slightly, toward enemy goals.
        ResetTrip();
        goForwardDistance(4, 100); // Plow into enemy goals.
    } else {
        // it's 2, angled at 45 degrees to us.
        pivotDegrees(-45, 80); // No space to arc, so pivot 45 degrees.
        ResetTrip();
        goForwardDistance(1.2, 80); // Driving at an angle.
        pivotDegrees(90, 80); // Pivot right to point to kickstand.
        ResetTrip();
        goForwardDistance(3, 80); // Drive through kickstsnd
        pivotDegrees(-90, 80); // Left after we are past goal.
        ResetTrip();
        goForwardDistance(2.5, 80); // Drive past end of center goal.
        pivotDegrees(-55, 80); // Turn so we are going roughly to the left.
        ResetTrip();
        goForwardDistance(3, 80); // Drive into enemy territory.
    }

    stop();
    while(true) wait1Msec(50);
    stop();
}
