task UpdateEncoderTask() {
    while(true) {
        left_encoder = nMotorEncoder[left_drive];
        right_encoder = nMotorEncoder[right_drive];

        total_distance_counts += (int) ((left_encoder - prev_left_encoder) + (right_encoder - prev_right_encoder)) / 2;
        total_distance_feet = (float) distance_counts / COUNTS_PER_FOOT;

        prev_left_encoder = left_encoder;
        prev_right_encoder = right_encoder;
        wait1Msec(20);
    }
}