void KickstandGetter();

void RampKickstand(){
	int i;

	/*
	 * Go for the kickstand.
	 * Assumes at the bottom of the ramp, back wheels just onto the field
	 * Start at the center.
	 */

	goForwardDistance(0.3, 80);
	pivotDegrees(-75, 60); //  Turn NW
	int range = 255;
	wait10Msec(50);
	range = getClosestRange();

	writeDebugStreamLine("range: %d", range);

	if(range < 105) {
		// it's 3. Skinny end of center goal is toward us. Kickstand on right.
		PlaySound(soundFastUpwardTones);
		pivotDegrees(30, 60);
		goForwardDistance(2, 100);
		pivotDegrees(-10, 60);
		goForwardDistance(2, 100);
		KickstandGetter();
	} else if(range < 130) {
		// it's 1. Flat part of goal is toward us.
		PlaySound(soundDownwardTones);
		pivotDegrees(10, 60);
		goForwardDistance(2.8, 100);
		pivotDegrees(-90, 70);
		goForwardDistance(1.5, 100);
		KickstandGetter();
	} else {
		// it's 2, angled at 45 degrees to us.
		PlaySound(soundBlip);
		goForwardDistance(1.5, 100); // Drive towards kickstand.
		pivotDegrees(-45, 70);
		goForwardDistance(1, 100);
		pivotDegrees(90, 70);
		int range = 255;
		range = getClosestRange();
		goBackwardDistance(0.5, 80);
		pivotDegrees(40, 80);
		goForwardDistance(1, 80);
		pivotDegrees(-30, 80);
		goForwardDistance(2, 80);
		goBackwardDistance(1, 80);
		pivotDegrees(-45, 80);
		goForwardDistance(2.5, 80);
	}

	StopAndDone();
}




void IfBlocked() {
	// if(KickstandIfBlocked) {}
	DetectObstacles = 0;

	// Go to the bottom of the ramp:
	GoToTotalDistance(4.8, 80);
	RampKickstand();
}
