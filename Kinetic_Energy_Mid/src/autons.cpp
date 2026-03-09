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
        else if (hasEntered == true && Inertial1.roll(deg) > 0) {
            LeftDriveSmart.stop(coast);
            RightDriveSmart.stop(coast);
            DescorePiston.set(false);
            std::cout << Brain.timer(sec) << std::endl;
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
        //std::cout << counter << std::endl;
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


void oscillate(int oscillator) {
    for (int i = 0; i < oscillator; i++) {
        Drivetrain.driveFor(30, inches, false);
        LeftDriveSmart.spin(reverse, 80, pct);
        RightDriveSmart.spin(fwd, 80, pct);
        wait(0.09, sec);
        LeftDriveSmart.spin(fwd, 80, pct);
        RightDriveSmart.spin(reverse, 80, pct);
        wait(0.09, sec);
    }
    Drivetrain.stop();
}


void Left() {
    //Heading: 243
    //X: 48
    //Y: -6
    setTurnConstants(0.4, 0.0, 0.79);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(24, 11);
    wait(0.5, sec);
    turnToHeading(135);
    TopIntakePiston.set(true);
    driveIn(-23.5, 1.25);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 95, pct);
    BackIntake.spin(fwd, 25, pct);
    driveIn(1.5);
    wait(1, sec);
    TopIntakePiston.set(false);
    BackIntake.stop();
    driveToPosition(49, -40.5, fwd);
    turnToHeading(90);
    driveIn(16, 1.3);
    LeftDriveSmart.spin(reverse, 100, pct);
    RightDriveSmart.spin(reverse, 100, pct);
    wait (1, sec);
    TopIntakePiston.set(true);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);

}




void Right() {
    //Heading: 295
    //X: 48
    //Y: 6
    setDriveConstants(3, 0.0, 0);
    setTurnConstants(0.4, 0.0, 0.79);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveInWithPiston(25, 10.25);
    DescorePiston.set(false);
    turnToHeading(225);
    BottomIntakePiston.set(true);
    driveIn(18, 1.5);
    FrontIntake.spin(reverse, 75, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (1.75, sec);
    driveIn(-12);
    BottomIntakePiston.set(false);
    DescorePiston.set(true);
    stopIntakes();
    //Second part
    setDriveConstants(2.8, 0.0, 0);
    setTurnConstants(0.43, 0.0, 0.79);
    turnToHeading(40);
    driveIn(37.5);
    intakeFill();
    turnTolerance = 0.75;
    setTurnConstants(0.4, 0.0, 0.79);
    turnToHeading(90);
    BackIntake.stop();
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(17, 0.65);
    turnToHeading(85, 0.8);
    driveIn(-100, 1.5);
    TopIntakePiston.set(true);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (1, sec);
    LeftDriveSmart.spin(fwd, 25, pct);
    RightDriveSmart.spin(fwd, 25, pct);
    wait (0.5, sec);
    Drivetrain.stop(brake);
    TopIntakePiston.set(false);
    driveIn(-100, 1);
}

void Odom_Right() {
    //Heading: 156
    //X: -61.4
    //Y: -25.5
    DescorePiston.set(true);
    driveToPosition(-50, -52, fwd);
    turnToHeading(270);
    MiddleIntake.spin(fwd, 25, pct);
    FrontIntake.spin(fwd, 100, pct);
    driveIn(12, 1);
    driveIn(-1);
    driveToPosition(-15, -48, reverse, 1.75);
    TopIntakePiston.set(true);
    MiddleIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    wait (0.5, sec);
    DescorePiston.set(false);
    driveIn(2, 1.75);
    driveToPosition(-48, -48, fwd);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 20, pct);
    BackIntake.stop();
    setDriveConstants(2.3, 0.0, 0);
    driveToPosition(-25,-25, fwd);
    driveIn(20, 1);
    BottomIntakePiston.set(true);
    FrontIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);

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
    //Heading: 149
    //X: -55
    //Y: -24
    task newTimer = task(runManualTimer);
    Brain.resetTimer();
    DescorePiston.set(true);            //Deploys piston and lines up next to the matchloader
    driveIn(31);
    turnToHeading(270);                 //Turns toward the matchloader
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.stop();
    driveIn(15.5, 2);                   //Drives into the matchloader
    oscillate(4);
    driveIn(5,0.5);
    oscillate(4);
    wait (1, sec);
    MiddleIntake.spin(fwd, 30, pct);
    driveIn(-6);                        //Back away from matchloader
    FrontIntake.stop();
    MiddleIntake.stop();
    turnToHeading(300);
    driveIn(-23.5, 1.5);                //Drive away from matchloader
    Wing.set(true);
    turnToHeading(275);
    driveIn(-64);                       //Drive Down Alley
    turnToHeading(0);
    driveTolerance = 0.25;
    driveIn(10);                         //After Alley turn
    driveTolerance = 0.5;
    turnToHeading(90);
    DescorePiston.set(false);
    driveIn(-30, 1.4);
    LeftDriveSmart.spin(reverse, 100, pct);
    RightDriveSmart.spin(reverse, 100, pct);
    DescorePiston.set(true);
    setDrivePosition(35.5, -41);                  //Backing up to score
    TopIntakePiston.set(true);          //Score in long goal First Time
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (.75, sec);
    FrontIntake.spin(reverse, 100, pct);//Outtaking to UnJam
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (.5, sec);
    FrontIntake.spin(fwd, 100, pct);    //Scoring once again
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (2, sec);
    BackIntake.stop();
    driveIn(2);
    TopIntakePiston.set(false);
    turnTolerance = 0.5;
    driveToPosition(65.5, -38, fwd, 2);                  //Turn to match loader and driving to matchloader and emptying it
    turnTolerance = 1;
    oscillate(4);
    driveIn(5,0.5);
    oscillate(4);
    MiddleIntake.stop();
    driveIn(-5);
    turnToHeading(90);
    TopIntakePiston.set(false);
    turnTolerance = 0.5;
    driveToPosition(45, -41, reverse);
    TopIntakePiston.set(false);             //Turn to line up with goal
    turnTolerance = 1;
    MiddleIntake.spin(fwd, 50, pct);
    BackIntake.spin(reverse, 3, pct);
    FrontIntake.spin(fwd, 100, pct);
    wait(0.1, sec);
    turnToHeading(89);
    TopIntakePiston.set(true); 
    driveIn(-38, 1.25);                 //Drive back to score again 🤞
    FrontIntake.spin(fwd, 100, pct);
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (.75, sec);
    FrontIntake.spin(reverse, 100, pct);//Outtaking to UnJam
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(reverse, 100, pct);
    wait (.5, sec);
    FrontIntake.spin(fwd, 100, pct);    //Scoring once again
    BackIntake.spin(reverse, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    wait (3, sec);
    BackIntake.stop();
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    driveIn(8);                         //Drive away from long goal

    //Temporary 48 from here
    driveToPosition(40, -20, fwd);
    DescorePiston.set(false);
    turnToHeading(268);
    BackIntake.spin(fwd, 100, pct);
    driveIn(110, 5);
    turnToHeading(350);
    FrontIntake.spin(fwd, 100, pct);
    MiddleIntake.spin(fwd, 100, pct);
    driveIn(1, 1);



    //Third matchloader

    /*driveToPosition(50, 55, fwd);       //Drive across field
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
    turnToHeading(93);                  //Angle down Alley
    Wing.set(true);
    driveIn(-72);                       //Going down the Alley
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
*/

    //Mckay stuff I guess

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
    trackingWheelPiston.set(true);*/
    DescorePiston.set(true);
    task stopInParkZone = task(parkJerk);
    trackingWheelPiston.set(true);
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

