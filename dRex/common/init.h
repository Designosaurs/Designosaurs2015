void initDisplay() {
    disableDiagnosticsDisplay();
    bNxtLCDStatusDisplay = false;
    eraseDisplay();
    nxtDisplayBigStringAt(4,60,"6369");
    nxtDisplayStringAt(20,42,"Designosaurs");
    nxtDisplayCenteredTextLine(5,"Waiting for");
    nxtDisplayCenteredTextLine(6,"Start");
}

void initDriveConfig() {
    bMotorReflected[left_drive] = true;
    nMotorEncoder[right_drive] = 0;
}