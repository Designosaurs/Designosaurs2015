// Smaller value = more up
void goalGrabberUp() {
	servo[goal_grab] = 23;
}

void updateServoPos( ) {
	elbowPos = (float) servo[ elbow ];
	wristPos = (float) servo[ wrist ];
}

// Larger value = further down
void goalGrabberDown() {
	servo[goal_grab] = 76;
}

void raiseBall() {
	servoChangeRate[placer] = 1;
	servo[placer] = 180;
}

void placeBall() {
	servoChangeRate[placer] = 3;
	servo[placer] = 87;
}

const int ELBOW_TUCK_POS = 230;
void initElbow() {
	servo[elbow] = ELBOW_TUCK_POS;
	elbowPos = (float) ELBOW_TUCK_POS;
}

const int WRIST_TUCK_POS = 120;
void initWrist() {
	servo[wrist] = WRIST_TUCK_POS;
	wristPos = (float) WRIST_TUCK_POS;
}

void initPlacer() {
	servoChangeRate[placer] = 4;
	servo[placer] = 255;
}
