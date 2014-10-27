typedef struct {
    bool wait;
    bool stopped;
    bool running;
} systemStateForm;

systemStateForm systemState;

typedef struct {
    bool TOP;
    bool LEFT;
    bool RIGHT;
    bool BOTTOM;
    bool BOTTOM_LEFT;
    bool BOTTOM_RIGHT;
    bool TOP_LEFT;
    bool TOP_RIGHT;
} dpadForm;

dpadForm dpad;

const int STATE_WAIT = 1;
const int STATE_RUN = 2;
const int STATE_STOP = 3;

int PWR_LEFT = 0;
int PWR_RIGHT = 0;

const int DEADBAND = 15;