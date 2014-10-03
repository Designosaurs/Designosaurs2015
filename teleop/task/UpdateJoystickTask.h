#include "../system/globals.h"

task UpdateJoystickTask() {
    while(true) {
        getJoystickSettings(joystick);
        int y1 = joystick.joy1_y1;
        int y2 = joystick.joy1_y2;
        int x1 = joystick.joy1_x1;
        int x2 = joystick.joy1_x2;

        int PWR_LEFT = (0.78 * y1) * (DRIVE_POWER / 100);
        int PWR_RIGHT = (0.78 * y2) * (DRIVE_POWER / 100);

        motor[left_drive] = PWR_LEFT;
        motor[right_drive] = PWR_LEFT;

        if(!joy1_TopHat == -1) {
            switch(joy1_TopHat) {
                case 0:
                    dpad.TOP = true;
                break;
                case 1:
                    dpad.TOP_RIGHT = true;
                break;
                case 2:
                    dpad.RIGHT = true;
                break;
                case 3:
                    dpad.BOTTOM_RIGHT = true;
                break;
                case 4:
                    dpad.BOTTOM = true;
                break;
                case 5:
                    dpad.BOTTOM_LEFT = true;
                break;
                case 6:
                    dpad.LEFT = true;
                break;
                case 7:
                    dpad.TOP_LEFT = true;
                break;
            }
        } else {
            dpad.TOP = false;
            dpad.LEFT = false;
            dpad.RIGHT = false;
            dpad.BOTTOM = false;
            dpad.BOTTOM_LEFT = false;
            dpad.BOTTOM_RIGHT = false;
            dpad.TOP_LEFT = false;
            dpad.TOP_RIGHT = false;
        }

        wait1Msec(50);
    }
}