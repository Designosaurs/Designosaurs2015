const float LIFT_COUNTS_PER_INCH = 127;  // Approximate.  Find experimenatally.
long prev_lift_encoder = 0;
	long lift_enc_speed;

task UpdateLiftEncoderTask() {

	while(true) {
		long lift_encoder;
		bool bad_reading = false;

		/*
		 * Detect bad encoder readings. If the encoder has changed wildly from the previous reading, it is
		 * a bad reading and should be ignored. The hardware does this once in awhile, and it is okay to
		 * just ignore this and use the next one.
		 */

		lift_encoder = nMotorEncoder[lift];
		lift_enc_speed = abs(lift_encoder - prev_lift_encoder);
		prev_lift_encoder = lift_encoder;

		if(lift_enc_speed > 1000) bad_reading = true;
		if(lift_enc_speed < 5) liftStopped = true;
		else liftStopped = false;

		if(!bad_reading) {
			lift_inches = (float) lift_encoder / LIFT_COUNTS_PER_INCH;
		}
		wait1Msec(20);
	}
}
