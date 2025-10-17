#include "vex.h"

double beginHeading;
double recordTime;
int sped;

void Right_Blue() {
    sped = 50;
    /*
    beginHeading = 270;
    X = 63.8;
    Y = 17;
    Inertial1.setHeading(beginHeading, deg);
    wait (3, sec);
    */

    ReversedIntake.spin(fwd, 100, pct);
    BottomIntake.spin(fwd, 100, pct);
    turnCurveP = 0.6;
    tracePath({56.3,54.7,53.6,52.4,51.7,50.6,49.2,48.6,47,45.8,45,44,43.2,42.4,41.5,40,39.2,38,37.3,36.4,35.6,34.7,33.3,32.4,31.3,30.5,29.6,28.8,27.6,26.8,26,25,24.2,23.6,23,22.2,21,19.7,18.8,17.4,16.8,15.7,15,14.8,14,13.4,11.7,11.4,10.6,10,9.2,8.6,7.4,7}, {17,17,17,17.5,18,19.3,20.4,21,21,21,21,21,21,21,21,21,21.3,21.6,21.9,21.9,21.9,21.9,22,22,22.4,22.4,22.4,22.4,22.4,22.4,22.7,22.7,22.7,21.8,21.3,20.4,19.3,18.7,18.2,17.3,16.7,16.2,15.3,14.5,13.6,13,11.6,10.8,10.2,9.7,9,8.2,8,8});
    turnToPosition(40, 47, reverse);
    TopIntake.spin(reverse, 100, pct);
    BottomIntake.spin(reverse, 100, pct);
    ReversedIntake.spin(reverse, 100, pct);
    wait (2, sec);
    TopIntake.stop();
    BottomIntake.stop();
    ReversedIntake.stop();
    curveToPosition(43, 45);
    DescorePiston.set(true);
    turnToHeading(90);
    recordTime = Brain.timer(sec);
    Brain.resetTimer();
    while (Brain.timer(sec) < 0.5) {
        sped -= sped * 2;
        LeftDriveSmart.spin(fwd, sped, pct);
        RightDriveSmart.spin(fwd, sped, pct);
    }
    Brain.setTimer(recordTime + Brain.timer(sec), sec);
    TopIntake.spin(fwd, 10, pct);
    BottomIntake.spin(fwd, 100, pct);
    ReversedIntake.spin(fwd, 100, pct);
    wait (1, sec);
    driveIn(-5);
    DescorePiston.set(false);
    IntakePiston.set(true);
    turnToHeading(270);
    TopIntake.spin(fwd, 100, pct);
    BottomIntake.spin(fwd, 100, pct);
    ReversedIntake.spin(fwd, 50, pct);
    curveToPosition(35, 45);
}


void Left_Blue() {
    sped = 50;
    /*
    beginHeading = 90;
    X = 63.8;
    Y = -17;
    Inertial1.setHeading(beginHeading, deg);
    wait (3, sec);
    */

    ReversedIntake.spin(fwd, 100, pct);
    BottomIntake.spin(fwd, 100, pct);
    turnCurveP = 0.6;
    tracePath({56.3,54.7,53.6,52.4,51.7,50.6,49.2,48.6,47,45.8,45,44,43.2,42.4,41.5,40,39.2,38,37.3,36.4,35.6,34.7,33.3,32.4,31.3,30.5,29.6,28.8,27.6,26.8,26,25,24.2,23.6,23,22.2,21,19.7,18.8,17.4,16.8,15.7,15,14.8,14,13.4,11.7,11.4,10.6}, {-17, -17, -17, -17.5, -18, -19.3, -20.4, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21.3, -21.6, -21.9, -21.9, -21.9, -21.9, -22, -22, -22.4, -22.4, -22.4, -22.4, -22.4, -22.4, -22.7, -22.7, -22.7, -21.8, -21.3, -20.4, -19.3, -18.7, -18.2, -17.3, -16.7, -16.2, -15.3, -14.5, -13.6, -13, -11.6, -10.8, -10.2});
    turnToPosition(40, -47, reverse);
    TopIntake.spin(fwd, 100, pct);
    BottomIntake.spin(fwd, 100, pct);
    ReversedIntake.spin(fwd, 100, pct);
    wait (1, sec);
    IntakePiston.set(true);
    wait (0.5, sec);
    IntakePiston.set(false);
    wait (0.5, sec);
    TopIntake.stop();
    BottomIntake.stop();
    ReversedIntake.stop();
    curveToPosition(43, -45);
    DescorePiston.set(true);
    wait (0.5, sec);
    turnToHeading(90);
    recordTime = Brain.timer(sec);
    Brain.resetTimer();
    while (Brain.timer(sec) < 0.5) {
        LeftDriveSmart.spin(fwd, 30, pct);
        RightDriveSmart.spin(fwd, 30, pct);
    }
    Brain.setTimer(recordTime + Brain.timer(sec), sec);
    TopIntake.spin(fwd, 10, pct);
    BottomIntake.spin(fwd, 100, pct);
    ReversedIntake.spin(fwd, 100, pct);
    wait (1, sec);
    driveIn(-8);
    DescorePiston.set(false);
    IntakePiston.set(true);
    turnToHeading(265);
    driveIn(14);
    TopIntake.spin(fwd, 100, pct);
    BottomIntake.spin(fwd, 100, pct);
    ReversedIntake.spin(fwd, 100, pct);
}


void Bad_Skills() {
    BottomIntake.spin(reverse, 100, pct);
    Drivetrain.driveFor(30, inches);
}