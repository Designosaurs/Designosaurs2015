task UpdateDisplayTask() {
	while( true ) {
		nxtDisplayTextLine(0, "6369 DESIGNOSARUS");
		if (liftStopped) nxtDisplayTextLine(1, "Lift: %3.2f""  STOP", lift_inches);
		else nxtDisplayTextLine(1, "Lift: %3.2f"" RUN", lift_inches);
		nxtDisplayTextLine(2, "Elbow: %d", servo[elbow]);
		nxtDisplayTextLine(3, "Wrist: %d", servo[ wrist ]);
		nxtDisplayTextLine(4, "Range: %d", SensorValue[ultrasonic]);


#ifdef READS_DRIVE_ENCODERS
		nxtDisplayTextLine(5, "Total Ft: %3.1f", total_distance_feet );
		nxtDisplayTextLine(6, "Angle: %3.1f", total_angle );
#endif

#ifdef HAS_IR
		nxtDisplayTextLine(7, "IR: %d DIR: %d ", PeakIR, dirAC);
#endif
		wait1Msec( 200 );
	}
}
