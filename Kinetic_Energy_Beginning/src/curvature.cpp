#include "vex.h"
double desiredHeading;
double linearVel;
double turnVel;

double desiredX;
double desiredY;

double turnCurveP = 0.5;

double desiredDist;

double Ll;
double Lr;


double validateHeading(double bestHeading) {
    if (bestHeading < 0) bestHeading += 360;
    if (bestHeading > 360) bestHeading -= 360;
    return bestHeading;
}

void curvature(double lX, double lY) {
    desiredHeading = validateHeading(atan2(lX - X, lY - Y) * (180 / M_PI));


        if (validateHeading(((atan2(lX - X, lY - Y) * (180 / M_PI)) - Inertial1.heading(deg))) > 90 && validateHeading(((atan2(lX - X, lY - Y) * (180 / M_PI)) - Inertial1.heading(deg))) < 270) {
            linearVel = -60;
            //Standard P controller.
            turnVel = (constrainAngle((desiredHeading - Inertial1.heading(deg)) + 180) * turnCurveP);
        }
        else {
            linearVel = 60;
            //Standard P controller.
            turnVel = (constrainAngle(desiredHeading - Inertial1.heading(deg)) * turnCurveP);
        }


        Ll = (linearVel + turnVel);
        Lr = (linearVel - turnVel);


        LeftDriveSmart.spin(fwd, Ll, pct);
        RightDriveSmart.spin(fwd, Lr, pct);
    

        wait (20, msec);
}

void curveToPosition(double desiredX, double desiredY) {
    while (true) {
        curvature(desiredX, desiredY);
        //If both values are within their certain tolerance, the function will terminate:
        if (getDistance(X, Y, desiredX, desiredY) <= 4) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }
    }
}

double preservedTime;

void curveToPosition(double desiredX, double desiredY, double time) {
    preservedTime = Brain.timer(sec) <= time;
    Brain.resetTimer();
    while (true) {
        curvature(desiredX, desiredY);
        //If both values are within their certain tolerance, the function will terminate:
        if (Brain.timer(sec) <= time + 0.1 && Brain.timer(sec) >= time - 0.1) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }
    }
    Brain.setTimer(Brain.timer(sec) + preservedTime, sec);
}