using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
//extern motor_group B_Intake;
extern motor LIB;
extern motor RIB;
extern motor TIB;

extern digital_out IntakePiston;
extern digital_out DescorePiston;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );