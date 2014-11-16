task main() {
    placerInit();
    goalGrabberUp();

    // waitForStart();

    bMotorReflected[left_drive] = true;
    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    // Start at the center.
    // Go forard a distance, and at that point you should be able to know the posiiont
    // of the center goal by the ultrasonic reading.
    // Ideal nominal distance to skinny end of goal is abut 74 cm, or 29 inches.
    goForwardDistance(2, 90);

    if(SensorValue[ultrasonic] < 64) {
        // it's 3. Skinny end of center goal is toward us. Kickstand on right.
        ArcToAngle(80, 0.3, 55); // Arc to right
        goForwardDistance(2.5, 80); // Driving at an angle.
        ArcToAngle(80, 0.3, 0); // Straighten out again.
        goForwardDistance(2.8, 80); // Drive through kickstand.
        KickstandGetter();
        stop();
    } else if(SensorValue[ultrasonic] < 130) {
        // it's 1. Flat part of goal is toward us.
        ArcToAngle(80, 0.3, 55); // Arc to right.
        goForwardDistance(2.5, 80); // Drive to angle.
        ArcToAngle(80, 0.3, 0); // Straighten out again.
        goForwardDistance(0.3, 80); // Straight just a little bit.
        pivotDegrees(-110, 80);
        goForwardDistance(4, 100); // Drive through kickstand.
        KickstandGetter();
        stop();
    } else {
        // it's 2, angled at 45 degrees to us.
        pivotDegrees(-45, 80); // No space to arc, so pivot 45 degrees.
        goForwardDistance(1.2, 80); // Driving at an angle.
        pivotDegrees(90, 80); // Pivot right to point to kickstand.
        goForwardDistance(3, 80); // Drive through kickstsnd
        KickstandGetter();
        stop();
    }

    stop();
    while(true) wait1Msec(50);
    stop();
}