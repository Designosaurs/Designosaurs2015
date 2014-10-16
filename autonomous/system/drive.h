void goForwardTime(float seconds, int power) {
    motor[left_drive] = power * LEFT_TRIM;
    motor[right_drive] = power * RIGHT_TRIM;
    last_power = power;
    wait1Msec(seconds * 1000);
}

void goForwardDistance(float feet, float power) {
    power = power * (MAX_SPEED * 0.01);
    float start_angle = total_angle;
    float angle_error = 0;
    float left_power, right_power;
    float feedback;

    while(total_distance_feet < feet) {
        angle_error = total_angle - start_angle;
        left_power = power;
        right_power = power;
        feedback = 10 * angle_error;
        if(feedback > 0) {
            left_power -= feedback;
        } else {
            right_power += feedback;  // feedback is negative value.
        }
        motor[left_drive] = left_power * LEFT_TRIM;
        motor[right_drive] = right_power * RIGHT_TRIM;
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
