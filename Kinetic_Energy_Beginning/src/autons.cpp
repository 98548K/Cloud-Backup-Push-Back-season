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
    driveToPosition(40.2, -50.6, fwd);
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
    driveToPosition(45.2, 40.6, reverse);
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
    /*//Heading: 149
    //X: -55
    //Y: -24
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.stop();
    //Deploys piston and lines up next to the matchloader
    DescorePiston.set(true);
    driveIn(26);
    //Turns toward the matchloader
    wait (0.25, sec);
    longDrive();
    //Drives into the matchloader
    driveToPosition(-60, -47, fwd, 3);
    MiddleIntake.spin(fwd, 50, pct);
    shortDrive();
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    driveToPosition(-26, -62, reverse);
    Wing.set(true);
    turnToHeading(270);
    tracePath({-20, -10, 0, 10, 20, 30, 40}, {-62, -62, -62, -62, -62, -62, -62});
    driveToPosition(40, -50, fwd);
    turnToHeading(90);
    driveIn(-22, 2);
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 50, pct);
    wait (1, sec);
    BackIntake.stop();
    longDrive();
    BackIntake.spin(reverse, 3, pct);
    driveIn(29, 3);
    turnToHeading(90, 1);
    MiddleIntake.stop();
    BackIntake.stop();
    shortDrive();
    driveIn(-30, 3);
    runGPS2.resume();
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    BackIntake.stop();
    runGPS2.suspend();
    DescorePiston.set(false);*/
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    //
    BackIntake.stop();
    curveToPosition(58, -24);
    task runDescore = task(readDescore);
    curveToPosition(62, -12);
    runGPS2.resume();
    trackingWheelPiston.set(true);
    tracePath({62, 58}, {30, 32});
    runGPS2.suspend();
    runDescore.suspend();
    setDrivePosition(offsetGPS2X, offsetGPS2Y);
    wait (1, sec);
    trackingWheelPiston.set(false);
    turnToHeading(315);
    curveToPosition(46.5, 72, 2);
    wait (1, sec);
    shortDrive();
    driveToPosition(46.5, 58, reverse);
    turnToHeading(90);
    driveIn(-20, 2);
    runGPS1.resume();
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    BackIntake.stop();
    runGPS1.suspend();
    DescorePiston.set(true);
    longDrive();
    driveIn(32, 3);
    shortDrive();
    driveIn(-28, 3);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    BackIntake.stop();
}

void Bad_Skills() {
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}