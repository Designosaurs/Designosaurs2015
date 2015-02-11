/*
* Angle compensation
* The encoders compute angle based on the difference between left and right values.
* The geometry is not perfectly identical, so we include a compensation factor that
* we will result in the proper angle displayed.
* If it veers left on a straight command, this value should be slightly less than 1.00.
*/

task UpdateDriveBearingsTask() {
	while(true) {
		float delta = 0;
		long enc_speed;
		bool bad_reading = false;

		left_encoder = nMotorEncoder[left_drive];
		right_encoder = nMotorEncoder[right_drive];

		/*
		 * Detect bad encoder readings. If the encoder has changed wildly from the previous reading, it is
		 * a bad reading and should be ignored. The hardware does this once in awhile, and it is okay to
		 * just ignore this and use the next one.
		 */

		enc_speed = abs(left_encoder - prev_left_encoder);
		enc_speed += abs(right_encoder - prev_right_encoder);
		if(enc_speed > 1000) bad_reading = true;

		if(!bad_reading) {
			// Odometer
			left_distance_counts += (int) (left_encoder - prev_left_encoder);
			right_distance_counts += (int) (right_encoder - prev_right_encoder);
			total_distance_feet =  ((float) left_distance_counts + (float) right_distance_counts) / (COUNTS_PER_FOOT * 2);

			// Trip odometer
			left_trip_counts += (int) (left_encoder - prev_left_encoder);
			right_trip_counts += (int) (right_encoder - prev_right_encoder);
			trip_distance_feet =  ((float)left_trip_counts + (float)right_trip_counts) / (COUNTS_PER_FOOT * 2);

			// Angle calculation
			delta = (LEFT_ENC_COMP * (float) left_distance_counts - (float) right_distance_counts);
			total_angle = (float) delta / COUNTS_PER_DEGREE;
			//total_angle= 6;

			prev_left_encoder = left_encoder;
			prev_right_encoder = right_encoder;



		}
		else {
			PlaySound(soundException);
	}


		wait1Msec(10);
	}
}
