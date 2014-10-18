void goToTube() {
    while(SensorValue[ultrasonic] > TARGET_DISTANCE) {
        int highest_value_cm = 0;
        int at_degree = 0;
        int x;
        for(x = 1; x < 20; x++ ) {
            pivotDegrees(1);
            if(SensorValue[ultrasonic] > highest_value_cm) {
                highest_value_cm = SensorValue[ultrasonic];
                at_degree = x;
            }
        }
        pivotDegrees(-20);
        for(x = -1; x > -20; x++ ) {
            pivotDegrees(-1);
            if(SensorValue[ultrasonic] > highest_value_cm) {
                highest_value_cm = SensorValue[ultrasonic];
                at_degree = x;
            }
        }
        pivotDegrees(20);
        pivotDegrees(at_degree);
        highest_value_cm = 0;
        x = 0;
        at_degree = 0;
        motor[left_drive] = 20;
        motor[right_drive] = 20;
        wait1Msec(500);
        stop();
    }
    stop();
    placeBall();
    wait1Msec(2000);
}