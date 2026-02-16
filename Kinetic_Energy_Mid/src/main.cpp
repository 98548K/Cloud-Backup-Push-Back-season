#include "vex.h"
using namespace vex;
competition Competition;


bool valid;

bool enabledComp() {
  if (Competition.isEnabled()) valid = true;
  else if (!Competition.isEnabled()) valid = false;

  return valid;
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  task odomTask = task(positionTracking);
  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
