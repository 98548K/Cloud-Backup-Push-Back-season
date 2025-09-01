#include "vex.h"


void curveToPosition(double desiredX, double desiredY) {
    while (true) {
        double desiredHeading = constrainAngle(atan2(desiredX - X, desiredY - Y) * (180 / M_PI));
        double linearVel = getDistance(X, Y, desiredX, desiredY) * .6;
        //Standard P controller
        double turnVel = (-constrainAngle(desiredHeading - Inertial1.heading(deg))) * .2;
        double Ll = (linearVel - turnVel);
        double Lr = (linearVel + turnVel);
        LeftDriveSmart.spin(fwd, Ll, pct);
        RightDriveSmart.spin(fwd, Lr, pct);
        //getDistance(X, Y, desiredX, desiredY) < 2  
        if (getDistance(X, Y, desiredX, desiredY) <= 0.5) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }
        

        wait (20, msec);
    }
}