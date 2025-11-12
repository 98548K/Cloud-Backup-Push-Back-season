#include "vex.h"

double beginHeading;

void Left() {
    BackIntake.stop();
    MiddleIntake.spin(fwd, 50, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(35);
    turnToHeading(135);
    driveIn(-12, 2);
    BackIntake.spin(fwd, 25, pct);
    driveIn(1);
    //Second part
    stopIntakes();
    turnToHeading(140);
    DescorePiston.set(true);
    driveIn(43);
    intakeFill();
    turnToHeading(90);
    driveIn(18, 3);
    driveIn(-34, 2);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.5, sec);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
}


void Right() {
    
}

void Skills() {
    
}

void Bad_Skills() {
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}