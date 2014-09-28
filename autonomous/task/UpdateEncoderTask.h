task UpdateEncoderTask() {
    while(true) {
        left_encoder = nMotorEncoder[right_drive];

        distance_counts += (left_encoder - prev_left_encoder);
        distance_feet = (float) distance_counts / COUNTS_PER_FOOT;

        prev_left_encoder = left_encoder;
        wait1Msec(20);
    }
}