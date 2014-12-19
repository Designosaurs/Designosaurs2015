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
   nMotorEncoder[right_drive] = 0;
	nMotorEncoder[left_drive]=0;
	nMotorEncoder[lift]=0;
	nMotorEncoder[harvester] = 0;
}
