/*
 * Drive in an increasing spiral to the right.  (Not a pivot, but really tight.)
 */
void KickstandGetter() {
	int i;
	for(i = 0; i< 10; i++) {
	motor[left_drive] = 100;
		motor[right_drive] = -20 + 2*i;
		wait10Msec(100);
	}
}

/*
 * Start at the center, facing north.
 * Go forward a distance, and at that point you should be able to know the position
 * of the center goal by the ultrasonic reading.
 */
void KickstandFromPark() {
	int range = 255;
    goForwardDistance(2, 90);
    stop();
    wait10Msec(50);
    range = getClosestRange();

    if(range < 58) {
        // it's 3. Skinny end of center goal is toward us. Kickstand on right.
        PlaySound(soundFastUpwardTones);
     	pivotDegrees( 90, 60);  // Turn to east.
     	StopAndDone();
    	goForwardDistance(1, 60); // Driving east.
        pivotDegrees(-90, 60); // Turn North
        StopAndDone();
        goForwardDistance(2.8, 100); // Drive through kickstand.
        KickstandGetter();
        StopAndDone();
    } else if(range < 130) {
        // it's 1. Flat part of goal is toward us.
    	PlaySound(soundDownwardTones);
    	pivotDegrees(-90, 60);  // Turn to west.
    	StopAndDone();
    	goForwardDistance(2, 60); // Driving west.
        pivotDegrees(90, 60); // Turn North
        goForwardDistance(2.8, 70); // Drive North
        pivotDegrees(70, 60);  // Turn East by NE
        StopAndDone();
        goForwardDistance(3, 100); // Drive through kickstand.
        KickstandGetter();
        StopAndDone();
    } else {
        // it's 2, angled at 45 degrees to us.
    	PlaySound(soundBlip);
        pivotDegrees(-45, 80); // Turn NW
        StopAndDone();
        goForwardDistance(1.2, 80); // Driving NW.
        pivotDegrees(80, 80); // Pivot right to point to kickstand.
        StopAndDone();
        goForwardDistance(2, 80); // Drive through kickstsnd
        KickstandGetter();
        StopAndDone();
    }

    stop();
    while(true) wait1Msec(50);
}
