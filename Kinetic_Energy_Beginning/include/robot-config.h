using namespace vex;

extern brain Brain;

extern controller Controller1;
extern drivetrain Drivetrain;
extern rotation frontTracking;
extern rotation sideTracking;
extern inertial Inertial1;
//If necessary add these in:
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

extern motor BackIntake;
extern motor FrontIntake;
extern motor MiddleIntake;


extern digital_out IntakePiston;
extern digital_out DescorePiston;
extern digital_out BruteForce;
extern digital_out Wing;

extern optical BorderControl;

extern bool RemoteControlCodeEnabled;

void  vexcodeInit( void );