task main() {
    placerInit();
    //waitForStart();

    bMotorReflected[left_drive] = true;

    nMotorEncoder[right_drive] = 0;
    nMotorEncoder[left_drive] = 0;

    StartTask(DebugTask);
    StartTask(UpdateEncoderTask);

    //goForwardTime( 4, 40);
    //accel(0,100);
    goForwardDistance(6,80);
    accel(80,0);
    //goForwardDistance(6,50);

    stop();
while( 1 );
    placeBall();
}
