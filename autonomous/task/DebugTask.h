task DebugTask {
    while(true) {
        nxtDisplayBigStringAt(4,60,"6369");
        nxtDisplayStringAt(20,42,"Designosaurs");

        nxtDisplayCenteredTextLine(5,"L enc: %d",left_encoder);
        nxtDisplayCenteredTextLine(6,"R enc: %d",right_encoder);
        wait1Msec(1000);
    }
}