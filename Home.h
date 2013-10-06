/*
|----\             
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/

#define HOMING_SPEED 30

void HomeArm( void )
{
	servo[Claw] = CLAW_CLOSED;
	VectorJoy = false;
	StopArm();
	ResetStall();
	if (Beeps) PlaySound(soundBlip);
	MoveSwivel( SWIVEL_HOME );
	MoveWrist( WRIST_HOME  );

	while(1)
	{
		Executor();
		if(joystick.joy1_TopHat == 6)
		{
			StopArm();
			return;
		}
		motor[ Elbow ] = HOMING_SPEED;
		if (Stalled[1] == 1)
		{
			if (Beeps) PlaySound(soundBlip);
			motor[ Elbow ] = 0;
			HomeAxisRead[1] = RelAxisPos[ 1 ];
			break;
		}
	}
	ResetStall();
	while(1)
	{
		Executor();
		if(joystick.joy1_TopHat == 6)
		{
			StopArm();
			return;
		}
		motor[ Shoulder ] = -HOMING_SPEED;
		if (Stalled[0] == 1)
		{
			if (Beeps) PlaySound(soundBlip);
			motor[ Shoulder ] = 0;
			HomeAxisRead[0] = RelAxisPos[ 0 ];
			break;
		}
	}
	ArmState = HOME;
}
