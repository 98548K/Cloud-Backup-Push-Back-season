#include "vex.h"

double beginHeading;
double beginX;
double beginY;

void Left() {
    //Heading: 263
    //X: 55
    //Y: -22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 50, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(36, 10);
    turnToHeading(135);
    driveIn(-14, 1.5);
    BackIntake.spin(fwd, 50, pct);
    wait (0.5, sec);
    //Second part
    BackIntake.stop();
    driveToPosition(47.2, -45.6, fwd);
    intakeFill();
    turnToHeading(90);
    driveIn(18.5, 1);
    driveIn(-34, 2);
    TopIntakePiston.set(true);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.25, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.25, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.25, sec);
    MiddleIntake.spin(fwd, 100, pct);
}


void Right() {
    //Heading: 277
    //X: 55
    //Y: 22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(38.5, 20);
    turnToHeading(224);
    DescorePiston.set(false);
    BottomIntakePiston.set(true);
    driveIn(20, 1.5);
    FrontIntake.spin(reverse, 75, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    driveIn(-12);
    BottomIntakePiston.set(false);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    driveToPosition(40.2, 50.6, reverse);
    intakeFill();
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(10, 1.65);
    driveIn(-34, 2);
    TopIntakePiston.set(true);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.125, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.125, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.125, sec);
    MiddleIntake.spin(fwd, 100, pct);
}

void Skills() {
    //Heading: 327
    //X: 50
    //Y: 23.5
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.stop();
    DescorePiston.set(true);
    driveIn(24.5);
    turnToHeading(90);
    wait (0.25, sec);
    driveIn(15, 4);
    MiddleIntake.spin(fwd, 25, pct);
    driveIn(-6);
    turnToHeading(125);
    driveIn(-21);
    Wing.set(true);
    FrontIntake.spin(fwd, 100, pct);
    turnToHeading(90);
    tracePath({20, 10, 0, -10, -20, -30, -40}, {60, 60, 60, 60, 60, 60, 60});
    turnToHeading(180);
    driveIn(8.5);
    turnToHeading(270);
    /*setDrivePosition(offsetGPS1X, offsetGPS1Y, GPS1.heading());
    wait (10, sec);
    driveToPosition(29.5, -50, reverse);*/
    driveIn(-20, 2);
    TopIntakePiston.set(true);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (3, sec);
    BackIntake.stop();
    driveIn(28, 4);
    MiddleIntake.stop();
    FrontIntake.stop();
    BackIntake.stop();
    driveIn(-30, 3);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (2, sec);
    driveIn(20);
    turnToHeading(180);
    Wing.set(false);
    DescorePiston.set(false);
    tracePath({-40,-30,-20,-10,0,10,20,30,40,43,47}, {60,60,60,60,60,60,60,60,55,50,40});
    turnToHeading(170);
    driveIn(30, 2);
}

void Bad_Skills() {
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}