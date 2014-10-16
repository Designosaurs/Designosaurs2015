task DebugTask {
    while(true) {
        writeDebugStreamLine("Left encoder is currently at (feet): %1.2f", total_distance_feet);
        wait1Msec(1000);
    }
}