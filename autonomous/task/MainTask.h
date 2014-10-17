task main() {
    placerInit();
    //waitForStart();

    bMotorReflected[left_drive] = true;

    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);


    // goForwardTime( 4, -80);

    //accel(0,80);
    //goForwardDistance(6,80);
    //accel(80,0);


    //accel(0,-80);
    goBackwardDistance(6,80);
    accel(-80,0);

    stop();
while( 1 );
    placeBall();
}
