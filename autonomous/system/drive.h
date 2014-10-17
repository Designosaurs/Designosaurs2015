void goForwardTime(float seconds, int power) {
    motor[left_drive] = power * LEFT_TRIM;
    motor[right_drive] = power * RIGHT_TRIM;
    last_power = power;
    wait1Msec(seconds * 1000);
}

void ResetTrip( void ) {
	left_trip_counts = 0;
	right_trip_counts = 0;
	trip_distance_feet = 0;
	}


int DebugCnt = 0;
void goForwardDistance(float feet, float power) {
	float feedback;  // A ratio, so 0.9 means apply 90% power.
	float start_angle;
	float angle_error;
	float error_integration;
	float error_value;

    float left_power, right_power;
		power = power * (MAX_SPEED * 0.01);
    start_angle = total_angle;

    while(trip_distance_feet < feet) {
    		// Error calculation:
        angle_error = total_angle - start_angle;
        error_integration += 0.01 * angle_error;
        error_value = angle_error + error_integration;
        left_power = power;
        right_power = power;
        // Cut the power 10% for every degree it is off.
        feedback = 1 - (0.1 * abs(error_value));
        // But not less than this much power:
        if (feedback < 0.6) feedback = 0.6;

         //Write debugging information if needed:
        if ( ++DebugCnt > 30)  {
    				writeDebugStreamLine("---");
         		writeDebugStream("Angle: %3.2f",(float) total_angle);
        		writeDebugStreamLine("  Angle err: %3.2f",(float) angle_error);
        		writeDebugStreamLine("L enc: %d",left_encoder);
         		writeDebugStreamLine("Feedback: %1.2f", feedback);
        		writeDebugStream(" R Drive: %1.2f", motor[right_drive]);
        		writeDebugStreamLine(" L Drive: %1.2f", motor[left_drive]);
        		DebugCnt = 0;
      	}
        // If it is veering right, decrease the left motor power.
        if(error_value > 0) {
            left_power = feedback * left_power;
        } else {
            right_power = feedback * right_power;  // feedback is negative value.
        }
        motor[left_drive] = left_power * LEFT_TRIM;
        motor[right_drive] = right_power * RIGHT_TRIM;
        wait1Msec(20);

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
