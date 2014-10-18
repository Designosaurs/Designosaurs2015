void goToRange(int range) {
    while(SensorValue[ultrasonic] > range) {
        motor[left_drive] = 5;
        motor[right_drive] = 5;
        wait1Msec(10);
    }
    stop();
}

int pointToNearest(int scan_range) {
    int lowest_value_cm = 255;
    int at_degree = 0;
    int x;
    for(x = 1; x < scan_range; x++) {
        pivotDegrees(1);
        if(SensorValue[ultrasonic] < lowest_value_cm) {
            lowest_value_cm = SensorValue[ultrasonic];
            at_degree = x;
        }
    }

    pivotDegrees(-scan_range);
    for(x = -1; x > -scan_range; x--) {
        pivotDegrees(-1);
        if(SensorValue[ultrasonic] < lowest_value_cm) {
            lowest_value_cm = SensorValue[ultrasonic];
            at_degree = x;
        }
    }

    pivotDegrees(scan_range);
    pivotDegrees(at_degree);
    return lowest_value_cm;
}

void goToTube() {
    while(SensorValue[ultrasonic] > TARGET_DISTANCE) {
        writeDebugStreamLine("%d", SensorValue[ultrasonic]);
        int lowest_value_cm = pointToNearest(SCAN_RANGE);
        stop();
        motor[left_drive] = DRIVE_POWER;
        motor[right_drive] = DRIVE_POWER;
        if(lowest_value_cm > 60) {
            wait1Msec(600);
        } else if(lowest_value_cm > 40) {
            wait1Msec(500);
        } else if(lowest_value_cm > 30) {
            wait1Msec(400);
        } else if(lowest_value_cm > 20) {
            wait1Msec(300);
        } else {
            wait1Msec(200);
        }

        stop();
    }
    motor[left_drive] = -DRIVE_POWER;
    motor[right_drive] = -DRIVE_POWER;
    wait1Msec(250);
    stop();
    pointToNearest(RESCAN_1);
    pointToNearest(RESCAN_2);
    stop();
    placeBall();
}
