void placerInit() {
    servoChangeRate[placer] = 4;
    servo[placer] = 255;
}

void placeBall() {
    servoChangeRate[placer] = 10;
    servo[placer] = 80;
    wait1Msec(2000);
    placerInit();
    wait1Msec(500);
}