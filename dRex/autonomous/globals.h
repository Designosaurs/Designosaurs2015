float elbowPos;
float wristPos;
float lift_inches;
int left_encoder = 0;
int right_encoder = 0;
int prev_left_encoder = 0;
int prev_right_encoder = 0;

float total_angle = 0;
long left_distance_counts = 0;
long right_distance_counts = 0;
float total_distance_feet = 0;
long left_trip_counts = 0;
long right_trip_counts = 0;
float trip_distance_feet = 0;

const int MAX_SPEED = 100;
const int COUNTS_PER_FOOT = 1834;
const float COUNTS_PER_DEGREE = 35.4;

// If it veers left, use a smaller value here
const float LEFT_ENC_COMP = 0.97;
