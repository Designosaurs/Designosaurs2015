void movementTrace(float angle_error, float error_integration, float feedback) {
    if(++debugCnt > 10) {
    	writeDebugStreamLine("---");
      	writeDebugStream("Angle: %3.1f",(float) total_angle);
     	writeDebugStream("  Angle err: %3.1f",(float) angle_error);
     	writeDebugStreamLine("  Angle int: %3.1f", error_integration);
     	writeDebugStream("R enc: %d", right_encoder);
     	writeDebugStreamLine(" L enc: %d",left_encoder);
      	writeDebugStreamLine("Feedback: %1.2f", feedback);
     	writeDebugStream(" R Drive: %1.0f", motor[right_drive]);
     	writeDebugStreamLine(" L Drive: %1.0f", motor[left_drive]);
     	debugCnt = 0;
    }
}
