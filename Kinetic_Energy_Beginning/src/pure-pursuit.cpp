#include "vex.h"


void purePursuitPath(std::vector<double> pathX, std::vector<double> pathY) {
    //Variable declaration:

    //Lookahead distance constant declaration for finding the point of intersection on the path.
    const double lookaheadDistance = 50;
    //Iterating factor.
    int i = 0;
    
    //Both pathPoints are the coordinates for the point of intersection on the lookahead circle.
    double pathPointX = 0.0;
    double pathPointY = 0.0;

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

    //Time values will replicate ticker behavior.
    double prevTime;
    double deltaTime;


    while (true) {
        //Path following math:

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

        //Curvature:

        //Angle vector:
        angleVector = {pathPointX - X, pathPointY - Y};

        //Errors:
        linearError = getDistance(X, Y, pathPointX, pathPointY);
        turnError = constrainAngle(Inertial1.heading(deg) - atan2(pathPointX - X, pathPointY - Y));

        //Radius of the arc the robot is travelling:
        pursuitArcRadius = (lookaheadDistance/2)/sin(turnError);

        //Integral calculations:
        linearIntegral += linearError;
        turnIntegral += turnError;

        //Derivative calculations:
        linearDerivative = linearError - prevTurnError;
        turnDerivative = turnError - prevTurnError;

        //Linear and turn velocity
        linearVel = linearError * kP + linearIntegral * kI + linearDerivative * kD;
        turnVel = turnError * turnKP + turnIntegral * turnKI + turnDerivative * turnKD;

        //Previous updates for derivative:
        prevLinearError = linearError;
        prevTurnError = turnError;
        
        LeftDriveSmart.spin(fwd, (linearVel - turnVel), pct);
        RightDriveSmart.spin(fwd, (linearVel + turnVel), pct);

        //This value should be the same as the ticker in the simulation.
        wait (20, msec);
    }
}