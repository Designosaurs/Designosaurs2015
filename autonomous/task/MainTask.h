task main() {
    placerInit();
    //waitForStart();

    bMotorReflected[right_drive] = true;

    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    pivotToTotalAngle(-90);
}
