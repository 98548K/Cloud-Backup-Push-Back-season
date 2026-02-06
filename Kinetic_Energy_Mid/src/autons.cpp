#include "vex.h"


double beginHeading;
double beginX;
double beginY;


bool hasEntered = false;


int counter = 0;


int parkJerk() {
    while (true) {
        if (Inertial1.roll(deg) <= -4) {
            hasEntered = true;


        }
        else if (hasEntered == true && Inertial1.roll(deg) > 2) {
            LeftDriveSmart.stop(coast);
            RightDriveSmart.stop(coast);
            return 0;
        }
        wait (25, msec);
    }
    return 0;
}




int runManualTimer() {
    while (true) {
        counter += 1;
        wait (1, sec);
    }
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
    setDriveConstants(3.0, 0.01, 0.0);
    setTurnConstants(0.42, 0.00027, 0.7);
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
    driveIn(16, 1.7);
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
    //X: 48
    //Y: 6
    setDriveConstants(3.0, 0.01, 0.0);
    setTurnConstants(0.42, 0.00027, 0.7);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(26, 10.25);
    wait (0.5, sec);
    turnToHeading(225);
    DescorePiston.set(false);
    BottomIntakePiston.set(true);
    driveIn(17, 1.5);
    FrontIntake.spin(reverse, 75, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1.25, sec);
    driveIn(-12);
    BottomIntakePiston.set(false);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    driveToPosition(54, 39.5, fwd);
    intakeFill();
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    setDriveConstants(2.4, 0.01, 0.0);
    driveIn(19.75, 1.15);
    setDriveConstants(3.0, 0.01, 0.0);
    turnToHeading(85, 0.6);
    driveIn(-100, 2);
    TopIntakePiston.set(true);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (1, sec);
    driveIn(5);
    TopIntakePiston.set(false);
    driveIn(-100, 1);
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
    task newTimer = task(runManualTimer);
    //Heading: 149
    //X: -55
    //Y: -24
    //Deploys piston and lines up next to the matchloader
    DescorePiston.set(true);
    setDriveConstants(3.0, 0.01, 0.0);
    driveIn(30 - 0.375);
    //Turns toward the matchloader
    wait (0.25, sec);
    //Drives into the matchloader
    turnToHeading(270, 1);
    setDriveConstants(2.0, 0.01, 0.0);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.stop();
    driveIn(17, 2.6);
    setDriveConstants(3.0, 0.01, 0.0);
    MiddleIntake.spin(fwd, 50, pct);
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(300);
    driveIn(-24.5, 1.5);
    turnToHeading(271);
    Wing.set(true);
    //Drive between goal and wall
    driveIn(-67);
    //Line up with goal
    turnToHeading(0);
    driveTolerance = 0.25;
    driveIn(10);
    driveTolerance = 0.5;
    setTurnConstants(0.4, 0.01, 0.79);
    turnToHeading(90);
    setTurnConstants(0.4075, 0.01, 0.79);
    driveIn(-38, 1.3);
    //Recalibrate Inertial
    Inertial1.setHeading(90, deg);
    //Score in long goal
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    TopIntakePiston.set(false);
    BackIntake.spin(reverse, 3, pct);
    //empty second matchloader
    driveIn(2);
    turnToHeading(88);
    setDriveConstants(3.0, 0.01, 0.0);
    driveIn(27, 2);
    turnToHeading(88, 2);
    setDriveConstants(3.0, 0.01, 0.0);
    MiddleIntake.stop();
    BackIntake.stop();
    TopIntakePiston.set(true);
    driveIn(-38, 1.8);
    //Score in long goal
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    //driveIn(5);
    TopIntakePiston.set(false);
    //driveIn(-7, 1.5);
    setDrivePosition(35.5, -41);
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    BackIntake.stop();
    //Drive across field
    driveIn(13);
    setTurnConstants(0.4, 0.01, 0.79);
    driveToPosition(54, 49, fwd);
    TopIntakePiston.set(false);
    DescorePiston.set(true);
    setTurnConstants(0.4075, 0.01, 0.79);
    turnToHeading(90);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 3, pct);
    setDriveConstants(2.0, 0.01, 3.3);
    driveIn(20.5, 3);      //Going to the Third Match Loader
    setDriveConstants(3.0, 0.01, 0.0);
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    BackIntake.stop();
    turnToHeading(120);
    driveIn(-26.5, 1.5);
    turnToHeading(93);
    Wing.set(true);
    driveIn(-65);    //Going down Alley
    turnToHeading(180);
    driveIn(9.5);
    turnToHeading(270);
    driveIn(-29, 1.5);   //To the driver side of the long goal
    Inertial1.setHeading(270, deg);
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    BackIntake.spin(reverse, 3, pct);
    TopIntakePiston.set(false);
    driveIn(2);
    turnToHeading(268);
    driveIn(28, 2.25);    //To the fourth Match loader
    MiddleIntake.stop();
    BackIntake.stop();
    driveIn(-31, 1.5);   //Back to the Long Goal
    TopIntakePiston.set(true);
    //runGPS2.resume();
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    //driveIn(5);
    TopIntakePiston.set(false);
    //driveIn(-7, 1);
    //runGPS2.suspend();
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    driveIn(6);
    turnToHeading(235);
    driveIn(28.5);
    turnToHeading(200);
    driveIn(12,.5);
    DescorePiston.set(true);
    task stopInParkZone = task(parkJerk);
    DescorePiston.set(false);
    trackingWheelPiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    LeftDriveSmart.spin(fwd, 30, pct);
    RightDriveSmart.spin(fwd, 30, pct);
}


/*
task stopInParkZone = task(parkJerk);
trackingWheelPiston.set(true);
FrontIntake.spin(fwd, 100, pct);
LeftDriveSmart.spin(fwd, 100, pct);
RightDriveSmart.spin(fwd, 100, pct);
*/


void Bad_Skills() {
    trackingWheelPiston.set(true);
    FrontIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(39, inches);
}

