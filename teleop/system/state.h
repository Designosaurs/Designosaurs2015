#include "globals.h"

task UpdateDisplayTask();

void onWait() {
    bMotorReflected[right_drive] = true;

    nMotorEncoder[right_drive] = 0;

    disableDiagnosticsDisplay();
    bNxtLCDStatusDisplay = false;

    eraseDisplay();
    nxtDisplayBigStringAt(4,60,"6369");
    nxtDisplayStringAt(20,42,"Designosaurs");

    nxtDisplayCenteredTextLine(5,"Waiting for");
    nxtDisplayCenteredTextLine(6,"connection.");
    StartTask(UpdateDisplayTask);
}

void onStop() {

}

void onRun() {
    eraseDisplay();
    nxtDisplayBigStringAt(4,60,"6369");
    nxtDisplayStringAt(20,42,"Designosaurs");

    nxtDisplayCenteredTextLine(5,"Running.");
}

void switchState(int newState) {
    systemState.wait = false;
    systemState.running = false;
    systemState.stopped = false;

    switch(newState) {
        case STATE_WAIT:
            systemState.wait = true;
            onWait();
            break;
        case STATE_RUN:
            systemState.running = true;
            onRun();
            break;
        case STATE_STOP:
            systemState.stopped = true;
            onStop();
            break;
    }

    StartTask(UpdateDisplayTask);
}