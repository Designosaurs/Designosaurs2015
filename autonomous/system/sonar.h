// Drive foward slowly to a range passed in cm.
// Note that this has a stop, because you usually will want to.
void goToRange(int range) {
	while(SensorValue[ultrasonic] > range) {
		motor[left_drive] = 5;
		motor[right_drive] = 5;
		wait1Msec(10);
	}
	stop();
}

// How far in degrees to scan, left and right, when searching (double for total range)
const float SCAN_RANGE = 30.0;
const float SCAN_INCREMENT = 0.1;
const int SCAN_DELAY = 20;


bool LocalMin(){
	int prev_range = 255;
	int returned_range = 255;
	int low_so_far = 255;
	bool getting_better = false;
	bool past_best = false;
	float start_angle = total_angle;
	float best_angle = total_angle;

	// Take an initial reading, which our best so far.
	prev_range = (int) SensorValue[ultrasonic];
	low_so_far = prev_range;

	// Try pivoting right:
	while(!past_best) {
		pivotDegrees(SCAN_INCREMENT);
		stop();
		wait10Msec( SCAN_DELAY );
		returned_range = (int) SensorValue[ultrasonic];
		// If we ever get the same reading after a pivot, we are close enough.
		// if (returned_range == prev_range) return true;
		if (returned_range < low_so_far ) {
			low_so_far = returned_range;
			best_angle = total_angle;
			getting_better = true;
		}
		if( returned_range > low_so_far) {
			past_best = true;
		}
		writeDebugStreamLine(" -------------------------");
		writeDebugStream("Trip: %3.1f ft ", trip_distance_feet);
    writeDebugStreamLine("Range: %d", SensorValue[ultrasonic]);
		writeDebugStreamLine("turn right.  low ao far:  %d ", low_so_far);

	}

	// If at any time during our right turn it was getting better, we have a new best.
	if (getting_better) {
		pivotToTotalAngle( best_angle );
		stop();
		return true;
	}

	// Turning right did not help.  So, go back to the start angle:
	pivotToTotalAngle( start_angle );
	stop();
	past_best = false;
	prev_range = (int) SensorValue[ultrasonic];
	best_angle = start_angle;
	low_so_far = prev_range;

	// Try turning left:
	while(!past_best) {
		pivotDegrees(-SCAN_INCREMENT);
		stop();
		wait10Msec( SCAN_DELAY );
		returned_range = (int) SensorValue[ultrasonic];
		// If we ever get the same reading after a pivot, we are close enough.
		// if (returned_range == prev_range) return true;
		if (returned_range < low_so_far ) {
			low_so_far = returned_range;
			best_angle = total_angle;
			getting_better = true;
		}
		if( returned_range > low_so_far) {
			past_best = true;
		}
		writeDebugStreamLine(" -------------------------");
		writeDebugStream("Trip: %3.1f ft ", trip_distance_feet);
    writeDebugStreamLine("Range: %d", SensorValue[ultrasonic]);
		writeDebugStreamLine("turn left. low ao far:  %d ", low_so_far);
	}

	pivotToTotalAngle( best_angle );
	stop();
	return true;

}


// Angle values within this are absolute, or total angle.
// Although, it will scan about a range from wherever it happens to be pointing.
// If close enough is passed, it will stop whenever it sees only a small change between
// two successive reads, figuring that is close enough.  If it cannot get such a reading
// it will run the whole scan, and point to the closest.
bool pointToNearest( bool close_enough ) {
	int lowest_cm = 255;
	float min_degree = 0;
	float start_angle = total_angle - SCAN_RANGE;
	float stop_angle = total_angle + SCAN_RANGE;
	int returned_range =255;
	int prev_range = 255;
	bool found_something;

	// Start pointing to the start ange of the scan.
	pivotToTotalAngle( start_angle);
	stop();

	while( total_angle < stop_angle ) {
		wait1Msec( SCAN_DELAY );
		returned_range = (int) SensorValue[ultrasonic];
		if( returned_range < 40) {
			found_something = true;
			if ((prev_range == returned_range) && close_enough) {
				return true;
			}
			prev_range = returned_range;
		}
		if( returned_range < lowest_cm) {
			lowest_cm = returned_range;
			min_degree = total_angle;
			writeDebugStreamLine(" -------------------------");
			writeDebugStreamLine("lowest cm: %3d ", min_degree);
			writeDebugStream("Trip: %3.1f ft ", trip_distance_feet);
      writeDebugStreamLine("Range: %d", SensorValue[ultrasonic]);

		}

		pivotDegrees(SCAN_INCREMENT);
		stop();
	}

	//writeDebugStreamLine("Min Angle: %3.2f", min_degree);
	//writeDebugStreamLine("lowest cm: %d ", lowest_cm);
	//while(true) wait1Msec(50);

	pivotToTotalAngle( min_degree);
	stop();

	return found_something;
}



void CreepToGoal( ) {
	int returned_range = 255;
	float jog_dist;

	// If the sensor is out of range find it.
	returned_range = (int) SensorValue[ultrasonic];
	if(returned_range > 60) pointToNearest( true );

	raiseBall();
	// Point to goal:
	LocalMin();

	// Go to within 30
  returned_range = (int) SensorValue[ultrasonic];
  if (returned_range > 31) {
  	jog_dist = ( float )returned_range - 30;
  	writeDebugStreamLine("***** Jog 1 dist %3.2f", jog_dist);
  	jogForwardCm( jog_dist );
	}

  // Point to goal
  LocalMin();

  // Go to withing 15
  returned_range = (int) SensorValue[ultrasonic];
  jog_dist = ( float )returned_range - 15;
  writeDebugStreamLine("******* Jog  2 dist %3.2f", jog_dist);
  jogForwardCm( jog_dist );

  // Point to goal
  LocalMin();

  // If needed jog forward again to get to 15 cm
  returned_range = (int) SensorValue[ultrasonic];
  if (returned_range > 20) {
  	jog_dist = ( float )returned_range - 18;
  	writeDebugStreamLine("***** Jog 3 dist %3.2f", jog_dist);
  	jogForwardCm( jog_dist );
  	LocalMin();
	}

	//PlaySound(soundDownwardTones);
   //wait10Msec( 100 );
   placeBall();

}
