#include "vex.h"

//Desmos graph here: https://www.desmos.com/calculator/4c9taq6heq.

double returnElement;
/*
void setTupleXY(double pos, const char* Axis) {
    if (Axis == "X" || Axis == "x") {
        returnElement = std::get<0>(element_tuple);
    }
    else if (Axis == "Y" || Axis == "y") {
        returnElement = std::get<0>(element_tuple);
    }
    return returnElement;
}*/

//Variable declaration:
std::vector<double> pathX;
std::vector<double> pathY;


//Both pathPoints are the coordinates for the point of intersection on the lookahead circle.
double pathPointX;
double pathPointY;


//Iterating factor.
int i = pathX.size();


//Lookahead distance constant declaration for finding the point of intersection on the path.
const double lookaheadDistance = 6.5;
const double lookaheadDistanceSquared = lookaheadDistance * lookaheadDistance;



void purePursuitPath(std::vector<std::tuple<double, double>> path) {
    while (true) {
        Controller1.Screen.setCursor(0,0);
        Controller1.Screen.print(getDistance(X, Y, pathPointX, pathPointY));
        Controller1.Screen.setCursor(2,0);
        Controller1.Screen.print(pathPointX);
        Controller1.Screen.print(", ");
        Controller1.Screen.print(pathPointY);
        //If the current iteration is beyond the circle intersection, it will continue iterating and prevent movement.
        if (std::round(((X - pathX[i]) * (X - pathX[i])) + ((Y - pathY[i]) * (Y - pathY[i]))) > lookaheadDistanceSquared) {
            i --;
            pathPointX = X;
            pathPointY = Y;
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
        }
        //If the iteration goes through the full cycle, it will repeat the iteration process.
        else if (i == -1) {
            i = pathX.size();
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
        }
        //If the distance from the robot center to the end of the path is relatively 0, it will terminate.
        else if (std::round(getDistance(X, Y, pathX[pathX.size()], pathY[pathY.size()])) == 0) {
            LeftDriveSmart.stop(brake);
            RightDriveSmart.stop(brake);
            break;
        }
        //If the furthest point of the iteration is within the circle, it will continue to increase until it reaches the border.
        else if (std::round(((X - pathX[i + 1]) * (X - pathX[i + 1])) + ((Y - pathY[i + 1]) * (Y - pathY[i + 1]))) <= lookaheadDistanceSquared) {
            pathPointX = pathX[i + 1];
            pathPointY = pathY[i + 1];
            i ++;
            //curveTo();
        }
        //If the end of the intersection plus one is not within the circle, it will not continue down the path until intersection again.
        else if (std::round(((X - pathX[i + 1]) * (X - pathX[i + 1])) + ((Y - pathY[i + 1]) * (Y - pathY[i + 1]))) > lookaheadDistanceSquared) {
            pathPointX = pathX[i];
            pathPointY = pathY[i];
            //curveTo();
        }
        wait (20, msec);
    }

}