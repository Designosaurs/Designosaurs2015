void goForwardTime(float seconds, int power) {
    motor[left_drive] = power;
    motor[right_drive] = power;
    last_power = power;
    wait1Msec(seconds * 1000);
}

void goForwardDistance(float feet, int power) {
    power = power * (MAX_SPEED * 0.01);
    while(distance_feet < feet) {
        motor[left_drive] = power;
        motor[right_drive] = power;
    }
}

void stop() {
    motor[left_drive] = 0;
    motor[right_drive] = 0;
    last_power = 0;
}

void goBackwardTime(float seconds, int power) {
    motor[left_drive] = -power;
    motor[right_drive] = -power;
    last_power = -power;
    wait1Msec(seconds * 1000);
}

void goBackwardDistance(float feet, int power) {
    power = power * (MAX_SPEED * 0.01);
    while(distance_feet < feet) {
        motor[left_drive] = -power;
        motor[right_drive] = -power;
    }
}

void accel(float from_speed, float to_speed) {
    to_speed = to_speed * (MAX_SPEED * 0.01);
    from_speed = from_speed * (MAX_SPEED * 0.01);

    int delta = from_speed - to_speed;
    goForwardTime(0.1, to_speed + (0.66 * delta));
    goForwardTime(0.1, to_speed + (0.33 * delta));
    goForwardTime(0.1, to_speed + (0.1 * delta));
    goForwardTime(0.1, to_speed);

    last_power = to_speed;
}