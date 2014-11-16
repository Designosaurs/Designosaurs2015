void RampKickstand(){
	// Go for the kickstand.
	// Assumes at the bottom of the ramp, back wheels at center of field  (on the seam)
	// Start at the center.
    // Go forard a distance, and at that point you should be able to know the posiiont
    // of the center goal by the ultrasonic reading.
    // Ideal nominal distance to skinny end of goal is abut 74 cm, or 29 inches.
  pivotToTotalAngle( -90, 80 );

	goForwardDistance(1, 90);

    if(SensorValue[ultrasonic] < 64) {
        // it's 3. Skinny end of center goal is toward us. Kickstand on right.
        ArcToAngle(80, 0.3, -145); // Arc to left
        goForwardDistance(2.5, 80); // Driving at an angle.
        ArcToAngle(80, 0.3, -90); // Straighten out again.
        goForwardDistance(2.8, 80); // Drive through kickstand.
        LeftKickstandGetter();
        stop();
    } else if(SensorValue[ultrasonic] < 130) {
        // it's 1. Flat part of goal is toward us.
        ArcToAngle(80, 0.3, 55); // Arc to left.
        goForwardDistance(2.5, 80); // Drive at angle.
        ArcToAngle(80, 0.3, 0); // Straighten out again.
        goForwardDistance(0.3, 80); // Straight just a little bit.
        pivotDegrees(110, 80);
        goForwardDistance(2.5, 100); // Drive through kickstand.
        KickstandGetter();
        stop();
    } else {
        // it's 2, angled at 45 degrees to us.
        pivotDegrees( 45, 80); // No space to arc, so pivot 45 degrees.
        goForwardDistance(1.2, 80); // Driving at an angle.
        pivotDegrees( -90, 80); // Pivot right to point to kickstand.
        goForwardDistance(3, 80); // Drive through kickstsnd
        LeftKickstandGetter();
        stop();
    }
		StopAndDone();
}


void IfBlocked() {
	if (StopIfBlocked ) StopAndDone();
	DetectObstacles = 0;
	// Go to a predictable spot on the field.
	GoToTotalDistance( 7, 80 );



}
