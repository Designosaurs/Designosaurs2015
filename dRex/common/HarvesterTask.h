long harv_encoder = 0;
long harv_mod_cnts;
int harv_deg;
int prev_harv_deg = 0;
//int harvstate = 0;
bool harv_flag = true;

void updateHarvDeg() {
	harv_encoder = nMotorEncoder[harvester];
	harv_mod_cnts = harv_encoder % 1440;
	harv_deg = harv_mod_cnts / 4;
	if (harv_deg < prev_harv_deg) harv_flag = true;  // stet on zero crossing.
	prev_harv_deg = harv_deg;

}

task HarvesterTask{
	int harv_error;
	while( true )
	{
		updateHarvDeg();
		if (run_harvester == true) {
			motor[harvester] = 50;
			harv_flag = false;
		}
		else
		{
			if(harv_back_jog) {
				motor[harvester] = -20;
				wait1Msec(200);
				updateHarvDeg();
				while(harv_deg > 60) {
					updateHarvDeg();
					motor[harvester] = -20;
				}
				harv_back_jog = false;
			}
			if  (!harv_flag)
				motor[harvester] = 20;
			else {
				if (harv_deg > 180)	{
					harv_error = harv_deg - 360;
				}
				else {
					harv_error = harv_deg;
				}

				motor[harvester] = -harv_error;
			}
			wait1Msec( 20 );
		}
	}
}
