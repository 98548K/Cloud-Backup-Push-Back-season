#include "vex.h"

void pre_auton(void) {
    vexcodeInit();
    Drivetrain.setDriveVelocity(100, pct);
    BorderControl.setLightPower(25, pct);
    runGPS1.suspend();
    runGPS2.suspend();
    //selectable();
  }