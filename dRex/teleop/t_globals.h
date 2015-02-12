float elbowPos;
float wristPos;
float lift_inches;
bool liftStopped;
const int DEADBAND = 12;
int drivePower = 100;
// 0=Floor, 1 = HiGoal, 2 = CenterGoal
int LiftPos = 0;
int pwrLift;
const int GUNNER_DEADBAND = 30;
bool run_harvester = false;
bool harv_back_jog = false;
int dirAC = 0;
int PeakIR = 0;
