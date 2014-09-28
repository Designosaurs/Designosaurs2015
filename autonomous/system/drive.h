void goForwardTime(float seconds, int power) {

}

void goForwardDistance(float feet, int power) {

}

void goBackwardTime(float seconds, int power) {

}

void goBackwardDistance(float feet, int power) {

}

void accel(int to_speed) {
    for (int i = 0; i < to_speed; i = i + 0.2 * to_speed) {
        goForwardTime(0.1, i);
    }
}

void decel(int to_speed) {
    for (int i = avg_speed; i < to_speed; i = i - 0.2 * to_speed) {
        goForwardTime(0.1, i);
    }
}