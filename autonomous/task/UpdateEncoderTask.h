

// Angle compensation
// The encoders compute angle based on the difference between left and right values.
// The geometery is not perfectly identical, so we include a compensation factor that
// we will result in the propoer angle displayed.
// If it veers left on a straight command, this value should be slighlty less than 1.00.
#define LEFT_ENC_COMP 0.960

task UpdateEncoderTask() {
    while(true) {
    		float delta = 0;

        left_encoder = nMotorEncoder[left_drive];
        right_encoder = nMotorEncoder[right_drive];

        // Odometer
        left_distance_counts += (int) (left_encoder - prev_left_encoder);
        right_distance_counts += (int) (right_encoder - prev_right_encoder);
        total_distance_feet = (float) ((left_distance_counts + right_distance_counts) / COUNTS_PER_FOOT) / 2;

        // Trip odometer
				left_trip_counts += (int) (left_encoder - prev_left_encoder);
    		right_trip_counts += (int) (right_encoder - prev_right_encoder);
				trip_distance_feet = (float) ((left_distance_counts + right_distance_counts) / COUNTS_PER_FOOT) / 2;

        // Angle calculation
        delta = (LEFT_ENC_COMP * (float) left_distance_counts - (float) right_distance_counts);
        total_angle = (float) delta / COUNTS_PER_DEGREE;

        prev_left_encoder = left_encoder;
        prev_right_encoder = right_encoder;
        wait1Msec(20);
    }
}
