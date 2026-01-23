#include "vex.h"


double beginHeading;
double beginX;
double beginY;


bool hasEntered = false;

int parkJerk() {
    while (true) {
        if (Inertial1.yaw(deg) > 20) {
            hasEntered = true;
        }
        else if (hasEntered == true && Inertial1.yaw(deg) <= 2) {
            Drivetrain.stop(brake);
            hasEntered = false;
        }
        wait (25, msec);
    }
}


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
    chassis.driveWithPiston(28, 11);
    wait (0.5, sec);
    chassis.turnToHeading(135);
    chassis.drive(32.5);
    intakeFill();
    chassis.turnToHeading(90);
    chassis.drive(16, 2);
    chassis.drive(-34, 2);
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
    chassis.drive(5);
    TopIntakePiston.set(false);
    chassis.drive(-15);
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
    chassis.driveWithPiston(23.5, 10.25);
    wait (0.5, sec);
    chassis.turnToHeading(218);
    DescorePiston.set(false);
    BottomIntakePiston.set(true);
    chassis.drive(20, 1.5);
    FrontIntake.spin(reverse, 75, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1.25, sec);
    chassis.drive(-12);
    BottomIntakePiston.set(false);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    chassis.turnToHeading(40);
    chassis.drive(28.5);
    intakeFill();
    chassis.turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    chassis.drive(16, 1.4);
    chassis.drive(-34, 2);
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
    chassis.drive(42);
    chassis.turnToHeading(367);
    MiddleIntake.stop();
    chassis.drive(10, 1);
    DescorePiston.set(true);
    chassis.drive(-10);
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
    chassis.drive(28.5);
    //Turns toward the matchloader
    wait (0.25, sec);
    //Drives into the matchloader
    chassis.turnToHeading(270, 1);
    chassis.drive(16.5, 2.3);
    MiddleIntake.spin(fwd, 50, pct);
    chassis.drive(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    chassis.turnToHeading(300);
    chassis.drive(-23.5, 1.5);
    chassis.turnToHeading(268.5);
    Wing.set(true);
    //Drive between goal and wall
    chassis.drive(-75);
    chassis.turnToHeading(0);
    chassis.drive(9.5);
    chassis.turnToHeading(90);
    chassis.drive(-38, 1.5);
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
    chassis.drive(2);
    chassis.turnToHeading(86);
    chassis.drive(31.5, 3);
    chassis.turnToHeading(86, 1);
    MiddleIntake.stop();
    BackIntake.stop();
    TopIntakePiston.set(true);
    chassis.drive(-38, 1.5);
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
    chassis.drive(3);
    TopIntakePiston.set(false);
    chassis.drive(-3, 1.5);
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    //
    BackIntake.stop();
    chassis.drive(13);
    driveToPosition(51, 51, fwd);
    chassis.turnToHeading(90);
    FrontIntake.spin(fwd, 100, pct);
    DescorePiston.set(true);
    chassis.drive(22, 3);
    MiddleIntake.spin(fwd, 100, pct);
    chassis.drive(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    chassis.turnToHeading(120);
    chassis.drive(-24.5, 1.5);
    chassis.turnToHeading(90);
    Wing.set(true);
    chassis.drive(-75);
    chassis.turnToHeading(180);
    chassis.drive(9.5);
    chassis.turnToHeading(270);
    chassis.drive(-28, 1.5);
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
    chassis.drive(2);
    TopIntakePiston.set(false);
    chassis.turnToHeading(266);
    chassis.drive(29, 3);
    chassis.turnToHeading(266, 1);
    MiddleIntake.stop();
    BackIntake.stop();
    chassis.drive(-30, 1.5);
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
    chassis.drive(3);
    TopIntakePiston.set(false);
    chassis.drive(-3, 1);
    runGPS2.suspend();
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    chassis.drive(6);
    chassis.turnToHeading(235);
    chassis.drive(28.5);
    chassis.turnToHeading(200);
    task stopInParkZone = task(parkJerk);
    LeftDriveSmart.spin(fwd, 100, pct);
    RightDriveSmart.spin(fwd, 100, pct);
    stopInParkZone.suspend();
}

void Bad_Skills() {
    trackingWheelPiston.set(true);
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}