void goForwardTime(float seconds, int power) {
    motor[left_drive] = power;
    motor[right_drive] = power;
    last_power = power;
    wait1Msec(seconds * 1000);
}

void goForwardDistance(float feet, int power) {

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

}

void accel(float to_speed) {
    float scaled_speed = to_speed * (MAX_SPEED * 0.01);
    for (int i = 0; i < to_speed; i = i + (0.2 * to_speed)) {
        goForwardTime(0.1, i);
    }

    last_power = to_speed;
}

void decel(float to_speed) {
    float scaled_speed = to_speed * (MAX_SPEED * 0.01);
    for (int i = last_power; i > scaled_speed; i = i - (0.2 * scaled_speed)) {
        goForwardTime(0.1, i);
    }

    last_power = scaled_speed;
}