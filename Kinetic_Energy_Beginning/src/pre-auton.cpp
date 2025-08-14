#include "vex.h"

void pre_auton(void) {
    vexcodeInit();
    Drivetrain.setDriveVelocity(100, pct);
    selectable();
  }