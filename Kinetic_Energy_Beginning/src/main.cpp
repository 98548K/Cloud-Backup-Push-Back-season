#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    7, 3, 5, 2, 10  
// Intakes              motor_group   18, 1           
// Claw                 motor         12              
// ringOptical          optical       19              
// Clamp                digital_out   H               
// Teeth                digital_out   G               
// Doinker              digital_out   F               
// colorSort            digital_out   A               
// frontTracking        rotation      14              
// sideTracking         rotation      20              
// clawTracking         rotation      11              
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

competition Competition;



int main() {
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  //task odomTask = task(positionTracking);


  pre_auton();

  
  while (true) {
    wait(100, msec);
  }
}
