#include "vex.h"


double beginHeading;
double beginX;
double beginY;


bool hasEntered = false;


int counter = 0;


int parkJerk() {
    while (true) {
        if (Inertial1.roll(deg) <= -2) {
            hasEntered = true;


        }
        else if (hasEntered == true && Inertial1.roll(deg) > 0) {
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





void Left() {
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

}




void Right() {
    //Heading: 295
    //X: 48
    //Y: 6
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(26, 10.25);
    turnToHeading(225);
    DescorePiston.set(false);
    BottomIntakePiston.set(true);
    driveIn(18, 1.5);
    FrontIntake.spin(reverse, 75, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1.25, sec);
    driveIn(-12);
    BottomIntakePiston.set(false);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    setDriveConstants(2.8, 0.0, 0);//setDriveConstants(2.8, 0.0011, 0);
    setTurnConstants(0.33, 0.0, 0.79);//setTurnConstants(0.33, 0.000000001, 0.79);
    turnToHeading(40);
    driveIn(34);
    intakeFill();
    turnTolerance = 0.75;
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(16, 0.8);
    turnToHeading(85, 0.8);
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
    //Heading: 295
    //X: 48
    //Y: 6
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(26, 10.25);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    turnToHeading(40);
    driveIn(30);
    intakeFill();
    turnTolerance = 0.75;
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(16, 0.8);
    turnToHeading(80, 0.8);
    driveIn(-100, 2);
    TopIntakePiston.set(true);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (1, sec);
    /*
    driveIn(5);
    TopIntakePiston.set(false);
    driveIn(-100, 1);
    */
}



void Skills() {
    task newTimer = task(runManualTimer);
    //Heading: 149
    //X: -55
    //Y: -24
    DescorePiston.set(true);            //Deploys piston and lines up next to the matchloader
    driveIn(31.5);
    turnToHeading(270);                 //Turns toward the matchloader
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.stop();
    driveIn(15, 2.6);                   //Drives into the matchloader
    MiddleIntake.spin(fwd, 50, pct);
    driveIn(-6);                        //Back away from matchloader
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(300);
    driveIn(-20.5, 1.5);                //Drive away from matchloader
    Wing.set(true);
    turnToHeading(275);
    driveIn(-72);                       //Drive Down Ally
    turnToHeading(0);
    driveTolerance = 0.25;
    driveIn(9.5);                         //After Ally turn
    driveTolerance = 0.5;
    turnToHeading(90);
    driveIn(-38, 1.3);                  //Backing up to score
    Inertial1.setHeading(90, deg);      //Recalibrate Inertial
    TopIntakePiston.set(true);          //Score in long goal First Time
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (.75, sec);
    FrontIntake.spin(reverse, 100, pct);//Outaking to UnJam
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (.1, sec);
    FrontIntake.spin(fwd, 100, pct);    //Scoring once again
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1.5, sec);
    BackIntake.stop();
    TopIntakePiston.set(false);
    BackIntake.spin(reverse, 3, pct);
    driveIn(2);
    turnToHeading(88);                  //Turn to match loader
    driveIn(27, 2.25);                  //Driving to matchloader and emptying it
    turnToHeading(86, 2);               //Turn to line up with goal
    MiddleIntake.stop();
    BackIntake.stop();
    TopIntakePiston.set(true);
    FrontIntake.spin(reverse, 100, pct);
    wait(0.1, sec);
    driveIn(-38, 1.25);                 //Drive back to score again 🤞
    FrontIntake.spin(fwd, 100, pct);    //Score in long goal
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    TopIntakePiston.set(false);
    setDrivePosition(35.5, -41);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    BackIntake.stop();
    driveIn(8);                         //Drive away from long goal
    driveToPosition(50, 55, fwd);       //Drive across field
    TopIntakePiston.set(false);
    turnToHeading(85);                  //Turn to Third Match loader
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 3, pct);
    driveIn(20.5, 3);                   //Driving into Third Matchloader
    driveIn(-6);                        //Backing away from Matchloader
    FrontIntake.stop();
    MiddleIntake.stop();
    BackIntake.stop();
    turnToHeading(120);                 //Turning to wall
    driveIn(-18, 1.5);                  //Driving to wall
    turnToHeading(93);                  //Angle down Ally
    Wing.set(true);
    driveIn(-72);                       //Going down the Ally
    turnToHeading(180);
    driveIn(11);
    turnToHeading(270);
    driveIn(-29, 1.5);                  //Lining up with the second long goal
    Inertial1.setHeading(270, deg);      //recalabrating Inertial to 270
    setDrivePosition(-32, 48);          //Setting odom
    TopIntakePiston.set(true);          //Scoring in long goal first time on second long goal
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (1.75, sec);
    BackIntake.stop();
    BackIntake.spin(reverse, 3, pct);
    TopIntakePiston.set(false);
    driveIn(2, 1);                       //Drive away from goal to turn to fourth match loader
    turnToHeading(269);                  //Turn to fourth Matchloader
    driveIn(27,3);                       //Driving to Matchloader
    driveIn(-10);                        //Driving away from matchloader
    DescorePiston.set(false);
    turnToHeading(225);                  //Turn to parkzone
    trackingWheelPiston.set(true);
    driveInWithPiston(36, 35.5);         //Drive to parkzone to park

    /*
    driveIn(2,1);
    driveToPosition(-64, 40, fwd, 2.5);
    MiddleIntake.stop();
    BackIntake.stop();
    driveIn(-33, 1.5);//Back to the Long Goal the last time
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    TopIntakePiston.set(false);
    DescorePiston.set(false);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 25, pct);
    TopIntakePiston.set(true);
    driveIn(8);
    turnToHeading(235);
    driveIn(30.5, 1.5);
    turnToHeading(200);
    trackingWheelPiston.set(true);
    driveInWithPiston(12, 11, 1);*/
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

