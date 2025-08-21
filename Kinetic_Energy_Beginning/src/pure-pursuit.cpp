#include "vex.h"

void curvature(double pX, double pY) {
    while (true) {
        double turnError = constrainAngle(Inertial1.heading(deg) - atan2(pX - X, pY - Y));
        double turnVel = turnError * turnKP;
        double Ll = (50 + turnVel);
        double Lr = (50 - turnVel);
        LeftDriveSmart.spin(fwd, Ll, pct);
        RightDriveSmart.spin(fwd, Lr, pct);
        if (getDistance(X, Y, pX, pY) < 2) break;

        wait (20, msec);
    }
}

void purePursuitPath(std::vector<double> pathX, std::vector<double> pathY) {
    //Variable declaration:

    //Lookahead distance constant declaration for finding the point of intersection on the path.
    double lookaheadDistance = 1;
    //Iterating factor.
    int i = 0;
    
    //Both pathPoints are the coordinates for the point of intersection on the lookahead circle.
    double pathPointX = pathX[1];
    double pathPointY = pathY[1];

    //Angle vector is used in the turn error formula.
    std::vector<double> angleVector;

    //Radius of the arc that calculates velocities.
    double pursuitArcRadius;

    //Both are the amount of velocity that needs to be sent to the curve.
    double leftCurve;
    double rightCurve;

    //Linear and turn velocity are basically the power calcualtions for PID so we can do proper PID implementation.
    double turnVel;
    double linearVel;

    //PID values will help to properly implement PID into the curvature.
    double linearIntegral = 0;
    double turnIntegral = 0;
    double linearDerivative;
    double turnDerivative;
    double linearError;
    double turnError;
    double prevLinearError;
    double prevTurnError;

    //Motor power calculations for each side will help calculate curvature.
    double Ll;
    double Lr;

    //Time values will replicate ticker behavior.
    double prevTime;
    double deltaTime;


    while (true) {
        //Path following math:
        /*
        //Will check to see if the current iteration of the checked point on the path
        //has intersected with the circle and will continue iterating until intersection.
        if ((std::round((((X - pathX[i]) * (X - pathX[i])) + ((Y - pathY[i]) * (Y - pathY[i]))))) > lookaheadDistance) {
            i -= 1;
            pathPointX = X;
            pathPointY = Y;
        }
        //Will reset the loop that checks for intersection until intersection
        //is found or something is blocking the beginning point of the path.
        else if (i == 0) {
            i = pathX.size();
        }
        //Will move the intersection and pursuit point further along the
        //path once the intersection circle is also further along the path.
        else if ((std::round((((X - pathX[i + 1]) * (X - pathX[i + 1])) + ((Y - pathY[i + 1]) * (Y - pathY[i + 1]))))) <= lookaheadDistance) {
            pathPointX = pathX[i + 1];
            pathPointY = pathY[i + 1];
            i = i + 1;
        }
        //Intersection point will remain the same until the next point on the path is able to
        //intersect with the robot so the furthest point on the lookahead circle can increase.
        else if ((std::round((((X - pathX[i + 1]) * (X - pathX[i + 1])) + ((Y - pathY[i + 1]) * (Y - pathY[i + 1]))))) > lookaheadDistance) {
            pathPointX = pathX[i];
            pathPointY = pathY[i];
        }
        //Failsafe for making sure the robot stops moving if it's within the goal point.
        else if ((std::round(getDistance(X, Y, pathX.size(), pathY.size()))) == 0) break;
        */
        //Curvature:
        lookaheadDistance = getDistance(pathX[i], pathY[i], pathPointX, pathPointY);

        //Angle vector:
        angleVector = {pathPointX - X, pathPointY - Y};

        //Errors:
        linearError = getDistance(X, Y, pathPointX, pathPointY);
        //Radius of the arc the robot is travelling:
        pursuitArcRadius = (lookaheadDistance/2) / sin(turnError);

        //Integral calculations:
        linearIntegral += linearError;
        turnIntegral += turnError;

        //Derivative calculations:
        linearDerivative = linearError - prevTurnError;
        turnDerivative = turnError - prevTurnError;

        //Linear and turn velocity
        linearVel = linearError * kP + linearIntegral * kI + linearDerivative * kD;

        //Previous updates for derivative:
        prevLinearError = linearError;
        prevTurnError = turnError;
        

        i += 1;
        if (i > pathX.size()) break;
        pathPointX = pathX[i + 1];
        pathPointY = pathY[i + 1];
        //curveToPosition(pathPointX, pathPointY);

        //This value should be the same as the ticker in the simulation.
        wait (20, msec);
    }
    LeftDriveSmart.stop();
    RightDriveSmart.stop();
}