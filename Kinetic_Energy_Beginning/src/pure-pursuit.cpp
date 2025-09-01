#include "vex.h"

//Desmos graph here: https://www.desmos.com/calculator/4c9taq6heq.

void purePursuitPath(std::vector<double> pathX, std::vector<double> pathY) {
    //Variable declaration:

    //Lookahead distance constant declaration for finding the point of intersection on the path.
    const double lookaheadDistance = 50;
    //Iterating factor.
    int i = 0;
    
    //Both pathPoints are the coordinates for the point of intersection on the lookahead circle.
    double pathPointX;
    double pathPointY;



    while (true) {
        //If the current iteration is beyond the circle intersection, it will continue iterating and prevent movement.
        if (std::round((X - (pathX[i] * pathX[i])) + (Y - (pathY[i] * pathY[i]))) > lookaheadDistance) {
            i = i - 1;
            pathPointX = X;
            pathPointY = Y;
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
        }
        //If the iteration goes through the full cycle, it will repeat the iteration process.
        else if (i == 0) {
            i = pathX.size();
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
        }
        //If the distance from the robot center to the end of the path is relatively 0, it will terminate.
        else if (std::round(getDistance(X, Y, pathX[pathX.size()], pathY[pathY.size()]))) {
            i = pathX.size();
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }
        //If the furthest point of the iteration is within the circle, it will continue to increase until it reaches the border.
        else if (std::round((X - (pathX[i + 1] * pathX[i + 1])) + (Y - (pathY[i + 1] * pathY[i + 1]))) <= lookaheadDistance) {
            pathPointX = pathX[i + 1];
            pathPointY = pathY[i + 1];
            i += 1;
            curveToPosition(pathPointX, pathPointY);
        }
        //If the end of the intersection plus one is not within the circle, it will not continue down the path until intersection again.
        else if (std::round((X - (pathX[i + 1] * pathX[i + 1])) + (Y - (pathY[i + 1] * pathY[i + 1]))) > lookaheadDistance) {
            pathPointX = pathX[i];
            pathPointY = pathY[i];
            curveToPosition(pathPointX, pathPointY);
        }
        //If the path has no designation, it will prevent movement.
        else if (pathPointX == X && pathPointY == Y) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
        }

        wait (20, msec);
    }
    LeftDriveSmart.stop(brake);
    RightDriveSmart.stop(brake);
}