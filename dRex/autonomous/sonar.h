// Drive forward slowly to a range passed in cm.
// Note that this has a stop, because you usually will want to.
void goToRange(int range, int power) {
	while(SensorValue[ultrasonic] > range) {
		motor[left_drive] = power;
		motor[right_drive] = power;
		wait1Msec(10);
	}
	stop();
}

// How far in degrees to scan, left and right, when searching (double for total range)
const float SCAN_RANGE = 30.0;
const int SCAN_DELAY = 12;
const int SCAN_SPEED = 10; // Any faster and it misses because lag for sensor is too high.

bool pointToGoal() {
	int low_so_far = 255;
	int start_of_low = 255;
	int end_of_low = 255;
	float best_aim_angle = total_angle;
	float angle_at_low_start = total_angle;
	float angle_at_low_end = total_angle;
	float angle_before_low_start = total_angle;
	float start_angle = total_angle - SCAN_RANGE;
	float stop_angle = total_angle + SCAN_RANGE;
	int returned_range = 255;
	int Points = 0;
	bool have_low = false;
	bool stop_scan = false;

	// Start pointing to the start ange of the scan.
	pivotToTotalAngle(start_angle, 80);
	stop();

	// Make the scan
	returned_range = (int) SensorValue[ultrasonic];
	low_so_far = returned_range;
	angle_before_low_start =  total_angle;
	while(!stop_scan) {
		motor[right_drive] = -SCAN_SPEED;
		motor[left_drive] = SCAN_SPEED;
		wait10Msec( SCAN_DELAY );
		returned_range = (int) SensorValue[ultrasonic];
		Points++;
		writeDebugStreamLine(" -------------------------");
		writeDebugStream("Points: %d ", Points );
		writeDebugStream("Angle: %3.2f ",(float) total_angle);
		writeDebugStreamLine("Range: %d", SensorValue[ultrasonic]);
		if (returned_range < 50) {
			// Look for a new low.  When we find one, update the angle before low.
			if (returned_range < 16 ){
				writeDebugStreamLine("Something is too close.");
				PlaySound(soundDownwardTones);
				stopAndWait();
				stop_scan = true;
			}


			if (returned_range < low_so_far ) {
				low_so_far = returned_range;
				angle_before_low_start = total_angle;
				start_of_low = total_angle;
				have_low = true;
				angle_at_low_start = total_angle;
				writeDebugStreamLine("New Low");
			}

			// Record each repeated low, for one will be the last one:
			if (have_low && (returned_range == low_so_far)) {
				end_of_low = total_angle;
				have_low = true;
				angle_at_low_end = total_angle;
				writeDebugStreamLine("Repeated Low");
			}
			// If we have had a new low, look for coming off the low.
			// add one for noise rejection.
			// If we do, stop the scan;
			if (have_low && (returned_range > low_so_far + 1)) {
				stop_scan = true;
			}
			// If it never finds goal, stop.
			if(total_angle > stop_angle) {
				writeDebugStreamLine("Could not find goal.  Stopping.");
				PlaySound(soundDownwardTones);
				stopAndWait();
				stop_scan = true;
			}
		}
	}
	stop();
	wait10Msec(5);
	best_aim_angle = (angle_at_low_start + angle_at_low_end) / 2.0;
	writeDebugStreamLine("Angle at low start: %3.1f", angle_at_low_start);
	writeDebugStreamLine("Angle at low end: %3.1f", angle_at_low_end);
	writeDebugStreamLine("Best Aim Angle: %3.1f", best_aim_angle);

	// Add or subtract to best aim angle experimentally, so it hits
	// straight on.
	pivotToTotalAngle(best_aim_angle + 2, 30);
	stop();
	//stopAndWait();
	return have_low;
}


// Routine to place in 2' goal.
// Robot nominally starts at 8-10" from ultrasonic sensor to tube. Works as close as 6".
// Ultrasonic sensor pointed straight at the tube.
// It can hande wide varation, but typically start there.

const float GOAL_PLACE_DIST = 20;  // cm from goal, indicated by ultrsonic sensor, at place

bool GoalPlacer() {
	int returned_range = 255;
	float jog_dist;

	//stopAndWait();
	pointToGoal();
	//stopAndWait();
	// First get to within defined distance, but not too close, because aim errors
	// become more significant then.
	raiseBall();
	goToRange(30, 20);

	// Now get in the last bit. Calculate based on ultrasonic reading from a bit our
	returned_range = (int) SensorValue[ultrasonic];
	jog_dist = (float) returned_range - GOAL_PLACE_DIST;
	writeDebugStreamLine("Final Jog dist %3.2f", jog_dist);
	jogForwardCm(jog_dist, 10);
	//stopAndWait();


	// Ths compensates for the fact that the placer is not centered.
	pivotDegrees(4, 25);
	placeBall();
	//stopAndWait();

	returned_range = (int) SensorValue[ultrasonic];
	writeDebugStreamLine("Range before place: %d", SensorValue[ultrasonic]);
	wait1Msec(1000); // Give some for the ball placer to work.
	initPlacer();

	// Back to pointing the goal grabber
	pivotDegrees(-16, 20);

	return true;
}
