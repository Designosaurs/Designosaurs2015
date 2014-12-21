
float clamp255( float input) {
		if (input > 255) return 255;
		if (input < 0) return 0;
		return input;
}


void stopAndWait() {
  	motor[left_drive] = 0;
    motor[right_drive] = 0;
    while(true) {
        wait1Msec(100);
    }
}
