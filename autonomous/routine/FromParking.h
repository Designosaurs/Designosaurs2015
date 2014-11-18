// Read range a few times and return the lowest value.  This is because
// the ultrasonic sensor has trouble.
int getClosestRange(){
	int i;
	int range = 255;
	for (i = 0; i<3; i++) {
			if ((SensorValue[ultrasonic]) < range) {
				range = SensorValue[ultrasonic];
		  }
		  wait10Msec( 5 );
	}
	return range;
}



void KickstandFromPark() {
		int range = 255;

    // Start at the center.
    // Go forard a distance, and at that point you should be able to know the posiiont
    // of the center goal by the ultrasonic reading.
    // Ideal nominal distance to skinny end of goal is abut 74 cm, or 29 inches.
    goForwardDistance(2, 90);
    stop();
    wait10Msec(50);
    range = getClosestRange();
    //StopAndDone();

    if(range < 58) {
        // it's 3. Skinny end of center goal is toward us. Kickstand on right.
        ArcToAngle(80, 0.3, 55); // Arc to right
        //goForwardDistance(2.5, 80); // Driving at an angle.
        ArcToAngle(80, 0.3, 0); // Straighten out again.
        goForwardDistance(2.8, 80); // Drive through kickstand.
        KickstandGetter();
        StopAndDone();
    } else if(range < 130) {
        // it's 1. Flat part of goal is toward us.
        ArcToAngle(80, 0.3, 55); // Arc to right.
        goForwardDistance(2.5, 80); // Drive at angle.
        ArcToAngle(80, 0.3, 0); // Straighten out again.
        goForwardDistance(0.3, 80); // Straight just a little bit.
        pivotDegrees(-110, 80);
        goForwardDistance(3, 100); // Drive through kickstand.
        KickstandGetter();
        StopAndDone();
    } else {
        // it's 2, angled at 45 degrees to us.
        pivotDegrees(-45, 80); // No space to arc, so pivot 45 degrees.
        goForwardDistance(1.2, 80); // Driving at an angle.
        pivotDegrees(90, 80); // Pivot right to point to kickstand.
        goForwardDistance(2, 80); // Drive through kickstsnd
        KickstandGetter();
        StopAndDone();
    }

    stop();
    while(true) wait1Msec(50);
    stop();
}
