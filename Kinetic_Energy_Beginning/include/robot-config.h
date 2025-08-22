using namespace vex;

extern brain Brain;

extern controller Controller1;
extern drivetrain Drivetrain;
extern motor_group Intakes;
extern motor IntakesMotorA;
extern motor IntakesMotorB;
extern motor Claw;
extern optical ringOptical;
//extern optical goalOptical;
extern limit limitSwitch;
extern digital_out Clamp;
extern digital_out Teeth;
extern digital_out Doinker;
extern digital_out colorSort;
extern rotation frontTracking;
extern rotation sideTracking;
extern rotation clawTracking;
//if necessary add these in
extern inertial Inertial1;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;

void  vexcodeInit( void );