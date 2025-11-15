#include "vex.h"

double beginHeading;

void Left() {
    //Heading: 263
    //X: 55
    //Y: -22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 50, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(38.5);
    turnToHeading(135);
    driveIn(-12.5, 2);
    BackIntake.spin(fwd, 50, pct);
    driveIn(1);
    wait (0.5, sec);
    //Second part
    turnToHeading(140);
    BackIntake.stop();
    DescorePiston.set(true);
    driveIn(44.25);
    intakeFill();
    turnToHeading(90);
    driveIn(18, 2.2);
    driveIn(-34, 2);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.5, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.5, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.5, sec);
    MiddleIntake.spin(fwd, 100, pct);
}


void Right() {
    //Heading: 277
    //X: 55
    //Y: 22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 50, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(36);
    turnToHeading(224);
    IntakePiston.set(true);
    driveIn(20, 2);
    FrontIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    FrontIntake.spin(reverse, 100, pct);
    wait (2, sec);
    driveIn(-12);
    IntakePiston.set(false);
    //Second part
    turnToHeading(44);
    DescorePiston.set(true);
    driveIn(33);
    intakeFill();
    turnToHeading(90);
    driveIn(16, 2.2);
    driveIn(-34, 2);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.5, sec);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
}

void Skills() {
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    Drivetrain.setDriveVelocity(35, pct);
    Drivetrain.driveFor(90, inches, false);
    wait (5, sec);
    Drivetrain.setDriveVelocity(10, pct);
    Drivetrain.driveFor(reverse, 60, inches);
}

void Bad_Skills() {
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}