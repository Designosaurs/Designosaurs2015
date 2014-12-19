// Smaller value = more up
void goalGrabberUp() {
	servo[goal_grab] = 23;
}

// Larger value = further down
void goalGrabberDown() {
	servo[goal_grab] = 68;
}

void raiseBall() {
	servoChangeRate[placer] = 1;
	servo[placer] = GOAL_PLACE_RAISE_POS;
}

void placeBall() {
	servoChangeRate[placer] = 1;
	servo[placer] = GOAL_PLACE_SERVO_POS;
}

const int ELBOW_TUCK_POS = 245;
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
