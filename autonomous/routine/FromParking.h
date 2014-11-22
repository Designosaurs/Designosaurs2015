/*
 * Drive in an increasing spiral to the right.  (Not a pivot, but really tight.)
 */
void KickstandGetter() {
	int i;
	for(i = 0; i < 11; i++) {
	motor[left_drive] = 100;
		motor[right_drive] = -20 + 4 * i;
		wait1Msec(1000);
	}
}

/*
 * Start at the center, facing north.
 * Go forward a distance, and at that point you should be able to know the position
 * of the center goal by the ultrasonic reading.
 */
void KickstandFromPark() {
	int range = 255;
    goForwardDistance(2, 100);
    stop();
    wait10Msec(50);
    range = getClosestRange();

    servoChangeRate[placer] = 5;
    if(range < 65) {
        // it's 3. Skinny end of center goal is toward us. Kickstand on right.
        PlaySound(soundFastUpwardTones);
     	pivotDegrees( 90, 70);  // Turn to east.
    	goForwardDistance(1.2, 80); // Driving east.
        pivotDegrees(-100, 70); // Turn North
        goForwardDistance(2.8, 100); // Drive through kickstand.
        KickstandGetter();
        StopAndDone();
    } else if(range < 100) {
        // it's 1. Flat part of goal is toward us.
    	PlaySound(soundDownwardTones);
    	pivotDegrees(-90, 60);  // Turn to west.
    	goForwardDistance(2.5, 70); // Driving west.
        pivotDegrees(90, 70); // Turn North
        goForwardDistance(1.5, 70); // Drive North
        pivotDegrees(90, 60);  // Turn East by NE
        goForwardDistance(3, 100); // Drive through kickstand.
        KickstandGetter();
        StopAndDone();
    } else {
        // it's 2, angled at 45 degrees to us.
    	PlaySound(soundBlip);
        pivotDegrees(-45, 80); // Turn NW
        goForwardDistance(1.1, 90); // Driving NW.
        pivotDegrees(90, 80); // Pivot right to point to kickstand.
        goForwardDistance(2, 90); // Drive through kickstand
        KickstandGetter();
        StopAndDone();
    }

    stop();
    while(true) wait1Msec(50);
}
