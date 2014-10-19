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
    //wait10Msec(200);
    //placerInit();
    //wait1Msec(500);
}
