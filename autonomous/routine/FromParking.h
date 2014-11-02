task main() {
    float angle_before_goal;

    placerInit();
    goalGrabberUp();

    // waitForStart();

    bMotorReflected[left_drive] = true;
    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);


    stop();
}
