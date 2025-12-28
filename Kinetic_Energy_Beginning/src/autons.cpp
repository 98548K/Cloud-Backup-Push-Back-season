#include "vex.h"

double beginHeading;
double beginX;
double beginY;


int readDescore() {
    while (enabledComp) {
        wait (0.4, sec);
        DescorePiston.set(true);
        wait (0.5, sec);
        break;
    }
    DescorePiston.set(false);
    return 0;
}


int readGPS1() {
    while (true) {
        setDrivePosition(offsetGPS1X, offsetGPS1Y);
        wait (25, msec);
    }
    return 0;
}

int readGPS2() {
    while (true) {
        setDrivePosition(offsetGPS2X, offsetGPS2Y);
        wait (25, msec);
    }
    return 0;
}

vex::directionType returnDir;

vex::directionType wrapEnd(double closestX, double closestY) {
    
    if (validateHeading(((atan2(closestX - X, closestY - Y) * (180 / M_PI)) - Inertial1.heading(deg))) > 90 && validateHeading(((atan2(closestX - X, closestY - Y) * (180 / M_PI)) - Inertial1.heading(deg))) < 270) {
        returnDir = reverse;
    }
    else {
        returnDir = fwd;
    }
    return returnDir;
}


task runGPS1 = task(readGPS1);

task runGPS2 = task(readGPS2);


//"runGPS1.resume();" will set the odometry to track the GPS 1 offset readings
//"runGPS2.resume();" will set the odometry to track the GPS 2 offset readings

void Left() {
    runGPS1.suspend();
    runGPS2.suspend();
    longDrive();
    longTurn();
    //Heading: 263
    //X: 55
    //Y: -22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 50, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(36.7, 10);
    turnToHeading(135);
    driveIn(-13.6, 1.5);
    //Second part
    BackIntake.stop();
    driveIn(55);
    intakeFill();
    turnToHeading(90);
    driveIn(15, 1.65);
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
    runGPS1.suspend();
    runGPS2.suspend();
    longDrive();
    longTurn();
    //Heading: 277
    //X: 55
    //Y: 22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(27, 5);
    wait (0.5, sec);
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
    turnToHeading(45);
    driveIn(55);
    intakeFill();
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(13, 1.65);
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

void Skills() {
    runGPS1.suspend();
    runGPS2.suspend();
    shortDrive();
    shortTurn();
    //Heading: 149
    //X: -55
    //Y: -24
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.stop();
    //Deploys piston and lines up next to the matchloader
    DescorePiston.set(true);
    driveIn(30.5);
    //Turns toward the matchloader
    wait (0.25, sec);
    longDrive();
    //Drives into the matchloader
    shortTurn();
    turnKD = 1.65;
    turnToHeading(270);
    shortTurn();
    driveIn(17.5, 2.3);
    MiddleIntake.spin(fwd, 50, pct);
    shortDrive();
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(315);
    driveIn(-17.5, 1.5);
    turnToHeading(270);
    Wing.set(true);
    longDrive();
    driveIntegralLimit = 35;
    kD = 3.0;
    driveIn(-80);
    shortDrive();
    turnToHeading(0);
    driveIn(11);
    turnToHeading(90);
    driveIn(-22, 1.5);
    TopIntakePiston.set(true);
    Inertial1.setHeading(90, deg);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.15, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    BackIntake.stop();
    longDrive();
    BackIntake.spin(reverse, 3, pct);
    driveIn(30, 3);
    turnToHeading(90, 1);
    MiddleIntake.stop();
    BackIntake.stop();
    shortDrive();
    driveIn(-30, 1.5);
    runGPS2.resume();
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.15, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    BackIntake.stop();
    runGPS2.suspend();
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    //
    BackIntake.stop();
    driveIn(15);
    shortTurn();
    turnKP = 0.4;
    turnToHeading(0);
    shortTurn();
    longDrive();
    driveIntegralLimit = 60;
    driveIn(92);
    shortDrive();
    shortTurn();
    turnKP = 0.4;
    turnToHeading(90);
    shortTurn();
    FrontIntake.spin(fwd, 100, pct);
    DescorePiston.set(true);
    longDrive();
    driveIn(24, 3);
    MiddleIntake.spin(fwd, 100, pct);
    shortDrive();
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(135);
    driveIn(-20, 1.5);
    turnToHeading(90);
    Wing.set(true);
    longDrive();
    kP = 2.2;
    driveIntegralLimit = 25;
    driveIn(-80);
    shortDrive();
    turnToHeading(180);
    driveIn(11);
    turnToHeading(270);
    driveIn(-22, 1.5);
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.15, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    BackIntake.stop();
    longDrive();
    BackIntake.spin(reverse, 3, pct);
    driveIn(34, 3);
    turnToHeading(270, 1);
    MiddleIntake.stop();
    BackIntake.stop();
    shortDrive();
    driveIn(-30, 1.5);
    runGPS2.resume();
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.15, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    BackIntake.stop();
    runGPS2.suspend();
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    runGPS2.resume();
    curveToPosition(-48, 30);
    task runDescore = task(readDescore);
    curveToPosition(-60, 0);
    runDescore.suspend();
    runGPS2.suspend();
}

void Bad_Skills() {
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}