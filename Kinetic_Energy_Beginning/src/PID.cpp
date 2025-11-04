#include "vex.h"


/*
Kasens tuning tips (numerical order of tuning):

1. kP values = make it as high as possible without it becoming unstable. Tune it until it has oscillated or goes back and forth for two rounds.
3. kI values = make it as high as possible without it becoming unstable. If it messes up you have the wrong value. Thats the best advice I can give.
2. kD values = make it as low as possible without it becoming unstable. Have it ramp itself down and try to do it without the abrupt stops and without any hint of oscillation or going back and forth.
*/


double kP = 3.35;//3.35
double kI = 0.01;//0.01
double kD = 1.45;//1.45

double turnKP = 0.4;//0.4
double turnKI = 0.0005;//0.0005
double turnKD = 0.1;//0.1

double wheelRad = 1.0;//0.0

double turnTolerance = 0.5;//1.0
double driveTolerance = 0.1;//0.1

double driveIntegralLimit = 10.0;//20.0
double turnIntegralLimit = 30.0;//30.0

const double drivetrainWidth = 13.0;//↔
const double drivetrainLength = 13.5;//↕


//Function for determining the turn direction. Credit to Caleb Carlson for making this function easy to find (https://www.vexforum.com/t/turning-with-pid-how-to-find-the-shortest-turn/110258/6):
double constrainAngle(double x) {
    x = fmod(x + 180, 360);
    if (x < 0)
        x += 360;
    return x - 180;
}

//PID class initialization:
class PID {
    //Declaring all instances in the class. (eg. PID math variables):
    private:
        //Declaring multiplication constants:
        //Declaring sensor math variables:
        double desiredValue;
        double error;
        double integral;
        double derivative;
        double pwr;
        double prevError;
        double storedTrackingMeasurements;
        double storedHeading;
        double resetCurrentPosition;
        double turnDifference;
        double timing;
        //Declaring what instance of motor control it is:
        bool timerEnabled;
        bool isTurning;
        bool isDriving;
    //PID class parameter setup:
    public:
        PID(double DesiredValue, bool IsDriving, bool IsTurning, bool TimerEnabled, double Timing) {
            desiredValue = DesiredValue;
            error = DesiredValue;
            isTurning = IsTurning;
            isDriving = IsDriving;
            timerEnabled = TimerEnabled;
            timing = Timing;
        }

        void run() {
            integral = 0;
            error = 0;
            //This accounts for the tracking wheel measuremants in PID:
            storedTrackingMeasurements = frontTracking.position(turns);

            storedHeading = Inertial1.heading(deg);
            while (true) {
                //This simmulates drive PID starting at 0:
                resetCurrentPosition = frontTracking.position(turns) - storedTrackingMeasurements;

                //This is nescessarry for odometry to work so we don't have to reset the forward/sideways tracking position.
                //It instead starts where the tracking position is to 0 allowing it to use distance values instead of coordinate values.

                //PID math:
                integral += error;
                //

                //Stops using integral in the power once the condition is met:
                if (error <= turnTolerance && error >= turnTolerance  && isTurning) {
                    integral = 0;
                }
                if (std::abs(error) < turnIntegralLimit && isTurning) {
                    integral = 0;
                } else if (std::abs(error) < driveIntegralLimit && (isDriving)) {
                    integral = 0;
                }

                //More PID math:
                derivative = error - prevError;
                prevError = error;
                //

                //Turn difference calculations for determing the distance between the left and right sides of the drivetrain:
                turnDifference = 2 * ((drivetrainWidth / 2) * radianHeading) * (sin(radianHeading / 2));

                

                //Class initialization for turning:
                if (isTurning) {
                    error = constrainAngle(desiredValue - Inertial1.heading(deg));
                    pwr = error * turnKP + integral * turnKI + derivative * turnKD;
                    LeftDriveSmart.spin(fwd, pwr, pct);
                    RightDriveSmart.spin(reverse, pwr, pct);
                    if (error == 0) break;
                    if (error >= -turnTolerance && error <= turnTolerance) break;
                }

                //If it messes up the acceleration or measurement values use this:
                //LeftDriveSmart.spin(fwd, pwr, pct);
                //RightDriveSmart.spin(fwd, pwr, pct);

                //Class initialization for driving:
                else if (isDriving) {
                    //This section is just drive PID:
                    error = desiredValue - resetCurrentPosition * (wheelRad * 2) * M_PI;
                    pwr = error * kP + integral * kI + derivative * kD;
                    if (constrainAngle(storedHeading - Inertial1.heading(deg)) < 0) {
                        RightDriveSmart.spin(fwd, pwr--, pct);
                        LeftDriveSmart.spin(fwd, pwr++, pct);
                    }
                    else if (constrainAngle(storedHeading - Inertial1.heading(deg)) > 0) {
                        RightDriveSmart.spin(fwd, pwr++, pct);
                        LeftDriveSmart.spin(fwd, pwr--, pct);
                    }
                    if (error == 0) break;
                    if (error >= -driveTolerance && error <= driveTolerance) break;
                }


                //Class initialization for turning with timer:
                if (isTurning && timerEnabled) {
                    error = constrainAngle(desiredValue - Inertial1.heading(deg));
                    pwr = error * turnKP + integral * turnKI + derivative * turnKD;
                    LeftDriveSmart.spin(fwd, pwr, pct);
                    RightDriveSmart.spin(reverse, pwr, pct);
                    if (Brain.timer(sec) == timing) break;
                }


                //Class initialization for driving with timer:
                else if (isDriving && timerEnabled) {
                    //This section is just drive PID:
                    error = desiredValue - resetCurrentPosition * (wheelRad * 2) * M_PI;
                    pwr = error * kP + integral * kI + derivative * kD;
                    if (constrainAngle(storedHeading - Inertial1.heading(deg)) < 0) {
                        RightDriveSmart.spin(fwd, pwr--, pct);
                        LeftDriveSmart.spin(fwd, pwr++, pct);
                    }
                    else if (constrainAngle(storedHeading - Inertial1.heading(deg)) > 0) {
                        RightDriveSmart.spin(fwd, pwr++, pct);
                        LeftDriveSmart.spin(fwd, pwr--, pct);
                    }
                    if (Brain.timer(sec) == timing) break;
                }


                wait (15, msec);
            }
            LeftDriveSmart.stop(hold);
            RightDriveSmart.stop(hold);
        }
};

//Drive PID function:
void driveIn(double driveDist) {
    PID drivePID(driveDist, true, false, false, 0);
    drivePID.run();
}

//Turn PID function:
void turnToHeading(double turnHeading) {
    PID turnPID(turnHeading, false, true, false, 0);
    turnPID.run();
}

double startTimer;

//Drive PID with timer function:
void driveIn(double driveDist, double drivePeriod) {
    startTimer = Brain.timer(sec);
    Brain.resetTimer();
    PID drivePID(driveDist, true, false, true, drivePeriod);
    drivePID.run();
    Brain.setTimer(Brain.timer(sec) + startTimer, sec);
}

//Turn PID with timer function:
void turnToHeading(double turnHeading, double turnPeriod) {
    startTimer = Brain.timer(sec);
    Brain.resetTimer();
    PID turnPID(turnHeading, false, true, true, turnPeriod);
    turnPID.run();
    Brain.setTimer(Brain.timer(sec) + startTimer, sec);
}