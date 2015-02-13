int getClosestRange(){
    int i;
    int range = 255;
    for (i = 0; i<5; i++) {
        if((SensorValue[ultrasonic]) < range) {
            range = SensorValue[ultrasonic];
        }
        wait10Msec(5);
    }
    return range;
}
