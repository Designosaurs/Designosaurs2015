float elbowPos;
float wristPos;
float lift_inches;
int left_encoder = 0;
int right_encoder = 0;
int prev_left_encoder = 0;
int prev_right_encoder = 0;
int DetectObstacles = 0;
bool liftStopped;

float total_angle = 0;
long left_distance_counts = 0;
long right_distance_counts = 0;
float total_distance_feet = 0;
long left_trip_counts = 0;
long right_trip_counts = 0;
float trip_distance_feet = 0;
