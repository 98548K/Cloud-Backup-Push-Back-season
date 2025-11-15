#include "vex.h"

//This is not pure pursuit it is just a much simpler path tracking algorithm alternative.

void tracePath(std::vector<double> pltX, std::vector<double> pltY) {
    int l = 0;
    while (true) {
        //Buttload of tolerance to allow for fluid movement.
        double hugeTolerance = 18;
        if (getDistance(X, Y, pltX[l], pltY[l]) <= hugeTolerance && l < pltX.size()) {
            l += 1;
        }
        else if (getDistance(X, Y, pltX[l], pltY[l]) <= 3 && l == pltX.size()) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }

        
        desiredHeading = validateHeading(atan2(pltX[l] - X, pltY[l] - Y) * (180 / M_PI));


        if (validateHeading(((atan2(pltX[l] - X, pltY[l] - Y) * (180 / M_PI)) - Inertial1.heading(deg))) > 90 && validateHeading(((atan2(pltX[l] - X, pltY[l] - Y) * (180 / M_PI)) - Inertial1.heading(deg))) < 270) {
            linearVel = -20;
            //Standard P controller.
            turnVel = (constrainAngle((desiredHeading - Inertial1.heading(deg)) - 180) * turnCurveP);
        }
        else {
            linearVel = 20;
            //Standard P controller.
            turnVel = (constrainAngle(desiredHeading - Inertial1.heading(deg)) * turnCurveP);
        }


        Ll = (linearVel + turnVel);
        Lr = (linearVel - turnVel);


        LeftDriveSmart.spin(fwd, Ll, pct);
        RightDriveSmart.spin(fwd, Lr, pct);

        wait (20, msec);
    }
    
}