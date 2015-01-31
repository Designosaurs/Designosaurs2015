float elbowPos;
float wristPos;
float lift_inches;
bool liftStopped;
int drivePower = 100;
// 0=Floor, 1 = HiGoal, 2 = CenterGoal
int LiftPos = 0;
int pwrLift;
int left_encoder = 0;
int right_encoder = 0;
int prev_left_encoder = 0;
int prev_right_encoder = 0;
bool run_harvester = false;
bool harv_back_jog = false;

float total_angle = 0;
long left_distance_counts = 0;
long right_distance_counts = 0;
float total_distance_feet = 0;
long left_trip_counts = 0;
long right_trip_counts = 0;
float trip_distance_feet = 0;
int DetectObstacles = 0;
