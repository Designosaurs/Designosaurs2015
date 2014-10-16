int last_power = 0;

int left_encoder = 0;
int right_encoder = 0;
int prev_left_encoder = 0;
int prev_right_encoder = 0;

long left_distance_counts = 0;
long right_distance_counts = 0;
float total_distance_feet = 0;

long delta = 0;
float total_angle = 0;


// Stop this many degrees early, because you will over-rotate by that much.
const int INTERTIAL_DEGREES = 1;