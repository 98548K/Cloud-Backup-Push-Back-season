#include "vex.h"

void pre_auton(void) {
    vexcodeInit();
    Intakes.setVelocity(100, pct);
    Claw.setVelocity(100, pct);
    Drivetrain.setDriveVelocity(100, pct);
    selectable();
  }