task main() {
    waitForStart();

    StartTask(UpdateEncoderTask);

    while (true) {
        accel(0,100);
        wait1Msec(3000);
        accel(100,0);
        wait1Msec(6000);
    }
}