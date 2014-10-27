void processDpad() {
    if(dpad.LEFT) {
        goalGrabberDown();
    }
    if(dpad.RIGHT) {
        goalGrabberUp();
    }
}