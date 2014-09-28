task UpdateEncoderTask() {
    left_encoder = nMotorEncoder[left_drive];

    distance_counts += (left_encoder - prev_left_encoder);
    distance_feet = distance_counts / COUNTS_PER_FOOT;

    writeDebugStreamLine("Left encoder is currently at (feet): %d",distance_feet);

    prev_left_encoder = left_encoder;
    wait1Msec(20);
}