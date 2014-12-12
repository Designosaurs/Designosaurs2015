long prev_lift_encoder = 0;
long lift_counts = 0;
const float LIFT_COUNTS_PER_INCH = 1000;

task LiftEncoderTask() {
	while(true) {
		long enc_speed, lift_encoder;
		bool bad_reading = false;

		lift_encoder = nMotorEncoder[lift];
		// Detect bad encoder readings.   If the encoder has changed wildly from the previous reading, it is
		// a bad reading and should be ignored. The hardware does this once in awhile, and it is okay to
		// just ignore this and use the next one.
		enc_speed = abs( lift_encoder - prev_lift_encoder);
		if(enc_speed > 1000) {
			bad_reading = true;
		}

		if(!bad_reading) {
			// Accumulate
			lift_counts += (int) (lift_encoder - prev_lift_encoder);
			prev_lift_encoder = lift_encoder;
			lift_inches = (float) lift_counts / LIFT_COUNTS_PER_INCH;
		}

		wait1Msec(10);
	}
}
