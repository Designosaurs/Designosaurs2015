typedef struct {
    bool wait;
    bool stopped;
    bool running;
} systemStateForm;

systemStateForm systemState;

const int STATE_WAIT = 1;
const int STATE_RUN = 2;
const int STATE_STOP = 3;

int PWR_LEFT = 0;
int PWR_RIGHT = 0;