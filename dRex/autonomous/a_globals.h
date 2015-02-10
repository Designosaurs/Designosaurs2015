float elbowPos;
float wristPos;
float lift_inches;
long left_encoder = 0;
long right_encoder = 0;
long prev_left_encoder = 0;
long prev_right_encoder = 0;
int DetectObstacles = 0;
bool liftStopped;

float total_angle = 0;
long left_distance_counts = 0;
long right_distance_counts = 0;
float total_distance_feet = 0;
long left_trip_counts = 0;
long right_trip_counts = 0;
float trip_distance_feet = 0;

bool run_harvester = false;
int LiftPos = 0;
bool harv_back_jog = false;
float angle_before_ir = 0;
