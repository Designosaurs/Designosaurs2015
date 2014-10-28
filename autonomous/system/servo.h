void placerInit() {
    servoChangeRate[placer] = 4;
    servo[placer] = 255;
}

void raiseBall() {
    servoChangeRate[placer] = 1;
    servo[placer] = GOAL_PLACE_RAISE_POS;
}

void placeBall() {
    servoChangeRate[placer] = 1;
    servo[placer] = GOAL_PLACE_SERVO_POS;
}


void goalGrabberUp() {
    servo[goal_grab] = GRABBER_UP;
}

void goalGrabberDown() {
    servo[goal_grab] = GRABBER_DOWN;
}
