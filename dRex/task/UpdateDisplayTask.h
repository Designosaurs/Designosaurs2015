task UpdateDisplayTask() {
	while( true ) {
		nxtDisplayTextLine(0, "6369 DESIGNOSARUS");
		nxtDisplayTextLine(1, "Lift: %3.2f""", lift_inches);
		nxtDisplayTextLine(2, "Elbow: %d", servo[elbow]);
		nxtDisplayTextLine(3, "Wrist: %d", servo[ wrist ]);

		//		nxtDisplayTextLine(4, "Angle: %3.2f deg", total_angle);
		//nxtDisplayTextLine(5, "Trip: %3.1f ft", trip_distance_feet);
		//nxtDisplayTextLine(6, "Range: %d", SensorValue[ultrasonic]);
		wait1Msec( 100 );
	}
}
