#include "vex.h"

//This is not pure pursuit it is just a much simpler path tracing algorithm alternative.

void tracePath(std::vector<double> pltX, std::vector<double> pltY) {
    int l = 0;
    while (true) {
        //Buttload of tolerance to allow for fluid movement.
        double hugeTolerance = drivetrainLength + 5;
        if (getDistance(X, Y, pltX[l], pltY[l]) <= hugeTolerance && l < pltX.size() - 1) {
            l += 1;
        }
        //Tolerance for ending the path
        else if (getDistance(X, Y, pltX[l], pltY[l]) <= 3 && l == pltX.size() - 1) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }

        curvature(pltX[l], pltY[l]);

        LeftDriveSmart.spin(fwd, Ll, pct);
        RightDriveSmart.spin(fwd, Lr, pct);

        wait (20, msec);
    }
}