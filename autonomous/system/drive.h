void goForwardTime(float seconds, int power) {
	motor[left_drive] = power * LEFT_TRIM;
	motor[right_drive] = power * RIGHT_TRIM;
	last_power = power;
	wait1Msec(seconds * 1000);
}

void ResetTrip() {
	left_trip_counts = 0;
	right_trip_counts = 0;
	trip_distance_feet = 0;
}

void jogForwardCm( float dist_cm) {
	float dist_feet = dist_cm * 0.0328;
	ResetTrip();
	wait10Msec( 10 );
	while(abs(trip_distance_feet) < dist_feet) {
		motor[left_drive] = 5;
		motor[right_drive] = 5;
		wait10Msec( 2 );
	}
	motor[left_drive] = 0;
  motor[right_drive] = 0;

}

void goDistance(float feet, float power, bool forward) {
	float feedback; // A ratio, so 0.9 means apply 90% power.
	float start_angle;
	float angle_error;
	float error_integration = 0;
	float error_value;
	float left_power, right_power;
	float direction = 1.00;
	power = power * (MAX_SPEED * 0.01); // Scale to whatever we make our max speed.
	start_angle = total_angle;

	if(!forward) direction = -1.00;

	while(abs(trip_distance_feet) < feet) {
		left_power = power * direction;
		right_power = power * direction;

		// Error calculation:
		angle_error = total_angle - start_angle;
		error_integration += 0.01 * angle_error;
		// The integration term makes the steady state error to near zero, but it
		// is a destabilizing influence.
		error_value = angle_error + 1.0 * error_integration;
		// Cut the power 10% for every degree it is off..+wait1Msec(300);
		feedback = 1 - (0.1 * abs(error_value));
		// But not less than this much power:
		if(feedback < 0.5) feedback = 0.5;

		// Write debugging information if needed:
        // movementTrace(angle_error, error_integration, feedback);

		// If it is veering right, decrease the left motor power.
		if(error_value * direction > 0) {
			left_power = feedback * left_power;
		} else {
			right_power = feedback * right_power; // feedback is negative value.
		}
		motor[left_drive] = left_power * LEFT_TRIM;
		motor[right_drive] = right_power * RIGHT_TRIM;
		wait1Msec(20);
	}
}

void goForwardDistance(float feet, float power ) {
	goDistance(feet, power, true);
}

void goBackwardDistance(float feet, int power) {
	goDistance(abs(feet), power, false);
}

/*
* This is intended for speed, not precision.
* So, it does not slow down at the end of the arc.
* But, we do try to compensate with an inertia allowance.
* Inside ratio is how fast the inside move wrt outside.  Typical is 0.1.
* Larger value for larger radius.
*/
void ArcToAngle(float power, float inside_ratio, float desired_angle) {
	float how_far;
	float inertia_allowance = 10;
	power = power * (MAX_SPEED * 0.01); // Scale to whatever we make our max speed.
    how_far = abs(desired_angle - total_angle);

	// Calculate inertial allowance.
	if(how_far < 60) inertia_allowance = 5;
	if(how_far < 30) inertia_allowance = 3;
	if(how_far < 10) inertia_allowance = 0.5;

	// clockwise arc, so right turns slower:
	if(total_angle < desired_angle) {
		// clockwise arc, and increasing total_angle, so right turns slower:
		while(total_angle < desired_angle - inertia_allowance) {
			motor[left_drive] = power;
			motor[right_drive] = power * inside_ratio;
			wait1Msec(10);
		}
	} else {
        // ccw arc, decreasing total angle
        while(total_angle > desired_angle + inertia_allowance) {
            motor[left_drive] =  power * inside_ratio;
            motor[right_drive] = power;
            wait1Msec(10);
        }
    }
}

void BackwardsArcToAngle(float power, float inside_ratio, float desired_angle) {
	float how_far;
	float inertia_allowance = 10;
	power = power * (MAX_SPEED * 0.01);  // Scale to whatever we make our max speed.
    how_far = abs(desired_angle - total_angle);

	// Calculate inertial allowance.
	if(how_far < 60) inertia_allowance = 5;
	if(how_far < 30) inertia_allowance = 3;
	if(how_far < 10) inertia_allowance = 0;

	// clockwise arc, so right turns slower:
	if(total_angle < desired_angle) {
		// Go backwards with increasing total angle, so left turns slower:
		while(total_angle < desired_angle - inertia_allowance) {
			motor[left_drive] = -power * inside_ratio;
			motor[right_drive] = -power;
			wait1Msec(10);
		}
	} else {
        // ccw arc, decreasing total angle
        while(total_angle > desired_angle + inertia_allowance) {
            motor[left_drive] =  -power;
            motor[right_drive] = -power * inside_ratio;
            wait1Msec(10);
        }
    }
}

// This does not stop-- it wlll return with the motorts running
// so as to pivot.  So, stop after if that is what you want to do.
void pivotToTotalAngle(float desired_angle) {
    float how_far;
    float current_speed = MAX_SPEED * 0.5;
    float inertia_allowance = 10;
    how_far = abs(desired_angle - total_angle);

    // Calculate inertial allowance.
    if(how_far < 60) inertia_allowance = 5;
    if(how_far < 30) inertia_allowance = 3;
    if(how_far < 10) inertia_allowance = 0;

    if(desired_angle > total_angle) {
        // Pivot clockwise, so total angle is increasing:
        while(total_angle < (desired_angle - inertia_allowance)) {
            how_far = abs(desired_angle - total_angle);
            if(how_far < 30.0) current_speed = MAX_SPEED * 0.03;
            if(how_far < 60.0) current_speed = MAX_SPEED * 0.1;
            motor[left_drive] = current_speed;
            motor[right_drive] = -current_speed;
            wait1Msec(10);
        }
    } else {
        while(total_angle > (desired_angle + inertia_allowance)) {
            how_far = abs(desired_angle - total_angle);
            if(how_far < 30.0) current_speed = MAX_SPEED * 0.03;
            if(how_far < 60.0) current_speed = MAX_SPEED * 0.1;
            motor[left_drive] = -current_speed;
            motor[right_drive] = current_speed;
            wait1Msec(10);
        }
    }
}

void pivotDegrees(float input) {
    float desired = 0;
    desired = total_angle + input;
    pivotToTotalAngle(desired);
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
