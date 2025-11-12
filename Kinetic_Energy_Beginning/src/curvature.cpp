#include "vex.h"
double desiredHeading;
double linearVel;
double turnVel;

double desiredX;
double desiredY;

double turnCurveP = 0.6;

double desiredDist;

double Ll;
double Lr;


double validateHeading(double bestHeading) {
    if (bestHeading < 0) bestHeading += 360;
    if (bestHeading > 360) bestHeading -= 360;
    return bestHeading;
}

void curveToPosition(double desiredX, double desiredY) {
    while (true) {

        desiredHeading = validateHeading(atan2(desiredX - X, desiredY - Y) * (180 / M_PI));


        if (validateHeading(((atan2(desiredX - X, desiredY - Y) * (180 / M_PI)) - Inertial1.heading(deg))) > 90 && validateHeading(((atan2(desiredX - X, desiredY - Y) * (180 / M_PI)) - Inertial1.heading(deg))) < 270) {
            linearVel = -40;
            //Standard P controller.
            turnVel = (constrainAngle((desiredHeading - Inertial1.heading(deg)) + 180) * turnCurveP);
        }
        else {
            linearVel = 40;
            //Standard P controller.
            turnVel = (constrainAngle(desiredHeading - Inertial1.heading(deg)) * turnCurveP);
        }


        Ll = (linearVel + turnVel);
        Lr = (linearVel - turnVel);


        LeftDriveSmart.spin(fwd, Ll, pct);
        RightDriveSmart.spin(fwd, Lr, pct);


        //If both values are within their certain tolerance, the function will terminate:
        if (getDistance(X, Y, desiredX, desiredY) <= 3) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }
    

        wait (20, msec);
    }
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(X);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(Y);
}