void goalGrabberUp() {
	servo[goal_grab] = 60;
}
void goalGrabberDown() {
	servo[goal_grab] = 23;
}

void placerDown() {
	servo[placer] = 255;
}

void placerPlace() {
	servo[placer] = 85;
}
