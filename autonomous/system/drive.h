void goForwardTime(float seconds, int power) {
    motor[left_drive] = power;
    motor[right_drive] = power;
    last_power = power;
    wait1Msec(seconds * 1000);
}

void goForwardDistance(float feet, float power) {
    power = power * (MAX_SPEED * 0.01);
    while(total_distance_feet < feet) {
        motor[left_drive] = power;
        motor[right_drive] = power;
    }
}

void pivotToTotalAngle(float desired_angle) {
    float how_far;
    float current_speed = MAX_SPEED * 0.5;

    if(desired_angle > total_angle) {
        while(total_angle < (desired_angle - INTERTIAL_DEGREES)) {
            how_far = abs(desired_angle - total_angle);
            if(how_far < 20.0) {
                current_speed = MAX_SPEED * 0.1;
            }
            motor[left_drive] = current_speed;
            motor[right_drive] = -current_speed;
        }
    } else {
        while(total_angle > (desired_angle + INTERTIAL_DEGREES)) {
            how_far = abs(desired_angle - total_angle);
            if (how_far < 20.0) {
                current_speed = MAX_SPEED * 0.1;
            }
            motor[left_drive] = -current_speed;
            motor[right_drive] = current_speed;
        }
    }
}

void stop() {
    motor[left_drive] = 0;
    motor[right_drive] = 0;
    last_power = 0;
}

void goBackwardTime(float seconds, int power) {
    motor[left_drive] = power;
    motor[right_drive] = power;
    last_power = -power;
    wait1Msec(seconds * 1000);
}

void goBackwardDistance(float feet, int power) {
    power = power * (MAX_SPEED * 0.01);
    while(total_distance_feet < feet) {
        motor[left_drive] = power;
        motor[right_drive] = power;
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
