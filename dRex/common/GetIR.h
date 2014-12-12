
// Show each of the sensor readings.
void GetIR( void )
{
	// read the current modulated signal direction
	dirAC = HTIRS2readACDir(HTIRS2);

	// Read the individual signal strengths of the internal sensors
	HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 );

	PeakIR = acS1;
	if (acS2 > PeakIR) PeakIR = acS2;
	if (acS3 > PeakIR) PeakIR = acS3;
	if (acS4 > PeakIR) PeakIR = acS4;
	if (acS5 > PeakIR) PeakIR = acS5;

	// Compute Center6 -- a value that will be zero when running straight down the middle,
	// Positive when slightly to the right.
	// Limited to +/- 10
	Center6 = acS4 - acS3;
	if (Center6 > 10) Center6 = 10;
	if (Center6 < -10) Center6 = -10;
}
