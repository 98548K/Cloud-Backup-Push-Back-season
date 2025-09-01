#include "vex.h"

//This is not pure pursuit it is just a much simpler path tracking algorithm alternative.

void tracePath(std::vector<double> pltX, std::vector<double> pltY) {
    int l = 1;
    while (true) {
        curveToPosition(pltX[l], pltY[l]);
        if (X == pltX[l] && Y == pltY[l]) {
            l += 1;
        }
        else if (l == pltX.size()) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }
    }
}