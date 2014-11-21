void RampKickstand(){
		int i;

	// Go for the kickstand.
	// Assumes at the bottom of the ramp, back wheels just onto the field
	// Start at the center.

		pivotDegrees( -45, 60);		 //  Turn NW
    goForwardDistance(2, 60);  // Driving NW
    pivotDegrees(-45, 60);			// Turn west

   	motor[right_drive] = 100;  // Arc into the kickstand for a time.
    motor[left_drive] = 30;
    wait10Msec( 100 );

	  // Now spiral out for 10 sec.
	for( i = 0; i< 10; i++) {
	 motor[left_drive] = -10 + 2* i;
		motor[right_drive] = 100;
		wait10Msec( 100 );
	}		StopAndDone();
}




void IfBlocked() {
	if (StopIfBlocked ) StopAndDone();
	DetectObstacles = 0;
	// Go to the bottom of the ramp:
	GoToTotalDistance( 5, 80 );
	RampKickstand();

}
