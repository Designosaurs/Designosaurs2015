task DebugTask {
    while(true) {
        nxtDisplayBigStringAt(4,60,"6369");
        nxtDisplayStringAt(20,42,"Designosaurs");
        nxtDisplayTextLine(4, "Angle: %1.2f", total_angle);


        //writeDebugStreamLine("Feedback: %1.2f", feedback);
        //writeDebugStream(" R Drive: %1.2f", motor[right_drive]);
        //writeDebugStreamLine(" L Drive: %1.2f", motor[left_drive]);
        //writeDebugStreamLine("---");
        //writeDebugStreamLine("L enc: %d",left_encoder);
        //writeDebugStreamLine("R enc: %d",right_encoder);
        //writeDebugStreamLine("Delta: %d", delta);
        //writeDebugStreamLine("Angle: %3.2f",(float) total_angle);
        //writeDebugStreamLine("Angle err: %3.2f",(float) angle_error);
        wait1Msec(500);
    }
}
