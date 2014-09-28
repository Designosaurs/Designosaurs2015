task DebugTask {
    while(true) {
        writeDebugStreamLine("Left encoder is currently at (feet): %d", distance_feet);
        wait1Msec(1000);
    }
}