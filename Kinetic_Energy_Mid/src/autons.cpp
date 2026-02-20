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
            DescorePiston.set(false);
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




//task runGPS1 = task(readGPS1);


//task runGPS2 = task(readGPS2);




//"runGPS1.resume();" will set the odometry to track the GPS 1 offset readings
//"runGPS2.resume();" will set the odometry to track the GPS 2 offset readings


void Left() {
    //runGPS1.suspend();
    //runGPS2.suspend();
    //setDriveConstants(3.0, 0.01, 0.0);
  //setTurnConstants(0.4075, 0.0000013, 0.79);
    //setTurnConstants(0.42, 0.0, 0.7);
    //Heading: 243
    //X: 48
    //Y: -6
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(22, 11);
    wait(0.5, sec);
    turnToHeading(135);
    driveIn(-20, 1.25);
    MiddleIntake.spin(reverse, 50, pct);
    wait(.1, sec);
    MiddleIntake.stop();
    TopIntakePiston.set(true);
    driveIn(1);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 95, pct);
    BackIntake.spin(fwd, 25, pct);
    wait(1, sec);
    TopIntakePiston.set(false);
    BackIntake.stop();
    driveToPosition(50, -37, fwd);
    turnToHeading(95);
    driveIn(16, 1.3);
    driveToPosition(32, -40, reverse, 1.5);
    
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);

    /*
    intakeFill();
    turnToHeading(90);
    driveIn(16, 1.7);
    driveIn(-34, 2);
    TopIntakePiston.set(true);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    FrontIntake.spin(fwd, 100, pct);
    DescorePiston.set(false);
    driveIn(5);
    TopIntakePiston.set(false);
    driveIn(-15);
    */
}




void Right() {
    //runGPS1.suspend();
    //runGPS2.suspend();
    //Heading: 295
    //X: 48
    //Y: 6
    //setDriveConstants(3.0, 0.0, 0.0);
    //setTurnConstants(0.42, 0.0, 0.7);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(26, 10.25);
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
    driveToPosition(53, 38, fwd);
    intakeFill();
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    //setDriveConstants(2.4, 0.01, 0.0);
    driveIn(12, 1);
    //setDriveConstants(3.0, 0.01, 0.0);
  //setTurnConstants(0.4075, 0.0000013, 0.79);
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

void Right_7_Block() {
    //runGPS1.suspend();
    //runGPS2.suspend();
    //Heading: 295
    //X: 48
    //Y: 6
    //setDriveConstants(3.0, 0.0, 0.0);
    //setTurnConstants(0.42, 0.0, 0.7);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(26, 10.25);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    driveToPosition(47, 43, fwd);
    intakeFill();
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    //setDriveConstants(2.4, 0.01, 0.0);
    driveIn(12, 1);
    //setDriveConstants(3.0, 0.01, 0.0);
  //setTurnConstants(0.4075, 0.0000013, 0.79);
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
    //runGPS1.suspend();
    //runGPS2.suspend();
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
    //runGPS1.suspend();
    //runGPS2.suspend();
    task newTimer = task(runManualTimer);
    //Heading: 149
    //X: -55
    //Y: -24
    //Deploys piston and lines up next to the matchloader
    DescorePiston.set(true);
    //setDriveConstants(3.0, 0.01, 0.0);
    //setTurnConstants(0.4075, 0.0000013, 0.79);
    driveIn(29);
    //Turns toward the matchloader
    //wait (0.25, sec);
    turnToHeading(270);
    //setDriveConstants(2.0, 0.01, 0.0);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.stop();
    driveIn(16, 2.6);//Drives into the matchloader
    //setDriveConstants(3.0, 0.01, 0.0);
    //setTurnConstants(0.4075, 0.0000013, 0.79);
    MiddleIntake.spin(fwd, 50, pct);
    driveIn(-6);//Back away from matchloader
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(300);
    //Drive away from matchloader
    driveIn(-17, 1.5);
    Wing.set(true);
    //Drive between goal and wall
    turnToHeading(275);
    driveIn(-76);
    //Line up with goal
    turnToHeading(0);
    driveTolerance = 0.25;
    driveIn(9.5);//After corridor turn
    driveTolerance = 0.5;
   ////setTurnConstants(0.4, 0.01, 0.79);
    turnToHeading(90);
    ////setTurnConstants(0.4075, 0.0000013, 0.79);
    driveIn(-38, 1.3);
    //Recalibrate Inertial
    Inertial1.setHeading(90, deg);
    //Score in long goal First Time
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1, sec);
    FrontIntake.spin(reverse, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (.1, sec);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1.25, sec);
    BackIntake.stop();
    TopIntakePiston.set(false);
    BackIntake.spin(reverse, 3, pct);
    //Empty second matchloader
    driveIn(2);//weird turn to match loader
    turnToHeading(88);
    //setDriveConstants(3.0, 0.01, 0.0);
    //setTurnConstants(0.4075, 0.0000013, 0.79);
    driveIn(27, 2);
    turnToHeading(86, 2);
    //setDriveConstants(3.0, 0.01, 0.0);
    //setTurnConstants(0.4075, 0.0000013, 0.79);
    MiddleIntake.stop();
    BackIntake.stop();
    TopIntakePiston.set(true);
    //setDriveConstants(2.25, 0.01, 0.0);
    driveIn(-38, 2);
    //setDriveConstants(3.0, 0.01, 0.0);
    //setTurnConstants(0.4075, 0.0000013, 0.79);
    //Score in long goal
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    TopIntakePiston.set(false);
    setDrivePosition(35.5, -41);
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    BackIntake.stop();
    //Drive across field
    driveIn(8);
    driveToPosition(49, 56, fwd);
    TopIntakePiston.set(false);
    DescorePiston.set(true);
    ////setTurnConstants(0.4075, 0.0000013, 0.79);
    turnToHeading(85);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 3, pct);
    //setDriveConstants(2.0, 0.01, 3.3);
    driveIn(20.5, 3);//Going to the Third Match Loader
    //setDriveConstants(3.0, 0.01, 0.0);
    //setTurnConstants(0.4075, 0.0000013, 0.79);
    driveIn(-6);
    FrontIntake.stop();
    MiddleIntake.stop();
    BackIntake.stop();
    turnToHeading(120);
    driveIn(-18, 1.5);
    turnToHeading(93);
    Wing.set(true);
    driveIn(-74);//Going down the corridor
    turnToHeading(180);
    driveIn(11);
    turnToHeading(270);
    driveIn(-29, 1.5);//To the driver side of the long goal
    Inertial1.setHeading(270, deg);
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1.75, sec);
    BackIntake.stop();
    BackIntake.spin(reverse, 3, pct);
    TopIntakePiston.set(false);
    driveToPosition(57, 47, fwd, 2.5);
    driveToPosition(56, 30, reverse, 1.5);
    MiddleIntake.stop();
    BackIntake.stop();
    driveIn(-33, 1.5);//Back to the Long Goal the last time
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
    //setDriveConstants(3.0, 0.01, 0.0);
    //setTurnConstants(0.4075, 0.0000013, 0.79);
    TopIntakePiston.set(true);
    driveIn(8);
    turnToHeading(235);
    driveIn(30.5, 1.5);
    turnToHeading(200);
    trackingWheelPiston.set(true);
    //setDriveConstants(3.5, 0.01, 0.0);
    driveInWithPiston(16, 12, 1);
    task stopInParkZone = task(parkJerk);
    trackingWheelPiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    LeftDriveSmart.spin(fwd, 100, pct);
    RightDriveSmart.spin(fwd, 100, pct);
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

