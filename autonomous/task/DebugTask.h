task DebugTask {
    while(true) {
        nxtDisplayBigStringAt(4,60,"6369");
        nxtDisplayStringAt(20,42,"Designosaurs");

        writeDebugStreamLine("---");
        writeDebugStreamLine("L enc: %d",left_encoder);
        writeDebugStreamLine("R enc: %d",right_encoder);
        writeDebugStreamLine("Delta: %d", delta);
        writeDebugStreamLine("Angle: %1.2f",(float) total_angle);
        wait1Msec(500);
    }
}