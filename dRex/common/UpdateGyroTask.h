task Gyro() {
	float GyroPeriodS;
	long ET;

	while(true) {
		ET = time1[T1];
		GyroPeriodS = (float) ET /1000;
		time1[T1]=0;  // Reset timer.
		rotSpeed = HTGYROreadRot(HTGYRO);
		heading += rotSpeed * GyroPeriodS;
		wait10Msec(1);
	}
}