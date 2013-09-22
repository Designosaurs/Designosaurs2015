/*
|----\             
|    | /--\ /--- - /--\ /--\ /--\ /--- /--\ |  | |-- /---
|    | |--/ \--\ | \--| |  | |  | \--\ |  | |  | |   \--\
|----/ \__  ---/ | __/  |  | \--/ ---/ \--\ \--\ |   ---/  Team 6369
*/

// Put global variables here,
// unless they are used ONLY in a single file.


// Define Shoulder, Elbow, wrist
typedef enum
{
	SHOULDER,
	ELBOW,
} TAxisN;

bool Beeps = true;

int EncRead[ ] = { 0, 0 };				// Direct reading of encoder, in counts.
int PriorEncRead[ ] = { 0, 0 };		// Prior direct reading, for speed determination.

int RelAxisPos[ ] = { 0, 0 };  		// In degrees relative to whatever the wake position is.
int HomeAxisRead[ ] = {0, 0 }; 		// In degrees, what the encoder reading is at home.
																	// If the wake up is at home, this is at zero.
int AxisPos[ ] = { 0, 0 };   			// In degrees, absolute, relative to straight up.

int AxisSpeed[ ]= { 0, 0 }; 		 	// In encoder counts per 50 mS.
int StallCount[ ] = {0, 0};				// For detecting stall
int Stalled[ ] = {0, 0};

int AxisSigns[ ] = {1, 1 };  			// For motor movement.


tMotor AxisMotors[ ] = { Shoulder, Elbow };

// Positions of the axis at the HOME position.
// This is the amount we should take off of the relative positions to
// get absolute.
// If you change the mechanical stop limits, these are the constants you change.
#define SHOULDER_HOME -147
// To adjust--
// Wake up in home, or start from home.
// If shoulder is too far forward, take a little off of this:
#define ELBOW_HOME 129

bool VectorJoy = false;  // Wakes up in manual mode.

bool Joy1Drive = false;  // Set means Joy1 is the driver.
// Happens if Joy1 pressed down on Joysticks.

bool Joy1HiGear = true;   // The gear requested by Joy1
bool Joy2HiGear = true;		// The gear requested by Joy2
bool UsingHiGear = true;  // The Gear we are actually using.

bool MoveTimedout = false;

////////////////////   SERVOS ///////////////////////////////////////
float fWristSpeed = 0;
float fWristPosDeg = 0;

#define WRIST_HOME 0  // In degress
#define WRIST_INIT_COUNTS  180 // Direct value to send to servo.

#define SWIVEL_HOME 90  // In degrees
#define SWIVEL_INIT_COUNTS 10

#define SWIVEL_CENTERED 0
#define CLAW_OPEN 255
#define CLAW_CLOSED 40


float fSwivelSpeed = 0;
float fSwivelPosDeg;

//the joystick must be above (or below) this value for anything to happen.
//Prevents the joystick being a little off from causing havoc.
#define JOY_DEADBAND 10

////////////////////////////////////  STATES ///////////////////////////////////////////////
typedef enum TypeArmState
{
	MANUAL = 0,
	HOME = 1,
	TRAVEL = 2,
	FRONT1 = 3,
	FRONT2 = 4,
	FRONT3 = 5,
		FRONT_FLOOR = 6,
	RINGDISP = 7,
	BACK_FLOOR = 8,
	STRAIGHT_UP = 9,
	QUICK_HOME = 10,
	RINGSPILL = 11,
	UNDEFINED = 12
} TypeArmState;

TypeArmState ArmState;
TypeArmState ReqArmState;
