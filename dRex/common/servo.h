void goalGrabberUp() {
	servo[goal_grab] = 60;
}
void goalGrabberDown() {
	servo[goal_grab] = 23;
}


void placerDown() {
	servo[placer] = 240;
}

void placerPlace() {
	servo[placer] = 85;
}

const int ELBOW_TUCK_POS = 240;
void initElbow() {
	servo[elbow] = ELBOW_TUCK_POS;
	elbowPos = (float) ELBOW_TUCK_POS;
}

const int WRIST_TUCK_POS = 120;
void initWrist() {
	servo[wrist] = WRIST_TUCK_POS;
	wristPos = (float) WRIST_TUCK_POS;
}
