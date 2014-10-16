task UpdateEncoderTask() {
    while(true) {
        left_encoder = nMotorEncoder[left_drive];
        right_encoder = nMotorEncoder[right_drive];

        left_distance_counts += (int) (left_encoder - prev_left_encoder);
        right_distance_counts += (int) (right_encoder - prev_right_encoder);

        total_distance_feet = (float) ((left_distance_counts + right_distance_counts) / COUNTS_PER_FOOT) / 2;

        delta = (left_distance_counts - right_distance_counts);

        total_angle = (float) delta / COUNTS_PER_DEGREE;

        prev_left_encoder = left_encoder;
        prev_right_encoder = right_encoder;
        wait1Msec(20);
    }
}