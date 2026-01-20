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

vex::directionType wrapDir(double closestX, double closestY) {
    
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
    //Heading: 243
    //X: 55
    //Y: -22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(28, 11);
    wait (0.5, sec);
    turnToHeading(135);
    driveIn(32.5);
    intakeFill();
    turnToHeading(90);
    driveIn(16, 2);
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
    wait (2, sec);
    DescorePiston.set(false);
    driveIn(5);
    TopIntakePiston.set(false);
    driveIn(-15);
}


void Right() {
    runGPS1.suspend();
    runGPS2.suspend();
    //Heading: 295
    //X: 55
    //Y: 22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(23.5, 10.25);
    wait (0.5, sec);
    turnToHeading(218);
    DescorePiston.set(false);
    BottomIntakePiston.set(true);
    driveIn(20, 1.5);
    FrontIntake.spin(reverse, 75, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1.25, sec);
    driveIn(-12);
    BottomIntakePiston.set(false);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    turnToHeading(40);
    driveIn(28.5);
    intakeFill();
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(16, 1.4);
    driveIn(-34, 2);
    TopIntakePiston.set(true);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (1, sec);
}


void New_Right() {
    runGPS1.suspend();
    runGPS2.suspend();
    //Heading: 294
    //X: 55
    //Y: 22
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(42);
    turnToHeading(367);
    MiddleIntake.stop();
    driveIn(10, 1);
    DescorePiston.set(true);
    driveIn(-10);
}

void Skills() {
    runGPS1.suspend();
    runGPS2.suspend();
    //Heading: 149
    //X: -55
    //Y: -24
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.stop();
    //Deploys piston and lines up next to the matchloader
    DescorePiston.set(true);
    driveIn(28.5);
    //Turns toward the matchloader
    wait (0.25, sec);
    //Drives into the matchloader
    turnToHeading(270, 1);
    setDriveConstants(2.4, 0.01, 3.3);
    driveIn(16.5, 2.3);
    setDriveConstants(2.7, 0.01, 3.3);
    MiddleIntake.spin(fwd, 50, pct);
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(300);
    driveIn(-23.5, 1.5);
    turnToHeading(268.5);
    Wing.set(true);
    //Drive between goal and wall
    driveIn(-75);
    turnToHeading(0);
    driveIn(9.5);
    turnToHeading(90);
    driveIn(-38, 1.5);
    setDrivePosition(35.5, -41);
    Inertial1.setHeading(90, deg);
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    MiddleIntake.spin(reverse, 100, pct);
    wait (0.15, sec);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    BackIntake.stop();
    TopIntakePiston.set(false);
    BackIntake.spin(reverse, 3, pct);
    driveIn(2);
    turnToHeading(86);
    setDriveConstants(2.3, 0.01, 3.3);
    driveIn(31.5, 3);
    setDriveConstants(2.7, 0.01, 3.3);
    turnToHeading(86, 1);
    MiddleIntake.stop();
    BackIntake.stop();
    TopIntakePiston.set(true);
    driveIn(-38, 1.5);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (0.85, sec);
    MiddleIntake.spin(reverse, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (0.15, sec);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (1, sec);
    BackIntake.stop();
    driveIn(3);
    TopIntakePiston.set(false);
    driveIn(-3, 1.5);
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    //
    BackIntake.stop();
    driveIn(13);
    setTurnConstants(0.4, 0.01, 0.79);
    driveToPosition(51, 51, fwd);
    setTurnConstants(0.4085, 0.01, 0.79);
    turnToHeading(90);
    FrontIntake.spin(fwd, 100, pct);
    DescorePiston.set(true);
    setDriveConstants(2.3, 0.01, 3.3);
    driveIn(22, 3);
    setDriveConstants(2.7, 0.01, 3.3);
    MiddleIntake.spin(fwd, 100, pct);
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(120);
    driveIn(-24.5, 1.5);
    turnToHeading(90);
    Wing.set(true);
    driveIn(-75);
    turnToHeading(180);
    driveIn(9.5);
    turnToHeading(270);
    driveIn(-28, 1.5);
    Inertial1.setHeading(270, deg);
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
    BackIntake.spin(reverse, 3, pct);
    driveIn(2);
    TopIntakePiston.set(false);
    turnToHeading(266);
    driveIn(29, 3);
    turnToHeading(266, 1);
    MiddleIntake.stop();
    BackIntake.stop();
    driveIn(-30, 1.5);
    TopIntakePiston.set(true);
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
    driveIn(3);
    TopIntakePiston.set(false);
    driveIn(-3, 1);
    runGPS2.suspend();
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    driveIn(6);
    turnToHeading(235);
    driveIn(28.5);
    turnToHeading(200);
    runGPS2.resume();
    task runDescore = task(readDescore);
    trackingWheelPiston.set(true);
    curveToPosition(-60, 0);
    runDescore.suspend();
    runGPS2.suspend();
}

void Bad_Skills() {
    trackingWheelPiston.set(true);
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}