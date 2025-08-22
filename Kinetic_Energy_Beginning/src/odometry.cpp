#include "vex.h"

//Tuning constants. Depending on the tracking wheel mounting we will probably need to change the operators
//Horizontal distance from the side of the forward/backward tracking wheel to center
const double horizontalTrackingCenter = 2.0;
//Vertical distance from the side of the left/right tracking wheel to center
const double verticalTrackingCenter = 2.25;

//Tracking wheel measurments in inches
double FRONT_WHEEL;
double SIDE_WHEEL;
double prevFRONT_WHEEL;
double prevSIDE_WHEEL;
double deltaFRONT_WHEEL;
double deltaSIDE_WHEEL;

//Tracking coordinates
double X;
double Y;
double deltaX;
double deltaY;
double prevX;
double prevY;

//Variables for determining arc calculations or translation calculations 
double XCalculation;
double YCalculation;

//Arc circle stuff
double radianHeading;
double deltaRadianHeading;
double averageRadianHeading;
double prevRadianHeading;
double arcLength;
double deltaArcLength;
double arcRadius;
double deltaRadius;
double targetOrientation;

/*

Fundamental odom math and updating math. Delta math formula is: delta value = value - previous value.
This is so we can solve for the original value, then add the diference between
where it was and where it's at using the formula. As Chris would put it, "So basically what you're saying
is that subtracting the previous values from the current values gives us the difference in where it is and where it's been,
so we can then add those to where it currently is and get the correct value."

*/

int positionTracking() {
    while (true) {
        //Updating tracking wheel measurments in inches
        FRONT_WHEEL = frontTracking.position(turns) * (wheelRad * 2) * M_PI;
        SIDE_WHEEL = sideTracking.position(turns) * (wheelRad * 2) * M_PI;
        deltaFRONT_WHEEL = FRONT_WHEEL - prevFRONT_WHEEL;
        deltaSIDE_WHEEL = SIDE_WHEEL - prevSIDE_WHEEL;

        //Arc math for determining the robots current side distance from the simulated circle center
        radianHeading = Inertial1.heading(deg) * M_PI / 180;
        arcRadius = deltaFRONT_WHEEL / radianHeading;
        arcLength = arcRadius * radianHeading + horizontalTrackingCenter;
        deltaArcLength = arcRadius * radianHeading + horizontalTrackingCenter;
        deltaRadianHeading = radianHeading - prevRadianHeading;
        averageRadianHeading = radianHeading - (deltaRadianHeading / 2);

        //Math for determining current coordinates using the values above



        //This is the math implemented from the video and sources from vex forum so I don't understand it as well. 
        //It's also the core math for calculating the coordinates. The rest is update math and orientation math

        //If statement for determining whether the robot needs to use arc math in case of change in orientation or
        //if it is just moving straightward in its current direction. I don't think this is necessarry for odom to work but it's really heplful
        //Here is the link to the formula: https://www.vexforum.com/t/2-tracking-wheel-imu-inertial-odometry/100037/2
        
        if (deltaRadianHeading == 0) {
            XCalculation = deltaSIDE_WHEEL;
            YCalculation = deltaFRONT_WHEEL;
        } 
        else {
            //Depending on the tracking wheel placement, the tracking distances may need to be changed. It's basically just adding or subtracting from the tracking positions on the grid
            XCalculation = 2 * sin(deltaRadianHeading / 2.0) * ((deltaSIDE_WHEEL / deltaRadianHeading) + horizontalTrackingCenter);
            YCalculation = 2 * sin(deltaRadianHeading / 2.0) * ((deltaFRONT_WHEEL / deltaRadianHeading) + verticalTrackingCenter); 
        }

        deltaX = (YCalculation * sin(averageRadianHeading)) + (XCalculation * cos(averageRadianHeading));
        deltaY = (YCalculation * cos(averageRadianHeading)) - (XCalculation * sin(averageRadianHeading));
        //


        //Updates distance from original position
        X += deltaX;
        Y += deltaY;


        //Previous values
        prevX = X;
        prevY = Y;
        prevRadianHeading = radianHeading;
        prevFRONT_WHEEL = FRONT_WHEEL;
        prevSIDE_WHEEL = SIDE_WHEEL;

        std::cout << "X: " << X << "   Y: " << Y << std::endl;
        //wait (25, msec);
        task::sleep(10);
    }
    return 0;
}

//Function for calculating the distance from both axes. First two parameters are where it's at, second parameters are where it needs to be. Credit to Kassidy Mickelson

/*
Square the difference between the x values.
Square the difference between the y values.
Add the two squares.
Take the square root of the result.
*/

double getDistance(double x1, double y1, double x2, double y2) {
    double x_difference_squared = ((x2 - x1) * (x2 - x1));
    double y_difference_squared = ((y2 - y1) * (y2 - y1));
    return sqrt(x_difference_squared + y_difference_squared);
}

//Sets the starting orientation of the robot
void setDrivePosition(double x, double y, double startHeading) {
    X = x;
    Y = y;
    Inertial1.setHeading(startHeading, deg);
    radianHeading = startHeading * M_PI / 180;
}

//Function for determining the coordinates the robot points at
//Here is the atan math: https://www.vexforum.com/t/turn-to-point/104602/2
void turnToPosition(double x, double y, vex::directionType dir) {
    //Uses atan to create the value that will multiply by radians formula to convert the heading to pointing toward certain coordinates
    if (dir == fwd) {
        turnToHeading((atan2(x - X, y - Y)) * (180 / M_PI));
    } else if (dir == reverse) {
        //This adds 180 to the desired orientation so that it is 180 degrees around the coordinates it should be pointing at
        turnToHeading((atan2(x - X, y - Y)) * (180 / M_PI) + 180);
    }
}

//Function for travelling the distance it needs to travel to reach the coordinates, then uses the PID controller to drive that exact distance
void driveToPosition(double x, double y, vex::directionType dir) {
    turnToPosition(x, y, dir);
    if (dir == fwd) {
        driveInOdom(getDistance(X, Y, x, y));
    }
    if (dir == reverse) {
        driveInOdom(-getDistance(X, Y, x, y));
    }
}

void slowDriveToPosition(double x, double y, vex::directionType dir) {
    if (dir == fwd) {
        slowDriveOdom(getDistance(X, Y, x, y));
    }
    if (dir == reverse) {
        slowDriveOdom(-getDistance(X, Y, x, y));
    }
}