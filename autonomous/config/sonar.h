/*
* ====================================
* Ultrasonic Tube Finder Configuration
* ====================================
*/

// How far the ultrasonic sensor should be away from the tube in centimeters
const int TARGET_DISTANCE = 26;
// How far in degrees to scan, left and right, when searching (double for total range)
const int SCAN_RANGE = 30;
// How fast to move.
const int DRIVE_POWER = 20;
// After we're within the target distance, how far to rescan the first time (in degrees, double for total range).
const int RESCAN_1 = 20;
// How far to rescan the second time (in degrees).
const int RESCAN_2 = 15;