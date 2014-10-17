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

int DebugCnt = 30;
void goDistance(float feet, float power, bool forward) {
		float feedback;  // A ratio, so 0.9 means apply 90% power.
		float start_angle;
		float angle_error;
		float error_integration = 0;
		float error_value;
    float left_power, right_power;
    float direction = 1.00;
		power = power * (MAX_SPEED * 0.01);  // Scale to whatever we make our max speed.
    start_angle = total_angle;
    if (!forward) direction = -1.00;

    while(abs(trip_distance_feet) < feet) {
        left_power = power * direction;
        right_power = power * direction;

    		// Error calculation:
        angle_error = total_angle - start_angle;
        error_integration += 0.01 * angle_error;
        // The integration term makes the steady state error to near zero, but it
        // is a destabilizing influence.
        error_value = angle_error + 1.0 * error_integration;
        // Cut the power 10% for every degree it is off.
        feedback = 1 - (0.1 * abs(error_value));
        // But not less than this much power:
        if (feedback < 0.5) feedback = 0.5;

         //Write debugging information if needed:
        if ( ++DebugCnt > 30)  {
    				writeDebugStreamLine("---");
         		writeDebugStream("Angle: %3.1f",(float) total_angle);
        		writeDebugStream("  Angle err: %3.1f",(float) angle_error);
        		writeDebugStreamLine("  Angle int: %3.1f", error_integration );
        		writeDebugStream("R enc: %d", right_encoder);
        		writeDebugStreamLine(" L enc: %d",left_encoder);
         		writeDebugStreamLine("Feedback: %1.2f", feedback);
        		writeDebugStream(" R Drive: %1.0f", motor[right_drive]);
        		writeDebugStreamLine(" L Drive: %1.0f", motor[left_drive]);
        		DebugCnt = 0;
      	}
        // If it is veering right, decrease the left motor power.
        if(error_value * direction > 0) {
            left_power = feedback * left_power;
        } else {
            right_power = feedback * right_power;  // feedback is negative value.
        }
        motor[left_drive] = left_power * LEFT_TRIM;
        motor[right_drive] = right_power * RIGHT_TRIM;
        wait1Msec(20);

    }
}

void goForwardDistance(float feet, float power ) {
	goDistance(feet, power, true );
	}

// Give this positive 2 feet to go backward two feet:
void goBackwardDistance(float feet, int power) {
  goDistance(feet, power, false );
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
            wait1Msec(20);
        }
    } else {
        while(total_angle > (desired_angle + INTERTIAL_DEGREES)) {
            how_far = abs(desired_angle - total_angle);
            if (how_far < 20.0) {
                current_speed = MAX_SPEED * 0.1;
            }
            motor[left_drive] = -current_speed;
            motor[right_drive] = current_speed;
           	wait1Msec(20);
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
