task DebugTask {
    while(true) {
        nxtDisplayBigStringAt(4,60,"6369");
        nxtDisplayStringAt(20,42,"Designosaurs");
        nxtDisplayTextLine(4, "Angle: %3.2f deg", total_angle);
        nxtDisplayTextLine(5, "Trip: %3.1f ft", trip_distance_feet);
				writeDebugStream("Trip: %3.1f ft ", trip_distance_feet);
        //writeDebugStreamLine("---");
        //writeDebugStreamLine("L enc: %d",left_encoder);
        //writeDebugStreamLine("R enc: %d",right_encoder);
        //writeDebugStreamLine("Delta: %d", delta);
        writeDebugStreamLine("Angle: %3.2f",(float) total_angle);
        //writeDebugStreamLine("Angle err: %3.2f",(float) angle_error);
        wait1Msec(500);
    }
}
